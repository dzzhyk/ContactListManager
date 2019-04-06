
// ContestListDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ContestList.h"
#include "ContestListDlg.h"
#include "afxdialogex.h"
// 引入编辑框的头文件
#include "CEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CContestListDlg 对话框



CContactListDlg::CContactListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTESTLIST_DIALOG, pParent)
	, m_strFind(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CContactListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_CONTACTLIST, m_lstcPersonList);
	DDX_Text(pDX, IDC_ED_FIND, m_strFind);
}

BEGIN_MESSAGE_MAP(CContactListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_CONTACTLIST, &CContactListDlg::OnLvnItemchangedLstContactlist)
	ON_BN_CLICKED(IDC_BTN_ADD, &CContactListDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CContactListDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CContactListDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_BACKUP, &CContactListDlg::OnBnClickedBtnBackup)
	ON_BN_CLICKED(IDC_BTN_RESTORE, &CContactListDlg::OnBnClickedBtnRestore)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_COPY, &CContactListDlg::OnBnClickedBtnCopy)
	ON_EN_CHANGE(IDC_ED_FIND, &CContactListDlg::OnChangeEdFind)
	ON_BN_CLICKED(IDC_BTN_FIND, &CContactListDlg::OnBnClickedBtnFind)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CContactListDlg::OnBnClickedBtnClear)
	ON_COMMAND(IDM_SAVE, &CContactListDlg::OnSave)
	ON_COMMAND(IDM_OPEN, &CContactListDlg::OnOpen)
	ON_COMMAND(IDM_EXIT, &CContactListDlg::OnExit)
	ON_COMMAND(IDM_ADD, &CContactListDlg::OnAdd)
	ON_COMMAND(IDM_COPY, &CContactListDlg::OnCopy)
	ON_COMMAND(IDM_EDIT, &CContactListDlg::OnEdit)
	ON_COMMAND(IDM_DEL, &CContactListDlg::OnDel)
	ON_COMMAND(IDM_ABOUT, &CContactListDlg::OnAbout)
	ON_COMMAND(ID_TOOLBTN_ADD, &CContactListDlg::OnToolbtnAdd)
	ON_COMMAND(ID_TOOLBTN_COPY, &CContactListDlg::OnToolbtnCopy)
	ON_COMMAND(ID_TOOLBTN_DELETE, &CContactListDlg::OnToolbtnDelete)
	ON_COMMAND(ID_TOOLBTN_EDIT, &CContactListDlg::OnToolbtnEdit)
	ON_COMMAND(ID_TOOLBTN_ABOUT, &CContactListDlg::OnToolbtnAbout)
//	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CContestListDlg 消息处理程序

BOOL CContactListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	InitPersonListCtrl();	// 初始化通讯录详单和格式
	CreateToolBar();		// 刷新工具栏

	// 获取默认通讯录文件名，用于软件打开/关闭的时候自动保存和读取通讯录
	WCHAR szCurPath[_MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurPath);
	m_strDefGCLFileName.Format(_T("%s\\ContactList.gcl"), szCurPath);

	if (PathFileExists(m_strDefGCLFileName))
	{
		DoLoadFile(m_strDefGCLFileName);		// 读入默认通讯录
		RefreshPersonListCtrl(m_lstPerson);		// 显示通讯录
	}
	//RefreshPersonListCtrl(m_lstPerson);	// 打开的时候先清除一下查找栏

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CContactListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CContactListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	// 添加显示头像的函数调用 - 系统启动的时候就显示头像
	if (m_lstPerson.GetCount() != 0 && PathFileExists(
		m_lstPerson[GetCurSel()].GetImageHead()))
	{
		CPersonList::ShowImage(this->m_hWnd, m_lstPerson[GetCurSel()].GetImageHead(), IDC_STA_HEAD);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CContactListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CContactListDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CContactListDlg::OnLvnItemchangedLstContactlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	// 使在选择不同联系人时显示不同的图片
	if (pNMLV->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
	{
		if (PathFileExists(m_lstPerson[GetCurSel()].GetImageHead()))
		{
			CPersonList::ShowImage(this->m_hWnd, m_lstPerson[GetCurSel()].GetImageHead(), IDC_STA_HEAD);
		}
	}
	*pResult = 0;
}

// InitPersonListCtrl 函数实现代码
void CContactListDlg::InitPersonListCtrl() {

	// 设置网格线和全行选择
	m_lstcPersonList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 添加分列  
	// 添加第一列，0是列编号，150像素宽度，对其方式为居中
	m_lstcPersonList.InsertColumn(0, _T("姓名"), LVCFMT_CENTER, 155);
	m_lstcPersonList.InsertColumn(1, _T("性别"), LVCFMT_CENTER, 140);
	m_lstcPersonList.InsertColumn(2, _T("手机号"), LVCFMT_CENTER, 170);
	m_lstcPersonList.InsertColumn(3, _T("QQ号"), LVCFMT_CENTER, 190);
	m_lstcPersonList.InsertColumn(4, _T("分组"), LVCFMT_CENTER, 170);
}

int CContactListDlg::GetCurSel() {
	// 得到当前列表选择的位置信息POSITION
	POSITION pos = m_lstcPersonList.GetFirstSelectedItemPosition();
	// 得到pos之后的一个位置，正好就是选择的编号
	return m_lstcPersonList.GetNextSelectedItem(pos);
}

// 刷新联系人列表函数实现
void CContactListDlg::RefreshPersonListCtrl(CPersonList& psnList, int iCurSel) {
	int iLastSel = GetCurSel();				// 保存上次选中的编号
	m_lstcPersonList.DeleteAllItems();		// 清除ListCtrl控件表格
	
	// 将通讯录中的每个CPerson对象逐行显示在控件的表格中
	for (int i = 0; i < psnList.GetSize(); i++)
	{
		m_lstcPersonList.InsertItem(i, psnList[i].GetName());
		m_lstcPersonList.SetItemText(i, 1, psnList[i].IsMale() ? _T("男") : _T("女"));
		m_lstcPersonList.SetItemText(i, 2, psnList[i].GetPhoneNo());
		m_lstcPersonList.SetItemText(i, 3, psnList[i].GetQQNo());
		m_lstcPersonList.SetItemText(i, 4, psnList[i].GetGroupName());

		// 设定一个联系人被选中
		if (iCurSel < 0)
		{
			if (iLastSel < 0)
			{
				// 一开始就没有选中联系人，需要先判断是不是有联系人，然后选择第一个
				iCurSel = psnList.GetSize() > 0 ? 0 : -1;
			}
			else {
				// 如果一开始上一次已经选中了联系人，就尽量保持不变
				iCurSel = min(psnList.GetSize() - 1, iLastSel);
			}
		}
		else {
			// 如果一开始已经选中了，就保持不变，这里的min是为了防止iCurSel越界
			iCurSel = min(psnList.GetSize() - 1, iCurSel);
		}
		if (iCurSel >= 0)
		{
			m_lstcPersonList.SetFocus();
			// 设置选中效果
			m_lstcPersonList.SetItemState(iCurSel, LVIS_SELECTED, LVIS_SELECTED);
		}
	}
	// 每一次刷新都调用统计男女生人数的函数
	CountMale();
	// 刷新头像显示 - 因为已经更改了头像，就需要刷新当前的头像
	if (m_lstPerson.GetCount() != 0 && m_lstPerson[GetCurSel()].GetImageHead())
	{
		CPersonList::ShowImage(m_hWnd, m_lstPerson[GetCurSel()].GetImageHead(), IDC_STA_HEAD);
	}
	else {
		CPersonList::ShowImage(m_hWnd, _T(".\\Unknown.jpg"), IDC_STA_HEAD);
	}
} // end of CContactListDlg::RefreshPersonListCtrl()

//将通讯录写入文件的函数实现
BOOL CContactListDlg::DoSaveFile(CString strFileName) {

	// 创建一个CFile对象fileGCL，选择创建模式和写模式，名称为strFileName
	CFile fileGCL(strFileName, CFile::modeWrite | CFile::modeCreate);
	
	// 定义一个与fileGCL相关的CArchive对象
	CArchive ar(&fileGCL, CArchive::store);
	// 保存通讯录数组
	m_lstPerson.Serialize(ar);

	return TRUE;
} // end of CContactListDlg::DoSaveFile()

// 从文件中读入通讯录的函数实现
BOOL CContactListDlg::DoLoadFile(CString strFileName) {

	// 定义一个CFile对象 - 读模式
	CFile fileGCL(strFileName, CFile::modeRead);
	// 定义一个与fileGCL相关联的CArchive对象
	CArchive ar(&fileGCL, CArchive::load);
	// 读通讯录数组
	m_lstPerson.Serialize(ar);
	return TRUE;

} // end of CContactListDlg::DoLoadFile()

void CContactListDlg::OnBnClickedBtnAdd()
{
	// “添加”按钮的响应函数
	// 首先声明一个联系人对象
	CPerson psnDef;
	// 声明一个编辑窗口CEditDlg对象
	CEditDlg dlgEdit(psnDef, this);
	// 接收到响应之后弹出上面创建的dlgEdit编辑窗口对象
	int iRet = dlgEdit.DoModal();	// 模态对话框 - 不关闭这个对话框，无法继续执行主窗口
	if (iRet == IDOK)
	{
		// 将联系人添加到通讯录
		// m_lstPerson是CContactListDlg.h中定义的 引用于CPersonList.h中定义的 继承于CPersons
		// (CPersons是一个typedef自主定义的CArray，其中的元素类型为CPerson)
		m_lstPerson.Add(dlgEdit.GetPerson());
		// 显示通讯录，并且选中新添加的联系人
		RefreshPersonListCtrl(m_lstPerson, m_lstPerson.GetSize() - 1);
	}
}


void CContactListDlg::OnBnClickedBtnDel()
{
	// “删除”按钮的响应函数
	// 首先取得当前选择的联系人
	int iCurSel = GetCurSel();
	if (iCurSel < 0) return;			// 如果当前没有选中联系人，就返回
	CString strHint;					// 定义一个提示信息字符串
	// 输出提示信息
	strHint.Format(_T("确定删除联系人 %s 吗？"), m_lstPerson[iCurSel].GetName());
	// 删除当前选中的联系人 - “确认删除字样是弹出对话框的标题”
	if (MessageBox(strHint, _T("确认删除"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		m_lstPerson.RemoveAt(iCurSel);
	}
	// 刷新通讯录，原先选中的行编号不变
	RefreshPersonListCtrl(m_lstPerson, iCurSel);
}


void CContactListDlg::OnBnClickedBtnEdit()
{
	// “编辑”按钮的响应函数
	// 首先取得当前的联系人 - 实际上就是取得当前联系人在数组中的编号
	int iCurSel = GetCurSel();
	if (iCurSel < 0) return;	// 如果当前没有选中联系人，就返回
	CEditDlg dlgEdit(m_lstPerson[iCurSel], this);	// 声明一个包含当前联系人信息的编辑框对象
	int iRet = dlgEdit.DoModal();	// 弹出dlgEdit设置属性
	if (iRet == IDOK)
	{
		// 更新信息
		m_lstPerson[iCurSel] = dlgEdit.GetPerson();
		RefreshPersonListCtrl(m_lstPerson, iCurSel);
	}
	else {
		RefreshPersonListCtrl(m_lstPerson, iCurSel);
	}
}


void CContactListDlg::OnBnClickedBtnBackup()
{
	// “备份”按钮响应函数
	// 定义了一个文件对话框，选择或者输入一个文件名
	// CFileDialog第一个参数如果是FALSE，代表另存为文件
	CFileDialog dlgFile(FALSE, _T(".gcl"), NULL, OFN_PATHMUSTEXIST | OFN_LONGNAMES | OFN_HIDEREADONLY
		, _T("通讯录(*.gcl) | *.gcl||"), NULL);
	// 弹出一个文件对话框 - 在没有确定之前要保持联系人列表中的选中状态
	if (dlgFile.DoModal() != IDOK)
	{
		m_lstcPersonList.SetFocus();
		return;
	}
	DoSaveFile(dlgFile.GetFileName());
}

void CContactListDlg::OnBnClickedBtnRestore()
{
	// “恢复”按钮响应函数
	// 获取一个保存了通讯录信息的文件.gcl
	// CFileDialog第一个参数如果是TRUE，代表选择文件
	CFileDialog dlgFile(TRUE, _T(".gcl"), NULL, OFN_PATHMUSTEXIST | OFN_LONGNAMES | OFN_HIDEREADONLY
		, _T("通讯录(*.gcl) | *.gcl||"), NULL);
	// 保持通讯录表格中联系人的选中状态
	if (dlgFile.DoModal() != IDOK)
	{
		m_lstcPersonList.SetFocus();
		return;
	}
	if (DoLoadFile(dlgFile.GetFileName()))
	{
		RefreshPersonListCtrl(m_lstPerson, 0);
	}
}


void CContactListDlg::OnBnClickedBtnCopy()
{
	// “复制”按钮响应函数
	int iCurSel = GetCurSel();
	if (iCurSel < 0) return;
	CPerson psnCopy = m_lstPerson[iCurSel];				// 复制联系人
	psnCopy.Duplicate();								// 修改复制之后的联系人姓名
	m_lstPerson.InsertAt(iCurSel + 1, psnCopy);			// 将复制联系人插入到当前联系人之后
	RefreshPersonListCtrl(m_lstPerson, iCurSel + 1);	// 刷新显示通讯录，并且选中新复制的联系人
}

// 为主对话框添加销毁响应事件函数
void CContactListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 一旦主对话框销毁（退出程序） - 自动保存
	DoSaveFile(m_strDefGCLFileName);	// 将通讯录保存到默认文件中

}


void CContactListDlg::OnChangeEdFind()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// 响应查找内容功能
	// 这是输入文本框的一个函数，这个函数本来在书中应该有实现内容，但是存在只能查找一个的缺陷，而且此时
	// 的“查找”按钮也没用了，因此这个函数作废，所有的实现转移到下边的“查找按钮响应函数中”
	
}


void CContactListDlg::OnBnClickedBtnFind()
{
	// “查找”按钮响应函数
	UpdateData(TRUE);
	m_lstFindPerson.RemoveAll();		// 清空上次查找的结果
	for (int i = 0; i < m_lstPerson.GetSize(); i++)
	{
		CString tempMale = m_lstPerson[i].IsMale() ? _T("男") : _T("女");
		// 如果有就添加到临时存储对象上来
		if (m_lstPerson[i].GetName().Find(m_strFind) != -1
			|| tempMale.Find(m_strFind) != -1
			|| m_lstPerson[i].GetPhoneNo().Find(m_strFind) != -1
			|| m_lstPerson[i].GetQQNo().Find(m_strFind) != -1
			|| m_lstPerson[i].GetGroupName().Find(m_strFind) != -1)
		{
			m_lstFindPerson.Add(m_lstPerson[i]);
		}
	}

	// 刷新显示查找到的结果
	RefreshPersonListCtrl(m_lstFindPerson);
}

void CContactListDlg::OnBnClickedBtnClear()
{
	// “清除内容”按钮响应函数
	m_strFind = "";
	UpdateData(FALSE);
	RefreshPersonListCtrl(m_lstPerson);
}

// 统计性别
void CContactListDlg::CountMale() {
	int iBoy = 0, iGirl = 0;
	for (int i = 0; i < m_lstPerson.GetSize(); i++)
	{
		if (m_lstPerson[i].IsMale() == 1)
		{
			iBoy++;
		}
		else
		{
			iGirl++;
		}
	}
	// 设置男生和女生的数量到static控件
	((CStatic*)GetDlgItem(IDC_STA_BOY))->SetWindowTextW(IntToString(iBoy));
	((CStatic*)GetDlgItem(IDC_STA_GIRL))->SetWindowTextW(IntToString(iGirl));
}

// 整型转换成字符串
CString CContactListDlg::IntToString(int n) {
	CString strTemp;
	strTemp.Format(_T("%d"), n);
	return strTemp;
}

void CContactListDlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnBackup();
}


void CContactListDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnRestore();
}


void CContactListDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx::OnOK();
}


void CContactListDlg::OnAdd()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnAdd();
}


void CContactListDlg::OnCopy()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnCopy();
}


void CContactListDlg::OnEdit()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnEdit();
}


void CContactListDlg::OnDel()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnDel();
}


void CContactListDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg about;
	about.DoModal();
}


void CContactListDlg::OnToolbtnAdd()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnAdd();
}


void CContactListDlg::OnToolbtnCopy()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnCopy();
}


void CContactListDlg::OnToolbtnDelete()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnDel();
}


void CContactListDlg::OnToolbtnEdit()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnEdit();
}


void CContactListDlg::OnToolbtnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg about;
	about.DoModal();
}

// 创建工具栏的函数实现
BOOL CContactListDlg::CreateToolBar() {
	// 加载工具栏资源
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||!m_ToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return false;
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	CImageList ImageList;
	ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 7, 1);
	// 设置背景颜色
	ImageList.SetBkColor(RGB(0, 0, 0));
	// 通过CBitmap类对象来加载位图作为工具栏的图标
	CBitmap bm;
	int bl = bm.LoadBitmap(IDB_BITMAP1);
	ImageList.Add(&bm, (CBitmap*)NULL);
	bm.Detach();
	m_ToolBar.GetToolBarCtrl().SetImageList(&ImageList);
	ImageList.Detach();
	return true;
}


