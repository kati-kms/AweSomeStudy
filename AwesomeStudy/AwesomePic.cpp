// AwesomePic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomePic.h"
#include "MainFrm.h"


// CAwesomePic

IMPLEMENT_DYNCREATE(CAwesomePic, CFormView)

CAwesomePic::CAwesomePic()
	: CFormView(IDD_AWESOMEPIC)
{

}

CAwesomePic::~CAwesomePic()
{
}

void CAwesomePic::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAwesomePic, CFormView)

	ON_COMMAND(IDC_HOME, &CAwesomePic::OnHome)
END_MESSAGE_MAP()


// CAwesomePic 진단입니다.

#ifdef _DEBUG
void CAwesomePic::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomePic::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomePic 메시지 처리기입니다.


BOOL CAwesomePic::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CAwesomePic::OnHome()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
}
