#pragma once

#include "CPerson.h"
#include "afxtempl.h"	// CArray头文件

// 将元素为CPerson属性的CArray定义为CPersons
typedef CArray<CPerson, CPerson> CPersons;

class CPersonList:public CPersons
{
public:
	CPersonList();
	~CPersonList();

public:
	// 实现数据存储
	void Serialize(CArchive& ar);
	// 显示头像的函数
	static void ShowImage(HWND hDlg, CString pathName, int pictureID);
};

