#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;
void log_append_line(string line) {
	ofstream log("server.log", ofstream::app);
	log << line << endl;
	log.close();
}

void log_overwrite_line(string line) {
	ofstream log("server.log");
	log << line << endl;
	log.close();
}