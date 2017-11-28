// AwesomeHome.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeHome.h"
#include "MainFrm.h"


// CAwesomeHome

IMPLEMENT_DYNCREATE(CAwesomeHome, CFormView)

CAwesomeHome::CAwesomeHome()
	: CFormView(IDD_AWESOMEHOME)
{
	class_name = "";
	class_professor = "";
	class_day = 0;
	class_start_hour = 0;
	class_start_minute = 0;
	class_end_hour = 0;
	class_end_minute = 0;
	class_room = "";
}

CAwesomeHome::~CAwesomeHome()
{
}

void CAwesomeHome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAwesomeHome, CFormView)
	ON_BN_CLICKED(IDC_HOME_WRITE, &CAwesomeHome::OnBnClickedHomeWrite)
	ON_BN_CLICKED(IDC_HOME_PIC, &CAwesomeHome::OnBnClickedHomePic)
	ON_BN_CLICKED(IDC_HOME_MINDMAP, &CAwesomeHome::OnBnClickedHomeMindmap)
	ON_COMMAND(ID_ADD, &CAwesomeHome::OnAdd)
END_MESSAGE_MAP()


// CAwesomeHome 진단입니다.

#ifdef _DEBUG
void CAwesomeHome::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeHome::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeHome 메시지 처리기입니다.


BOOL CAwesomeHome::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeHome::OnBnClickedHomeWrite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_WRITE);
}


void CAwesomeHome::OnBnClickedHomePic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_PIC);
}


void CAwesomeHome::OnBnClickedHomeMindmap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_Mmap);
}


void CAwesomeHome::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	pDC->Rectangle(50, 50, 590, 810);
	for (int i = 0; i < 12; i++) {
		pDC->MoveTo(50, 90 + i * 60);
		pDC->LineTo(590, 90 + i * 60);
	}
	for (int i = 0; i < 5; i++) {
		pDC->MoveTo(90 + i * 100, 50);
		pDC->LineTo(90 + i * 100, 810);
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(135, 70, _T("월"));
	pDC->TextOut(235, 70, _T("화"));
	pDC->TextOut(335, 70, _T("수"));
	pDC->TextOut(435, 70, _T("목"));
	pDC->TextOut(535, 70, _T("금"));

	for (int i = 0; i < 12; i++) {
		CString str;
		if ((i + 9) > 12) {
			str.Format(_T("%d"), i - 3);
			pDC->TextOut(70, 90 + i * 60, str);
		}
		else {
			str.Format(_T("%d"), i + 9);
			pDC->TextOut(70, 90 + i * 60, str);
		}
	}
}


void CAwesomeHome::OnAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//To Do : Dlg 생성
	MessageBox(_T("강의명, 교수명, 시간, 장소"));

	// 입력됐다 치고(윈플, 김익수, 월요일 10시, 정보과학관 305호
	class_name = _T("윈도우 프로그래밍");
	class_professor = _T("김익수");
	class_day = 0; // 0 ~ 4 월 ~ 금
	class_start_hour = 1; // 0 ~ 11 9시 ~ 20시
	class_start_minute = 0; // 0 ~ 11 0분 ~ 55분
	class_end_hour = 2;
	class_end_minute = 10;
	class_room = _T("정보과학관 305호");

	// 강의 rect 생성
	CClientDC dc(this);
	srand((unsigned)time(NULL));
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));
	dc.SelectObject(brush);
	CRect rect(class_day * 100 + 90, class_start_hour * 60 + class_start_minute * 5 + 90, class_day * 100 + 190, class_end_hour * 60 + class_end_minute * 5 + 90);
	dc.Rectangle(rect);

	// rect에 강의명 넣기
	//dc.DrawText(class_name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(class_name, &rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);

	// To Do : rect를 저장할 List 생성하기
}
