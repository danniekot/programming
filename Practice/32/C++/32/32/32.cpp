#include <sstream>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
using namespace std;
string ReplaceAll(string str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

struct Passenger {
	string name, cabin, ticket;
	float fare;
	int	id;
	bool survival;
	uint8_t age, pclass, sex, sibsp, parch, embarked;
};

struct Passenger_str {
	string name, cabin, ticket, fare, id, survival, pclass, sex, age, sibsp, parch, embarked;
};

vector<vector<string>> parse_cvs( istream& out,	char end_ch = '\r', char quote_ch = '"', char sep_ch = ',') {
	string line;
	string buffer;

	vector<string> seperated_string;
	vector<vector<string>> result;

	char quote_depth = 0;
	char pos = 0;

	while (getline(out, line, end_ch)) {
		pos = 0;
		quote_depth = 0;

		for (char ch : line) {
			if (ch == sep_ch) {
				switch (quote_depth) {
				case 0:
					seperated_string.push_back(buffer);
					buffer.clear();
					++pos;
					continue;
				case 2:
					seperated_string.push_back(buffer);
					buffer.clear();
					quote_depth = 0;
					++pos;
					continue;
				}
			}
			if (ch == quote_ch) {
				switch (quote_depth) {
				case 0:
					quote_depth = 1;
					continue;
				case 1:
					quote_depth = 2;
					continue;
				case 2:
					buffer.push_back(quote_ch);
					quote_depth = 1;
					continue;
				}
			}
			buffer.push_back(ch);
		}
		seperated_string.push_back(buffer);
		buffer.clear();

		result.push_back(seperated_string);
		seperated_string.clear();
	}
	return result;
}
istream& operator>> (istream& stream, vector<Passenger>& vec) {
	auto matrix = parse_cvs(stream);
	matrix.erase(matrix.begin());

	for (auto row : matrix) {
		Passenger p;

		p.id = stoi(row[0]);
		p.survival = stoi(row[1]);
		p.pclass = stoi(row[2]);
		p.name = row[3];
		p.sex = row[4] == "male" ? 'm' : 'f';
		p.age = row[5] == "" ? 0 : stof(row[5]);
		p.sibsp = stoi(row[6]);
		p.parch = stoi(row[7]);
		p.ticket = row[8];
		p.fare = stof(row[9]);
		p.cabin = row[10];
		p.embarked = row[11][0];

		vec.push_back(p);
	}

	return stream;
}
ostream& operator<< (ostream& stream, vector<Passenger>& vec) {
	char sep = ',';
	char end = '\r';
	for (auto& pass : vec) {
		string name = pass.name;
		name = ReplaceAll(name, "\"", "\"\"");

		stream << pass.id << sep
			<< pass.survival << sep
			<< int(pass.pclass) << sep
			<< '"' << name << '"' << sep
			<< ((pass.sex == 'm') ? "male" : "female") << sep
			<< int(pass.age) << sep
			<< int(pass.sibsp) << sep
			<< int(pass.parch) << sep
			<< pass.ticket << sep
			<< pass.fare << sep
			<< pass.cabin << sep
			<< pass.embarked
			<< end << flush;
	}
	return stream;
}
void sort(vector<Passenger*>& vec) {
	sort(vec.begin(), vec.end(), [](const Passenger* a, const Passenger* b) { return a->age < b->age; });
}

int main() {
	ifstream file("train.csv");
	ofstream outfile("out.csv");
	vector<Passenger> passengers;

	file >> passengers;
	vector<Passenger*> passengers_ptr;

	for (auto& elem : passengers) passengers_ptr.push_back(&elem);

	sort(passengers_ptr);

	vector<Passenger> newvec;
	for (auto elem : passengers_ptr) newvec.push_back(*elem);

	outfile << newvec;
}