#include<opencv2/opencv.hpp>
#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include "Header.h"
#include <bitset>
#include <string>
#include <climits>
using namespace std;
using namespace cv;

string message_into_code(string message) {
	//message into code
	// code into 01;
	// 01 into photo
	int *message_code = new int[message.size()];
	for (int i = 0; i < message.size(); i++) {
		message_code[i] = alphabet.find(message[i])->second;
	//	cout << message[i]<<"="<<message_code[i] << endl;
	}
	
	const int size_of_bitset = message.size() * 8;
	string bits_of_message;
	bits_of_message.reserve(size_of_bitset);
	for (int i = 0; i < message.size(); i++) {
		bitset<8> bit(message_code[i]);
		//cout << message_code[i] << "=" <<bit << endl;
		string bit_str = bit.to_string();
		//cout << bit_str << endl;
		bits_of_message += bit_str;
	}

	cout << bits_of_message <<"->size()="<< bits_of_message.size()<< endl;
	return bits_of_message;

}

int change_bit(int num, string bit_to_write) {
	bitset<8> bit_num(num);
	bitset<8> bit_string_to_write(bit_to_write);
	//cout << bit_num << "+" << bit_string_to_write << endl;
	bool bool_num;
	if (bit_string_to_write == '1') {
		bool_num = 1;
	}
	else {
		bool_num =0;
	}
	bit_num.set(0, bool_num);
	//cout << bit_num << "->" << bit_num.to_ulong() << endl;
	return bit_num.to_ulong();
}

int change_bit(int num, bool bit_to_write) {
	bitset<8> bit_num(num);	

	//cout <<num<<"->"<< bit_num << "+" << bit_to_write << endl;
	bit_num.set(0, bit_to_write);
	//cout << bit_num << "->" << bit_num.to_ulong() << endl;
	return bit_num.to_ulong();
}
bool change(bool bit,string _s) {
	if (_s == "0") {
		return bit = 0;
	}
	else {
		return bit = 1;
	}
}

string bitset_bit_to_string(bitset<8> num) {
	string bit;
	if (num[0] == 0) {
		bit = "0";
	}
	else if (num[0] == 1) {
		bit = "1";
	}
	else
		cout << "err" << endl;
	return bit;
}

template<typename K, typename V>
K findByValue_2(std::map<K, V> mapOfElemen, V value)
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
string decode_image(Mat image) {
	string text="";
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Point3_<uchar>* p2 = image.ptr<Point3_<uchar> >(i, j);
			//cout << "i=" << i << " j=" << j << " R=" << (int)p2->z << " G=" << (int)p2->y << " B=" << (int)p2->x << endl;
			bitset<8> color_R ((int)p2->z);
			string str_color_R = bitset_bit_to_string(color_R);
			text += str_color_R;
			bitset<8> color_G((int)p2->y);
			string str_color_G = bitset_bit_to_string(color_G);
			text += str_color_G;
			bitset<8> color_B((int)p2->x);
			string str_color_B = bitset_bit_to_string(color_B);
			text += str_color_B;
		}		
	}
	//cout << text << endl;
	int *code_txt = new int[text.size()];
	int begin_i = 0;
	string text_decoded="";
	for (int runing_i= 7; runing_i < text.size(); runing_i +=8) {
		bitset<8> bit_code(text.substr(begin_i+1, runing_i));
		
		int coded_int = bit_code.to_ulong();
		if (coded_int <= 0 || coded_int > 44) {
			continue;
		}
		char g=findByValue_2(alphabet,coded_int);
		//cout <<"beg:" <<begin_i<<"run:"<< runing_i<< bit_code<<"->int "<< coded_int<<" char->"<< g << endl;
		text_decoded += g;
		begin_i = runing_i;
	}
	cout << "!---!DECODED TEXT:" << text_decoded << endl;
	return text;
}
int main()
{

	setlocale(LC_ALL, "ukr");
	//string ptob = "00011111000011010000110100100001001000100001001000010101000001010001100100001010000011000010001000001111000000010000101100001100000100100";
	//string text_decoded = "";
	//int begin_i = 0;
	//for (int runing_i = 7; runing_i < ptob.size(); runing_i += 8) {
	//	bitset<8> bit_code(ptob.substr(begin_i+1, runing_i));

	//	int coded_int = bit_code.to_ulong();
	//	char g = findByValue_2(alphabet, coded_int);
	//	//cout << "beg:" << begin_i << "run:" << runing_i << bit_code << "->int " << coded_int << " char->" << g << endl;
	//	text_decoded += g;
	//	begin_i = runing_i;
	//}
	//cout << "!---!" << text_decoded << endl;



	//system("pause");
	setlocale(LC_ALL, "ukr");
	//string message = "²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ";
	//	string message = "ËÀÁÀ 3 ²ËËß ÐÓÄ×ÈÊ ÍÀÉÊÐÀÙÈÉ ÏÐÎÃÐÀÌ²ÑÒ ÑÒÎË²ÒÒß ² Â²Í ÏÐÎ ÖÅ ÇÍÀª ÒÎÌÓ ÙÎ Â²Í ÇÍÀª ÂÑÅ ² ÌÎÆÅ ÇÐÎÁÈÒÈ ÂÑÅ ÍÀÂ²ÒÜ ÍÅÌÎÆËÈÂÅ ÑÀÌÅ ÒÎÌÓ ²ËËß ÍÀÉÊÐÀÙÈÉ ÁÎ ÖÅ ²ËËß ²ËËß ²ËËËËËßßß ²ËËß ÐÓÄ×ÈÊ";
	string message = "ÑÒÅÍÎÃÐÀÔ²ß ÊÎÄÓÂÀÍÍß ÒÅÊÑÒÓ Â ÇÎÁÐÀÆÅÍÍß ÍÀ ÎÑÍÎÂ² ÀËÔÀÂ²ÒÓ ÓÊÐÀ¯ÍÑÜÊÎ¯ ÌÎÂÈ";
	cout << "Text to code:" << message << endl;
	string message_in_bits= message_into_code(message);
	system("pause");


	Mat image = imread("fox.png");
	imshow("image", image);
	//imshow("image", image);
	//	for (int r = 0; r < image.rows; r++) {
	//		// We obtain a pointer to the beginning of row r
	//		cv::Vec3b* ptr = image.ptr<cv::Vec3b>(r);
	//		for (int c = 0; c < image.cols; c++) {
	//			
	//			// We invert the blue and red values of the pixel
	//			ptr[c] = cv::Vec3b(ptr[c][2], ptr[c][1], ptr[c][0]);
	//			
	//		}
	//	}
	// ïîìåùàåì äàííûå â ìàòðèöó


	Point3_<uchar>* p = image.ptr<Point3_<uchar> >(0, 0);
	int k = message.size()*8;
	int _s = 0;
	bool continue_wrie=true;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Point3_<uchar>* p2 = image.ptr<Point3_<uchar> >(i, j);
			//cout << "!i=" << i << " j=" << j << " R=" << (int)p2->z << " G=" << (int)p2->y << " B="<< (int)p2->x << endl;
			//cout <<"bit from string:"<<_s<<" is:"<< message_in_bits[_s] << endl;
			//string s = message_in_bits[_s];
			if (_s == k) {
				continue_wrie = false;
				break;
			}
			bool bit = 0;
			if (message_in_bits[_s] == '0') {
				bit = 0;
			}
			else if (message_in_bits[_s] == '1') {
				bit = 1;
			}
			else {
				cout << "!!!eror" << endl;
			}
			//cout << "write:" << bit << endl;
			p2->z =change_bit(p2->z, bit) ;
			_s++;
			//cout << "bit from string:" << _s << " is:" << message_in_bits[_s] << endl;
			if (_s == k) {
				continue_wrie = false;
				break;
			}
			if (message_in_bits[_s] == '0') {
				bit = 0;
			}
			else if (message_in_bits[_s] == '1') {
				bit = 1;
			}
			else {
				cout << "!!!eror" << endl;
			}
		
			p2->y = change_bit(p2->y, bit);
			_s++;
			//cout << "bit from string:" << _s << " is:" << message_in_bits[_s] << endl;
			if (_s == k) {
				continue_wrie = false;
				break;
			}
			if (message_in_bits[_s] == '0') {
				bit = 0;
			}
			else if (message_in_bits[_s] == '1') {
				bit = 1;
			}
			else {
				cout << "!!!eror" << endl;
			}
			p2->x =  change_bit(p2->x,  bit );
			_s++;
			//cout << "~i=" << i << " j=" << j << " R=" << (int)p2->z << " G=" << (int)p2->y << " B=" << (int)p2->x << endl;
			//p2->y = 255;
			//p2->x = 43;
			//RGB(255, 255, 43)

		}
		if (continue_wrie == false) {

			break;
		}
	}
	//cout << "_s=" << _s << endl;
	//cout << (int)p->x << endl; //B
	//cout<<(int)p->y << endl;;//G
	//cout<<(int)p->z << endl;;//R
	//cout << blue << " " << green << " " << red << endl;
	imshow("image2", image);
	imwrite("name.png", image);

	decode_image(image);

	waitKey(0);
	system("pause");
	return 0;
}