#pragma once

#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <map>  
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;


std::map<char, int> alphabet = {
	{ 'А', 1 },
	{ 'Б', 2 },
	{ 'В', 3 },
	{ 'Г', 4 },
	{ 'Д', 5 },
	{ 'Е', 6 },
	{ 'Ї', 7 },
	{ 'Ж', 8 },
	{ 'З', 9 },
	{ 'И', 10 },
	{ 'Й', 11 },
	{ 'К', 12 },
	{ 'Л', 13 },
	{ 'М', 14 },
	{ 'Н', 15 },
	{ 'О', 16 },
	{ 'П', 17 },
	{ 'Р', 18 },
	{ 'С', 19 },
	{ 'Т', 20 },
	{ 'У', 21 },
	{ 'Ф', 22 },
	{ 'Х', 23 },
	{ 'Ц', 24 },
	{ 'Ч', 25 },
	{ 'Ш', 26 },
	{ 'Щ', 27 },
	{ 'Є', 28 },
	{ 'Ґ', 29 },
	{ 'Ь', 30 },
	{ 'І', 31 },
	{ 'Ю', 32 },
	{ 'Я', 33 },
	{ ' ', 34 },
	{ '0', 35 },
	{ '1', 36 },
	{ '2', 37 },
	{ '3', 38 },
	{ '4', 39 },
	{ '5', 40 },
	{ '6', 41 },
	{ '7', 42 },
	{ '8', 43 },
	{ '9', 44 }
};


std::map<char, int> alphabet_2laba = {
	{ 'А', 1 },
	{ 'Б', 2 },
	{ 'В', 3 },
	{ 'Г', 4 },
	{ 'Ґ', 5 },
	{ 'Д', 6 },
	{ 'Е', 7 },
	{ 'Є', 8 },
	{ 'Ж', 9 },
	{ 'З', 10 },
	{ 'И', 11 },
	{ 'І', 12 },
	{ 'Ї', 13 },
	{ 'Й', 14 },
	{ 'К', 15 },
	{ 'Л', 16 },
	{ 'М', 17 },
	{ 'Н', 18 },
	{ 'О', 19 },
	{ 'П', 20 },
	{ 'Р', 21 },
	{ 'С', 22 },
	{ 'Т', 23 },
	{ 'У', 24 },
	{ 'Ф', 25 },
	{ 'Х', 26 },
	{ 'Ц', 27 },
	{ 'Ч', 28 },
	{ 'Ш', 29 },
	{ 'Щ', 30 },
	{ 'Ь', 31 },
	{ 'Ю', 32 },
	{ 'Я', 33 },
	{ ' ', 34 },
	{ '0', 35 },
	{ '1', 36 },
	{ '2', 37 },
	{ '3', 38 },
	{ '4', 39 },
	{ '5', 40 },
	{ '6', 41 },
	{ '7', 42 },
	{ '8', 43 },
	{ '9', 44 }
};
void Permutation_cipher(std::string file_data, std::string key) {//file data only symb
	string **Matrix;
	int rows = file_data.size() / key.size();
	float **ptrarray = new float*[2]; // две строки в массиве
	for (int count = 0; count < 2; count++)
		ptrarray[count] = new float[5]; // и пять столбцов

}


void permutationcode(std::string& text, std::string& const key)
{
	int col = key.size();
	int row;
	if (text.size() % col) {

		row = ((text.size() / col) + 1);
	}
	else {

		row = (text.size() / col);
	}
	int** arrtext = new int*[row];
	for (int i = 0; i < row; ++i)
		arrtext[i] = new int[col];

	//inizialization array {0}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			arrtext[i][j] = 0;

	//fill array {text[i]}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if ((i*col) + j <= text.size()) {
				arrtext[i][j] = (int)text[(i*col) + j];
			}
		}
	}


	int index = 0;

	//permutation
	string tezt_ret;
	for (int i = -64; i != 0; i++) {
		for (int j = 0; j < col; j++) {
			if ((int)key[j] == i) {
				for (int k = 0; k < row; ++k, ++index) {
					tezt_ret += (char)arrtext[k][j];
					//text[index] = arrtext[k][j];
				}

				//tezt_ret += " ";
			}
		}
	}
	cout << tezt_ret << endl;
	text = tezt_ret;
}
void permutationdecode(string &text, string& const key) {
	int col = key.size();
	int row;
	if (text.size() % col) {
		row = ((text.size() / col) + 1);
	}
	else {
		row = (text.size() / col);
	}
	int** arrtext = new int*[row];
	for (int i = 0; i < row; ++i)
		arrtext[i] = new int[col];

	//inizialization array {0}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			arrtext[i][j] = 0;

	//fill array {text[i]}
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			if ((i*col) + j <= text.size()) {
				arrtext[i][j] = (int)text[(j*row) + i];
			}
		}
	}

	//decode

	map<char, int> key_pos;

	int first = 1;
	for (int i = -64; i != 0; i++) {
		for (int j = 0; j < col; j++) {
			if ((int)key[j] == i) {
				key_pos.insert(pair<char, int>(key[j], first));
				first++;
			}
		}
	}


	int** arrtext_decode = new int*[row];
	for (int i = 0; i < row; ++i)
		arrtext_decode[i] = new int[col];

	//inizialization array {0}
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			arrtext_decode[i][j] = 0;

	for (int j = 0; j < col; j++) {
		auto itr = key_pos.find(key[j]);


		for (int i = 0; i < row; i++) {
			arrtext_decode[i][j] = (int)arrtext[i][itr->second - 1];
		}
	}
	string tezt_ret;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << (char)arrtext_decode[i][j] << " ";
			tezt_ret += (char)arrtext_decode[i][j];
		}
		cout << endl;
	}
	text = tezt_ret;

}

template<typename K, typename V>
K findByValue(std::map<K, V> mapOfElemen, V value)
{
	bool bResult = false;
	auto it = mapOfElemen.begin();
	while (it != mapOfElemen.end())
	{
		// Check if value of this entry matches with given value
		if (it->second == value)
		{
			// Yes found
			bResult = true;
			// Push the key in given map
			return(it->first);
		}
		// Go to next entry in map
		it++;
	}
	return bResult;
}
