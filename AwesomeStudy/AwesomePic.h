#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "AwesomeStudyDoc.h"



// CAwesomePic �� ���Դϴ�.

class CAwesomePic : public CFormView
{
	DECLARE_DYNCREATE(CAwesomePic)

public:
	CAwesomePic();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAwesomePic();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWESOMEPIC };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CString PicNodePath;
	int IsPic;
	HTREEITEM PicNode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	afx_msg void OnHome();
	virtual void OnInitialUpdate();
	CAwesomeStudyDoc* GetDocument() const;
	CTreeCtrl m_PicTree;
	afx_msg void OnNMClickPictree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPicAddFolder();
	afx_msg void OnBnClickedPicAddFile();
	afx_msg void OnBnClickedPicDelete();
	afx_msg void OnBnClickedFileSave();
	virtual void OnDraw(CDC* pDC);
	CEdit m_PicMemo;
};


