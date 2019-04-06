#include "stdafx.h"
#include "CPerson.h"

// 引用
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
	// 先判断是不是有组，或者是存储组数的数字比存储组名的列表大
	if (m_iGroupNo < 0 || m_iGroupNo >= g_lstGroups.GetSize())
	{
		return _T("");
	}
	return g_lstGroups[m_iGroupNo];
} // end of CPerson::GetGroupName()

// 将数据写入文件或者从文件中读取数据
void CPerson::Serialize(CArchive& ar) {
	// 写数据
	if (ar.IsStoring())
	{
		ar << m_strName;
		ar << m_bMale;
		ar << m_strPhoneNo;
		ar << m_strQQNo;
		ar << m_iGroupNo;
		ar << m_strHead;
	}
	else  // 读数据
	{
		ar >> m_strName;
		ar >> m_bMale;
		ar >> m_strPhoneNo;                                                             
		ar >> m_strQQNo;
		ar >> m_iGroupNo;
		ar >> m_strHead;
	}
} // end of CPerson::Serialize()

// 复制联系人，按照规则修改姓名
void CPerson::Duplicate() {
	int iLen = m_strName.GetLength();

	if (iLen <= 0)
	{
		m_strName += _T("~1");			// 如果名字的长度是0，就直接在名字后面添加"~1"
		return;
	}
	int iEndChar = m_strName[iLen - 1];
	// 如果姓名以数字结尾，将此数字增加1
	if (iEndChar >= int('0') && iEndChar <= int('8'))
	{
		m_strName.SetAt(iLen-1, iEndChar+1);
	}
	else
	{
		m_strName += _T("~1");
	}
} // end of CPerson::Duplicate()