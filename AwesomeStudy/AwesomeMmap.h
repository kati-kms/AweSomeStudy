#pragma once
#include "Idea.h"

//get document 하는 법 : 
//CTestDoc *pDoc = ((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();

// CAwesomeMmap 뷰입니다.

class CAwesomeMmap : public CView
{
	DECLARE_DYNCREATE(CAwesomeMmap)

public:
	CAwesomeMmap();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CAwesomeMmap();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHome();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 마우스가 객체 안에 들어있으면 변경. (리전 생성 후 제거 요망
	BOOL CheckPtInIdea(CPoint point);
};


