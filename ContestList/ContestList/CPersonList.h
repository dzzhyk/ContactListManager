#pragma once

#include "CPerson.h"
#include "afxtempl.h"	// CArrayͷ�ļ�

// ��Ԫ��ΪCPerson���Ե�CArray����ΪCPersons
typedef CArray<CPerson, CPerson> CPersons;

class CPersonList:public CPersons
{
public:
	CPersonList();
	~CPersonList();

public:
	// ʵ�����ݴ洢
	void Serialize(CArchive& ar);
	// ��ʾͷ��ĺ���
	static void ShowImage(HWND hDlg, CString pathName, int pictureID);
};

