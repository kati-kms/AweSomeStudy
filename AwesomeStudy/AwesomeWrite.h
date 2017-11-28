#pragma once
#include "afxwin.h"



// CAwesomeWrite 폼 뷰입니다.

class CAwesomeWrite : public CFormView
{
	DECLARE_DYNCREATE(CAwesomeWrite)

public:
	CAwesomeWrite();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CAwesomeWrite();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWESOMEWRITE };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHome();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	CEdit m_write;
	afx_msg void OnBnClickedWriteAllclear();
	afx_msg void OnBnClickedWriteSave();
	afx_msg void OnWriteSelectall();
	afx_msg void OnBnClickedWriteClose();
};


