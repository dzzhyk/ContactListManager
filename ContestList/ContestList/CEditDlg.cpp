// CEditDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ContestList.h"
#include "CEditDlg.h"
#include "afxdialogex.h"
#include "CPersonList.h"


// CEditDlg 对话框

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

// 这里需要将构造函数中的形参修改一致
CEditDlg::CEditDlg(CPerson psn, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT, pParent)
	, m_bMale(0)
	, m_strName(_T(""))
	, m_strPhoneNo(_T(""))
	, m_strQQNumber(_T(""))
	, m_iGroup(0)
	, m_strHead(psn.GetImageHead())		// 构造函数中也要添加头像的信息
{
	m_psnEdit = psn;
	m_bMale = psn.IsMale();
	m_strName = psn.GetName();
	m_strPhoneNo = psn.GetPhoneNo();
	m_strQQNumber = psn.GetQQNo();
	m_iGroup = psn.GetGroupNo();
	m_strHead = psn.GetImageHead();
}

//CEditDlg::CEditDlg(CPerson psn, CWnd* pParent /*=nullptr*/, bool isNew = FALSE)	
//{
//	// 构造函数中也要添加头像的信息
//	m_psnEdit = psn;
//	CDialogEx::CDialogEx(IDD_EDIT, pParent);
//	BOOL m_bMale(psn.IsMale());
//	CString m_strName(psn.GetName);
//	CString m_strPhoneNo(psn.GetPhoneNo());
//	CString m_strQQNumber(psn.GetQQNo());
//	int m_iGroup(psn.GetGroupNo());
//	CString m_strHead(psn.GetImageHead());
//}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_CB_GENDER, m_bMale);
	DDX_Text(pDX, IDC_ED_NAME, m_strName);
	DDX_Text(pDX, IDC_ED_PHONENUMBER, m_strPhoneNo);
	DDX_Text(pDX, IDC_ED_QQNUMBER, m_strQQNumber);
	DDX_Control(pDX, IDC_CB_GROUP, m_cbGroup);
	DDX_CBIndex(pDX, IDC_CB_GROUP, m_iGroup);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CB_GENDER, &CEditDlg::OnCbnSelchangeCbGender)
	ON_BN_CLICKED(IDOK, &CEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CEditDlg::OnBnClickedBtnBrowse)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEditDlg 消息处理程序


void CEditDlg::OnCbnSelchangeCbGender()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化编辑页面分组下拉框
	for (int i = 0; i<g_lstGroups.GetSize(); i++)
	{
		m_cbGroup.AddString(g_lstGroups[i]);
	}

	// UpdateData(TRUE)		用来刷新控件的值到对应变量		控件->变量
	// UpdateData(FALSE)	用来复制变量值到控件上显示		变量->控件
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_psnEdit = CPerson(m_strName, m_bMale, m_strPhoneNo, m_strQQNumber, m_iGroup);
	// 新增保存上传图片的路径
	m_psnEdit.SetImageHead(m_strHead);
	CDialogEx::OnOK();
}


void CEditDlg::OnBnClickedBtnBrowse()
{
	// “浏览”按钮响应函数
	// 构造打开文件的对话框
	CFileDialog ccFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
		OFN_ALLOWMULTISELECT,
		_T("Image files(*.png ; *.jpg; *.jpeg) | *png;*jpg;*.jpeg | All files(*.*) | *.* ||"), NULL);
	if (ccFileDlg.DoModal() == IDOK)
	{
		// 获取文件路径
		CString strPathName = ccFileDlg.GetPathName();
		// 获取文件名字.后缀
		m_strHead = ccFileDlg.GetFileName();
		// 设置默认上传图片文件夹
		CString strFolderPath = _T("head\\");
		if (!PathIsDirectory(strFolderPath))
		{
			// 如果不存在初始的存储路径，就创建一个询问消息 - 询问是否创建
			CString strMsg;
			strMsg.Format(_T("指定路径“ %s ”不存在，是否创建？"), strFolderPath);
			if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
			{
				// 特举创建路径失败的情况
				if (!CreateDirectory(strFolderPath, NULL))
				{
					strMsg.Format(_T("创建路径“ %s ”失败！"), strFolderPath);
					if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
					{
						return;
					}
				}
			}
		}
		m_strHead = _T("head\\") + m_strHead;
		// 复制文件到指定路径
		CopyFile(strPathName, m_strHead, TRUE);
		// 显示图片文件
		CPersonList::ShowImage(this->m_hWnd, m_strHead, IDC_STA_PHOTO);
	}
}


void CEditDlg::OnPaint()
{
	// 添加OnPrint函数在当编辑框打开的时候自动调用显示头像的函数
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	if (PathFileExists(m_psnEdit.GetImageHead()))
	{
		CPersonList::ShowImage(this->m_hWnd, m_strHead, IDC_STA_PHOTO);
	}
}
