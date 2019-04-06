
// ContestListDlg.h: 头文件
//

#pragma once
#include "CPersonList.h"

// CContestListDlg 对话框
class CContactListDlg : public CDialogEx
{
// 构造
public:
	CContactListDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTESTLIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_lstcPersonList;
	afx_msg void OnLvnItemchangedLstContactlist(NMHDR *pNMHDR, LRESULT *pResult);
	
protected:
	void InitPersonListCtrl();	// ListCtrl 样式的设置
	void RefreshPersonListCtrl(CPersonList& psnList, int iCursel = -1);	// 刷新主界面的用户列表
	int GetCurSel();		// 得到用户当前选中的联系人编号
	void CountMale();		// 统计性别
	CString IntToString(int n);	// 整型转换成字符串类型

protected:
	// 联系人列表数组
	CPersonList m_lstPerson;
	// 默认存储路径
	CString m_strDefGCLFileName;
	// 暂存查找的结果
	CPersonList m_lstFindPerson;
	// 工具栏对象
	CToolBar m_ToolBar;
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnEdit();
protected:
	// 将通讯录写入文件strFileName
	BOOL DoSaveFile(CString strFileName);
	// 从文件strFileName中读入通讯录
	BOOL DoLoadFile(CString strFileName);
	// 创建工具栏
	BOOL CreateToolBar();	
public:
	afx_msg void OnBnClickedBtnBackup();
	afx_msg void OnBnClickedBtnRestore();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnCopy();
	CString m_strFind;
	afx_msg void OnChangeEdFind();
	afx_msg void OnBnClickedBtnFind();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnSave();
	afx_msg void OnOpen();
	afx_msg void OnExit();
	afx_msg void OnAdd();
	afx_msg void OnCopy();
	afx_msg void OnEdit();
	afx_msg void OnDel();
	afx_msg void OnAbout();
	afx_msg void OnToolbtnAdd();
	afx_msg void OnToolbtnCopy();
	afx_msg void OnToolbtnDelete();
	afx_msg void OnToolbtnEdit();
	afx_msg void OnToolbtnAbout();
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
