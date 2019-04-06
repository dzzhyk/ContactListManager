#pragma once
class CPerson
{
public:
	CPerson();
	// ���ع��캯��
	CPerson(CString strName, BOOL bMale = TRUE, CString strPhoneNo = _T("88888888888"),
		CString strQQNo = _T("0000"), int iGroupNo = 0, CString strHead = _T(""));
	~CPerson();

	// ���CPerson�����������
	//Get
	CString GetName()		{ return m_strName; }
	BOOL	IsMale()		{ return m_bMale; }
	CString GetPhoneNo()	{ return m_strPhoneNo; }
	CString GetQQNo()		{ return m_strQQNo; }
	int 	GetGroupNo()	{ return m_iGroupNo; }
	CString GetGroupName();	// ���ַ�����g_lstGroups�л�ȡ����
	CString GetImageHead()	{ return m_strHead; }

	//Set
	void SetName(CString strName)		{ m_strName = strName; }
	void SetMale(BOOL bMale)			{ m_bMale = bMale; }
	void SetPhoneNo(CString strPhoneNo) { m_strPhoneNo = strPhoneNo; }
	void SetQQNo(CString strQQNo)		{ m_strQQNo = strQQNo; }
	void SetGroupNo(int iGroupNo)		{ m_iGroupNo = iGroupNo; }
	void SetImageHead(CString strHead)	{ m_strHead = strHead; }

protected:
	CString m_strName;		// ����
	BOOL	m_bMale;		// �Ա�TRUEΪ�У�FALSEΪŮ
	CString m_strPhoneNo;	// �ֻ���
	CString m_strQQNo;		// QQ����
	int		m_iGroupNo;		// ��ţ�ȫ���ַ������� g_lstGroup ������
	CString m_strHead;		// ͷ�񣺴洢ͷ��ͼƬ��·��

// ���ʵ�����ݴ洢�ĺ�������
public:
	void Serialize(CArchive& ar);
	void Duplicate();	//������������ӡ�~+���֡������ã�������ϵ�ˣ�
};

