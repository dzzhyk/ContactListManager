#include "stdafx.h"
#include "CPersonList.h"


CPersonList::CPersonList()
{
}


CPersonList::~CPersonList()
{
}

void CPersonList::Serialize(CArchive& ar) {
	// GetSize����������CPersons�����CArray��
	int iSize = GetSize();

	if (ar.IsStoring())
	{
		// д����
		ar << iSize;
	}
	else
	{
		// ������
		ar >> iSize;
		SetSize(iSize);
	}
	// ���д����߶�ȡCPersonԪ��
	for (int i = 0; i < iSize; i++)
	{
		(*this)[i].Serialize(ar);
	}
} // end of CPersonList::Serialize()

void CPersonList::ShowImage(HWND hDlg, CString pathName, int pictureID) {
	CImage image;
	CRect rect;
	// ����·������ͼƬ
	image.Load(pathName);
	// ��ȡ�ؼ����
	HWND hWnd = GetDlgItem(hDlg, pictureID);
	// ��ȡ���ָ��Ŀؼ�����ͼ��򣩵Ĵ�С
	GetClientRect(hWnd, &rect);
	// ��ȡpicture��DC
	HDC hdc = GetDC(hWnd);
	// ��ͼƬ���Ƶ�picture��ʾ��������
	image.Draw(hdc, rect);
}