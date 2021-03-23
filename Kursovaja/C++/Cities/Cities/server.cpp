#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

string Letters = "�����Ũ�����������������������";
string letters = "�����������������������������";
string valid_values = letters + "��� -'";


bool Valid(string current_city) {
	for (int i = 0; i < current_city.length(); i++)
		if (!count(valid_values.begin(), valid_values.end(), current_city[i]))
			return 0;
	return 1;
}

string Register(string current_city) {
	for (int i = 0; i < current_city.length(); i++)
		for (int j = 0; j < Letters.length(); j++)
			if (current_city[i] == Letters[j])
				current_city[i] = letters[j];
	return current_city;
}

map<int, vector<string>> CityBase() {
	map<int, vector<string>> city_base;
	ifstream fin;
	fin.open("cities.txt");
	if (fin.is_open())
		while (!fin.eof()) {
			string city = "";
			getline(fin, city);
			for (int i = 0; i < Letters.length(); i++)
				if (city[0] == Letters[i]) // ���� ����� ������������� ��������, ���� ����� � � ������������ ��� �
					city_base[i].push_back(city);
		}

	fin.close();
	return city_base;
}
void Randomizer() {
	string current_city = "";
	map<int, vector<string>> city_base = CityBase();
	/*for (auto item : city_base) { // ����� �� ����� ������� �� ������ �����
		cout << Letters[item.first] << ":\n\n";
		for (int i = 0; i < item.second.size() - 1; ++i) cout << item.second[i] << ", ";
		cout << item.second[item.second.size() - 1] << ".\n\n"; }*/
	srand(time(0));
	cout << "��� ������������ ���-��� ��� ���� � ������.\n\n"
		<< "����������:\n\n"
		<< "�� ��������� ����� �����. ����� ��������� �������� �����,\n"
		<< "������ ������ �������� �������� ��������� ����� ������ ������.\n"
		<< "����� ������ ����, �������� ����� '����'\n"
		<< "�������? �������� ����� '����'\n"
		<< "������� ����� �����:\n";
	int score = 0;
	vector<string> stop_list{ "����!", "����.", "����" };
	vector<string> score_list{ "����!", "����.", "����", "����!", "����.", "����" };
	string bad_letters_list = "���";
	while (1) {
		getline(cin, current_city);
		current_city = Register(current_city);
		if (count(score_list.begin(), score_list.end(), current_city) > 0) {
			cout << "��� ����: " << score << ".\n";
			continue;
		}
		if (count(stop_list.begin(), stop_list.end(), current_city) > 0) {
			cout << "��� ����: " << score << ".\n";
			break;
		}
		if (Valid(current_city)) {
			int letter_index, first_letter_index;
			for (int i = 0; i < letters.length(); i++)
				if (current_city[0] == letters[i])
					first_letter_index = i;
			string last_letter = "";
			if (count(bad_letters_list.begin(), bad_letters_list.end(), current_city[current_city.length() - 1]) > 0)
				last_letter += current_city[current_city.length() - 2];
			else
				last_letter += current_city[current_city.length() - 1];
			string temp = last_letter;
			for (int i = 0; i < letters.length(); i++)
				if (temp[0] == letters[i] || temp[0] == Letters[i])
					letter_index = i;
			vector<string> used_city_list;
			vector<string> city_base_temp = city_base[first_letter_index];
			for (int i = 0; i < city_base_temp.size(); i++)
				city_base_temp[i] = Register(city_base_temp[i]);
			if (count(city_base_temp.begin(), city_base_temp.end(), current_city) == 0) {
				cout << "����� ������ ��� � ����.\n�� �������� �� �������� �������������.\n���������� ������.\n";
				continue;
			}
			else if (count(used_city_list.begin(), used_city_list.end(), current_city) > 0) {
				cout << "���� ����� ��� ��� :)\n���������� ������.\n";
				continue;
			}
			else {
				used_city_list.push_back(current_city); // ��������� � �������������� ������
				bool b = 0;
				int random_city_index;
				do {
					random_city_index = rand() % city_base[letter_index].size(); // ���������� ������ ���������� ������ �� ����
					current_city = city_base[letter_index][random_city_index];
					if (count(used_city_list.begin(), used_city_list.end(), current_city) > 0)
						b = 1;
					else
						break;
				} while (b == 0); // ���� ������ �� ������������ ����� ����������, ���� ����������! ���������!!!
				for (int i = 0; i < letters.length(); i++)
					if (current_city[0] == letters[i])
						current_city[0] = Letters[i];
				last_letter = "";
				if (count(bad_letters_list.begin(), bad_letters_list.end(), current_city[current_city.length() - 1]) > 0)
					last_letter += current_city[current_city.length() - 2];
				else
					last_letter += current_city[current_city.length() - 1];
				for (int i = 0; i < letters.length(); i++)
					if (count(last_letter.begin(), last_letter.end(), letters[i])) {
						last_letter = "";
						last_letter += Letters[i];
					}
				int radnom_answer = rand() % 3;
				if (radnom_answer == 0)
					cout << "����� " << current_city << ". ������ �������� ����� �� ����� " << last_letter << "\n\n";
				if (radnom_answer == 1)
					cout << "��� ���: " << current_city << ". ��� �� " << last_letter << "\n\n";
				if (radnom_answer == 2)
					cout << "����, � ������� ������ ����� " << current_city << ". �� ��� ������ ��������� ������� ����� �� ����� " << last_letter << "\n\n";
				score++;
				last_letter = "";
			}
		}
		else
			cout << "�� ������� �������� �����. �� ����������� ������ �������.\n\n";
	}
}
int main() {
	system("chcp 1251 > nul");
	Randomizer();
}