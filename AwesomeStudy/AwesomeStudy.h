
// AwesomeStudy.h : AwesomeStudy ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CAwesomeStudyApp:
// �� Ŭ������ ������ ���ؼ��� AwesomeStudy.cpp�� �����Ͻʽÿ�.
//

class CAwesomeStudyApp : public CWinApp
{
public:
	CAwesomeStudyApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAwesomeStudyApp theApp;
