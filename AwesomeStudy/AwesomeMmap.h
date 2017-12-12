#pragma once
#include "Idea.h"

//get document �ϴ� �� : 
//CTestDoc *pDoc = ((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();
#define RGN_IDEA_OUT 0
#define RGN_IDEA_IN 1
#define RGN_ADD_CHILD_HND 2
#define RGN_SIZE_HND_TOPLEFT 3
#define RGN_SIZE_HND_TOPRIGHT 4
#define RGN_SIZE_HND_BTMLEFT 5
#define RGN_SIZE_HND_BTMRIGHT 6

typedef int IndexPointer;

// CAwesomeMmap ���Դϴ�.
class CMemDC;
class CIdea;

class CAwesomeMmap : public CView
{
	DECLARE_DYNCREATE(CAwesomeMmap)

	//�����Դϴ�.
public:
	BOOL m_bChangeSizeMode;
	BOOL m_bMoveMode;
	BOOL m_bAddChildMode;
	BOOL m_bLBtnPressed;
	BOOL m_bPressOnlyOneFlag;
	//CPoint m_tmpPoint1, m_tmpPoint2;
	CPoint m_mousePointInRect;
	IndexPointer m_ipParent; 
	IndexPointer m_ipChild;
	//CIdea m_ChildIdea;
	CIdea m_ParentIdea;
	CPoint m_tmpChildPnt1, m_tmpChildPnt2;
	CPoint *m_pPolyBezierPoints;
	int m_tmpX1, m_tmpX2, m_tmpY1, m_tmpY2;
	int m_nPressedFlag;
	int m_childHndX1, m_childHndY1, m_childHndX2, m_childHndY2;

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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// ���콺�� ��ü �ȿ� ��������� ����. (���� ���� �� ���� ���
	int CheckPtInIdea(CPoint point, CIdea& whichIdea);
	int CheckPtInIdea(CPoint point);
	// ����Ʈ�� ��� Idea���� m_bHighlighted�� False�� �ٲپ��ִ� �Լ�
	int SetDehighlight(CList<CIdea, CIdea&>& ideaList);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRbnInInsertIndependent();
	afx_msg void OnRbnOutInsertIndependent();
	// pos->prev�� new Idea�� ��ü�Ѵ�.
	void SetIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList, CIdea& newIdea);
	CIdea& GetIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// pos->Prev�ڸ��� ��带 �����Ѵ�.
	CIdea& DeleteIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList);
	// OnDraw �Լ��� ȣ���Ͽ� ����ϴ� ������۸��� �׸��� DC
	void DrawImage(CDC* pDC);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
};


