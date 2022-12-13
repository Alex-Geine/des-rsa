#pragma once
#include<iostream>
#include<string>
#include<time.h>
#include <cstdlib>

using namespace std;

//класс хранящий в себе данные сообщений
class Message {
public:
	string
		plain,
		closed;

	Message::Message() {

	} //конструктор по умолчанию 

	//метод получения закрытого текста
	string GetClosed() {
		return closed;
	}
	//метод получения открытого текста
	string GetPlain() {
		return plain;
	}
	//получает закрытый текст
	void SetClosed(string str) {
		closed = str;
	}
	//получает открытый текст
	void SetPlain(string str) {
		plain = str;
	}

};

//класс для алгоритма дес
class Des :public Message {
private:
	bool 
		bit_key[64],
		r_keys[16][48];
		string Key;
protected:
	//циклический сдвиг вправо
	void Shift(bool* in, int n = 56) {
		bool buf[56];

		for (int i = 0; i < 56; i++)
			buf[i] = in[i];
		in[0] = buf[55];

		for (int i = 1; i < n; i++)
			in[i] = buf[i - 1];
	}

	//получение бита с позиции
	bool get_bit(char ch, int pos) {
		return ch & (1 << pos);
	}

	bool get_bit(int in, int pos) {
		return in & (1 << pos);
	}
	//Функция получения раундовых ключей
	void Get_RKeys() {
		//Tables
		const int PC_1[56] =
		{ 57,49,41,33,25,17,9,
	   1,58,50,42,34,26,18,
	   10,2,59,51,43,35,27,
	   19,11,3,60,52,44,36,
	   63,55,47,39,31,23,15,
	   7,62,54,46,38,30,22,
	   14,6,61,53,45,37,29,
	   21,13,5,28,20,12,4 };	//таблица перестановок для C0 & D0

		const int PC_2[48] = { 14,17,11,24,1,5,
						   3,28,15,6,21,10,
						   23,19,12,4,26,8,
						   16,7,27,20,13,2,
						   41,52,31,37,47,55,
						   30,40,51,45,33,48,
						   44,49,39,56,34,53,
						   46,42,50,36,29,32 };  //таблица для раундовых ключей

		const int PC_3[16] = { 1,1,2,2,
								2,2,2,2,
								1,2,2,2,
								2,2,2,1

		}; //таблица сдвигов

		//генерация раундовых ключей(r_keys) //перенеси в отдельную функцию

		//определение C0 & D0
		bool CD[56]; //блоки СД

		for (int i = 0; i < 56; i++)
			CD[i] = bit_key[PC_1[i] - 1];

		//генерация раундовых ключей
		for (int i = 0; i < 16; i++) {
			//циклический сдвиг вправо
			for (int j = 0; j < PC_3[i]; j++)
				Shift(CD);
			//выбор раундового ключа
			for (int j = 0; j < 48; j++)
				r_keys[i][j] = CD[PC_2[j] - 1];
		}
	}

	//перевод из битового предствавления в символьное
	string Convert_simb(bool* in) {
		string res;

		for (int i = 0; i < 8; i++) {
			unsigned char a = 0;
			int init = 0;
			for (int j = 7; j >= 0; j--) {
				if (in[8 * i + j])
				{
					a = a | (1 << init);
					
				}
				
				init++;
			}

			res.push_back(a);
		}

		return res;
	}

	//перевод из битового предствавления в числовое
	int Convert_int(bool* in, int n) {
		int res = 0;

		int init = 0;
		for (int j = n - 1; j >= 0; j--) {
			if (in[j])
			{
				res = res | (1 << init);
				
			}

			init++;
		}

		return res;
	}

	//перевод из символьного в битовое
	void Convert_bit(string in, bool* res) {
		int f;

		for (int j = 0; j < 8; j++) {
			f = (j + 1) * 8 - 1; // 7 15 23 ...
			for (int i = 0; i < 8; i++) {
				res[f] = get_bit(in[j], i); //get_bit получает биты справа налево
				f--;
			}

		}

	}
	
	//функция f шифрации
	void funk(bool *in, bool* out, int I) {
		//Tables
		const int E_exp[48] = { 32,1,2,3,4,5,
							4,5,6,7,8,9,
							8,9,10,11,12,13,
							12,13,14,15,16,17,
							16,17,18,19,20,21,
							20,21,22,23,24,25,
							24,25,26,27,28,29,
							28,29,30,31,32,1 };//расширение

		const int P_transform[32] = { 16,7,20,21,
								  29,12,28,17,
								  1,15,23,26,
								  5,18,31,10,
								  2,8,24,14,
								  32,27,3,9,
								  19,13,30,6,
								  22,11,4,25 }; //перестановка P
		const int SBOX_1[4][16] = { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
							   {0,15,7,4,15,2,13,1,10,6,12,11,9,5,3,8},
							   {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
							   {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} };

		const int SBOX_2[4][16] = { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
								   {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
								   {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
								   {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} };

		const int SBOX_3[4][16] = { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
								   {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
								   {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
								   {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} };

		const int SBOX_4[4][16] = { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
								   {12,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
								   {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
								   {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} };

		const int SBOX_5[4][16] = { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
								   {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
								   {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
								   {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} };

		const int SBOX_6[4][16] = { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
								   {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
								   {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
								   {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} };

		const int SBOX_7[4][16] = { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
								   {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
								   {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
								   {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} };

		const int SBOX_8[4][16] = { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
								   {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
								   {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
								   {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} };

		typedef const int(*SBOX)[16];
		SBOX SBox[8] = { SBOX_1, SBOX_2, SBOX_3, SBOX_4, SBOX_5, SBOX_6, SBOX_7, SBOX_8 }; //C блоки

		// функция расширения & XOR with key
		bool buf[48];
		for (int i = 0; i < 48; i++) {
			buf[i] = in[E_exp[i] - 1];
			buf[i] = buf[i] ^ r_keys[I][i];
		}

		//приемение С блоков
		int mas[8]; // массив с выходами С блока потом переводим в биты
		for (int i = 0; i < 8; i++) {
			int a, //столбец
				b; //cтрока
			bool
				a_mas[4],
				b_mas[2];
			for (int j = 0; j < 6; j++) {
				if (j == 0)
					b_mas[0] = buf[6 * i + j];
				else if (j == 5)
					b_mas[1] = buf[6 * i + j];
				else
					a_mas[j - 1] = buf[6 * i + j];
			}
			a = Convert_int(a_mas, 4);
			b = Convert_int(b_mas, 2);

			mas[i] = SBox[i][b][a]; // получили число из таблицы S

		}
		bool buf2[32];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++)
				buf2[i * 4 + j] = get_bit(mas[i], j);
		}

		//конечная перестановка
		for (int i = 0; i < 32; i++)
			out[i] = buf2[P_transform[i] - 1];
	}


public:
	Des::Des() {
		Message();
	}

	//получение ключа
	void SetKey(string Key) {
		this->Key = Key;
		Convert_bit(Key, bit_key);
		
	}

	//функция шифрации
	string Code() {
		string in = plain;
		//получение раундовых ключей
		Get_RKeys();

		//начальные перестановки битов (mod 64 - val)
		static const size_t IP[64] =
		{
						58,50,42,34,26,18,10,2,
						 60,52,44,36,28,20,12,4,
						 62,54,46,38,30,22,14,6,
						 64,56,48,40,32,24,16,8,
						 57,49,41,33,25,17, 9,1,
						 59,51,43,35,27,19,11,3,
						 61,53,45,37,29,21,13,5,
						 63,55,47,39,31,23,15,7 };

		//конечная перестановка
		static const size_t IP_1[64] = {
							40,8,48,16,56,24,64,32,
						   39,7,47,15,55,23,63,31,
						   38,6,46,14,54,22,62,30,
						   37,5,45,13,53,21,61,29,
						   36,4,44,12,52,20,60,28,
						   35,3,43,11,51,19,59,27,
						   34,2,42,10,50,18,58,26,
						   33,1,41,9,49,17,57,25 };

		string res; //строка с результатом

		bool
			M[64], //представление 8 символов в битах
			L1[32], //левый блок в преобразовании Фейстеля
			L2[32]; //правый

		int f, // индекс бита в массиве M
		g = 0;

		//представление символов в битах      (!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ВАЖНО!!!!!!!!!!!!!!!!!!!!!!!!) зачем тут f &&&
		for (int j = 0; j < 8; j++) {
			f = (j + 1) * 7 + g; // 7 15 23 ...
			for (int i = 0; i < 8; i++) {
				M[f] = get_bit(in[j], i); //get_bit получает биты справа налево
				f--;
			}
			g++;

		}

		//начальная перестановка
		for (int i = 0; i < 64; i++) {
			if (i < 32)
				L1[i] = M[IP[i] - 1];//L1[i] = M[i];//L1[i] = M[IP[i] - 1];
			else
				L2[i - 32] = M[IP[i] - 1];//L2[i - 32] = M[i]; //L2[i - 32] = M[IP[i] - 1];
		}

		//преобразование Фейстеля
		for (int i = 0; i < 2; i++) {
			bool
				RNew[32],//результат XOR
				mas[32]; // результат f()

			//функция f
			funk(L2, mas, i);

			//xor L1 & f(L2, ki)
			for (int j = 0; j < 32; j++) {
				RNew[j] = L1[j] ^ mas[j];//r_keys[0][j]; //mas[j];
				//RNew[j] ^= mas[j];//r_keys[0][j]; //mas[j];

			}

			//перестановка блоков
			for (int j = 0; j < 32; j++)
				L1[j] = L2[j];

			for (int j = 0; j < 32; j++)
				L2[j] = RNew[j];
		}

		//Обьединение блоков
		for (int i = 0; i < 64; i++) {
			if (i < 32)
				M[i] = L1[i];
			else
				M[i] = L2[i - 32];
		}

		//обратная подстановка
		bool M_1[64];
		for (int i = 0; i < 64; i++) {
			M_1[i] = M[IP_1[i] - 1]; //M_1[i] = M[i]; //M_1[i] = M[IP_1[i] - 1];
		}

		//перевод из битоВОго представления в символьное
		res = Convert_simb(M_1);

		return res;
	}

	//Функция декодирования
	string DeCode() {
		string in = closed;
		//получение раундовых ключей
		Get_RKeys();

		//начальные перестановки битов (mod 64 - val)
		static const size_t IP[64] =
		{
						58,50,42,34,26,18,10,2,
						 60,52,44,36,28,20,12,4,
						 62,54,46,38,30,22,14,6,
						 64,56,48,40,32,24,16,8,
						 57,49,41,33,25,17, 9,1,
						 59,51,43,35,27,19,11,3,
						 61,53,45,37,29,21,13,5,
						 63,55,47,39,31,23,15,7 };

		//конечная перестановка
		static const size_t IP_1[64] = {
							40,8,48,16,56,24,64,32,
						   39,7,47,15,55,23,63,31,
						   38,6,46,14,54,22,62,30,
						   37,5,45,13,53,21,61,29,
						   36,4,44,12,52,20,60,28,
						   35,3,43,11,51,19,59,27,
						   34,2,42,10,50,18,58,26,
						   33,1,41,9,49,17,57,25 };

		string res;
		bool
			M[64], //представление 8 символов в битах
			L1[32], //левый блок в преобразовании Фейстеля
			L2[32]; //правый

		int f, g = 0; // индекс бита в массиве M
		int Byte = 8;

		//представление символов в битах      (!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ВАЖНО!!!!!!!!!!!!!!!!!!!!!!!!) зачем тут f &&&
		for (int j = 0; j < 8; j++) {
			f = (j + 1) * 7 + g; // 7 15 23 ...
			for (int i = 0; i < 8; i++) {
				M[f] = get_bit(in[j], i); //get_bit получает биты справа налево
				f--;
			}
			g++;
		}

		bool M_2[64];
		for (int i = 0; i < 64; i++)
			M_2[IP_1[i] - 1] = M[i]; //M_2[i] = M[i]; //M_2[IP_1[i] - 1] = M[i];

		//начальная перестановка
		for (int i = 0; i < 64; i++) {
			if (i < 32)
				L1[i] = M_2[i];// M[i];
			else
				L2[i - 32] = M_2[i]; // M[i];
		}



		//преобразование Фейстеля
		for (int i = 1; i >= 0; i--) {
			bool
				RNew[32],
				mas[32];

			//функция f
			funk(L1, mas, i);

			//xor L1 & f(L2, ki)
			for (int j = 0; j < 32; j++) {
				RNew[j] = L2[j] ^ mas[j];//r_keys[0][j]; //mas[j];
				//RNew[j] ^= mas[j];//r_keys[0][j]; //mas[j];
			}
			

			//перестановка блоков
			for (int j = 0; j < 32; j++)
				L2[j] = L1[j];

			for (int j = 0; j < 32; j++)
				L1[j] = RNew[j];
		}

		//Обьединение блоков
		for (int i = 0; i < 64; i++) {
			if (i < 32)
				M[i] = L1[i];
			else
				M[i] = L2[i - 32];
		}


		//обратная подстановка
		bool M_1[64];
		for (int i = 0; i < 64; i++) {
			M_1[IP[i] - 1] = M[i]; //M_1[i] = M[i]; //M_1[IP[i] - 1] = M[i];//  M[i];
		}

		//перевод из битоВОго представления в обычное

		res = Convert_simb(M_1);

		return res;
	}
	


};

// класс для алгоритма rsa
class Rsa : private Message {

	
	
protected:
	//Генерация рандомного числа
	unsigned long long  CreateInt() {
		//srand(time(0));
		//сначала случайным образом выбираем "ширину битовой строки от 8 до 16"
		int size = 6 + rand() % 11;

		unsigned long long a = 1;
		

		int init = 1;
		
		for (int j = 1; j < size - 1; j++) {

			//bool check = rand() % 2
			if (rand()%2)
			{
				a = a | (1 << init);
			}

			init++;
		}
		a = a | (1 << init);
		return a;

	}
	//возведение в степень по модулю
	long long unsigned Modn(long long unsigned n, long long unsigned b) {
		long long unsigned c = 1;
		
		for (int i = 1; i <= n - 1; i++)
			c = (c * b) % n;
		return c;
	}

	//возведение в степень по модулю(j,общая формула)
	long long unsigned Modn(long long unsigned n, long long unsigned b, long long unsigned a) {
		long long unsigned c = 1;

		for (int i = 1; i <= a; i++)
			c = (c * b) % n;
		return c;
	}
	//вероятностный тест Ферма на простоту
	bool FermaTest(unsigned long long a) {
		srand(time(0));

		for (int i = 0; i < 10; i++) {
			unsigned long long b = rand();
			if (Modn(a, b) != 1)
				return 0;
							
		}
		return 1;
	}
	//расширенный алгоритм Евклида
	unsigned long long gcd(unsigned long long a, unsigned long  long b, unsigned long long& x, unsigned long long& y) {
		if (a == 0) {
			x = 0; y = 1;
			return b;
		}
		unsigned long long x1, y1;
		unsigned long long d = gcd(b % a, a, x1, y1);
		x = y1 - (b / a) * x1;
		y = x1;
		return d;
	}
	long long unsigned modexp(long long unsigned base, long long unsigned exp, long long unsigned modulo)
	{
		unsigned long long res = 1;

		while (exp != 0)
		{
			if ((exp & 1) != 0)
			{
				res = (1ll * res * base) % modulo;
			}

			base = (1ll * base * base) % modulo;
			exp >>= 1;
		}

		return res;
	}
	bool mulmod(unsigned long long e, unsigned long  long d, long long unsigned mod) {
		if (((e * d) % mod) == 1)
			return true;
		else
			return false;
	}

	

	

public:
	unsigned long long
		p,
		q,
		e,
		f,
		d,
		n;
	Rsa::Rsa() {
		Message();
	}
	//функция генерации ключей
	void GenKey() {
		srand(time(0));
		do
		{
			p = CreateInt();
		} while (!FermaTest(p));
		//srand(time(0));
		do
		{
			q = CreateInt();
			if (q == p)
				q = 4;
		} while (!FermaTest(q));

		n = p * q;
		f = (p - 1) * (q - 1);
		
		unsigned long long x, y, // коэффициенты в алгоритме Эвклида
			g;
		
		
		srand(time(0));
		do {
			e = 1 + rand() % (f - 2);
			g = gcd(e, f, x, y);
		}
			
		while (g != 1);

		d = x;
		if (!mulmod(e, d, f)) //Если произведенние е на д != 1 генерятся новые значения ключа
			GenKey();
		
	}
	//функция шифрования
	string Code(string data) {
		unsigned long long a;
		string res;
		for (int i = 0; i < data.size(); i++) {
			unsigned char sl = unsigned char(data[i]);
			a = modexp(sl, e, n);
			res += to_string(a) + " ";
		}
		return res;
	}
	//функция дешифрования
	string DeCode(string data) {
		unsigned long long a;
		string res;

		while (!data.empty()) {
			int h = data.find(" ");
			string buf = data.substr(0, h);
			data.erase(0, h + 1);
			unsigned long long x = stoi(buf);
			//a = powmod(x, d, n);
			a = modexp(x, d, n);
			char ch = a;
			res += ch;
		}
			
		
		return res;
	}


};