// AwesomeHome.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeHome.h"
#include "MainFrm.h"
#include "ClassInfo.h"
#include <afxtempl.h>


// CAwesomeHome

IMPLEMENT_DYNCREATE(CAwesomeHome, CFormView)

CAwesomeHome::CAwesomeHome()
	: CFormView(IDD_AWESOMEHOME)
{
	m_pAddDlg = NULL;
	class_name = "";
	class_professor = "";
	class_day = 0;
	class_start_hour = 0;
	class_start_minute = 0;
	class_end_hour = 0;
	class_end_minute = 0;
	class_room = "";
	m_array.RemoveAll();
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
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CAwesomeHome::OnUpdateFileOpen)
	ON_WM_LBUTTONDOWN()
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
	for (int i = 0; i < m_array.GetCount(); i++) {
		CBrush brush(m_array[i].m_color);
		pDC->SelectObject(brush);
		pDC->Rectangle(m_array[i].rect);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(m_array[i].m_class, &m_array[i].rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);
	}
}


void CAwesomeHome::OnAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClassInfo AddDlg;
	int result = AddDlg.DoModal();
	MyClass temp;
	if (result == IDOK) {
		temp.m_class = AddDlg.m_class;
		temp.m_professor = AddDlg.m_professor;
		temp.m_date = AddDlg.m_date;// 0 ~ 4 월 ~ 금
		temp.m_s_hour = AddDlg.m_s_hour; // 0 ~ 11 9시 ~ 20시
		temp.m_s_minute = AddDlg.m_s_minute; // 0 ~ 11 0분 ~ 55분
		temp.m_e_hour = AddDlg.m_e_hour;
		temp.m_e_minute = AddDlg.m_e_minute;
		temp.m_place = AddDlg.m_place;
		
		// Error : 시작 시간과 끝시간이 같을 경우 or 끝시간이 빠를 경우
		if (temp.m_s_hour > temp.m_e_hour || ((temp.m_s_hour == temp.m_e_hour) && (temp.m_s_minute > temp.m_e_minute))){
			AfxMessageBox(_T("시간을 다시 설정해주세요."));
			return;
		}

		// Error : 이미 지정된 시간에 강의가 추가된 경우
		int error_Start = temp.m_s_hour * 12 + temp.m_s_minute;
		int error_End = temp.m_e_hour * 12 + temp.m_e_minute;
		for (int i = error_Start; i < error_End; i++)
			if (IsAble[temp.m_date][i] == TRUE) {
				AfxMessageBox(_T("해당 시간에는 이미 강의가 있습니다."));
				return;
			}

		/*
		// Error : 이미 지정된 시간에 강의가 추가된 경우
		int error_num = (AddDlg.m_e_hour - AddDlg.m_s_hour) * 12 + (AddDlg.m_e_minute - AddDlg.m_s_minute);
		int error_hour = AddDlg.m_s_hour;
		int error_minute = AddDlg.m_s_minute;
		int error_i_temp = 0;
		
		for (int i = 0; i < error_num; i++) {
			if ((error_minute + error_i_temp) > 11) {
				error_hour += 1;
				error_minute = 0;
				error_i_temp = 0;
			}
			if (IsAble[AddDlg.m_date][error_hour][error_minute+ error_i_temp] == 1) {
				AfxMessageBox(_T("해당 시간에는 이미 강의가 있습니다."));
				return;
			}
			error_i_temp += 1;
		}
		*/
		// 강의 rect 생성
		CClientDC dc(this);
		srand((unsigned)time(NULL));
		CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));
		dc.SelectObject(brush);
		CRect rect(temp.m_date * 100 + 90, temp.m_s_hour * 60 + temp.m_s_minute * 5 + 90,
			temp.m_date * 100 + 190, temp.m_e_hour * 60 + temp.m_e_minute * 5 + 90);
		dc.Rectangle(rect);
		temp.m_color = dc.GetPixel(temp.m_date * 100 + 90 + 1, temp.m_s_hour * 60 + temp.m_s_minute * 5 + 90 + 1);
		temp.rect = rect;

		// rect에 강의명 넣기
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(temp.m_class, &rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);


		// 시간정보 넣기
		int Start = temp.m_s_hour * 12 + temp.m_s_minute;
		int End = temp.m_e_hour * 12 + temp.m_e_minute;
		for (int i = Start; i < End; i++)
			IsAble[temp.m_date][i] = TRUE;

		// 시간정보 넣기
		/*
		int able_num = (AddDlg.m_e_hour - AddDlg.m_s_hour) * 12 + (AddDlg.m_e_minute - AddDlg.m_s_minute);
		int able_hour = AddDlg.m_s_hour;
		int able_minute = AddDlg.m_s_minute;
		int able_i_temp = 0;
		for (int i = 0; i < able_num; i++) {
			if ((able_minute + able_i_temp) > 11) {
				able_hour += 1;
				able_minute = 0;
				able_i_temp = 0;
			}
			IsAble[AddDlg.m_date][able_hour][able_minute + able_i_temp] = 1;
			able_i_temp += 1;
		}
		*/
		// 강의 정보 m_array에 저장
		m_array.Add(temp);
	}
}


void CAwesomeHome::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	/*CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndHome) {
		pCmdUI->Enable(0);
	}*/   //지우지마시오 ㅠㅠㅠㅠㅠㅠㅠ
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CAwesomeHome::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i = 0; i < m_array.GetCount(); i++) {
		//if (point == m_array[i].rect.)
	}
	CFormView::OnLButtonDown(nFlags, point);
}
