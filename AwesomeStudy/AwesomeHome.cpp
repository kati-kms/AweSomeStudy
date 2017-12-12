// AwesomeHome.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeHome.h"
#include "AwesomeStudyDoc.h"
#include "MainFrm.h"
#include "ClassInfo.h"
#include <afxtempl.h>
#include "InfoSave.h"


// CAwesomeHome

IMPLEMENT_DYNCREATE(CAwesomeHome, CFormView)

CAwesomeHome::CAwesomeHome()
	: CFormView(IDD_AWESOMEHOME)
{
	m_pAddDlg = NULL;
	class_name = "";
	class_professor = "";
	class_day = 0;
	class_start_hour = 0;
	class_start_minute = 0;
	class_end_hour = 0;
	class_end_minute = 0;
	class_room = "";
	m_array.RemoveAll();
	AddList = FALSE;
	Select_num = 0;
	m_color[0] = RGB(255, 160, 122);
	m_color[1] = RGB(255, 127, 80);
	m_color[2] = RGB(188, 143, 143);
	m_color[3] = RGB(173, 255, 47);
	m_color[4] = RGB(144, 238, 144);
	m_color[5] = RGB(32, 178, 170);
	m_color[6] = RGB(135, 206, 235);
	m_color[7] = RGB(250, 240, 230);
	m_color[8] = RGB(123, 104, 238);
	m_color[9] = RGB(192, 192, 192);
	color_num = 0;
}

CAwesomeHome::~CAwesomeHome()
{
}

void CAwesomeHome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Control(pDX, IDC_INFO, m_list);
	DDX_Control(pDX, IDC_HOME_WRITE, m_write);
	DDX_Control(pDX, IDC_HOME_PIC, m_pic);
	DDX_Control(pDX, IDC_HOME_MINDMAP, m_map);
}

BEGIN_MESSAGE_MAP(CAwesomeHome, CFormView)
	ON_BN_CLICKED(IDC_HOME_WRITE, &CAwesomeHome::OnBnClickedHomeWrite)
	ON_BN_CLICKED(IDC_HOME_PIC, &CAwesomeHome::OnBnClickedHomePic)
	ON_BN_CLICKED(IDC_HOME_MINDMAP, &CAwesomeHome::OnBnClickedHomeMindmap)
	ON_COMMAND(ID_ADD, &CAwesomeHome::OnAdd)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CAwesomeHome::OnUpdateFileOpen)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_DELETE, &CAwesomeHome::OnBnClickedDelete)
	ON_UPDATE_COMMAND_UI(IDC_HOME, &CAwesomeHome::OnUpdateHome)
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
	CAwesomeStudyDoc* pDoc = (CAwesomeStudyDoc *)GetDocument();

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
	for (int i = 0; i < m_array.GetCount(); i++) {
		CBrush brush(m_array[i].m_color);
		pDC->SelectObject(brush);
		pDC->Rectangle(m_array[i].rect);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(m_array[i].m_class, &m_array[i].rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);
	}
}


void CAwesomeHome::OnAdd()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CClassInfo AddDlg;
	int result = AddDlg.DoModal();
	CInfoSave temp;
	if (result == IDOK) {
		temp.m_class = AddDlg.m_class;
		temp.m_professor = AddDlg.m_professor;
		temp.m_date = AddDlg.m_date;// 0 ~ 4 �� ~ ��
		temp.m_s_hour = AddDlg.m_s_hour; // 0 ~ 11 9�� ~ 20��
		temp.m_s_minute = AddDlg.m_s_minute; // 0 ~ 11 0�� ~ 55��
		temp.m_e_hour = AddDlg.m_e_hour;
		temp.m_e_minute = AddDlg.m_e_minute;
		temp.m_place = AddDlg.m_place;

		//Error : ���Ǹ��� ���� ���� ���
		if (temp.m_class == _T("")) {
			AfxMessageBox(_T("���Ǹ��� �������� �ʾҽ��ϴ�."));
			return;
		}

		// Error : ���� �ð��� ���ð��� ���� ��� or ���ð��� ���� ���
		if (temp.m_s_hour > temp.m_e_hour || ((temp.m_s_hour == temp.m_e_hour) && (temp.m_s_minute >= temp.m_e_minute))) {
			AfxMessageBox(_T("�ð��� �ٽ� �������ּ���."));
			return;
		}

		// Error : �̹� ������ �ð��� ���ǰ� �߰��� ���
		int error_Start = temp.m_s_hour * 12 + temp.m_s_minute;
		int error_End = temp.m_e_hour * 12 + temp.m_e_minute;
		for (int i = error_Start; i < error_End; i++)
			if (IsAble[temp.m_date][i] == TRUE) {
				AfxMessageBox(_T("�ش� �ð����� �̹� ���ǰ� �ֽ��ϴ�."));
				return;
			}

		// ���� rect ����
		CClientDC dc(this);
		srand((unsigned)time(NULL));
		CBrush brush(m_color[color_num]);
		color_num++;
		if (color_num > 9)
			color_num = 0;
		dc.SelectObject(brush);
		CRect rect(temp.m_date * 100 + 90, temp.m_s_hour * 60 + temp.m_s_minute * 5 + 90,
			temp.m_date * 100 + 190, temp.m_e_hour * 60 + temp.m_e_minute * 5 + 90);
		dc.Rectangle(rect);
		temp.m_color = dc.GetPixel(temp.m_date * 100 + 90 + 1, temp.m_s_hour * 60 + temp.m_s_minute * 5 + 90 + 1);
		temp.rect = rect;

		// rect�� ���Ǹ� �ֱ�
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(temp.m_class, &rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);


		// �ð����� �ֱ�
		int Start = temp.m_s_hour * 12 + temp.m_s_minute;
		int End = temp.m_e_hour * 12 + temp.m_e_minute;
		for (int i = Start; i < End; i++)
			IsAble[temp.m_date][i] = TRUE;

		// ���� ���� m_array�� ����
		m_array.Add(temp);
	}
}


void CAwesomeHome::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndHome) {
	pCmdUI->Enable(0);
	}  //���������ÿ� �ФФФФФФ�
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CAwesomeHome::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	AddList = FALSE;
	m_delete.EnableWindow(FALSE);
	for (int i = 0; i < m_array.GetSize(); i++) {
		Select_num = i;
		if (m_array[i].rect.PtInRect(point)) {
			m_list.ResetContent();
			CString str;
			str.Format(_T("���Ǹ� : %s"), m_array[i].m_class);
			m_list.AddString(str);
			str.Format(_T("������ : %s"), m_array[i].m_professor);
			m_list.AddString(str);
			switch (m_array[i].m_date) {
			case 0: str.Format(_T("���� : ������"));
				break;
			case 1: str.Format(_T("���� : ȭ����"));
				break;
			case 2: str.Format(_T("���� : ������"));
				break;
			case 3: str.Format(_T("���� : �����"));
				break;
			case 4: str.Format(_T("���� : �ݿ���"));
				break;
			}
			m_list.AddString(str);
			str.Format(_T("�ð� : %d�� %d�� ~ "), m_array[i].m_s_hour + 9, (m_array[i].m_s_minute) * 5);
			m_list.AddString(str);
			str.Format(_T("		  %d�� %d��"), m_array[i].m_e_hour + 9, (m_array[i].m_e_minute) * 5);
			m_list.AddString(str);
			str.Format(_T("��� : %s"), m_array[i].m_place);
			m_list.AddString(str);

			AddList = TRUE;
			m_delete.EnableWindow(TRUE);
			break;
		}
	}
	if (AddList == FALSE)
		m_list.ResetContent();
	CFormView::OnLButtonDown(nFlags, point);
}


void CAwesomeHome::OnBnClickedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int Start = m_array[Select_num].m_s_hour * 12 + m_array[Select_num].m_s_minute;
	int End = m_array[Select_num].m_e_hour * 12 + m_array[Select_num].m_e_minute;
	for (int i = Start; i < End; i++)
		IsAble[m_array[Select_num].m_date][i] = FALSE;

	m_array.RemoveAt(Select_num);
	m_list.ResetContent();
	Invalidate();
}

void CAwesomeHome::OnUpdateHome(CCmdUI *pCmdUI)
{
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndHome) {
		pCmdUI->Enable(0);
	}
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
