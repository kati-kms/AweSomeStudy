// AwesomePic.cpp : ���� �����Դϴ�.
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


// CAwesomePic �����Դϴ�.

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


// CAwesomePic �޽��� ó�����Դϴ�.


BOOL CAwesomePic::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CAwesomePic::OnHome()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
}
