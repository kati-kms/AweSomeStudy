
// AwesomeStudyView.h : CAwesomeStudyView Ŭ������ �������̽�
//

#pragma once
#include "afxwin.h"


class CAwesomeStudyView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CAwesomeStudyView();
	DECLARE_DYNCREATE(CAwesomeStudyView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_AWESOMESTUDY_FORM };
#endif

// Ư���Դϴ�.
public:
	CAwesomeStudyDoc* GetDocument() const;


// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CAwesomeStudyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_path;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedLogin();

	CStatic m_password;
	virtual void OnDraw(CDC* /*pDC*/);
};

#ifndef _DEBUG  // AwesomeStudyView.cpp�� ����� ����
inline CAwesomeStudyDoc* CAwesomeStudyView::GetDocument() const
   { return reinterpret_cast<CAwesomeStudyDoc*>(m_pDocument); }
#endif

