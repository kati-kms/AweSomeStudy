// AwesomeWrite.cpp : ���� �����Դϴ�.
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


// CAwesomeWrite �����Դϴ�.

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


// CAwesomeWrite �޽��� ó�����Դϴ�.


void CAwesomeWrite::OnHome()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
}
