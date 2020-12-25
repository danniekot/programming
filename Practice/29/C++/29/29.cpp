#include <iostream>
#include <map>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdlib>
#include "bozosort.hpp"
using namespace std;
struct Student {
	map<string, int> m_exams;
	string m_name;
	int m_group;

	Student(string name, int group, int math, int phys, int hist, int prog) {
		if (group < 1 or group > 9)
			throw invalid_argument("Invalid group. Got " + to_string(group));
		if (math < 0 or math > 9 or phys < 0 or phys > 9 or hist < 0 or hist > 9
			or prog < 0 or prog > 9)
			throw invalid_argument("Invalid notes. Got " +
				to_string(math) + ", " + to_string(phys) + ", " + to_string(hist)
				+ ", " + to_string(prog));

		m_exams = { {"math", math}, {"phys", phys}, {"hist", hist}, {"prog", prog} };
		m_name = name;
		m_group = group;
	}

	friend
		ostream& operator << (ostream& out, const Student& student)
	{
		auto name_len = int(student.m_name.length() > 4 ? student.m_name.length() : 4);
		auto name_delim = string(name_len, '-');
		out << "+-" << name_delim << "-+-------+------+------+------+------+\n"
			<< "| Name " << string(name_len - 4, ' ')
			<< "| Group | Math | Phys | Hist | Prog |\n"
			<< "+-" << name_delim << "-+-------+------+------+------+------+\n"
			<< "| " << student.m_name << " | " << student.m_group
			<< "     | " << student.m_exams.at("math")
			<< "    | " << student.m_exams.at("phys")
			<< "    | " << student.m_exams.at("hist")
			<< "    | " << student.m_exams.at("prog")
			<< "    |\n"
			<< "+-" << name_delim << "-+-------+------+------+------+------+\n";
		return out;
	}

	bool operator < (const Student& other) const {
		return m_name < other.m_name;
	}
	bool operator > (const Student& other) const {
		return m_name > other.m_name;
	}
};

ostream& operator << (ostream& out, const vector<Student>& student_vec) {
	auto name_len = student_vec.at(0).m_name.length();
	for (auto itr = student_vec.begin() + 1; itr != student_vec.end(); ++itr)
		if (itr->m_name.length() > name_len)
			name_len = itr->m_name.length();
	auto name_delim = string(name_len, '-');
	out << "+-" << name_delim << "-+-------+------+------+------+------+\n"
		<< "| Name " << string(name_len - 4, ' ')
		<< "| Group | Math | Phys | Hist | Prog |\n"
		<< "+-" << name_delim << "-+-------+------+------+------+------+\n";

	for (auto& student : student_vec)
		out << "| " << student.m_name
		<< string(name_len - student.m_name.length(), ' ')
		<< " | " << student.m_group
		<< "     | " << student.m_exams.at("math")
		<< "    | " << student.m_exams.at("phys")
		<< "    | " << student.m_exams.at("hist")
		<< "    | " << student.m_exams.at("prog")
		<< "    |\n"
		<< "+-" << name_delim << "-+-------+------+------+------+------+\n";
	return out;
};

int main() {
	srand(time(0));
	vector<Student> students = {
		Student("Maria",        4, 3, 3, 2, 5),
		Student("Oleg",    4, 3, 3, 3, 5),
		Student("Olesia",      4, 3, 5, 2, 5),
		Student("Mitya",   4, 3, 3, 4, 5),
		Student("Veronika",     4, 3, 2, 3, 5),
		Student("Maxim",     2, 4, 3, 4, 5),
		Student("Oxana",         3, 4, 5, 3, 5),
		Student("Dmitry",       2, 2, 5, 3, 5),
		Student("Alexey",     2, 3, 3, 4, 5),
		Student("Janna",        2, 3, 3, 4, 5),
	};

	auto has_failed = [](Student& student) -> bool {
		for (auto& pair : student.m_exams)
			if (pair.second == 2)
				return true;
		return false;
	};

	vector<Student> failed;
	for (auto& student : students)
		if (has_failed(student))
			failed.push_back(student);
	if (failed.size() > 0) {
		cout << failed << endl;

		cout << "\nExplusion\n"
			<< failed.at(rand() % failed.size()) << endl;
	}
	else
		cout << "Not found" << endl;
}
