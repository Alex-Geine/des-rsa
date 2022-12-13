
// desDlg.h: файл заголовка
//
#include <iostream>
#include <fstream>
#include "Encryption.h"
#pragma once

using namespace std;

// Диалоговое окно CdesDlg
class CdesDlg : public CDialogEx
{
// Создание
public:
	CdesDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	const int dataSize = 64;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedOk();
	//открытый текст
	CString plain_t;
	string Plain_t;
	//закрытый текст
	CString closed_t;
	string Closed_t;
	//ключ
	CString key;
	string Key;
	bool bit_key[64]; // битовое представление ключа
	//размер ключа
	const int key_size = 8;
	CButton check;
	afx_msg void OnBnClickedRadio1();
	//функция закгрузки из файла
	string Load();
	//функция сохранения файла
	void Save(string in);
	//функция шифрования
	string Code(string in);
	//функция f
	void funk(bool *in, bool * out, int I);
	//функция f
	void funk(bool* in, bool* out);
	//функция получения раундовых ключей
	void Get_RKeys();
	
	
	
	void Test();
	//функция дешифрования
	string DeCode(string in);
	
	string open_text_path;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	
	//раундовые ключи
	bool r_keys[16][48];


	Message mes;
	

	BOOL checkDES;
	BOOL checkRSA;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnEnChangeEdit4();
	unsigned long long n;
	unsigned long long d;
	unsigned long long e;
	unsigned long long q;
	unsigned long long p;
	unsigned long long f;
};
