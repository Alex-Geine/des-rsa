
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
	
	, plain_t(_T("привет"))
	, closed_t(_T(""))
	, key(_T(""))
	
	, checkDES(TRUE)
	, checkRSA(FALSE)
	, d(0)
	, e(0)
	, q(0)
	, p(0)
	, f(0)
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
	DDX_Check(pDX, IDC_CHECK1, checkDES);
	DDX_Check(pDX, IDC_CHECK2, checkRSA);
	DDX_Text(pDX, IDC_EDIT4, n);
	DDX_Text(pDX, IDC_EDIT5, d);
	DDX_Text(pDX, IDC_EDIT6, e);
	DDX_Text(pDX, IDC_EDIT7, q);
	DDX_Text(pDX, IDC_EDIT8, p);
	DDX_Text(pDX, IDC_EDIT9, f);
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
	ON_BN_CLICKED(IDC_CHECK1, &CdesDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CdesDlg::OnBnClickedCheck2)
	ON_EN_CHANGE(IDC_EDIT4, &CdesDlg::OnEnChangeEdit4)
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

//генерация ключа
void CdesDlg::OnBnClickedButton7()
{	
	Key.clear();
	key = (_T(""));

	setlocale(LC_ALL, "rus"); 
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
		key += (_T("%c"), Key[i]);	
		
	UpdateData(false);	
}

//преобразование
void CdesDlg::OnBnClickedOk()
{			
	setlocale(LC_ALL, "rus");
	UpdateData(true);

	//исходные данные
	string data;
	
	if (check.GetCheck()) {
		USES_CONVERSION;
		data = W2A(plain_t);
	}
	if (!check.GetCheck()) {
		USES_CONVERSION;
		data = W2A(closed_t);
	}
		
	//Число блоков
	int blockNum = (data.length() % key_size == 0) ? (data.length() / key_size) : (data.length() / key_size + 1);
	
	//сторока с результатом
	string 
		res,
		buf;

	res.resize(blockNum * key_size);
	//Шифрование Дес
	if (checkDES) {
		Des des;
		des.SetKey(Key);
		for (int i = 0; i < blockNum; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i * 8 + j) <= data.length())
					buf.push_back(data[i * 8 + j]);
				else
					buf.push_back(0);
			}
			if (!check.GetCheck()) {
				des.SetPlain(buf);
				buf = des.Code();
			}
			else {
				des.SetClosed(buf);
				buf = des.DeCode();
			}


			for (int j = 0; j < 8; j++) {
				res[i * 8 + j] = buf[j];
			}
			buf.clear();
		}
	}
	//RSA
	else {
		Rsa rsa;
		if (n == 0) {
			rsa.GenKey();
			n = rsa.n;
			e = rsa.e;
			d = rsa.d;
			q = rsa.q;
			p = rsa.p;
			f = rsa.f;
		}
		else {
			rsa.n = n;
			rsa.e = e;
			rsa.d = d;
			rsa.q = q;
			rsa.p = p;
			rsa.f = f;
		}
		
		
		if (check.GetCheck())
			res = rsa.Code(data);
		else
			res = rsa.DeCode(data);

	}
	
	//заполнение строки для вывода
	if (check.GetCheck())
		closed_t = res.c_str();
	else
		plain_t = res.c_str();

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

//флажок для DES
void CdesDlg::OnBnClickedCheck1()
{
	UpdateData();
	if (!checkDES) 		
		checkRSA = true;	
	else 
		checkRSA = false;
		
	
	UpdateData(false);
	// TODO: добавьте свой код обработчика уведомлений
}

//флажок для RES
void CdesDlg::OnBnClickedCheck2()
{
	UpdateData();
	if (!checkRSA)
		checkDES = true;
	else
		checkDES = false;
	UpdateData(false);
	// TODO: добавьте свой код обработчика уведомлений
}

void CdesDlg::OnBnClickedRadio1()
{
}



void CdesDlg::OnEnChangeEdit4()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
