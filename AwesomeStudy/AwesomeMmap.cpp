// AwesomeMmap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeMmap.h"
#include "AwesomeStudyDoc.h"
#include "MainFrm.h"

#include <WinUser.h>

//임시 전역변수
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
	m_nPressedFlag = 0;
	m_bMoveMode = FALSE;
	m_mousePointInRect.SetPoint(0, 0);
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
END_MESSAGE_MAP()


// CAwesomeMmap 그리기입니다.

///TODO: 가능하면 다 끝나고 더블 버퍼링 시도해보자
void CAwesomeMmap::OnDraw(CDC* pDC)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	//CAwesomeStudyDoc * pDoc = (CAwesomeStudyDoc *)((CMainFrame *)AfxGetMainWnd())->GetActiveDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	POSITION pos;
	CIdea *ideas;
	CBrush ideaBrush;
	CPen ideaPen;
	CPoint roundPoint;
	CList<CIdea, CIdea&> *ideaList = &(pDoc->m_ideaList);
	int r, g, b;
	double rndX, rndY;
	const double brightRate = 0.80;
	int pointCode = cursorFlag;
	

	//Idea 객체 보이기
	//인쇄할 땐 Tail부터 반대로 인쇄해야겠다.
	//왜냐면 상대적으로 뒤늦게 인쇄된 Idea가 다른 Idea를 덮었을 경우,
	//겹친 부분을 클릭했을 때 뒤늦게 인쇄된 Idea가 되어야 하기 때문이다.
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

		//size handle
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
		}
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

		CPoint point;
		POSITION pos;
		CRgn unionRgn;
		CList<CIdea, CIdea&> *tmpList = &(pDoc->m_ideaList);
		unionRgn.CreateRectRgn(0, 0, 1, 1);
		::GetCursorPos(&point);
		ScreenToClient(&point);
		cursorFlag = CheckPtInIdea(point);

		//OR 연산을 해서 리전들 중 하나라고 겹치는 부분이 있다면
		//flag에 따라 각각 다른 커서의 모양을 만든다.
		if (cursorFlag == RGN_IDEA_IN) {
			::SetCursor((LoadCursor(NULL, IDC_SIZEALL)));
		}
		else if (cursorFlag == RGN_IDEA_OUT){
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
	//이 코드는 새로운 객체 생성을 위한 참고용입니다.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bLBtnPressed = TRUE;
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	POSITION ideaPosition = NULL;
	CIdea selectedIdea;
	CString str;
	//TODO: selectedIdea의 주소값을 던져줬을 때 List에 맞는 Idea의 주소값을 얻어왔으면 좋겠다.
	//CList는 GetNext로 얻어온 값은 진짜값이 아니라 복사된 객체일 듯 하다.
	//결국, SetAt(POSITION pos, ARG_TYPE newElement); 함수를 사용해서 
	//다시 그 자리의 Element를 newElement로 대체해야 할 것 같다.
	//TODO: GetNext(pos)의 pos는 Element를 정확히 가리키는 pos가 아니라
	//Element의 Next를 가리키는 pos이기 때문에 이에 관한 추가적인 코딩이 필요하다
	int pointCode = CheckPtInIdea(point, selectedIdea);
	//선택된 아이디아를 Head에 가져다 놓는다.


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
	//Idea in일 경우 : 먼저 전부 선택을 FALSE로, 
	//선택한 녀석의 m_bHighlight를 True로 설정
	if (pointCode == RGN_IDEA_IN && &selectedIdea != NULL) {
		SetDehighlight(pDoc->m_ideaList);
		selectedIdea.SetHighlight(TRUE);

		//마우스 끌었을 때 움직이도록 nPressedFlag의 값을 고정시킨다.
		if (m_bPressOnlyOneFlag == TRUE) {
			m_bPressOnlyOneFlag = FALSE;
			m_nPressedFlag = cursorFlag;
			m_bMoveMode = TRUE;
			m_mousePointInRect = point - selectedIdea.m_ideaRect.TopLeft();
		}
		//SetAt(POSITION, ARG_TYPE)를 호출하여 위에서 저장한 ideaPosition 변수의
		//Prev값이 곧 원 Element이기 때문에 ideaPosition.Prev한 자리에 selectedIdea를 
		//집어넣는다.
		//ToDO:아니! 선택된 Idea는 Head에 올려줘야 한다. 즉, 현재 Idea가 있는 자리의 노드는
		//제거하고 이걸 Head에다가 붙혀주면 되겠다
		//SetIdea(tmpPosition, pDoc->m_ideaList, selectedIdea);
		DeleteIdea(tmpPosition, pDoc->m_ideaList);
		pDoc->m_ideaList.AddHead(selectedIdea);

		pDoc->SetModifiedFlag();
		Invalidate();
	}

	//Idea out일 경우 : 모든 놈들의 m_bHighlight를 False로 설정
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

	//Size Handle일 경우 : 4가지 경우
	//어차피 경우에 따른 나눔은 OnMouseMove에서 처리한다.
	if (pointCode == RGN_SIZE_HND_BTMLEFT || pointCode == RGN_SIZE_HND_BTMRIGHT
		|| pointCode == RGN_SIZE_HND_TOPLEFT || pointCode == RGN_SIZE_HND_TOPRIGHT) 
		if (m_bPressOnlyOneFlag == TRUE) {
			m_nPressedFlag = cursorFlag;
			m_bChangeSizeMode = TRUE;
			m_bPressOnlyOneFlag = FALSE;
		}
	//else { m_bChangeSizeMode = FALSE; }

	/////////////////////////////////////////////
	//이 코드는 왼쪽 버튼 클릭시 임의로 새 Idea를 생성하는 코드로,
	//이젠 사용하지 않으므로 주석처리합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
	CIdea *thisIdea = &GetIdea(tmpPosition, pDoc->m_ideaList);
	CClientDC dc(this);
	//debug
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
	tmpStr.Format(_T("\n현재 리스트 개수 : %d\n"), pDoc->m_ideaList.GetCount());
	str.Append(tmpStr);
	debugDc.DrawText(str, debugRect, 0);
	//debug_end
	// 사이즈 조절모드면 계속해서 마우스를 따라 사각형의 끌리고 있는 핸들의 꼭짓점을 그 위치로 stretch 시킨다.
	// 그리는건 여기에서 하자.
	if (m_bChangeSizeMode)
	{
		CRect drawRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		CPoint roundPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);

		dc.SelectStockObject(NULL_BRUSH);
		//이전에 그린 사각형을 지운다.
///TODO : 왜 이전에 그린 사각형이 지워지지 않지?
		dc.SetROP2(R2_NOT);
		dc.RoundRect(drawRect, roundPoint);
		m_tmpX1 = thisIdea->m_ideaRect.left;
		m_tmpY1 = thisIdea->m_ideaRect.top;
		m_tmpX2 = thisIdea->m_ideaRect.right;
		m_tmpY2 = thisIdea->m_ideaRect.bottom;

		drawRect.SetRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		roundPoint.SetPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);


		//새로운 사각형을 그린다.
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
		dc.RoundRect(drawRect, roundPoint);
		//thisIdea.SetRect(drawRect);
		//SetIdea(tmpPosition, pDoc->m_ideaList, thisIdea);

		m_bChangeSizeMode = TRUE;
	}

	//이거는 직접 움직이게 해야겠다
	if (m_bMoveMode) {
		thisIdea->m_ideaRect.MoveToXY(
			point.x - m_mousePointInRect.x,
			point.y - m_mousePointInRect.y
		);
		SetIdea(tmpPosition, pDoc->m_ideaList, *thisIdea);

		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}



// 마우스가 객체 안에 들어있으면 변경. (리전 생성 후 제거 요망
int CAwesomeMmap::CheckPtInIdea(CPoint point, CIdea& whichIdea)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRgn topLeftRgn, topRightRgn, btmLeftRgn, btmRightRgn;
	CRgn addChildHandleRgn;
	tmpPosition = (pDoc->m_ideaList.GetHeadPosition());

	while (tmpPosition != NULL)
	{
		//TODO : CIdea* whichIdea에 list.GetNext()의 리턴한 객체의 주소를 
		//넘겨주고 싶은데..(그렇게 해야 CheckPtInIdea함수를 호출한 데에서 whichIdea를 가지고
		//바꾸어야 리스트 안에 있는 진짜 객체가 바뀌지)
		whichIdea = (pDoc->m_ideaList.GetNext(tmpPosition));
		whichIdea.DeleteIdeaRgn();
		///Region = Idea in = 1
		//리전 리턴 한 뒤 PtInRgn가 TRUE라면
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
		//활성화가 되어있는 경우 --> 
		//{ size handle에 대한 리전 생성 후 PtInRegion(point)
		// , 또는 Add Child Handle에 대한 리전 생성 후 PtInRegion(point) }
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


			//마우스가 이미 눌려져 있는 상태라면 유지시킨다.
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

			//참고로 드래그시 작동하는건 여기에서 관여하지 않는다.
			//OnMouseMove 함수에서 마우스가 드래그 하고 있는데 m_ideaRect.CenterPoint()를 중심으로
			//4분면으로 나뉘어있으니까 그때가서 고려하면 된다.

			//addChildHandleRgn

			//addChildHandleRgn Delete
			return tmpReturnValue;
		}
	}

	///Region = Idea out = 0
	//이건 제일 마지막에 해야겠다. 전부 다 아닐 경우
	return RGN_IDEA_OUT;
}

int CAwesomeMmap::CheckPtInIdea(CPoint point)
{
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRgn topLeftRgn, topRightRgn, btmLeftRgn, btmRightRgn;
	CRgn addChildHandleRgn;
	CIdea *whichIdea;
	POSITION pos = pDoc->m_ideaList.GetHeadPosition();

	while (pos != NULL)
	{
		//TODO : CIdea* whichIdea에 list.GetNext()의 리턴한 객체의 주소를 
		//넘겨주고 싶은데..(그렇게 해야 CheckPtInIdea함수를 호출한 데에서 whichIdea를 가지고
		//바꾸어야 리스트 안에 있는 진짜 객체가 바뀌지)
		whichIdea = &pDoc->m_ideaList.GetNext(pos);
		whichIdea->DeleteIdeaRgn();
		///Region = Idea in = 1
		//리전 리턴 한 뒤 PtInRgn가 TRUE라면
		//마우스가 눌려있는 상태라면 기존 상태를 계속 유지한다.
		//박스를 움직이고 있던가 크기핸들을 가지고 움직인다던가
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
		//활성화가 되어있는 경우 --> 
		//{ size handle에 대한 리전 생성 후 PtInRegion(point)
		// , 또는 Add Child Handle에 대한 리전 생성 후 PtInRegion(point) }
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

			//참고로 드래그시 작동하는건 여기에서 관여하지 않는다.
			//OnMouseMove 함수에서 마우스가 드래그 하고 있는데 m_ideaRect.CenterPoint()를 중심으로
			//4분면으로 나뉘어있으니까 그때가서 고려하면 된다.

			//addChildHandleRgn

			//addChildHandleRgn Delete


			return tmpReturnValue;
		}
	}
	///Region = Idea out = 0
	//이건 제일 마지막에 해야겠다. 전부 다 아닐 경우
	return RGN_IDEA_OUT;
}


// 리스트의 모든 Idea들의 m_bHighlighted를 False로 바꾸어주는 함수
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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu menu;
	CMenu* pMenu;
	ScreenToClient(&point);
	int ideaOption = CheckPtInIdea(point);
	menu.LoadMenu(IDR_MMAP_CNTXT);
	if (ideaOption == RGN_IDEA_IN) {
		//임시전역변수에 point를 집어넣는다.
		tmpPoint = point;
		ClientToScreen(&point);
		pMenu = menu.GetSubMenu(RGN_IDEA_IN);
		pMenu->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y, AfxGetMainWnd()
		);
	}
	else if (ideaOption == RGN_IDEA_OUT) {
		//임시전역변수에 point를 집어넣는다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRect newRect(tmpPoint.x - 50, tmpPoint.y - 50, tmpPoint.x + 50, tmpPoint.y + 50);
	CString newStr;
	newStr.Format(_T("[%d,%d]"), tmpPoint.x, tmpPoint.y);

	CIdea newIdea(newRect, newStr);
	newIdea.NewIdea();
	pDoc->m_ideaList.AddTail(newIdea);
	pDoc->SetModifiedFlag();

	Invalidate();
}


void CAwesomeMmap::OnRbnOutInsertIndependent()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

	CRect newRect(tmpPoint.x - 50, tmpPoint.y - 50, tmpPoint.x + 50, tmpPoint.y + 50);
	CString newStr;
	newStr.Format(_T("[%d,%d]"), tmpPoint.x, tmpPoint.y);

	CIdea newIdea(newRect, newStr);
	newIdea.NewIdea();
	pDoc->m_ideaList.AddTail(newIdea);
	pDoc->SetModifiedFlag();

	Invalidate();
}


// pos->prev에 new Idea로 교체한다.
void CAwesomeMmap::SetIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList, CIdea& newIdea)
{
	//마지막 원소(tail)에 있는 경우 pos가 nullptr인 경우가 있다!!!
	//문제를 해결할 수 있다. pos가 nullptr인 경우에만 tail을 가리키면 된다.
	if (pos == 0) {
		pos = ideaList.GetTailPosition();
		ideaList.SetAt(pos, newIdea);
		return;
	}
	ideaList.GetPrev(pos);
	ideaList.SetAt(pos, newIdea);
	return;
}

// 말 그대로 get idea합니다.
CIdea& CAwesomeMmap::GetIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (pos == 0) {
		pos = ideaList.GetTailPosition();
		return ideaList.GetAt(pos);
	}
	ideaList.GetPrev(pos);
	return ideaList.GetAt(pos);
}



void CAwesomeMmap::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bLBtnPressed = FALSE;
	m_bPressOnlyOneFlag = TRUE;
	m_mousePointInRect.SetPoint(0, 0);
	if (m_bChangeSizeMode) {
		CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();
		CClientDC dc(this);
		CRect drawRect(m_tmpX1, m_tmpY1, m_tmpX2, m_tmpY2);
		CPoint roundPoint(drawRect.Width() * roundRate, drawRect.Height() * roundRate);
		CIdea *newIdea = &GetIdea(tmpPosition, pDoc->m_ideaList);
		m_bChangeSizeMode = FALSE;

		//사각형 지우기
		dc.SetROP2(R2_NOT);
		dc.RoundRect(drawRect, roundPoint);
		
		//최종적인 사각형의 Rect를 집어넣고 SetIdea시킨다.
		newIdea->SetRect(drawRect);
		SetIdea(tmpPosition, pDoc->m_ideaList, *newIdea);

		pDoc->SetModifiedFlag();
		Invalidate();
	}
	if (m_bMoveMode) {
		m_bMoveMode = FALSE;
	}

	CView::OnLButtonUp(nFlags, point);
}


// pos->Prev자리의 노드를 제거한다.
//만약 지우려는 노드가 Tail이라 pos가 NULL인 경우,
//Tail을 지운다
CIdea& CAwesomeMmap::DeleteIdea(POSITION pos, CList<CIdea, CIdea&>& ideaList)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	CIdea* tmpIdea;
	if (pos == NULL) {
		return ideaList.RemoveTail();
	}
	ideaList.GetPrev(pos);
	tmpIdea = &ideaList.GetAt(pos);
	ideaList.RemoveAt(pos);
	return *tmpIdea;
}
