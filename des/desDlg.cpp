
// desDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "des.h"
#include "desDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#ifndef _DEBUG
#define USES_CONVERSION int _convert; (_convert); UINT _acp = ATL::_AtlGetConversionACP() /*CP_THREAD_ACP*/; (_acp); LPCWSTR _lpw; (_lpw); LPCSTR _lpa; (_lpa)
#else
#define USES_CONVERSION int _convert = 0; (_convert); UINT _acp = ATL::_AtlGetConversionACP() /*CP_THREAD_ACP*/; (_acp); LPCWSTR _lpw = NULL; (_lpw); LPCSTR _lpa = NULL; (_lpa)
#endif

using namespace std;
// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CdesDlg



CdesDlg::CdesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DES_DIALOG, pParent)
	
	, plain_t(_T(""))
	, closed_t(_T(""))
	, key(_T(""))
	
{	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDIT1, plain_t);
	DDX_Text(pDX, IDC_EDIT2, closed_t);
	DDX_Text(pDX, IDC_EDIT3, key);
	DDX_Control(pDX, IDC_RADIO1, check);
}

BEGIN_MESSAGE_MAP(CdesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON7, &CdesDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDOK, &CdesDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CdesDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON1, &CdesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CdesDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CdesDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CdesDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CdesDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CdesDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// Обработчики сообщений CdesDlg

BOOL CdesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CdesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CdesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CdesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
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
void  CdesDlg::Get_RKeys() {
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
string Convert_simb( bool* in) {
	string res;

	for (int i = 0; i < 8; i++) {
		unsigned char a = 0;
		int init = 0;
		for (int j = 7; j >= 0; j--) {
			if (in[8 * i + j])
			{
				a = a | (1 << init);
				//file << "j: " << j << " int a = " << (int)a << endl;
			}
			if (!in[8 * i + j]) {
				//	a = a << 1;
				//file << "j: " << j << " int a = " << (int)a << endl;
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
	for (int j = n-1; j >= 0; j--) {
		if (in[j])
		{
				res = res | (1 << init);
				//file << "j: " << j << " int a = " << (int)a << endl;
		}
	
		init++;
	}
	
	return res;
}

//перевод из символьного в битовое
void Convert_bit(string in, bool *res) {
	int f;

	for (int j = 0; j < 8; j++) {
		f = (j + 1) * 8 - 1; // 7 15 23 ...
		for (int i = 0; i < 8; i++) {
			res[f] = get_bit(in[j], i); //get_bit получает биты справа налево
			f--;
		}

	}

}





//генерация ключа
void CdesDlg::OnBnClickedButton7()
{
	


	Key.clear();
	key = (_T(""));

	setlocale(LC_ALL, "rus"); // Спорно
	srand(time(0));
	
	//генерация битового представления ключа
	for (int i = 0; i < 8; i++) {
		bool sum = 0;
		for (int j = 0; j < 8; j++) {
			if (j != 7) {
				double a = (double)rand() / RAND_MAX; //7 случайных бит 1 проверочный
				if (a > 0.5) {
					bit_key[8 * i + j] = 1;
					sum = !sum;
				}					
				else 
					bit_key[8 * i + j] = 0;								
			}

			else 
				bit_key[8 * i + j] = sum ? 0 : 1; // контрольный бит
		}
	}
		
	//перевод в символьный вид
	Key = Convert_simb(bit_key);
	for (int i = 0; i < 8; i++) 		
		key += (_T("%c"), Key[i]);	//мб тут трабл
		
	

	
	
	//Затесть всю эту шайку лейку и раздели на модули(выдели функцию генерации раундовых ключей)


	//file.close();
	UpdateData(false);

	
}

//функция f шифрации
void CdesDlg::funk(bool* in, bool*out, int I) {
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

//функция шифрации
string CdesDlg::Code(string in) {
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

	int f; // индекс бита в массиве M
	
	
	//представление символов в битах      (!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ВАЖНО!!!!!!!!!!!!!!!!!!!!!!!!) зачем тут f &&&
	for (int j = 0; j < 8; j++) {
		f = (j+1)  * 7; // 7 15 23 ...
		for (int i = 0; i < 8; i++) {
			M[f] = get_bit(in[j], i); //get_bit получает биты справа налево
			f--;
		}		
	
	}

	//начальная перестановка
	for (int i = 0; i < 64; i++) {
		if (i < 32)
			L1[i] = M[IP[i] - 1];
		else
			L2[i - 32] = M[IP[i] - 1];
	}
	
	//преобразование Фейстеля
	for (int i = 0; i < 16; i++) {
		bool 
			RNew[32],//результат XOR
			mas[32]; // результат f()
				
		//функция f
		funk(L2,mas,i);
		
		//xor L1 & f(L2, ki)
		for (int j = 0; j < 32; j++) {
			RNew[j] = L1[j] ^ mas[j]; // r_keys[0][j];
			
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
		M_1[i] = M[IP_1[i] - 1];
	}
		
	//перевод из битоВОго представления в символьное
	res = Convert_simb(M_1);
	
	return res;
}

//Функция декодирования
string CdesDlg::DeCode(string in) {
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

	int f; // индекс бита в массиве M
	int Byte = 8;

	//представление символов в битах      (!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ВАЖНО!!!!!!!!!!!!!!!!!!!!!!!!) зачем тут f &&&
	for (int j = 0; j < 8; j++) {
		f = (j + 1) * 7; // 7 15 23 ...
		for (int i = 0; i < 8; i++) {
			M[f] = get_bit(in[j], i); //get_bit получает биты справа налево
			f--;
		}

	}

	bool M_2[64];
	for (int i = 0; i < 64; i++) 
		M_2[IP_1[i] - 1] = M[i];
	
	//начальная перестановка
	for (int i = 0; i < 64; i++) {
		if (i < 32)
			L1[i] = M_2[i];// M[i];
		else
			L2[i - 32] = M_2[i]; // M[i];
	}



	//преобразование Фейстеля
	for (int i = 15; i >= 0; i--) {
		bool
			RNew[32],
			mas[32];

		//функция f
		funk(L1, mas,i);

		//xor L1 & f(L2, ki)
		for (int j = 0; j < 32; j++) 
			RNew[j] = L2[j] ^ mas[j];
			
		
			

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
		M_1[IP[i] - 1] = M[i];//  M[i];
	}

	//перевод из битоВОго представления в обычное

	res = Convert_simb(M_1);

	return res;
}


//int f = 1;
//преобразование
void CdesDlg::OnBnClickedOk()
{
	
	//if (f == 1) {
	//	check.SetCheck(true);
	//	f++;
	//}
		
	setlocale(LC_ALL, "rus");
	UpdateData(true);

	//исходные данные

	string data;
	/*
	if (check.GetCheck()) {
		USES_CONVERSION;
		data = W2A(plain_t);
	}
	if (!check.GetCheck()) {
		USES_CONVERSION;
		data = W2A(closed_t);
	}*/

	//перепиши, чтобы в строку закидывалось произвольное количество данныъх

	string text = "12345678";
	string ctext;

	//Число блоков
	int blockNum = (data.length() % key_size == 0) ? (data.length() / key_size) : (data.length() / key_size + 1);
	//сторока с результатом
	string res;// (blockNum * key_size);
	res.resize(blockNum * key_size);

	   

	//попробуем просто переставлять блоки местами
	
	res = Code(text);
	fstream file;
	file.open("data.txt");
	file << "old text:  " << text << endl;
	file << endl;
	file << "key:  " << Key << endl;
	file << endl;
	file << "ctext:  " << res << endl;
	file << endl;

	text = DeCode(res);

	file << "new text:  " << text << endl;

	file.close();








	//if(check.GetCheck())res = Code(data);
	//if(!check.GetCheck())res = DeCode(data);


	////заполнение строки для вывода
	//if (check.GetCheck())
	//	closed_t = res.c_str();
	//if (!check.GetCheck())
	//	plain_t = res.c_str();


	UpdateData(false);
	
}

//Функция загрузки инфы
string CdesDlg::Load() {
	USES_CONVERSION;
	string a = "";
	CFileDialog fd(true);
	if (fd.DoModal() == IDOK)
	{
		open_text_path.clear();
		open_text_path = W2A(fd.m_ofn.lpstrFile);
	}

	ifstream(file);
	file.open(open_text_path);

	if (file.is_open())
	{
		
		getline(file, a);
		
	}
	return a;	
	file.close();
}
//Функция сохранения инфы
void CdesDlg::Save(string in) {
	USES_CONVERSION;

	CFileDialog fd(FALSE);
	fd.m_ofn.lpstrDefExt = L"*.txt";

	if (fd.DoModal() == IDOK)
	{
		open_text_path.clear();
		open_text_path = W2A(fd.m_ofn.lpstrFile);
	}
	ofstream file;
	file.open(open_text_path);
	if (file.is_open()) {
		MessageBox(L"Файл  открыт", L" открытиt файла", MB_OK);
		for (int i = 0; i < in.size(); i++)
			file << in[i];

	}
	file.close();
}
void CdesDlg::OnBnClickedRadio1()
{
	if (check.GetCheck())
		check.SetCheck(false);
	else
		check.SetCheck(true);
	UpdateData(true);
	// TODO: добавьте свой код обработчика уведомлений
}

//сохраняет открытытй текст
void CdesDlg::OnBnClickedButton1()
{
	USES_CONVERSION;
	UpdateData(true);

	Plain_t = W2A(plain_t);
	Save(Plain_t);

	UpdateData(false);
	
}

//сохраняет закрытый текст
void CdesDlg::OnBnClickedButton2()
{
	USES_CONVERSION;
	UpdateData(true);

	Closed_t = W2A(closed_t);
	Save(Closed_t);

	UpdateData(false);
}

//сохраняет ключ
void CdesDlg::OnBnClickedButton3()
{
	USES_CONVERSION;
	UpdateData(true);

	Key = W2A(key);
	Save(Key);

	UpdateData(false);
}

//загружает открытытй текст
void CdesDlg::OnBnClickedButton4()
{
	Plain_t.clear();
	Plain_t = Load();
	plain_t = Plain_t.c_str();
	UpdateData(false);
}

//Кнопка загрузки закрытого текста
void CdesDlg::OnBnClickedButton5()
{
	Closed_t.clear();
	Closed_t = Load();
	closed_t = Closed_t.c_str();
	UpdateData(false);
}

//загружает ключ
void CdesDlg::OnBnClickedButton6()
{
	Key.clear();
	Key = Load();
	key = Key.c_str();
	UpdateData(false);
}
