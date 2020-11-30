#pragma once
#include "nlohmann/json.hpp"
using json = nlohmann::json;
json get_json();
json get_cache();
bool cache_json(json j);
json get_time();
json get_hour_forecast(const json &hourly);
void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr);
void log_append_line(std::string line);
void log_overwrite_line(std::string line);