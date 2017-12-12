
// AwesomeStudyView.h : CAwesomeStudyView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"


class CAwesomeStudyView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CAwesomeStudyView();
	DECLARE_DYNCREATE(CAwesomeStudyView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_AWESOMESTUDY_FORM };
#endif

// 특성입니다.
public:
	CAwesomeStudyDoc* GetDocument() const;


// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CAwesomeStudyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_path;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedLogin();

	CStatic m_password;
	virtual void OnDraw(CDC* /*pDC*/);
};

#ifndef _DEBUG  // AwesomeStudyView.cpp의 디버그 버전
inline CAwesomeStudyDoc* CAwesomeStudyView::GetDocument() const
   { return reinterpret_cast<CAwesomeStudyDoc*>(m_pDocument); }
#endif

