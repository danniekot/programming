#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>

using namespace std;

string Letters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ";
string letters = "абвгдеёжзийклмнопрстуфхцчшщэюя";


/*

	map<int, vector<string>> city_base;
	ifstream fin;
	fin.open("cities.txt");
	if (fin.is_open())
		while (!fin.eof()) {
			string city = "";
			getline(fin, city);
			for (int i = 0; i < Letters.length(); i++)
				if (city[0] == Letters[i]) // Либо буква соответствует алфавиту, либо равна Ё и записывается как Е
					city_base[i].push_back(city);
		}
*/
bool Valid(string current_city) {
	if ()
	for (int i = 0; i < Letters.length(); i++)
		if (current_city[0] == letters[i] || current_city[0] == Letters[i]) {
			current_city[0] = Letters[i];
		}
		else return 0;
	for (int i = 1; i < current_city.length(); i++)
		for (int j = 0; j < letters.length(); j++)
			if (current_city[j] == letters[j] || current_city[i] == Letters[j]) {
				current_city[i] = letters[j];
			}
			else return 0;
	return 1;
}

string Register(string current_city) {
	for (int i = 0; i < current_city.length(); i++)
		for (int j = 0; j < Letters.length(); j++)
			if (current_city[i] == Letters[j])
				current_city[i] = letters[j];
	return current_city;
}

map<char, vector<string>> CityBase() {
	
	map<char, vector<string>> city_base;
	ifstream fin;
	fin.open("cities.txt");
	if (fin.is_open())
		while (!fin.eof()) {
			string city = "";
			getline(fin, city);
			city = Register(city);
			city_base[city[0]].push_back(city);
		}
	// Вывод на экран городов на каждую букву
	/*for (auto item : city_base) {
		cout << Letters[item.first] << ":\n\n";
		for (int i = 0; i < item.second.size() - 1; ++i)
			cout << item.second[i] << ", ";
		cout << item.second[item.second.size() - 1] << ".\n\n";
	}*/
	fin.close();
	return city_base;
}
vector<string> CityList() {
	vector<string> city_list;
	ifstream fin;
	fin.open("cities.txt");
	if (fin.is_open())
		while (!fin.eof()) {
			string city = "";
			getline(fin, city);
			city = Register(city);
			city_list.push_back(city);
		}
	fin.close();
	return city_list;
}
void Randomizer() {
	vector<string> city_list = CityList();
	/*for (auto item : city_list) {
		cout << item << ".\n\n";
	}*/
	string current_city = "";
	map<char, vector<string>> city_base = CityBase();
	srand(time(0));
	cout << "Вас приветствует чат-бот для игры в города.\n\n"
		 << "ИНСТРУКЦИЯ:\n\n"
		 << "Вы называете любой город. Затем компьютер называет город,\n"
		 << "первой буквой которого является последняя буква Вашего города.\n"
		 << "Надоело? Напишите слово 'Стоп'\n"
		 << "Введите любой город:\n";
	int score = 0;
	vector<string> stop_list{ "стоп!", "стоп.", "стоп" };
	while (1) {
		
		cin >> current_city;
		current_city = Register(current_city);
		if (count(stop_list.begin(), stop_list.end(), current_city)) {
			cout << "Ваш счёт: " << score << ".";
			break;
		}
		if (Valid(current_city)) {
			char letter_index;

			if (current_city[current_city.length() - 1] == 'ъ' || current_city[current_city.length() - 1] == 'ы' || current_city[current_city.length() - 1] == 'ь') // Qt ругается, а Vs не видит...
				current_city.pop_back();
			char temp = current_city.back();
			for (int i = 0; i < letters.length(); i++)
				if (temp == letters[i] || temp == Letters[i])
					letter_index = Letters[i];

			vector<string> used_city_list;

			if (city_list.size() > 0 && count(city_list.begin(), city_list.end(), current_city) == 0) {
				cout << "Этого города нет в базе.\nОн добавлен на проверку администрации.\nПопробуйте другой.\n";
				continue;
			}
			else if (used_city_list.size() > 0 && count(used_city_list.begin(), used_city_list.end(), current_city) > 0) {
				cout << "Этот город уже был :)\nПопробуйте другой.\n";
				continue;
			}
			else {
				used_city_list.push_back(current_city); // Добавляем в использованные города
				bool b = 0;
				int random_city_index;
				do {
					random_city_index = rand() % city_base[letter_index].size(); // Генерируем индекс случайного города из базы
					current_city = city_base[letter_index][random_city_index];
					if (used_city_list.size() > 0 && count(used_city_list.begin(), used_city_list.end(), current_city) > 0)
						b = 1;
				} while (b == 0);
				for (int i = 0; i < letters.length(); i++)
					if (current_city[0] == letters[i])
						current_city[0] = Letters[i];
				int radnom_answer = rand() % 3;
				if (radnom_answer == 0)
					cout << "Город " << current_city << ". Теперь назовите город на букву " << Letters[letter_index];
				if (radnom_answer == 1)
					cout << "Мой ход: " << current_city << ". Вам на " << Letters[letter_index];
				if (radnom_answer == 2)
					cout << "Итак, я пожалуй назову город " << current_city << ". А Вы назовите город на букву " << Letters[letter_index];
				score++;
			}
		}
	}
}
int main() {
	system("chcp 1251 > nul");
	Randomizer();
}