// AwesomeHome.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeHome.h"
#include "AwesomeStudyDoc.h"
#include "MainFrm.h"
#include "ClassInfo.h"
#include <afxtempl.h>
#include "InfoSave.h"


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
	AddList = FALSE;
	Select_num = 0;
	m_color[0] = RGB(255, 160, 122);
	m_color[1] = RGB(255, 127, 80);
	m_color[2] = RGB(188, 143, 143);
	m_color[3] = RGB(173, 255, 47);
	m_color[4] = RGB(144, 238, 144);
	m_color[5] = RGB(32, 178, 170);
	m_color[6] = RGB(135, 206, 235);
	m_color[7] = RGB(250, 240, 230);
	m_color[8] = RGB(123, 104, 238);
	m_color[9] = RGB(192, 192, 192);
	color_num = 0;
}

CAwesomeHome::~CAwesomeHome()
{
}

void CAwesomeHome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Control(pDX, IDC_INFO, m_list);
	DDX_Control(pDX, IDC_HOME_WRITE, m_write);
	DDX_Control(pDX, IDC_HOME_PIC, m_pic);
	DDX_Control(pDX, IDC_HOME_MINDMAP, m_map);
}

BEGIN_MESSAGE_MAP(CAwesomeHome, CFormView)
	ON_BN_CLICKED(IDC_HOME_WRITE, &CAwesomeHome::OnBnClickedHomeWrite)
	ON_BN_CLICKED(IDC_HOME_PIC, &CAwesomeHome::OnBnClickedHomePic)
	ON_BN_CLICKED(IDC_HOME_MINDMAP, &CAwesomeHome::OnBnClickedHomeMindmap)
	ON_COMMAND(ID_ADD, &CAwesomeHome::OnAdd)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CAwesomeHome::OnUpdateFileOpen)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_DELETE, &CAwesomeHome::OnBnClickedDelete)
	ON_UPDATE_COMMAND_UI(IDC_HOME, &CAwesomeHome::OnUpdateHome)
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
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

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
	CInfoSave temp;
	if (result == IDOK) {
		temp.m_class = AddDlg.m_class;
		temp.m_professor = AddDlg.m_professor;
		temp.m_date = AddDlg.m_date;// 0 ~ 4 월 ~ 금
		temp.m_s_hour = AddDlg.m_s_hour; // 0 ~ 11 9시 ~ 20시
		temp.m_s_minute = AddDlg.m_s_minute; // 0 ~ 11 0분 ~ 55분
		temp.m_e_hour = AddDlg.m_e_hour;
		temp.m_e_minute = AddDlg.m_e_minute;
		temp.m_place = AddDlg.m_place;

		//Error : 강의명을 지정 안한 경우
		if (temp.m_class == _T("")) {
			AfxMessageBox(_T("강의명을 설정하지 않았습니다."));
			return;
		}

		// Error : 시작 시간과 끝시간이 같을 경우 or 끝시간이 빠를 경우
		if (temp.m_s_hour > temp.m_e_hour || ((temp.m_s_hour == temp.m_e_hour) && (temp.m_s_minute >= temp.m_e_minute))) {
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

		// 강의 rect 생성
		CClientDC dc(this);
		srand((unsigned)time(NULL));
		CBrush brush(m_color[color_num]);
		color_num++;
		if (color_num > 9)
			color_num = 0;
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

		// 강의 정보 m_array에 저장
		m_array.Add(temp);
	}
}


void CAwesomeHome::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndHome) {
	pCmdUI->Enable(0);
	}  //지우지마시오 ㅠㅠㅠㅠㅠㅠㅠ
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CAwesomeHome::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	AddList = FALSE;
	m_delete.EnableWindow(FALSE);
	for (int i = 0; i < m_array.GetSize(); i++) {
		Select_num = i;
		if (m_array[i].rect.PtInRect(point)) {
			m_list.ResetContent();
			CString str;
			str.Format(_T("강의명 : %s"), m_array[i].m_class);
			m_list.AddString(str);
			str.Format(_T("교수명 : %s"), m_array[i].m_professor);
			m_list.AddString(str);
			switch (m_array[i].m_date) {
			case 0: str.Format(_T("요일 : 월요일"));
				break;
			case 1: str.Format(_T("요일 : 화요일"));
				break;
			case 2: str.Format(_T("요일 : 수요일"));
				break;
			case 3: str.Format(_T("요일 : 목요일"));
				break;
			case 4: str.Format(_T("요일 : 금요일"));
				break;
			}
			m_list.AddString(str);
			str.Format(_T("시간 : %d시 %d분 ~ "), m_array[i].m_s_hour + 9, (m_array[i].m_s_minute) * 5);
			m_list.AddString(str);
			str.Format(_T("		  %d시 %d분"), m_array[i].m_e_hour + 9, (m_array[i].m_e_minute) * 5);
			m_list.AddString(str);
			str.Format(_T("장소 : %s"), m_array[i].m_place);
			m_list.AddString(str);

			AddList = TRUE;
			m_delete.EnableWindow(TRUE);
			break;
		}
	}
	if (AddList == FALSE)
		m_list.ResetContent();
	CFormView::OnLButtonDown(nFlags, point);
}


void CAwesomeHome::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Start = m_array[Select_num].m_s_hour * 12 + m_array[Select_num].m_s_minute;
	int End = m_array[Select_num].m_e_hour * 12 + m_array[Select_num].m_e_minute;
	for (int i = Start; i < End; i++)
		IsAble[m_array[Select_num].m_date][i] = FALSE;

	m_array.RemoveAt(Select_num);
	m_list.ResetContent();
	Invalidate();
}

void CAwesomeHome::OnUpdateHome(CCmdUI *pCmdUI)
{
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndHome) {
		pCmdUI->Enable(0);
	}
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
