
// ContestList.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CContestListApp:
// 有关此类的实现，请参阅 ContestList.cpp
//

class CContactListApp : public CWinApp
{
public:
	CContactListApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CContactListApp theApp;
// 对编辑框中的分组下拉框进行初始化 - 2.添加全局变量的引用
extern CStringArray g_lstGroups;