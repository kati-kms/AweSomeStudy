// AwesomeWrite.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeWrite.h"
#include "MainFrm.h"

#include "WriteGoLine.h"


// CAwesomeWrite
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

IMPLEMENT_DYNCREATE(CAwesomeWrite, CFormView)

CAwesomeWrite::CAwesomeWrite()
	: CFormView(IDD_AWESOMEWRITE)
{
	pFindDlg = NULL;
	m_color = RGB(0, 0, 0);

	m_next_start = 0;
	m_find_next = false;
	m_replace_first = false;
}

CAwesomeWrite::~CAwesomeWrite()
{
}

void CAwesomeWrite::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WRITE, m_write);
}

BEGIN_MESSAGE_MAP(CAwesomeWrite, CFormView)
	ON_COMMAND(IDC_HOME, &CAwesomeWrite::OnHome)
	ON_BN_CLICKED(IDC_WRITE_ALLCLEAR, &CAwesomeWrite::OnBnClickedWriteAllclear)
	ON_BN_CLICKED(IDC_WRITE_SAVE, &CAwesomeWrite::OnBnClickedWriteSave)
	ON_COMMAND(ID_WRITE_SELECTALL, &CAwesomeWrite::OnWriteSelectall)
	ON_BN_CLICKED(IDC_WRITE_CLOSE, &CAwesomeWrite::OnBnClickedWriteClose)
	ON_COMMAND(ID_WRITE_UNDO, &CAwesomeWrite::OnWriteUndo)
	ON_COMMAND(ID_WRITE_CUT, &CAwesomeWrite::OnWriteCut)
	ON_COMMAND(ID_WRITE_COPY, &CAwesomeWrite::OnWriteCopy)
	ON_COMMAND(ID_WRITE_PASTE, &CAwesomeWrite::OnWritePaste)
	ON_COMMAND(ID_WRITE_FIND, &CAwesomeWrite::OnWriteFind)
	ON_COMMAND(ID_WRITE_FINDNEXT, &CAwesomeWrite::OnWriteFindnext)
	ON_COMMAND(ID_WRITE_REPLACE, &CAwesomeWrite::OnWriteReplace)
	ON_COMMAND(ID_WRITE_GO, &CAwesomeWrite::OnWriteGo)
	ON_COMMAND(ID_WRITE_DATETIME, &CAwesomeWrite::OnWriteDatetime)
	ON_COMMAND(ID_WRITE_FONTSTATE, &CAwesomeWrite::OnWriteFontstate)
	ON_EN_CHANGE(IDC_WRITE, &CAwesomeWrite::OnEnChangeWrite)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFindReplaceCmd)
END_MESSAGE_MAP()


// CAwesomeWrite 진단입니다.

#ifdef _DEBUG
void CAwesomeWrite::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeWrite::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeWrite 메시지 처리기입니다.


void CAwesomeWrite::OnHome()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);

}


BOOL CAwesomeWrite::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeWrite::OnBnClickedWriteAllclear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int len = m_write.GetWindowTextLength();
	m_write.SetSel(0, len);
	m_write.Clear();
}

void CAwesomeWrite::OnBnClickedWriteSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	m_write.GetWindowText(str);
	//str저장하면됨
	//폰트 저장
	//색깔 저장
}


void CAwesomeWrite::OnBnClickedWriteClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//저장할지 물어보고 Home으로 이동
	//저장 누르고 닫기면, 그냥 닫힘
}


//메뉴바 처리


void CAwesomeWrite::OnWriteUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_write.Undo();
}

//----------------------------------------

void CAwesomeWrite::OnWriteCut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_write.Cut();
}

void CAwesomeWrite::OnWriteCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_write.Copy();
}

void CAwesomeWrite::OnWritePaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_write.Paste();
}

//----------------------------------------

void CAwesomeWrite::OnWriteFind()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (pFindDlg != NULL)
		pFindDlg->SetFocus();
	else {
		pFindDlg = new CFindReplaceDialog();
		pFindDlg->Create(TRUE, _T(""), _T(""), FR_DOWN, this);
	}
}

void CAwesomeWrite::OnWriteFindnext()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_find_next = true;
	OnFindReplaceCmd(0,0);
}

void CAwesomeWrite::OnWriteReplace()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (pFindDlg != NULL) {
		pFindDlg->SetFocus();
	}
	else {
		pFindDlg = new CFindReplaceDialog();
		m_replace_first = true;
		pFindDlg->Create(FALSE, _T(""), _T(""), FR_DOWN, this);
	}
}

void CAwesomeWrite::OnWriteGo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CWriteGoLine dlg;
	int TotalLine = m_write.GetLineCount();
	int result = dlg.DoModal();

	if (result == IDOK) {
		if (dlg.m_line > TotalLine) {
			//오류
			AfxMessageBox(_T("줄번호가 전체 줄 수를 넘습니다"),MB_ICONINFORMATION);
		}
		else {
			//go goline
			int index = m_write.LineIndex(dlg.m_line - 1);
			m_write.SetSel(index, index, true);
			Invalidate();
		}
	}
	else
		Invalidate();
}

//----------------------------------------

void CAwesomeWrite::OnWriteSelectall()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	m_write.SetSel(0, -1);
}

void CAwesomeWrite::OnWriteDatetime()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CTime tm;
	tm = CTime::GetCurrentTime();
	CString str_date;
	str_date.Format(_T("%d-%d-%d "), tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	CString str_am_pm;
	int Hour = tm.GetHour();
	if (Hour < 12) {
		str_am_pm = _T("오전 ");
	}
	else {
		Hour -= 12;
		str_am_pm = _T("오후 ");
	}
	if (Hour == 0)
		Hour = 12; // 오전 12시 예외처리
	CString str_time;
	str_time.Format(_T("%d : %d "), Hour, tm.GetMinute());
	m_write.ReplaceSel(str_am_pm + str_time + str_date);
}

//----------------------------------------

void CAwesomeWrite::OnWriteFontstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//cfont dialog // 책
	CFontDialog FontDlg;
	
	if (FontDlg.DoModal() == IDOK) {
		//매번 폰트를 눌러야하는 오류가 있음 // 저장시 해결각
		m_color = FontDlg.GetColor();
		LOGFONT lf;
		if (m_font.m_hObject != NULL)
			m_font.DeleteObject();
		FontDlg.GetCurrentFont(&lf);
		
		m_font.CreateFontIndirectW(&lf);
		m_write.SetFont(&m_font);

		// 색깔 구해야함	
	}
}

//-----------------------------------------------------------------------edit창 자체 이벤트 컨트롤------------------------------------------------------

void CAwesomeWrite::OnEnChangeWrite()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 문자열이 바뀌면 Updata()? 함수 호출 // for 저장
	// 문자열이 바뀌면 전체줄 기억하기
	
	int total_line = m_write.GetLineCount();
	CString str;
	str.Format(_T("%d"), total_line);
	//AfxMessageBox(str);	
	//상태바에 추가하기
}


LRESULT CAwesomeWrite::OnFindReplaceCmd(WPARAM wParam, LPARAM lParam)
{
	if (pFindDlg->IsTerminating()) {
		pFindDlg = NULL;
		m_next_start = 0; // 히히히히히히
		return 0;
	}
	if (pFindDlg->FindNext() || m_find_next) {
		//검색할String
		CString FindStr;
		FindStr = pFindDlg->GetFindString();
		int length = FindStr.GetLength();
		//전체 String
		CString TotalWrite;
		m_write.GetWindowText(TotalWrite); // 전체String 가져오기   // 찾을때마다 짤라내자 ㅎ // next_start부터의 string
		int total_length = TotalWrite.GetLength();

		//Sub String
		CString SubWrite;
		SubWrite = TotalWrite.Right(total_length - m_next_start); //이전까지 찾은 문자열은 빼기
		int start = SubWrite.Find(FindStr);
		if (start == -1) {
			AfxMessageBox(FindStr + _T("을 찾을 수 없습니다"), MB_ICONINFORMATION);
			return 0;
		}
		int end = start + length;
		m_write.SetSel(m_next_start + start, m_next_start + end);
		m_next_start = m_next_start + end;
		m_find_next = false;
	}
	else if (pFindDlg->ReplaceCurrent() || m_find_next) {
		if (!m_replace_first) {
			m_write.ReplaceSel(pFindDlg->GetReplaceString());
		}

		//검색할String
		CString FindStr;
		FindStr = pFindDlg->GetFindString();
		int length = FindStr.GetLength();
		//전체 String
		CString TotalWrite;
		m_write.GetWindowText(TotalWrite); // 전체String 가져오기   // 찾을때마다 짤라내자 ㅎ // next_start부터의 string
		int total_length = TotalWrite.GetLength();

		//Sub String
		CString SubWrite;
		SubWrite = TotalWrite.Right(total_length - m_next_start); //이전까지 찾은 문자열은 빼기
		int start = SubWrite.Find(FindStr);
		if (start == -1) {
			AfxMessageBox(FindStr + _T("을 찾을 수 없습니다"), MB_ICONINFORMATION);
			return 0;
		}
		int end = start + length;
		m_write.SetSel(m_next_start + start, m_next_start + end);
		m_next_start = m_next_start + end;
		m_find_next = false;
		m_replace_first = false;
	}
	else if (pFindDlg->ReplaceAll()) {
		int start = 0;
		while (1) {
			//검색할String
			CString FindStr;
			FindStr = pFindDlg->GetFindString();
			int length = FindStr.GetLength();
			//전체 String
			CString TotalWrite;
			m_write.GetWindowText(TotalWrite); // 전체String 가져오기   // 찾을때마다 짤라내자 ㅎ // next_start부터의 string
			int total_length = TotalWrite.GetLength();

			//Sub String
			CString SubWrite;
			SubWrite = TotalWrite.Right(total_length - m_next_start); //이전까지 찾은 문자열은 빼기
			int start = SubWrite.Find(FindStr);
			if (start == -1) {
				break;
			}
			int end = start + length;
			m_write.SetSel(m_next_start + start, m_next_start + end);
			m_next_start = m_next_start + end;
			m_find_next = false;

			m_write.ReplaceSel(pFindDlg->GetReplaceString());
		}
	}
	return LRESULT();
}