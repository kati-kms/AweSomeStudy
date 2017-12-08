// AwesomeMmap.cpp : 구현 파일입니다.
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


// CAwesomeMmap 그리기입니다.

void CAwesomeMmap::OnDraw(CDC* pDC)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	//CAwesomeStudyDoc * pDoc = (CAwesomeStudyDoc *)((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	POSITION pos;
	CIdea ideas, ideas1;
	CBrush ideaBrush;
	CPen ideaPen;
	CPoint roundPoint;
	CList<CIdea, CIdea&>  *ideaList = &(pDoc->m_ideaList);
	int r, g, b;
	double rndX, rndY;
	const double brightRate = 0.80;

	//Idea 객체 보이기
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


// CAwesomeMmap 진단입니다.

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


// CAwesomeMmap 메시지 처리기입니다.


void CAwesomeMmap::OnHome()
{
	CMainFrame * frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


BOOL CAwesomeMmap::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

		//OR 연산을 해서 리전들 중 하나라고 겹치는 부분이 있다면
		//flag를 TRUE로 해서 break, 
		//flag가 TRUE이면 마우스 커서의 모양을 바꾼다.
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
			//리전을 하나로 합쳐버린다.
			unionRgn.CombineRgn(&unionRgn, &tmpIdea.m_ideaRegion, RGN_OR);
		}

		//마우스가 리전의 합집합들 사이에 존재한다면
		if (unionRgn.PtInRegion(point)) {
			::SetCursor(AfxGetApp()->LoadCursorW(IDC_ADD));
		}
		else {
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

			///TODO: 경우에 따른 추가 작업 필요!!!
		}
		*/

		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}



void CAwesomeMmap::OnLButtonDown(UINT nFlags, CPoint point)
{
	//이 코드는 새로운 객체 생성을 위한 참고용입니다.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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


// 마우스가 객체 안에 들어있으면 변경. (리전 생성 후 제거 요망
BOOL CAwesomeMmap::CheckPtInIdea(CPoint point)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CIdea *tmpIdea;
	POSITION pos = pDoc->m_ideaList.GetHeadPosition();

	while (pos != NULL)
	{
		tmpIdea = &pDoc->m_ideaList.GetNext(pos);
		//리전 리턴 한 뒤 PtInRgn가 TRUE라면
		if (tmpIdea->MakeIdeaRgn().PtInRegion(point))
		{
			tmpIdea->DeleteIdeaRgn();
			return TRUE;
		}
		tmpIdea->DeleteIdeaRgn();
	}
	return FALSE;
}
