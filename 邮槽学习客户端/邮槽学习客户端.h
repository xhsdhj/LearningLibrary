
// 邮槽学习客户端.h: 邮槽学习客户端 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// C邮槽学习客户端App:
// 有关此类的实现，请参阅 邮槽学习客户端.cpp
//

class C邮槽学习客户端App : public CWinApp
{
public:
	C邮槽学习客户端App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C邮槽学习客户端App theApp;
