#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <nlohmann/json.hpp>
#include <utils.hpp>
#include <cpp_httplib/httplib.h>
using json = nlohmann::json;
using namespace httplib;

Client owm("http://api.openweathermap.org");
std::string latitude = "44.952116", longitude = "34.102411", exclude = "hourly", lang = "ru", units = "metric", appid = "1ec9379707616eb1562b5c3ca4e273ef";

Client time_srv("http://worldtimeapi.org");

void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr) {
	size_t pos = data.find(toSearch);
	while (pos != std::string::npos) {
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

json get_json() {
	std::string request = "/data/2.5/onecall?lat=" + latitude + "&lon=" + longitude + "&exclude=" + exclude + "&appid=" + appid + "&units=" + units + "&lang=" + lang;

	auto result = owm.Get(request.c_str());

	if (!result) {
		return { "err", "Request to weather server wasn't successful" };
	}

	int status_code = result->status;

	if (status_code < 200 || status_code >= 300) {
		return { "err", "Got non-successful code " + std::to_string(status_code) + "." };
	}

	return json::parse(result->body);
}

json get_cache() {
	json cache;
	std::ifstream cache_file("cache.json");
	if (cache_file.is_open()) {
		std::string content;
		getline(cache_file, content, '\0');

		if (!content.empty()) {
			cache = json::parse(content);
		}
		cache_file.close();
	}
	else {
		return { "err", "Could not open `cache.json` to read cache." };
	}
	return cache;
}

bool cache_json(json j) {
	std::ofstream cache_file("cache.json");
	if (cache_file.is_open()) {
		cache_file << j;
		cache_file.close();
	}
	else {
		return false;
	}
	return true;
}

json get_time() {
	std::string request = "/api/timezone/Europe/Simferopol";

	auto result = time_srv.Get(request.c_str());

	if (!result) {
		return { "err", "Request to time server wasn't successful" };

		return json::object();
	}

	int status_code = result->status;

	if (status_code < 200 || status_code >= 300) {
		return { "err", "Got non-successful code " + std::to_string(status_code) + "." };
	}

	return json::parse(result->body);
}

json get_hour_forecast(const json &hourly) {
	json hour_forecast;

	int last = hourly.size() - 1;
	int current_time;
	json time_j = get_time();
	if (time_j["err"].is_null()) {
		current_time = time_j["unixtime"];
	}
	else {
		current_time = std::time(0);
	}

	if (hourly[last]["dt"] < current_time) {
		return json::object();
	}

	for (int i = 0; i <= last; ++i) {
		if (hourly[i]["dt"] >= current_time) {
			hour_forecast = hourly[i];
			break;
		}
	}
	return hour_forecast;
}

void gen_response_test(const Request &req, Response &res) {
	res.set_content("Test successful!", "text/plain;charset=utf-8");
}

void gen_response(const Request& req, Response& res) {
	json hour_forecast;
	json body;

	bool retry = false;
	do {
		body = get_cache();
		if (body.empty()) {
			body = get_json();
			if (!body["err"].is_null()) {
				res.set_content(body["err"], "text/plain;charset=utf-8");
				return;
			}
			cache_json(body);
		}
		else if (!body["err"].is_null()) {
			res.set_content(body, "text/json;charset=utf-8");
		}

		hour_forecast = get_hour_forecast(body["hourly"]);
		if (!hour_forecast["err"].is_null()) {
			if (retry) {
				res.set_content(hour_forecast["err"], "text/plain;charset=utf-8");
				return;
			}
		}
	} while (retry);


	std::string template_file_name = "template.html";
	std::ifstream template_file(template_file_name);
	std::string site;

	if (template_file.is_open()) {
		getline(template_file, site, '\0');
		template_file.close();
	}
	else {
		res.set_content("Error! Could not open `template.html` file.", "text/plain;charset=utf-8");
		return;
	}

	findAndReplaceAll(site, "{hourly[i].weather[0].description}",
		hour_forecast["weather"][0]["description"]);
	findAndReplaceAll(site, "{hourly[i].weather[0].icon}",
		hour_forecast["weather"][0]["icon"]);
	findAndReplaceAll(site, "{hourly[i].temp}",
		std::to_string(int(std::round(hour_forecast["temp"].get<double>()))));

	res.set_content(site, "text/html;charset=utf-8");
}

void gen_response_raw(const Request &req, Response &res) {
	json hour_forecast;
	json body;

	bool retry = false;
	do {
		body = get_cache();
		if (body.empty()) {
			body = get_json();
			if (!body["err"].is_null()) {
				res.set_content(body, "text/json;charset=utf-8");
				return;
			}
		}
		else if (!body["err"].is_null()) {
			res.set_content(body, "text/json;charset=utf-8");
		}

		hour_forecast = get_hour_forecast(body["hourly"]);
		if (!hour_forecast["err"].is_null()) {
			if (retry) {
				res.set_content(hour_forecast["err"], "text/plain;charset=utf-8");
				return;
			}
		}
	} while (retry);

	cache_json(body);

	std::string template_file_name = "template.html";
	std::ifstream template_file(template_file_name);
	std::string site;

	if (template_file.is_open()) {
		getline(template_file, site, '\0');
		template_file.close();
	}
	else {
		res.set_content("{\"err\":\"Could not open `template.html` file\"}", "text/json;charset=utf-8");
		return;
	}

	json out;
	out["temp"] = hour_forecast["temp"];
	out["description"] = hour_forecast["weather"][0]["description"];

	res.set_content(out.dump(), "text/json;charset=utf-8");
}

int main() {
	Server svr;
	svr.Get("/", gen_response);
	svr.Get("/raw", gen_response_raw);
	svr.Get("/test", gen_response_test);

	svr.listen("localhost", 3000);
}