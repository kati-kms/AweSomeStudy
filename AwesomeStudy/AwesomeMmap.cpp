// AwesomeMmap.cpp : ���� �����Դϴ�.
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


// CAwesomeMmap �����Դϴ�.

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


// CAwesomeMmap �޽��� ó�����Դϴ�.


BOOL CAwesomeMmap::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeMmap::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	pDC->SetMapMode(MM_LOMETRIC);
	pDC->Rectangle(50, -50, 550, -550);
	pDC->TextOut(50, -50, _T("Mmap"));
}


void CAwesomeMmap::OnHome()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//����
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
}
