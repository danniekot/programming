#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
using std::cout;
using std::cin;
using std::to_string;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using namespace httplib;
using json = nlohmann::json;

void findAndReplaceAll(string &data, string toSearch, string replaceStr) {
	size_t pos = data.find(toSearch);
	while (pos != string::npos) {
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

json get_time() {
	Client taim("http://worldtimeapi.org");
	auto res = taim.Get("/api/timezone/Europe/Simferopol");
	if (!res)
		return { "err", "Request to time server failed" };
	if (res->status < 200 || res->status >= 300)
		return { "err", "Code " + to_string(res->status) + "." };
	return json::parse(res->body);
}
json get_weather() {

	Client weather("http://api.openweathermap.org");
	auto res = weather.Get("/data/2.5/onecall?lat=44.952116&lon=34.102411&exclude=hourly&appid=a9c029b1f8f08c04c0f08350bd7b6f5e&units=metric&lang=russian");
	if (!res)
		return { "err", "Request to weather server failed" };
	if (res->status < 200 || res->status >= 300)
		return { "err", "Code " + to_string(res->status) + "." };
	return json::parse(res->body);
}

json get_forecast(const json &hourly) {
	json hour_forecast;

	int last = hourly.size() - 1;
	time_t cur;
	json taim = get_time();
	if (taim["err"].is_null())
		cur = taim["unixtime"];
	else
		cur = time(0);

	if (hourly[last]["dt"] < cur)
		return json::object();

	for (int i = 0; i <= last; ++i) {
		if (hourly[i]["dt"] >= cur) {
			hour_forecast = hourly[i];
			break;
		}
	}
	return hour_forecast;

}

json get_cache() {
	json cache;
	ifstream fin("cache.json");
	if (fin.is_open()) {
		string content;
		getline(fin, content, '\0');
		if (!content.empty())
			content = json::parse(fin);
		fin.close();
	}
	return cache;
}
bool cache_json(json cache) {
	ofstream fout("cache.json");
	if (fout.is_open()) {
		fout << cache;
		fout.close();
	}
	else return 0;
	return 1;
}

void gen_response(const Request& req, Response& res) {
	json body, hour_forecast;
	body = get_cache();
	if (body.empty()) {
		body = get_weather();
		if (!body["err"].is_null()) {
			res.set_content(body, "text/json;charset=utf-8");
			return;
		}
		cache_json(body);
	}
	else if (!body["err"].is_null())
		res.set_content(body, "text/json;charset=utf-8");
	hour_forecast = get_forecast(body["hourly"]);
	if (!hour_forecast["err"].is_null()) 
		res.set_content(hour_forecast["err"], "text/plain;charset=utf-8");
	ifstream file("template.html");
	string site;
	if (file.is_open()) {
		getline(file, site, '\0');
		file.close();
	}
	else {
		res.set_content("Cannot open `template.html` file.", "text/plain;charset=utf-8");
		return;
	}

	findAndReplaceAll(site, "{hourly[i].weather[0].description}",
		hour_forecast["weather"][0]["description"]);
	findAndReplaceAll(site, "{hourly[i].weather[0].icon}",
		hour_forecast["weather"][0]["icon"]);
	findAndReplaceAll(site, "{hourly[i].temp}",
		to_string(int(round(hour_forecast["temp"].get<double>()))));

	res.set_content(site, "text/html;charset=utf-8");
}

void gen_response_raw(const Request &req, Response &res) {
	json hour_forecast;
	json body;

	body = get_cache();
	if (body.empty()) {
		body = get_weather();
		if (!body["err"].is_null()) {
			res.set_content(body, "text/json;charset=utf-8");
			return;
		}
	}
	else if (!body["err"].is_null())
		res.set_content(body, "text/json;charset=utf-8");
	hour_forecast = get_forecast(body["hourly"]);
	if (!hour_forecast["err"].is_null())
		res.set_content(hour_forecast["err"], "text/plain;charset=utf-8");

	cache_json(body);

	string site;
	ifstream template_file("template.html");

	if (template_file.is_open()) {
		getline(template_file, site, '\0');
		template_file.close();
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
	svr.listen("localhost", 3000);
}