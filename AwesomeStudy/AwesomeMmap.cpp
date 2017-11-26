// AwesomeMmap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeMmap.h"
#include "MainFrm.h"


// CAwesomeMmap

IMPLEMENT_DYNCREATE(CAwesomeMmap, CFormView)

CAwesomeMmap::CAwesomeMmap()
	: CFormView(IDD_AWESOMEMMAP)
{

}

CAwesomeMmap::~CAwesomeMmap()
{
}

void CAwesomeMmap::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAwesomeMmap, CFormView)
	ON_COMMAND(IDC_HOME, &CAwesomeMmap::OnHome)
END_MESSAGE_MAP()


// CAwesomeMmap 진단입니다.

#ifdef _DEBUG
void CAwesomeMmap::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeMmap::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeMmap 메시지 처리기입니다.


BOOL CAwesomeMmap::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeMmap::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	pDC->SetMapMode(MM_LOMETRIC);
	pDC->Rectangle(50, -50, 550, -550);
	pDC->TextOut(50, -50, _T("Mmap"));
}


void CAwesomeMmap::OnHome()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//저장
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
}
