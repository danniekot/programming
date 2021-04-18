#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

string Letters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ";
string letters = "абвгдеёжзийклмнопрстуфхцчшщэюя";
string valid_values = letters + "ъыь -'";


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
	ifstream fin("cities.txt");
	if (fin.is_open())
		while (!fin.eof()) {
			string city = "";
			getline(fin, city);
			for (int i = 0; i < Letters.length(); i++)
				if (city[0] == Letters[i]) // Либо буква соответствует алфавиту, либо равна Ё и записывается как Е
					city_base[i].push_back(city);
		}

	fin.close();
	return city_base;
}

string CmdRead() {
	string current_city = "";
	ifstream fin("D:/универ/Программирование/Kursovaja/console_user.txt");
	if (fin.is_open())
		getline(fin, current_city);
	fin.close();
	return current_city;
}

void CmdWrite(string current_city) {
	ofstream fout("D:/универ/Программирование/Kursovaja/console_bot.txt");
	if (fout.is_open())
		fout << current_city;
	fout.close();
}
void Randomizer() {
	string current_city = "", previous_city = "";
	map<int, vector<string>> city_base = CityBase();
	/*for (auto item : city_base) { // Вывод на экран городов на каждую букву
		cout << Letters[item.first] << ":\n\n";
		for (int i = 0; i < item.second.size() - 1; ++i) cout << item.second[i] << ", ";
		cout << item.second[item.second.size() - 1] << ".\n\n"; }*/
	srand(time(0));
	int score = 0;
	/*vector<string> stop_list{ "стоп!", "стоп.", "стоп" }; // объявление векторов будет в .py файле
	vector<string> score_list{ "счёт!", "счёт.", "счёт", "счет!", "счет.", "счет" };*/
	vector<string> used_city_list;
	string bad_letters_list = "ъыь";
	while (1) {
		if (CmdRead() != previous_city && CmdRead() != "") {
			current_city = CmdRead();
			current_city = Register(current_city);
			/*if (count(score_list.begin(), score_list.end(), current_city) > 0) { // этот код будет в .py файле
				cout << "Ваш счёт: " << score << ".\n";
				continue;
			}
			if (count(stop_list.begin(), stop_list.end(), current_city) > 0) { // этот код будет в .py файле
				cout << "Ваш счёт: " << score << ".\n";
				break;
			}*/
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
				vector<string> city_base_temp = city_base[first_letter_index];
				for (int i = 0; i < city_base_temp.size(); i++)
					city_base_temp[i] = Register(city_base_temp[i]);
				if (count(city_base_temp.begin(), city_base_temp.end(), current_city) == 0) {
					CmdWrite("Этого города нет в базе. Он добавлен на проверку администрации. Попробуйте другой.");
					continue;
				}
				else if (count(used_city_list.begin(), used_city_list.end(), current_city) > 0) {
					CmdWrite("Этот город уже был :). Попробуйте другой.");
					continue;
				}
				used_city_list.push_back(current_city); // Добавляем в использованные города
				// for (int i = 0; i < used_city_list.size(); i++) cout << used_city_list[i] << " "; cout << endl;
				bool b = 0;
				int random_city_index;
				do {
					random_city_index = rand() % city_base[letter_index].size(); // Генерируем индекс случайного города из базы
					current_city = city_base[letter_index][random_city_index];
					if (count(used_city_list.begin(), used_city_list.end(), current_city) > 0)
						b = 1;
					else
						break;
				} while (b == 0); // Если города на определенную букву закончатся, цикл зациклится! ИСПРАВИТЬ!!!
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
				CmdWrite(current_city);
				previous_city = current_city;
				current_city = Register(current_city);
				used_city_list.push_back(current_city);
				score++;
				last_letter = "";
			}
			else
				CmdWrite("Вы указали неверный город. Не используйте лишние символы.");
		}
	}
}
int main() {
	system("chcp 1251 > nul");
	Randomizer();
}