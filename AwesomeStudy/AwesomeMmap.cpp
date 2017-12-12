// AwesomeMmap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeMmap.h"
#include "AwesomeStudyDoc.h"
#include "MainFrm.h"

#include <WinUser.h>

//�ӽ� ��������
CPoint tmpPoint;
POSITION tmpPosition;
int cursorFlag = FALSE;
int tmpReturnValue = 0;

// CAwesomeMmap

IMPLEMENT_DYNCREATE(CAwesomeMmap, CView)

CAwesomeMmap::CAwesomeMmap()
{
	m_bChangeSizeMode = FALSE;
	m_bLBtnPressed = FALSE;
	m_bPressOnlyOneFlag = FALSE;
	m_bAddChildMode = FALSE;
	m_bMoveMode = FALSE;
	m_nPressedFlag = 0;
	m_mousePointInRect.SetPoint(0, 0);
	m_ChildIdea = NULL;
	m_ParentIdea = NULL;
	m_tmpChildPnt1.SetPoint(0, 0);
	m_tmpChildPnt2.SetPoint(0, 0);
}

CAwesomeMmap::~CAwesomeMmap()
{
}

BEGIN_MESSAGE_MAP(CAwesomeMmap, CView)
	ON_COMMAND(IDC_HOME, &CAwesomeMmap::OnHome)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_RBN_IN_INSERT_INDEPENDENT, &CAwesomeMmap::OnRbnInInsertIndependent)
	ON_COMMAND(ID_RBN_OUT_INSERT_INDEPENDENT, &CAwesomeMmap::OnRbnOutInsertIndependent)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CAwesomeMmap::OnUpdateFileOpen)
END_MESSAGE_MAP()


// CAwesomeMmap �׸����Դϴ�.

///TODO: �����ϸ� �� ������ ���� ���۸� �õ��غ���
void CAwesomeMmap::OnDraw(CDC* pDC)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	//CAwesomeStudyDoc * pDoc = (CAwesomeStudyDoc *)((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	CRect rect;
	GetClientRect(&rect);
	//�޸� DC�� BITMAP ����
	CDC MemDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	//�޸� DC�� ���� DC�� ���� ��ġ
	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap*)MemDC.SelectObject(&bmp);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	//�޸� DC�� �׸���
	DrawImage(&MemDC);

	//�޸� DC�� ���� DC�� ����
	pDC->BitBlt(
		0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY
	);
	
	//���� �޸�DC �� BITMAP ����
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}


// CAwesomeMmap �����Դϴ�.

#ifdef _DEBUG
void CAwesomeMmap::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeMmap::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeMmap �޽��� ó�����Դϴ�.


void CAwesomeMmap::OnHome()
{
	CMainFrame * frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CAwesomeMmap::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nHitTest == HTCLIENT) {
		CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

		CPoint point;
		POSITION pos;
		CRgn unionRgn;
		CList<CIdea, CIdea&> *tmpList = &(pDoc->m_ideaList);
		unionRgn.CreateRectRgn(0, 0, 1, 1);
		::GetCursorPos(&point);
		ScreenToClient(&point);
		cursorFlag = CheckPtInIdea(point);

		//OR ������ �ؼ� ������ �� �ϳ���� ��ġ�� �κ��� �ִٸ�
		//flag�� ���� ���� �ٸ� Ŀ���� ����� �����.
		if (cursorFlag == RGN_IDEA_IN) {
			::SetCursor((LoadCursor(NULL, IDC_SIZEALL)));
		}
		else if (cursorFlag == RGN_IDEA_OUT) {
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
		else if (cursorFlag == RGN_SIZE_HND_TOPRIGHT) {
			::SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		}
		else if (cursorFlag == RGN_SIZE_HND_BTMLEFT) {
			::SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		}
		else if (cursorFlag == RGN_SIZE_HND_BTMRIGHT) {
			::SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		}
		else if (cursorFlag == RGN_SIZE_HND_TOPLEFT) {
			::SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		}
		else if (cursorFlag == RGN_ADD_CHILD_HND) {
			::SetCursor(AfxGetApp()->LoadCursorW(IDC_ADD_CHILD));
		}
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}



void CAwesomeMmap::OnLButtonDown(UINT nFlags, CPoint point)
{
	//�� �ڵ�� ���ο� ��ü ������ ���� ������Դϴ�.
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bLBtnPressed = TRUE;
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	POSITION ideaPosition = NULL;
	CIdea selectedIdea;
	CString str;
	//TODO: selectedIdea�� �ּҰ��� �������� �� List�� �´� Idea�� �ּҰ��� �������� ���ڴ�.
	//CList�� GetNext�� ���� ���� ��¥���� �ƴ϶� ����� ��ü�� �� �ϴ�.
	//�ᱹ, SetAt(POSITION pos, ARG_TYPE newElement); �Լ��� ����ؼ� 
	//�ٽ� �� �ڸ��� Element�� newElement�� ��ü�ؾ� �� �� ����.
	//TODO: GetNext(pos)�� pos�� Element�� ��Ȯ�� ����Ű�� pos�� �ƴ϶�
	//Element�� Next�� ����Ű�� pos�̱� ������ �̿� ���� �߰����� �ڵ��� �ʿ��ϴ�
	int pointCode = CheckPtInIdea(point, selectedIdea);
	//���õ� ���̵�Ƹ� Head�� ������ ���´�.


	/*
	//debug
	if (pointCode == 0)
		str.Format(_T("RGN_IDEA_OUT\n"));
	else if (pointCode == 1)
		str.Format(_T("RGN_IDEA_IN\n"));
	else if (pointCode == 2)
		str.Format(_T("RGN_ADD_CHILD_HND\n"));
	else if (pointCode == 3)
		str.Format(_T("RGN_SIZE_HND_TOPLEFT\n"));
	else if (pointCode == 4)
		str.Format(_T("RGN_SIZE_HND_TOPRIGHT\n"));
	else if (pointCode == 5)
		str.Format(_T("RGN_SIZE_HND_BTMLEFT\n"));
	else if (pointCode == 6)
		str.Format(_T("RGN_SIZE_HND_BTMRIGHT\n"));
	str.Append(selectedIdea.StringOutIdea());
	AfxMessageBox(str);
	//debug_end
	*/


	//CheckPtInIdea(point) -->
	//Idea in�� ��� : ���� ���� ������ FALSE��, 
	//������ �༮�� m_bHighlight�� True�� ����
	if (pointCode == RGN_IDEA_IN /*&& &selectedIdea != NULL*/) {
		SetDehighlight(pDoc->m_ideaList);
		selectedIdea.SetHighlight(TRUE);

		//���콺 ������ �� �����̵��� nPressedFlag�� ���� ������Ų��.
		if (m_bPressOnlyOneFlag == TRUE) {
			m_bPressOnlyOneFlag = FALSE;
			m_nPressedFlag = cursorFlag;
			m_bMoveMode = TRUE;
			m_mousePointInRect = point - selectedIdea.m_ideaRect.TopLeft();
		}
		//SetAt(POSITION, ARG_TYPE)�� ȣ���Ͽ� ������ ������ ideaPosition ������
		//Prev���� �� �� Element�̱� ������ ideaPosition.Prev�� �ڸ��� selectedIdea�� 
		//����ִ´�.
		//ToDO:�ƴ�! ���õ� Idea�� Head�� �÷���� �Ѵ�. ��, ���� Idea�� �ִ� �ڸ��� ����
		//�����ϰ� �̰� Head���ٰ� �����ָ� �ǰڴ�
		//SetIdea(tmpPosition, pDoc->m_ideaList, selectedIdea);
		DeleteIdea(tmpPosition, pDoc->m_ideaList);
		pDoc->m_ideaList.AddHead(selectedIdea);

		pDoc->SetModifiedFlag();
		Invalidate();
	}

	//Idea out�� ��� : ��� ����� m_bHighlight�� False�� ����
	if (pointCode == RGN_IDEA_OUT) {
		CList<CIdea, CIdea&> *ideaList = &pDoc->m_ideaList;
		POSITION pos = ideaList->GetHeadPosition();
		SetDehighlight(pDoc->m_ideaList);
		//while (pos != NULL) {
		//CIdea tmpIdea;
		//	tmpIdea = ideaList->GetNext(pos);
		//	if (tmpIdea.m_bHighlighted) {
		//
		//		//debug
		//		CString str;
		//		str.Format(_T("string : \"%d\" was dehighlighted."), tmpIdea.m_ideaString);
		//		AfxMessageBox(str);
		//		//debug_end
		//
		//		tmpIdea.m_bHighlighted = FALSE;
		//	}
		//}
		pDoc->SetModifiedFlag();
		Invalidate();
	}

	//Size Handle�� ��� : 4���� ���
	//������ ��쿡 ���� ������ OnMouseMove���� ó���Ѵ�.
	if (pointCode == RGN_SIZE_HND_BTMLEFT || pointCode == RGN_SIZE_HND_BTMRIGHT
		|| pointCode == RGN_SIZE_HND_TOPLEFT || pointCode == RGN_SIZE_HND_TOPRIGHT)
		if (m_bPressOnlyOneFlag == TRUE) {
			m_bPressOnlyOneFlag = FALSE;
			m_nPressedFlag = pointCode;
			m_bChangeSizeMode = TRUE;
		}
	//else { m_bChangeSizeMode = FALSE; }

	//Add Child Handle�� ���
	if (pointCode == RGN_ADD_CHILD_HND) {
		if (m_bPressOnlyOneFlag == TRUE) {
			m_bPressOnlyOneFlag = FALSE;
			m_nPressedFlag = pointCode;
			m_bAddChildMode = TRUE;

			m_ipParent = selectedIdea.m_ipSelfNode;
			m_ParentIdea = &selectedIdea;
			m_tmpChildPnt1 = CPoint(point.x - 50, point.y - 50);
			m_tmpChildPnt2 = CPoint(point.x + 50, point.y + 50);
		}
	}

	/////////////////////////////////////////////
	//�� �ڵ�� ���� ��ư Ŭ���� ���Ƿ� �� Idea�� �����ϴ� �ڵ��,
	//���� ������� �����Ƿ� �ּ�ó���մϴ�.
	//CRect newRect(point.x - 50, point.y - 50, point.x + 50, point.y + 50);
	//CString newStr;
	//newStr.Format(_T("[%d,%d]"), point.x, point.y);

	//CIdea newIdea(newRect, newStr);
	//pDoc->m_ideaList.AddTail(newIdea);
	//pDoc->SetModifiedFlag();

	//Invalidate();
	////////////////////////////////////////////////
	CView::OnLButtonDown(nFlags, point);
}

void CAwesomeMmap::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	CIdea *thisIdea = &GetIdea(tmpPosition, pDoc->m_ideaList);
	CClientDC dc(this);
	CPoint roundPoint;
	CPoint *bezierPnts = (CPoint*) malloc(3 * sizeof(CPoint));
	CRect drawRect;
	//debug --------------------------------------------------------
	CClientDC debugDc(this);
	CString str;
	CString tmpStr;
	CRect debugRect;
	GetClientRect(&debugRect);
	int pointCode = cursorFlag;
	if (pointCode == 0)
		str.Format(_T("RGN_IDEA_OUT\n"));
	else if (pointCode == 1)
		str.Format(_T("RGN_IDEA_IN\n"));
	else if (pointCode == 2)
		str.Format(_T("RGN_ADD_CHILD_HND\n"));
	else if (pointCode == 3)
		str.Format(_T("RGN_SIZE_HND_TOPLEFT\n"));
	else if (pointCode == 4)
		str.Format(_T("RGN_SIZE_HND_TOPRIGHT\n"));
	else if (pointCode == 5)
		str.Format(_T("RGN_SIZE_HND_BTMLEFT\n"));
	else if (pointCode == 6)
		str.Format(_T("RGN_SIZE_HND_BTMRIGHT\n"));
	str.Append(GetIdea(tmpPosition, pDoc->m_ideaList).StringOutIdea());
	tmpStr.Format(_T("\n���� ����Ʈ ���� : %d\n"), pDoc->m_ideaList.GetCount());
	str.Append(tmpStr);
	debugDc.DrawText(str, debugRect, 0);
	//debug_end--------------------------------------------------------



	// ������ �������� ����ؼ� ���콺�� ���� �簢���� ������ �ִ� �ڵ��� �������� �� ��ġ�� stretch ��Ų��.
	// �׸��°� ���⿡�� ����.
	if (m_bChangeSizeMode)
	{
		drawRect.SetRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		roundPoint.SetPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);

		dc.SelectStockObject(NULL_BRUSH);
		//������ �׸� �簢���� �����.
///TODO : �� ������ �׸� �簢���� �������� ����?
		dc.SetROP2(R2_NOT);
		dc.RoundRect(drawRect, roundPoint);
		m_tmpX1 = thisIdea->m_ideaRect.left;
		m_tmpY1 = thisIdea->m_ideaRect.top;
		m_tmpX2 = thisIdea->m_ideaRect.right;
		m_tmpY2 = thisIdea->m_ideaRect.bottom;

		drawRect.SetRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		roundPoint.SetPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);


		//���ο� �簢���� �׸���.
		dc.SetROP2(R2_NOT);
		if (m_nPressedFlag == RGN_SIZE_HND_BTMRIGHT) {
			m_tmpX2 = point.x;
			m_tmpY2 = point.y;
		}
		else if (m_nPressedFlag == RGN_SIZE_HND_BTMLEFT) {
			m_tmpX1 = point.x;
			m_tmpY2 = point.y;
		}
		else if (m_nPressedFlag == RGN_SIZE_HND_TOPLEFT) {
			m_tmpX1 = point.x;
			m_tmpY1 = point.y;
		}
		else if (m_nPressedFlag == RGN_SIZE_HND_TOPRIGHT) {
			m_tmpX2 = point.x;
			m_tmpY1 = point.y;
		}
		drawRect.SetRectEmpty();
		drawRect.SetRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		roundPoint.SetPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);
		dc.RoundRect(drawRect, roundPoint);
		//thisIdea.SetRect(drawRect);
		//SetIdea(tmpPosition, pDoc->m_ideaList, thisIdea);

		m_bChangeSizeMode = TRUE;
	}

	//�̰Ŵ� ���� �����̰� �ؾ߰ڴ�
	if (m_bMoveMode) {
		thisIdea->m_ideaRect.MoveToXY(
			point.x - m_mousePointInRect.x,
			point.y - m_mousePointInRect.y
		);
		SetIdea(tmpPosition, pDoc->m_ideaList, *thisIdea);

		Invalidate();
	}

	//add child Handle
	if (m_bAddChildMode) 
	{
		//TODO: ��� �� �׷�����
		//BezierLine, Rect �� �ΰ����� �����ٰ� �ٽ� �׸��� �ɷ� ����
		bezierPnts[0] = m_ParentIdea->m_ideaRect.CenterPoint();
		bezierPnts[1] = CPoint(m_tmpX1, m_ParentIdea->m_ideaRect.CenterPoint().y);
		bezierPnts[2] = CPoint(m_tmpX1, m_tmpY1);
		drawRect.SetRect(m_tmpChildPnt1, m_tmpChildPnt2);
		roundPoint.SetPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);

		dc.SelectStockObject(NULL_BRUSH);
		//������ �׸� �簢���� ��� �����
		dc.SetROP2(R2_NOT);
		dc.PolyBezier(bezierPnts, 3);
		dc.RoundRect(drawRect, roundPoint);

		m_tmpChildPnt1 = CPoint(point.x - 50, point.y - 50);
		m_tmpChildPnt2 = CPoint(point.x + 50, point.y + 50);
		m_tmpX1 = point.x;
		m_tmpY1 = point.y;
		bezierPnts[1].x = m_tmpX1;
		bezierPnts[2] = (m_tmpX1, m_tmpY1);

		//���ο� �簢���� ��� �׸���
		dc.SetROP2(R2_NOT);
		dc.PolyBezier(bezierPnts, 3);

		drawRect.SetRectEmpty();
		drawRect.SetRect(m_tmpChildPnt1, m_tmpChildPnt2);
		roundPoint.SetPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);
		dc.RoundRect(drawRect, roundPoint);

		m_bAddChildMode = TRUE;
	}

	CView::OnMouseMove(nFlags, point);
}



// ���콺�� ��ü �ȿ� ��������� ����. (���� ���� �� ���� ���
int CAwesomeMmap::CheckPtInIdea(CPoint point, CIdea& whichIdea)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRgn topLeftRgn, topRightRgn, btmLeftRgn, btmRightRgn;
	CRgn addChildHandleRgn;
	tmpPosition = (pDoc->m_ideaList.GetHeadPosition());

	while (tmpPosition != NULL)
	{
		//TODO : CIdea* whichIdea�� list.GetNext()�� ������ ��ü�� �ּҸ� 
		//�Ѱ��ְ� ������..(�׷��� �ؾ� CheckPtInIdea�Լ��� ȣ���� ������ whichIdea�� ������
		//�ٲپ�� ����Ʈ �ȿ� �ִ� ��¥ ��ü�� �ٲ���)
		whichIdea = (pDoc->m_ideaList.GetNext(tmpPosition));
		whichIdea.DeleteIdeaRgn();
		///Region = Idea in = 1
		//���� ���� �� �� PtInRgn�� TRUE���
		if (whichIdea.MakeIdeaRgn().PtInRegion(point) == TRUE)
		{
			//debugstart
			//CString str;
			//str.Format(_T("tmpIdea->m_ideaString : "));
			//str.Append(tmpIdea->m_ideaString);
			//	AfxMessageBox(str);
			//	//debugend
			return RGN_IDEA_IN;
		}

		///Region = Idea Size Handle = 3 ~ 6
		///Region = Idea Add Child Handle = 2
		//Ȱ��ȭ�� �Ǿ��ִ� ��� --> 
		//{ size handle�� ���� ���� ���� �� PtInRegion(point)
		// , �Ǵ� Add Child Handle�� ���� ���� ���� �� PtInRegion(point) }
		if (whichIdea.m_bHighlighted) {
			int tmpReturnValue = 0;
			//sizeHandleRgn * 4
			topLeftRgn.CreateRectRgn(
				whichIdea.m_ideaRect.left - szhnd
				, whichIdea.m_ideaRect.top - szhnd
				, whichIdea.m_ideaRect.left + szhnd
				, whichIdea.m_ideaRect.top + szhnd
			);
			topRightRgn.CreateRectRgn(
				whichIdea.m_ideaRect.right - szhnd
				, whichIdea.m_ideaRect.top - szhnd
				, whichIdea.m_ideaRect.right + szhnd
				, whichIdea.m_ideaRect.top + szhnd
			);
			btmLeftRgn.CreateRectRgn(
				whichIdea.m_ideaRect.left - szhnd
				, whichIdea.m_ideaRect.bottom - szhnd
				, whichIdea.m_ideaRect.left + szhnd
				, whichIdea.m_ideaRect.bottom + szhnd
			);
			btmRightRgn.CreateRectRgn(
				whichIdea.m_ideaRect.right - szhnd
				, whichIdea.m_ideaRect.bottom - szhnd
				, whichIdea.m_ideaRect.right + szhnd
				, whichIdea.m_ideaRect.bottom + szhnd
			);
			//addChildHandleRgn
			addChildHandleRgn.CreateRectRgn(m_childHndX1, m_childHndY1,
				m_childHndX2, m_childHndY2);


			//���콺�� �̹� ������ �ִ� ���¶�� ������Ų��.
			if (topLeftRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_TOPLEFT;
			}
			else if (topRightRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_TOPRIGHT;
			}
			else if (btmLeftRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_BTMLEFT;
			}
			else if (btmRightRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_BTMRIGHT;
			}
			else if (addChildHandleRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_ADD_CHILD_HND;
			}
			//sizeHandleRgn Delete
			topLeftRgn.DeleteObject();
			topRightRgn.DeleteObject();
			btmLeftRgn.DeleteObject();
			btmRightRgn.DeleteObject();
			//addChildHandleRgn Delete
			addChildHandleRgn.DeleteObject();

			return tmpReturnValue;
		}
	}

	///Region = Idea out = 0
	//�̰� ���� �������� �ؾ߰ڴ�. ���� �� �ƴ� ���
	return RGN_IDEA_OUT;
}

int CAwesomeMmap::CheckPtInIdea(CPoint point)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRgn topLeftRgn, topRightRgn, btmLeftRgn, btmRightRgn;
	CRgn addChildHandleRgn;
	//����� �� �Լ��� CIdea ������ ������� �ʴ´�.
	CIdea whichIdea;
	return CAwesomeMmap::CheckPtInIdea(point, whichIdea);
	//������ �����ε��� �Լ��� �ϳ��� ���� �ٸ� �Լ����� ������ ���� �ǰڱ���
	/* 
	POSITION pos = pDoc->m_ideaList.GetHeadPosition();

	while (pos != NULL)
	{
		//TODO : CIdea* whichIdea�� list.GetNext()�� ������ ��ü�� �ּҸ� 
		//�Ѱ��ְ� ������..(�׷��� �ؾ� CheckPtInIdea�Լ��� ȣ���� ������ whichIdea�� ������
		//�ٲپ�� ����Ʈ �ȿ� �ִ� ��¥ ��ü�� �ٲ���)
		whichIdea = &pDoc->m_ideaList.GetNext(pos);
		whichIdea->DeleteIdeaRgn();
		///Region = Idea in = 1
		//���� ���� �� �� PtInRgn�� TRUE���
		//���콺�� �����ִ� ���¶�� ���� ���¸� ��� �����Ѵ�.
		//�ڽ��� �����̰� �ִ��� ũ���ڵ��� ������ �����δٴ���
		if (whichIdea->MakeIdeaRgn().PtInRegion(point) == TRUE)
		{
			//debugstart
			//CString str;
			//str.Format(_T("tmpIdea->m_ideaString : "));
			//str.Append(tmpIdea->m_ideaString);
			//	AfxMessageBox(str);
			//	//debugend
			return RGN_IDEA_IN;
		}

		///Region = Idea Size Handle = 3 ~ 6
		///Region = Idea Add Child Handle = 2
		//Ȱ��ȭ�� �Ǿ��ִ� ��� --> 
		//{ size handle�� ���� ���� ���� �� PtInRegion(point)
		// , �Ǵ� Add Child Handle�� ���� ���� ���� �� PtInRegion(point) }
		if (whichIdea->m_bHighlighted) {
			tmpReturnValue = 0;
			//sizeHandleRgn * 4
			topLeftRgn.CreateRectRgn(
				whichIdea->m_ideaRect.left - szhnd
				, whichIdea->m_ideaRect.top - szhnd
				, whichIdea->m_ideaRect.left + szhnd
				, whichIdea->m_ideaRect.top + szhnd
			);
			topRightRgn.CreateRectRgn(
				whichIdea->m_ideaRect.right - szhnd
				, whichIdea->m_ideaRect.top - szhnd
				, whichIdea->m_ideaRect.right + szhnd
				, whichIdea->m_ideaRect.top + szhnd
			);
			btmLeftRgn.CreateRectRgn(
				whichIdea->m_ideaRect.left - szhnd
				, whichIdea->m_ideaRect.bottom - szhnd
				, whichIdea->m_ideaRect.left + szhnd
				, whichIdea->m_ideaRect.bottom + szhnd
			);
			btmRightRgn.CreateRectRgn(
				whichIdea->m_ideaRect.right - szhnd
				, whichIdea->m_ideaRect.bottom - szhnd
				, whichIdea->m_ideaRect.right + szhnd
				, whichIdea->m_ideaRect.bottom + szhnd
			);

			//
			if (topLeftRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_TOPLEFT;
			}
			else if (topRightRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_TOPRIGHT;
			}
			else if (btmLeftRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_BTMLEFT;
			}
			else if (btmRightRgn.PtInRegion(point)) {
				tmpReturnValue = RGN_SIZE_HND_BTMRIGHT;
			}
			//sizeHandleRgn Delete
			topLeftRgn.DeleteObject();
			topRightRgn.DeleteObject();
			btmLeftRgn.DeleteObject();
			btmRightRgn.DeleteObject();

			//����� �巡�׽� �۵��ϴ°� ���⿡�� �������� �ʴ´�.
			//OnMouseMove �Լ����� ���콺�� �巡�� �ϰ� �ִµ� m_ideaRect.CenterPoint()�� �߽�����
			//4�и����� �����������ϱ� �׶����� ����ϸ� �ȴ�.

			//addChildHandleRgn

			//addChildHandleRgn Delete


			return tmpReturnValue;
		}
	}
	///Region = Idea out = 0
	//�̰� ���� �������� �ؾ߰ڴ�. ���� �� �ƴ� ���
	return RGN_IDEA_OUT;
	*/
}


// ����Ʈ�� ��� Idea���� m_bHighlighted�� False�� �ٲپ��ִ� �Լ�
int CAwesomeMmap::SetDehighlight(CList<CIdea, CIdea&>& ideaList)
{
	int count = 0;
	POSITION pos = ideaList.GetHeadPosition();
	CIdea *tmpIdea;
	while (pos != NULL) {
		tmpIdea = &ideaList.GetNext(pos);
		//debug
		//CString str;
		//str.Format(_T("%s.m_bHighlight : %d"), tmpIdea.m_ideaString, tmpIdea.m_bHighlighted);
		//AfxMessageBox(str);
		//debug_end

		if (tmpIdea->m_bHighlighted) {
			tmpIdea->m_bHighlighted = FALSE;
			SetIdea(pos, ideaList, *tmpIdea);
			count++;
		}
	}

	//tmpPosition = NULL;

	return count;
}


void CAwesomeMmap::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CMenu menu;
	CMenu* pMenu;
	ScreenToClient(&point);
	int ideaOption = CheckPtInIdea(point);
	menu.LoadMenu(IDR_MMAP_CNTXT);
	if (ideaOption == RGN_IDEA_IN) {
		//�ӽ����������� point�� ����ִ´�.
		tmpPoint = point;
		ClientToScreen(&point);
		pMenu = menu.GetSubMenu(RGN_IDEA_IN);
		pMenu->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y, AfxGetMainWnd()
		);
	}
	else if (ideaOption == RGN_IDEA_OUT) {
		//�ӽ����������� point�� ����ִ´�.
		tmpPoint = point;
		ClientToScreen(&point);
		pMenu = menu.GetSubMenu(RGN_IDEA_OUT);
		pMenu->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y, AfxGetMainWnd()
		);
	}

}


void CAwesomeMmap::OnRbnInInsertIndependent()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRect newRect(tmpPoint.x - 50, tmpPoint.y - 50, tmpPoint.x + 50, tmpPoint.y + 50);
	CString newStr;
	newStr.Format(_T("[%d,%d]"), tmpPoint.x, tmpPoint.y);

	CIdea newIdea(newRect, newStr);
	newIdea.NewIdea();
	pDoc->m_ideaList.AddHead(newIdea);
	pDoc->SetModifiedFlag();

	Invalidate();
}


void CAwesomeMmap::OnRbnOutInsertIndependent()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRect newRect(tmpPoint.x - 50, tmpPoint.y - 50, tmpPoint.x + 50, tmpPoint.y + 50);
	CString newStr;
	newStr.Format(_T("[%d,%d]"), tmpPoint.x, tmpPoint.y);

	CIdea newIdea(newRect, newStr);
	newIdea.NewIdea();
	pDoc->m_ideaList.AddHead(newIdea);
	pDoc->SetModifiedFlag();

	Invalidate();
}


// pos->prev�� new Idea�� ��ü�Ѵ�.
void CAwesomeMmap::SetIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList, CIdea& newIdea)
{
	//������ ����(tail)�� �ִ� ��� pos�� nullptr�� ��찡 �ִ�!!!
	//������ �ذ��� �� �ִ�. pos�� nullptr�� ��쿡�� tail�� ����Ű�� �ȴ�.
	if (pos == 0) {
		pos = ideaList.GetTailPosition();
		ideaList.SetAt(pos, newIdea);
		return;
	}
	ideaList.GetPrev(pos);
	ideaList.SetAt(pos, newIdea);
	return;
}

// �� �״�� get idea�մϴ�.
CIdea& CAwesomeMmap::GetIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	if (pos == 0) {
		pos = ideaList.GetTailPosition();
		return ideaList.GetAt(pos);
	}
	ideaList.GetPrev(pos);
	return ideaList.GetAt(pos);
}



void CAwesomeMmap::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	CClientDC dc(this);
	m_bLBtnPressed = FALSE;
	m_bPressOnlyOneFlag = TRUE;
	m_nPressedFlag = 0;

	//Change Size Mode
	if (m_bChangeSizeMode) {
		m_bChangeSizeMode = FALSE;
		CRect drawRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		CPoint roundPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);
		CIdea *newIdea = &GetIdea(tmpPosition, pDoc->m_ideaList);

		//�簢�� �����
		dc.SetROP2(R2_NOT);
		dc.RoundRect(drawRect, roundPoint);

		//�������� �簢���� Rect�� ����ְ� SetIdea��Ų��.
		newIdea->SetRect(drawRect);
		SetIdea(tmpPosition, pDoc->m_ideaList, *newIdea);

		m_mousePointInRect.SetPoint(0, 0);
		pDoc->SetModifiedFlag();
		Invalidate();
	}

	//Move Mode
	if (m_bMoveMode) {
		m_bMoveMode = FALSE;
	}

	//Add Child Mode
	if (m_bAddChildMode) {
		m_bAddChildMode = FALSE;
		//TODO: ���ο� Child�� �����Ͽ� ����, �ε����� ���� ������.
		CString str;
		str.Format(_T("[%d, %d]"), point.x, point.y);
		AfxMessageBox(str);
		CRect rect(m_tmpChildPnt1, m_tmpChildPnt2);
		CIdea newIdea(rect, str, m_ParentIdea);
		pDoc->m_ideaList.AddHead(newIdea);

		//TODO: m_ipParent�� m_ipChild �ʱ�ȭ
		m_ipParent = m_ipChild = 0;

		//
		pDoc->SetModifiedFlag();
		Invalidate();
	}

	m_tmpX1 = m_tmpX2 = m_tmpY1 = m_tmpY2 = 0;
	CView::OnLButtonUp(nFlags, point);
}


// pos->Prev�ڸ��� ��带 �����Ѵ�.
//���� ������� ��尡 Tail�̶� pos�� NULL�� ���,
//Tail�� �����
CIdea& CAwesomeMmap::DeleteIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	CIdea* tmpIdea;
	if (pos == NULL) {
		return ideaList.RemoveTail();
	}
	ideaList.GetPrev(pos);
	tmpIdea = &ideaList.GetAt(pos);
	ideaList.RemoveAt(pos);
	return *tmpIdea;
}


// OnDraw �Լ��� ȣ���Ͽ� ����ϴ� ������۸��� �׸��� DC
void CAwesomeMmap::DrawImage(CDC* pDC)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	POSITION pos;
	CIdea *ideas;
	CBrush ideaBrush;
	CPen ideaPen;
	CPoint roundPoint;
	CList<CIdea, CIdea&> *ideaList = &(pDoc->m_ideaList);
	CBitmap acBitmap;	//Add Child -> ac
	int r, g, b;
	double rndX, rndY;
	const double brightRate = 0.50;
	int pointCode = cursorFlag;

	//DEBUG//////////////////////////////////////////////////////////////
	//���ݱ��� ������ �ִ� ��� ����Ʈ�� Idea���� 
	//���� Ŭ���̾�Ʈ�� ����Ѵ�.
	CClientDC dc(this);
	CString masterStr;
	CString semiStr;
	CRect debugRect(0, 100, 200, 500);
	pos = ideaList->GetHeadPosition();
	while (pos != NULL) {
		ideas = &ideaList->GetNext(pos);
		semiStr.Format(_T("m_ideaRect.CenterPoint() : (%d, %d)\n"), ideas->m_ideaRect.CenterPoint().x,
			ideas->m_ideaRect.CenterPoint().y);
		masterStr.Append(semiStr);
		semiStr.Format(_T("m_ideaString : %s\n"), ideas->m_ideaString);
		masterStr.Append(semiStr);

		semiStr.Format(_T("m_ipSelfNode : %d\n"), ideas->m_ipSelfNode);
		masterStr.Append(semiStr);
		semiStr.Format(_T("m_ipParentNode : %d\n"), ideas->m_ipParentNode);
		masterStr.Append(semiStr);
		semiStr.Format(_T("m_ipChildNode : %d\n"), ideas->m_ipLeftChild);
		masterStr.Append(semiStr);
		semiStr.Format(_T("m_ipSiblingNode : %d\n"), ideas->m_ipRightSibling);
		masterStr.Append(semiStr);

		masterStr.Append(_T("\n\n"));
	}
	dc.DrawText(masterStr, &debugRect, DT_LEFT);

	//DEBUG//////////////////////////////////////////////////////////////


	//Idea ��ü ���̱�
	//�μ��� �� Tail���� �ݴ�� �μ��ؾ߰ڴ�.
	//�ֳĸ� ��������� �ڴʰ� �μ�� Idea�� �ٸ� Idea�� ������ ���,
	//��ģ �κ��� Ŭ������ �� �ڴʰ� �μ�� Idea�� �Ǿ�� �ϱ� �����̴�.
	pos = ideaList->GetTailPosition();
	while (pos != NULL) {
		ideas = &ideaList->GetPrev(pos);
		//debug
		//CString str;
		//str.Format(_T("%d, %d, %d"), GetRValue(ideas.m_ideaColor), GetGValue(ideas.m_ideaColor), GetBValue(ideas.m_ideaColor));
		//AfxMessageBox(str);

		//round value to each of Ideas
		rndX = ideas->m_ideaRect.Width() * roundRate;
		rndY = ideas->m_ideaRect.Height() * roundRate;
		roundPoint.SetPoint(rndX, rndY);

		//debug
		/*
		CString str;
		str.Format(_T("%d, %d"), ideas.m_ideaRect.left, ideas.m_ideaRect.bottom);
		AfxMessageBox(str);
		*/

		//brush
		ideaBrush.DeleteObject();
		ideaBrush.CreateSolidBrush(ideas->m_ideaColor);
		//darker pen
		r = GetRValue(ideas->m_ideaColor);
		g = GetGValue(ideas->m_ideaColor);
		b = GetBValue(ideas->m_ideaColor);

		r = r - r * brightRate;
		g = g - g * brightRate;
		b = b - b * brightRate;
		ideaPen.DeleteObject();
		ideaPen.CreatePen(PS_SOLID, 4, RGB((int)r, (int)g, (int)b));

		pDC->SelectObject(ideaBrush);
		pDC->RoundRect(ideas->m_ideaRect, roundPoint);
		pDC->SelectObject(ideaPen);
		pDC->RoundRect(ideas->m_ideaRect, roundPoint);
		ideaBrush.DeleteObject();
		//text
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(ideas->m_ideaString, ideas->m_ideaRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		//size handle & add child handle
		if (ideas->m_bHighlighted == TRUE) {
			ideaPen.DeleteObject();
			ideaPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			pDC->SelectStockObject(NULL_BRUSH);
			pDC->SelectObject(ideaPen);

			pDC->Rectangle(
				ideas->m_ideaRect.left - szhnd, ideas->m_ideaRect.top - szhnd
				, ideas->m_ideaRect.left + szhnd, ideas->m_ideaRect.top + szhnd
			);
			pDC->Rectangle(
				ideas->m_ideaRect.right - szhnd, ideas->m_ideaRect.top - szhnd
				, ideas->m_ideaRect.right + szhnd, ideas->m_ideaRect.top + szhnd
			);
			pDC->Rectangle(
				ideas->m_ideaRect.left - szhnd, ideas->m_ideaRect.bottom - szhnd,
				ideas->m_ideaRect.left + szhnd, ideas->m_ideaRect.bottom + szhnd
			);
			pDC->Rectangle(
				ideas->m_ideaRect.right - szhnd, ideas->m_ideaRect.bottom - szhnd
				, ideas->m_ideaRect.right + szhnd, ideas->m_ideaRect.bottom + szhnd
			);
			ideaPen.DeleteObject();


			//Add Child Handle
			acBitmap.LoadBitmapW(IDB_ADD_CHILD);
			BITMAP acBmpInfo;
			acBitmap.GetBitmap(&acBmpInfo);
			//�޸� DC�� ���� �� ��Ʈ���� ������ �ִ´�.
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&acBitmap);

			//��Ʈ�� ȭ�����
			m_childHndX1 = ideas->m_ideaRect.right + 5;
			m_childHndY1 = ideas->m_ideaRect.CenterPoint().y - 6;
			m_childHndX2 = m_childHndX1 + acBmpInfo.bmWidth / 2;
			m_childHndY2 = m_childHndY1 + acBmpInfo.bmHeight / 2;
			pDC->StretchBlt(m_childHndX1, m_childHndY1,
				acBmpInfo.bmWidth / 2, acBmpInfo.bmHeight / 2, &dcmem, 0, 0, 
				acBmpInfo.bmWidth, acBmpInfo.bmHeight ,SRCCOPY);
			
		}

	}
}


void CAwesomeMmap::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndMmap) {
		pCmdUI->Enable(0);
	}
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
