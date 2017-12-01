// AwesomeWrite.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeWrite.h"
#include "MainFrm.h"


// CAwesomeWrite

IMPLEMENT_DYNCREATE(CAwesomeWrite, CFormView)

CAwesomeWrite::CAwesomeWrite()
	: CFormView(IDD_AWESOMEWRITE)
{

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
	ON_COMMAND(ID_WRITE_DEL, &CAwesomeWrite::OnWriteDel)
	ON_COMMAND(ID_WRITE_FIND, &CAwesomeWrite::OnWriteFind)
	ON_COMMAND(ID_WRITE_FINDNEXT, &CAwesomeWrite::OnWriteFindnext)
	ON_COMMAND(ID_WRITE_REPLACE, &CAwesomeWrite::OnWriteReplace)
	ON_COMMAND(ID_WRITE_GO, &CAwesomeWrite::OnWriteGo)
	ON_COMMAND(ID_WRITE_DATETIME, &CAwesomeWrite::OnWriteDatetime)
	ON_COMMAND(ID_WRITE_FONTSTATE, &CAwesomeWrite::OnWriteFontstate)
	ON_EN_CHANGE(IDC_WRITE, &CAwesomeWrite::OnEnChangeWrite)
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
	//저장 추가
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

void CAwesomeWrite::OnWriteDel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_write.Clear();
}

//----------------------------------------

void CAwesomeWrite::OnWriteFind()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFindReplaceDialog *pFindDlg = NULL;
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
	//문자열 찾는거 실질적인 기능 추가 --> viewedit.cpp 에서 확인
}

void CAwesomeWrite::OnWriteReplace()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFindReplaceDialog *pReplaceDlg = NULL;
	if (pReplaceDlg != NULL)
		pReplaceDlg->SetFocus();
	else {
		pReplaceDlg = new CFindReplaceDialog();
		pReplaceDlg->Create(FALSE, _T(""), _T(""), FR_DOWN, this);
	}
	//문자열 찾는거 실질적인 기능 추가 --> viewedit.cpp 에서 확인
}

void CAwesomeWrite::OnWriteGo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//찾아서 다음거로 가는것. // 다이얼로그 띄어서 할지말지
	//전체 줄 기억하는 변수 만들기 // enchanged 이벤트 처리기에서 처리
	//커서이동이 포인트! > viewedit.cpp
}

//----------------------------------------

void CAwesomeWrite::OnWriteSelectall()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str;
	int len = m_write.GetWindowTextLength();
	m_write.SetSel(0, len);
}

void CAwesomeWrite::OnWriteDatetime()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//2장확인
}

//----------------------------------------

void CAwesomeWrite::OnWriteFontstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//cfont dialog // 책
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

}
