#pragma once
#include "stdafx.h"
// 引入CPerson类
#include "CPerson.h"

// CEditDlg 对话框

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	// 新加一个isNew来判断是添加还是编辑，默认为添加
	CEditDlg(CPerson psn, CWnd* pParent = nullptr);   // 修改后的构造函数
	virtual ~CEditDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	// 获取CPerson类对象
	CPerson& GetPerson() { return m_psnEdit; }

protected:
	// 定义一个CPerson类对象
	CPerson m_psnEdit;
	// 定义一个CString类型来存储头像路径
	CString m_strHead;

public:
	afx_msg void OnCbnSelchangeCbGender();
	// 使用类向导创建的变量
	int m_bMale;
	CString m_strName;
	CString m_strPhoneNo;
	CString m_strQQNumber;
	CComboBox m_cbGroup;
	int m_iGroup;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnPaint();
};
