
// AwesomeStudyView.cpp : CAwesomeStudyView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CAwesomeStudyView ����/�Ҹ�

CAwesomeStudyView::CAwesomeStudyView()
	: CFormView(IDD_AWESOMESTUDY_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.


	return CFormView::PreCreateWindow(cs);
}

void CAwesomeStudyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CAwesomeStudyView ����

#ifdef _DEBUG
void CAwesomeStudyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAwesomeStudyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAwesomeStudyDoc* CAwesomeStudyView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAwesomeStudyDoc)));
	return (CAwesomeStudyDoc*)m_pDocument;
}
#endif //_DEBUG


// CAwesomeStudyView �޽��� ó����


void CAwesomeStudyView::OnBnClickedOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CAwesomeStudyDoc* pDoc = GetDocument();
	CString strFileName;
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_READONLY, _T("ALL Files(*.*)|*.*|"));

	int iRet = fDlg.DoModal();
	strFileName = fDlg.GetPathName();
	if (iRet != IDOK) {
		AfxMessageBox(_T("���������� ����ϼ̽��ϴ�."));
		return;
	}
	m_path.SetWindowTextW(strFileName);
	
}


void CAwesomeStudyView::OnBnClickedLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CAwesomeStudyDoc* pDoc = GetDocument();
	CString str;
	m_password.GetWindowText(str);
	if (str.Compare(pDoc->PassWord) == 0) {
		CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
		frame->SwitchView(VIEWID_HOME);
	}
	else {
		AfxMessageBox(_T("��й�ȣ�� �ٽ� �Է����ּ���"));
	}
}




