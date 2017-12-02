#pragma once
#include "afxwin.h"



// CAwesomeWrite �� ���Դϴ�.

class CAwesomeWrite : public CFormView
{
	DECLARE_DYNCREATE(CAwesomeWrite)

public:
	CAwesomeWrite();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHome();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	CEdit m_write;
	afx_msg void OnBnClickedWriteAllclear();
	afx_msg void OnBnClickedWriteSave();
	afx_msg void OnWriteSelectall();
	afx_msg void OnBnClickedWriteClose();
	afx_msg void OnWriteUndo();
	afx_msg void OnWriteCut();
	afx_msg void OnWriteCopy();
	afx_msg void OnWritePaste();
	afx_msg void OnWriteDel();
	afx_msg void OnWriteFind();
	afx_msg void OnWriteFindnext();
	afx_msg void OnWriteReplace();
	afx_msg void OnWriteGo();
	afx_msg void OnWriteDatetime();
	afx_msg void OnWriteFontstate();
	afx_msg void OnEnChangeWrite();
	CFindReplaceDialog *pFindDlg;
	CFindReplaceDialog *pReplaceDlg;
	int m_next_start;//�˻��� ���� ����
	bool m_find_next; // �����˻� �Լ��� ����
protected:
	LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
};


