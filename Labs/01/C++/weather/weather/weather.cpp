#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
using namespace std;
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
	return json::parse(res->body);
}

json get_weather() {
	Client weather("http://api.openweathermap.org");
	auto res = weather.Get("/data/2.5/onecall?lat=44.952116&lon=34.102411&appid=a9c029b1f8f08c04c0f08350bd7b6f5e&units=metric&lang=ru");
	return json::parse(res->body);
}

json get_forecast(const json &hourly) {
	json hour_forecast, taim = get_time();;
	int last = hourly.size() - 1;
	if (hourly[last]["dt"] < taim["unixtime"])
		return json::object();
	for (int i = 0; i <= last; ++i) {
		if (hourly[i]["dt"] >= taim["unixtime"]) {
			hour_forecast = hourly[i];
			break;
		}
	}
	return hour_forecast;
}

json get_cache() {
	json cache;
	ifstream file("cache.json");
	if (file.is_open()) {
		string content;
		getline(file, content, '\0');
		if (!content.empty())
			cache = json::parse(content);
		file.close();
	}
	return cache;
}

bool cache_json(json cache) {
	ofstream file("cache.json");
	if (file.is_open()) {
		file << cache;
		file.close();
	}
	else return 0;
	return 1;
}

void gen_response(const Request& req, Response& res) {
	json body, hour_forecast;
	body = get_cache();
	if (body.empty()) {
		body = get_weather();
		cache_json(body);
	}
	hour_forecast = get_forecast(body["hourly"]);
	ifstream file("template.html");
	string site;
	if (file.is_open()) {
		getline(file, site, '\0');
		file.close();
	}
	else {
		res.set_content("Cannot open template file.", "text/plain;charset=utf-8");
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
	json hour_forecast, body, out;
	string site;
	ifstream file("template.html");
	body = get_cache();
	if (body.empty())
		body = get_weather();
	hour_forecast = get_forecast(body["hourly"]);
	cache_json(body);
	if (file.is_open()) {
		getline(file, site, '\0');
		file.close();
	}
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