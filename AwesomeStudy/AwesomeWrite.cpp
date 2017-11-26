// AwesomeWrite.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeWrite.h"
#include "MainFrm.h"


// CAwesomeWrite

IMPLEMENT_DYNCREATE(CAwesomeWrite, CRichEditView)

CAwesomeWrite::CAwesomeWrite()
{

}

CAwesomeWrite::~CAwesomeWrite()
{
}

BEGIN_MESSAGE_MAP(CAwesomeWrite, CRichEditView)
	ON_COMMAND(IDC_HOME, &CAwesomeWrite::OnHome)
END_MESSAGE_MAP()


// CAwesomeWrite 진단입니다.

#ifdef _DEBUG
void CAwesomeWrite::AssertValid() const
{
	CRichEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeWrite::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
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
