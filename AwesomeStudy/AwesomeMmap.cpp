// AwesomeMmap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeMmap.h"
#include "AwesomeStudyDoc.h"
#include "MainFrm.h"


// CAwesomeMmap

IMPLEMENT_DYNCREATE(CAwesomeMmap, CView)

CAwesomeMmap::CAwesomeMmap()
{

}

CAwesomeMmap::~CAwesomeMmap()
{
}

BEGIN_MESSAGE_MAP(CAwesomeMmap, CView)
	ON_COMMAND(IDC_HOME, &CAwesomeMmap::OnHome)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CAwesomeMmap �׸����Դϴ�.

void CAwesomeMmap::OnDraw(CDC* pDC)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	//CAwesomeStudyDoc * pDoc = (CAwesomeStudyDoc *)((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	POSITION pos;
	CIdea ideas, ideas1;
	CBrush ideaBrush;
	CPen ideaPen;
	CPoint roundPoint;
	CList<CIdea, CIdea&>  *ideaList = &(pDoc->m_ideaList);
	int r, g, b;
	double rndX, rndY;
	const double brightRate = 0.80;

	//Idea ��ü ���̱�
	pos = ideaList->GetHeadPosition();
	while (pos != NULL) {
		ideas = ideaList->GetNext(pos);
		//debug
		//CString str;
		//str.Format(_T("%d, %d, %d"), GetRValue(ideas.m_ideaColor), GetGValue(ideas.m_ideaColor), GetBValue(ideas.m_ideaColor));
		//AfxMessageBox(str);

		//round value to each of Ideas
		rndX = ideas.m_ideaRect.Width() * roundRate;
		rndY = ideas.m_ideaRect.Height() * roundRate;
		roundPoint.SetPoint(rndX, rndY);

		//debug
		/*
		CString str;
		str.Format(_T("%d, %d"), ideas.m_ideaRect.left, ideas.m_ideaRect.bottom);
		AfxMessageBox(str);
		*/

		//brush
		ideaBrush.DeleteObject();
		ideaBrush.CreateSolidBrush(ideas.m_ideaColor);
		//darker pen
		r = GetRValue(ideas.m_ideaColor);
		g = GetGValue(ideas.m_ideaColor);
		b = GetBValue(ideas.m_ideaColor);

		r = r - r * brightRate;
		g = g - g * brightRate;
		b = b - b * brightRate;
		ideaPen.DeleteObject();
		ideaPen.CreatePen(PS_SOLID, 4, RGB((int)r, (int)g, (int)b));

		pDC->SelectObject(ideaBrush);
		pDC->RoundRect(ideas.m_ideaRect, roundPoint);
		pDC->SelectObject(ideaPen);
		pDC->RoundRect(ideas.m_ideaRect, roundPoint);
		//text
		pDC->SetBkColor(ideas.m_ideaColor);
		pDC->DrawText(ideas.m_ideaString, ideas.m_ideaRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
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

		BOOL cursorFlag = FALSE;
		CPoint point;
		POSITION pos;
		CIdea tmpIdea;
		CRgn unionRgn;
		CList<CIdea, CIdea&> *tmpList = &(pDoc->m_ideaList);
		unionRgn.CreateRectRgn(0, 0, 1, 1);
		::GetCursorPos(&point);
		ScreenToClient(&point);

		//OR ������ �ؼ� ������ �� �ϳ���� ��ġ�� �κ��� �ִٸ�
		//flag�� TRUE�� �ؼ� break, 
		//flag�� TRUE�̸� ���콺 Ŀ���� ����� �ٲ۴�.
		if (CheckPtInIdea(point)) {
			::SetCursor((LoadCursor(NULL, IDC_SIZEALL)));
		}
		else {
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
		

		/*
		pos = m_pDoc->m_ideaList.GetHeadPosition();
		while (pos != NULL) {
			tmpIdea = tmpList->GetNext(pos);
			//������ �ϳ��� ���Ĺ�����.
			unionRgn.CombineRgn(&unionRgn, &tmpIdea.m_ideaRegion, RGN_OR);
		}

		//���콺�� ������ �����յ� ���̿� �����Ѵٸ�
		if (unionRgn.PtInRegion(point)) {
			::SetCursor(AfxGetApp()->LoadCursorW(IDC_ADD));
		}
		else {
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

			///TODO: ��쿡 ���� �߰� �۾� �ʿ�!!!
		}
		*/

		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}



void CAwesomeMmap::OnLButtonDown(UINT nFlags, CPoint point)
{
	//�� �ڵ�� ���ο� ��ü ������ ���� ������Դϴ�.
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRect newRect(point.x - 50, point.y - 50, point.x + 50, point.y + 50);
	CString newStr;
	newStr.Format(_T("[%d,%d]"), point.x, point.y);

	CIdea newIdea(newRect, newStr);
	pDoc->m_ideaList.AddTail(newIdea);
	pDoc->SetModifiedFlag();

	Invalidate();


	CView::OnLButtonDown(nFlags, point);
}


// ���콺�� ��ü �ȿ� ��������� ����. (���� ���� �� ���� ���
BOOL CAwesomeMmap::CheckPtInIdea(CPoint point)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CIdea *tmpIdea;
	POSITION pos = pDoc->m_ideaList.GetHeadPosition();

	while (pos != NULL)
	{
		tmpIdea = &pDoc->m_ideaList.GetNext(pos);
		//���� ���� �� �� PtInRgn�� TRUE���
		if (tmpIdea->MakeIdeaRgn().PtInRegion(point))
		{
			tmpIdea->DeleteIdeaRgn();
			return TRUE;
		}
		tmpIdea->DeleteIdeaRgn();
	}
	return FALSE;
}
