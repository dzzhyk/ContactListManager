#pragma once
class CPerson
{
public:
	CPerson();
	// 重载构造函数
	CPerson(CString strName, BOOL bMale = TRUE, CString strPhoneNo = _T("88888888888"),
		CString strQQNo = _T("0000"), int iGroupNo = 0, CString strHead = _T(""));
	~CPerson();

	// 添加CPerson的类操作函数
	//Get
	CString GetName()		{ return m_strName; }
	BOOL	IsMale()		{ return m_bMale; }
	CString GetPhoneNo()	{ return m_strPhoneNo; }
	CString GetQQNo()		{ return m_strQQNo; }
	int 	GetGroupNo()	{ return m_iGroupNo; }
	CString GetGroupName();	// 从字符数组g_lstGroups中获取组名
	CString GetImageHead()	{ return m_strHead; }

	//Set
	void SetName(CString strName)		{ m_strName = strName; }
	void SetMale(BOOL bMale)			{ m_bMale = bMale; }
	void SetPhoneNo(CString strPhoneNo) { m_strPhoneNo = strPhoneNo; }
	void SetQQNo(CString strQQNo)		{ m_strQQNo = strQQNo; }
	void SetGroupNo(int iGroupNo)		{ m_iGroupNo = iGroupNo; }
	void SetImageHead(CString strHead)	{ m_strHead = strHead; }

protected:
	CString m_strName;		// 姓名
	BOOL	m_bMale;		// 性别：TRUE为男，FALSE为女
	CString m_strPhoneNo;	// 手机号
	CString m_strQQNo;		// QQ号码
	int		m_iGroupNo;		// 组号：全局字符串数组 g_lstGroup 的索引
	CString m_strHead;		// 头像：存储头像图片的路径

// 添加实现数据存储的函数代码
public:
	void Serialize(CArchive& ar);
	void Duplicate();	//在姓名后面添加“~+数字”（作用：复制联系人）
};

