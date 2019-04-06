#include "stdafx.h"
#include "CPersonList.h"


CPersonList::CPersonList()
{
}


CPersonList::~CPersonList()
{
}

void CPersonList::Serialize(CArchive& ar) {
	// GetSize方法来自于CPersons的这个CArray类
	int iSize = GetSize();

	if (ar.IsStoring())
	{
		// 写数据
		ar << iSize;
	}
	else
	{
		// 读数据
		ar >> iSize;
		SetSize(iSize);
	}
	// 逐个写入或者读取CPerson元素
	for (int i = 0; i < iSize; i++)
	{
		(*this)[i].Serialize(ar);
	}
} // end of CPersonList::Serialize()

void CPersonList::ShowImage(HWND hDlg, CString pathName, int pictureID) {
	CImage image;
	CRect rect;
	// 根据路径载入图片
	image.Load(pathName);
	// 获取控件句柄
	HWND hWnd = GetDlgItem(hDlg, pictureID);
	// 获取句柄指向的控件区域（图相框）的大小
	GetClientRect(hWnd, &rect);
	// 获取picture的DC
	HDC hdc = GetDC(hWnd);
	// 将图片绘制到picture表示的区域内
	image.Draw(hdc, rect);
}