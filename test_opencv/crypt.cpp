
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
	{ '�', 1 },
	{ '�', 2 },
	{ '�', 3 },
	{ '�', 4 },
	{ '�', 5 },
	{ '�', 6 },
	{ '�', 7 },
	{ '�', 8 },
	{ '�', 9 },
	{ '�', 10 },
	{ '�', 11 },
	{ '�', 12 },
	{ '�', 13 },
	{ '�', 14 },
	{ '�', 15 },
	{ '�', 16 },
	{ '�', 17 },
	{ '�', 18 },
	{ '�', 19 },
	{ '�', 20 },
	{ '�', 21 },
	{ '�', 22 },
	{ '�', 23 },
	{ '�', 24 },
	{ '�', 25 },
	{ '�', 26 },
	{ '�', 27 },
	{ '�', 28 },
	{ '�', 29 },
	{ '�', 30 },
	{ '�', 31 },
	{ '�', 32 },
	{ '�', 33 },
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
	{ '�', 1 },
	{ '�', 2 },
	{ '�', 3 },
	{ '�', 4 },
	{ '�', 5 },
	{ '�', 6 },
	{ '�', 7 },
	{ '�', 8 },
	{ '�', 9 },
	{ '�', 10 },
	{ '�', 11 },
	{ '�', 12 },
	{ '�', 13 },
	{ '�', 14 },
	{ '�', 15 },
	{ '�', 16 },
	{ '�', 17 },
	{ '�', 18 },
	{ '�', 19 },
	{ '�', 20 },
	{ '�', 21 },
	{ '�', 22 },
	{ '�', 23 },
	{ '�', 24 },
	{ '�', 25 },
	{ '�', 26 },
	{ '�', 27 },
	{ '�', 28 },
	{ '�', 29 },
	{ '�', 30 },
	{ '�', 31 },
	{ '�', 32 },
	{ '�', 33 },
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
	float **ptrarray = new float*[2]; // ��� ������ � �������
	for (int count = 0; count < 2; count++)
		ptrarray[count] = new float[5]; // � ���� ��������

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

void second_laba_anyalphabet() {
	string T = "�����ʲ� 500 ��";
	string G = "������";
	for (int i = 0; i < T.size(); i++) {
		cout << (int)T[i] + 256 << " ";
	}
	cout << "!!!" << endl;
	for (int i = 0; i < G.size(); i++) {
		cout << (int)G[i] + 256 << " ";
	}
	cout << endl;
	int k = 0;
	for (int g = G.size(); g < T.size(); g++) {
		G += G[k];
		k++;
		if (k > G.size()) {
			k = 0;
		}
	}
	cout << endl << G << endl;
	cout << G.size() << T.size() << endl;
	string coded_T = T;
	/*string prova = "�";
	cout << (int)prova[0] << "=" << prova[0] << endl;
	prova[0] += (char)256;
	cout << (int)prova[0] << "=" << prova[0] << endl;*/
	for (int i = 0; i < G.size(); i++) {
		coded_T[i] = T[i] + G[i];

		cout << (int)coded_T[i] << "=" << coded_T[i] << endl;
	}
	cout << "coded= " << coded_T << endl;
	string Decoded_T = coded_T;
	for (int i = 0; i < G.size(); i++) {
		Decoded_T[i] = coded_T[i] - G[i];

		cout << (int)coded_T[i] << "=" << coded_T[i] << endl;
	}
	cout << "Decoded= " << Decoded_T << endl;

	/*for (int i = -64; i <=256; i++) {
		cout << i << " " << (char)i << endl;
	}
	if ((char)(-64) == (char)(192)) {
		cout << "true" << endl;
	}*/
}

string second_laba_code(string T, string G) {

	int k = 0;
	for (int g = G.size(); g < T.size(); g++) {
		G += G[k];
		k++;
		if (k > G.size()) {
			k = 0;
		}
	}
	std::cout << endl << G << endl;
	std::cout << G.size() << " " << T.size() << endl;
	string coded_T = T;

	for (int i = 0; i < G.size(); i++) {
		int T_plus_G = alphabet_2laba.find(T[i])->second + alphabet_2laba.find(G[i])->second;
		if (T_plus_G > alphabet_2laba.size()) {
			T_plus_G -= alphabet_2laba.size();
		}
		std::cout << alphabet_2laba.find(T[i])->second << "+" << alphabet_2laba.find(G[i])->second << "=" << T_plus_G << endl;
		coded_T[i] = findByValue(alphabet_2laba, T_plus_G);

	}

	return coded_T;
}


string second_laba_decode(string coded_T, string G) {
	int k = 0;
	for (int g = G.size(); g < coded_T.size(); g++) {
		G += G[k];
		k++;
		if (k > G.size()) {
			k = 0;
		}
	}
	std::cout << endl << G << endl;
	std::cout << G.size() << " " << coded_T.size() << endl;
	string Decoded_T = coded_T;
	for (int i = 0; i < G.size(); i++) {
		int T_minus_G = alphabet_2laba.find(coded_T[i])->second - alphabet_2laba.find(G[i])->second;
		if (T_minus_G <= 0) {
			T_minus_G += alphabet_2laba.size();
		}
		std::cout << alphabet_2laba.find(coded_T[i])->second << "-" << alphabet_2laba.find(G[i])->second << "=" << T_minus_G << endl;
		Decoded_T[i] = findByValue(alphabet_2laba, T_minus_G);
	}
	return Decoded_T;
}




void second_laba() {
	//string T = "�����ʲ� 500 ��";
	//string G = "������";
	string T = "��������� 20 ���";
	string G = "����²�";
	cout << T << endl << G << endl;
	cout << "Coded= " << second_laba_code(T, G) << endl;;

	string coded_T = "�Ԫ��������2ʯ��";
	string coded_G = "��������";
	cout << coded_T << endl << coded_G << endl;
	cout << "Decoded= " << second_laba_decode(coded_T, coded_G) << endl;;

}
int simple_num(int p) {

	for (int i = p - 1; i > 2; i--) {
		int count = 0;
		for (int j = 1; j <= i; j++) {
			if (i%j == 0) { count++; }
		}
		if (count == 2) {
			return i;
		}
	}

	return 2;
}


void first_laba() {
	string s;
	char temp;
	ifstream ifs("example.txt");
	ifs.unsetf(ios::skipws);
	while (ifs >> temp)
		s += temp;
	cout << s << endl;
	cout << "text size=" << s.size() << endl;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			s.erase(i, 1);
		}
	}
	cout << s << endl;
	cout << "text size=" << s.size() << endl;
	string key = "�������";

	permutationcode(s, key);
	std::cout << "Coded text:  " << s << std::endl << std::endl;
	std::cout << "Coded text 16x:  ";
	for (int i = 0; i < s.size(); i++) {
		cout << std::hex << (int)s[i];
	}
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;
	permutationdecode(s, key);
	std::cout << "Decoded text:  " << s << std::endl << std::endl;
	std::cout << "Decoded text 16x:  ";
	for (int i = 0; i < s.size(); i++) {
		cout << std::hex << (int)s[i];
	}
}