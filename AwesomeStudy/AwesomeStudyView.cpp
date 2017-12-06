
// AwesomeStudyView.cpp : CAwesomeStudyView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AwesomeStudy.h"
#endif

#include "AwesomeStudyDoc.h"
#include "AwesomeStudyView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAwesomeStudyView

IMPLEMENT_DYNCREATE(CAwesomeStudyView, CFormView)

BEGIN_MESSAGE_MAP(CAwesomeStudyView, CFormView)
	ON_BN_CLICKED(IDC_OPEN, &CAwesomeStudyView::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_LOGIN, &CAwesomeStudyView::OnBnClickedLogin)
END_MESSAGE_MAP()

// CAwesomeStudyView 생성/소멸

CAwesomeStudyView::CAwesomeStudyView()
	: CFormView(IDD_AWESOMESTUDY_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAwesomeStudyView::~CAwesomeStudyView()
{
}

void CAwesomeStudyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATH, m_path);
	DDX_Control(pDX, IDC_PASSWORD, m_password);
}

BOOL CAwesomeStudyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.


	return CFormView::PreCreateWindow(cs);
}

void CAwesomeStudyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CAwesomeStudyView 진단

#ifdef _DEBUG
void CAwesomeStudyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAwesomeStudyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAwesomeStudyDoc* CAwesomeStudyView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAwesomeStudyDoc)));
	return (CAwesomeStudyDoc*)m_pDocument;
}
#endif //_DEBUG


// CAwesomeStudyView 메시지 처리기


void CAwesomeStudyView::OnBnClickedOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAwesomeStudyDoc* pDoc = GetDocument();
	CString strFileName;
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_READONLY, _T("ALL Files(*.*)|*.*|"));

	int iRet = fDlg.DoModal();
	strFileName = fDlg.GetPathName();
	if (iRet != IDOK) {
		AfxMessageBox(_T("파일지정을 취소하셨습니다."));
		return;
	}
	m_path.SetWindowTextW(strFileName);
	
}


void CAwesomeStudyView::OnBnClickedLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAwesomeStudyDoc* pDoc = GetDocument();
	CString str;
	m_password.GetWindowText(str);
	if (str.Compare(pDoc->PassWord) == 0) {
		CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
		frame->SwitchView(VIEWID_HOME);
	}
	else {
		AfxMessageBox(_T("비밀번호를 다시 입력해주세요"));
	}
}




