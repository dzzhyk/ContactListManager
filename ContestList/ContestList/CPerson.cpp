#include "stdafx.h"
#include "CPerson.h"

// ����
extern CStringArray g_lstGroups;

CPerson::CPerson()
{
	m_strName		=	_T("Unknown");
	m_bMale			=	TRUE;
	m_strPhoneNo	=	_T("88888888888");
	m_strQQNo		=	_T("0000");
	m_strHead		=	_T(".\\Unknown.jpg");
}

CPerson::CPerson(CString strName, BOOL bMale, CString strPhoneNo, CString strQQNo, int iGroupNo, CString strHead):
	m_strName(strName), m_bMale(bMale), m_strPhoneNo(strPhoneNo), m_strQQNo(strQQNo),
	m_iGroupNo(iGroupNo)
{

} // end of CPerson::CPerson()

CPerson::~CPerson()
{
}

CString CPerson::GetGroupName() {
	// ���ж��ǲ������飬�����Ǵ洢���������ֱȴ洢�������б��
	if (m_iGroupNo < 0 || m_iGroupNo >= g_lstGroups.GetSize())
	{
		return _T("");
	}
	return g_lstGroups[m_iGroupNo];
} // end of CPerson::GetGroupName()

// ������д���ļ����ߴ��ļ��ж�ȡ����
void CPerson::Serialize(CArchive& ar) {
	// д����
	if (ar.IsStoring())
	{
		ar << m_strName;
		ar << m_bMale;
		ar << m_strPhoneNo;
		ar << m_strQQNo;
		ar << m_iGroupNo;
		ar << m_strHead;
	}
	else  // ������
	{
		ar >> m_strName;
		ar >> m_bMale;
		ar >> m_strPhoneNo;                                                             
		ar >> m_strQQNo;
		ar >> m_iGroupNo;
		ar >> m_strHead;
	}
} // end of CPerson::Serialize()

// ������ϵ�ˣ����չ����޸�����
void CPerson::Duplicate() {
	int iLen = m_strName.GetLength();

	if (iLen <= 0)
	{
		m_strName += _T("~1");			// ������ֵĳ�����0����ֱ�������ֺ������"~1"
		return;
	}
	int iEndChar = m_strName[iLen - 1];
	// ������������ֽ�β��������������1
	if (iEndChar >= int('0') && iEndChar <= int('8'))
	{
		m_strName.SetAt(iLen-1, iEndChar+1);
	}
	else
	{
		m_strName += _T("~1");
	}
} // end of CPerson::Duplicate()