#pragma once
#include "Idea.h"

//get document �ϴ� �� : 
//CTestDoc *pDoc = ((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();

// CAwesomeMmap ���Դϴ�.

class CAwesomeMmap : public CView
{
	DECLARE_DYNCREATE(CAwesomeMmap)

public:
	CAwesomeMmap();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAwesomeMmap();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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
	// ���콺�� ��ü �ȿ� ��������� ����. (���� ���� �� ���� ���
	BOOL CheckPtInIdea(CPoint point);
};


