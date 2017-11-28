// AwesomeHome.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeHome.h"
#include "MainFrm.h"


// CAwesomeHome

IMPLEMENT_DYNCREATE(CAwesomeHome, CFormView)

CAwesomeHome::CAwesomeHome()
	: CFormView(IDD_AWESOMEHOME)
{
	class_name = "";
	class_professor = "";
	class_day = 0;
	class_start_hour = 0;
	class_start_minute = 0;
	class_end_hour = 0;
	class_end_minute = 0;
	class_room = "";
}

CAwesomeHome::~CAwesomeHome()
{
}

void CAwesomeHome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAwesomeHome, CFormView)
	ON_BN_CLICKED(IDC_HOME_WRITE, &CAwesomeHome::OnBnClickedHomeWrite)
	ON_BN_CLICKED(IDC_HOME_PIC, &CAwesomeHome::OnBnClickedHomePic)
	ON_BN_CLICKED(IDC_HOME_MINDMAP, &CAwesomeHome::OnBnClickedHomeMindmap)
	ON_COMMAND(ID_ADD, &CAwesomeHome::OnAdd)
END_MESSAGE_MAP()


// CAwesomeHome �����Դϴ�.

#ifdef _DEBUG
void CAwesomeHome::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeHome::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeHome �޽��� ó�����Դϴ�.


BOOL CAwesomeHome::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeHome::OnBnClickedHomeWrite()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_WRITE);
}


void CAwesomeHome::OnBnClickedHomePic()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_PIC);
}


void CAwesomeHome::OnBnClickedHomeMindmap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_Mmap);
}


void CAwesomeHome::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	pDC->Rectangle(50, 50, 590, 810);
	for (int i = 0; i < 12; i++) {
		pDC->MoveTo(50, 90 + i * 60);
		pDC->LineTo(590, 90 + i * 60);
	}
	for (int i = 0; i < 5; i++) {
		pDC->MoveTo(90 + i * 100, 50);
		pDC->LineTo(90 + i * 100, 810);
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(135, 70, _T("��"));
	pDC->TextOut(235, 70, _T("ȭ"));
	pDC->TextOut(335, 70, _T("��"));
	pDC->TextOut(435, 70, _T("��"));
	pDC->TextOut(535, 70, _T("��"));

	for (int i = 0; i < 12; i++) {
		CString str;
		if ((i + 9) > 12) {
			str.Format(_T("%d"), i - 3);
			pDC->TextOut(70, 90 + i * 60, str);
		}
		else {
			str.Format(_T("%d"), i + 9);
			pDC->TextOut(70, 90 + i * 60, str);
		}
	}
}


void CAwesomeHome::OnAdd()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//To Do : Dlg ����
	MessageBox(_T("���Ǹ�, ������, �ð�, ���"));

	// �Էµƴ� ġ��(����, ���ͼ�, ������ 10��, �������а� 305ȣ
	class_name = _T("������ ���α׷���");
	class_professor = _T("���ͼ�");
	class_day = 0; // 0 ~ 4 �� ~ ��
	class_start_hour = 1; // 0 ~ 11 9�� ~ 20��
	class_start_minute = 0; // 0 ~ 11 0�� ~ 55��
	class_end_hour = 2;
	class_end_minute = 10;
	class_room = _T("�������а� 305ȣ");

	// ���� rect ����
	CClientDC dc(this);
	srand((unsigned)time(NULL));
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));
	dc.SelectObject(brush);
	CRect rect(class_day * 100 + 90, class_start_hour * 60 + class_start_minute * 5 + 90, class_day * 100 + 190, class_end_hour * 60 + class_end_minute * 5 + 90);
	dc.Rectangle(rect);

	// rect�� ���Ǹ� �ֱ�
	//dc.DrawText(class_name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(class_name, &rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);

	// To Do : rect�� ������ List �����ϱ�
}
