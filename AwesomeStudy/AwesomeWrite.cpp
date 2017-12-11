// AwesomeWrite.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeWrite.h"
#include "MainFrm.h"
#include "AwesomeStudyDoc.h"
#include "PicNameDialog.h"

#include "WriteGoLine.h"


// CAwesomeWrite
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

IMPLEMENT_DYNCREATE(CAwesomeWrite, CFormView)

CAwesomeWrite::CAwesomeWrite()
	: CFormView(IDD_AWESOMEWRITE)
{
	pFindDlg = NULL;
	m_color = RGB(0, 0, 0);

	m_next_start = 0;
	m_find_next = false;
	m_replace_first = false;
}

CAwesomeWrite::~CAwesomeWrite()
{
}

void CAwesomeWrite::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WRITE, m_write);
	DDX_Control(pDX, IDC_TREE1, m_treeWrite);
}

BEGIN_MESSAGE_MAP(CAwesomeWrite, CFormView)
	ON_COMMAND(IDC_HOME, &CAwesomeWrite::OnHome)
	ON_BN_CLICKED(IDC_WRITE_ALLCLEAR, &CAwesomeWrite::OnBnClickedWriteAllclear)
	ON_BN_CLICKED(IDC_WRITE_SAVE, &CAwesomeWrite::OnBnClickedWriteSave)
	ON_COMMAND(ID_WRITE_SELECTALL, &CAwesomeWrite::OnWriteSelectall)
	ON_BN_CLICKED(IDC_WRITE_CLOSE, &CAwesomeWrite::OnBnClickedWriteClose)
	ON_COMMAND(ID_WRITE_UNDO, &CAwesomeWrite::OnWriteUndo)
	ON_COMMAND(ID_WRITE_CUT, &CAwesomeWrite::OnWriteCut)
	ON_COMMAND(ID_WRITE_COPY, &CAwesomeWrite::OnWriteCopy)
	ON_COMMAND(ID_WRITE_PASTE, &CAwesomeWrite::OnWritePaste)
	ON_COMMAND(ID_WRITE_FIND, &CAwesomeWrite::OnWriteFind)
	ON_COMMAND(ID_WRITE_FINDNEXT, &CAwesomeWrite::OnWriteFindnext)
	ON_COMMAND(ID_WRITE_REPLACE, &CAwesomeWrite::OnWriteReplace)
	ON_COMMAND(ID_WRITE_GO, &CAwesomeWrite::OnWriteGo)
	ON_COMMAND(ID_WRITE_DATETIME, &CAwesomeWrite::OnWriteDatetime)
	ON_COMMAND(ID_WRITE_FONTSTATE, &CAwesomeWrite::OnWriteFontstate)
	ON_EN_CHANGE(IDC_WRITE, &CAwesomeWrite::OnEnChangeWrite)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFindReplaceCmd)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_WriteTree, &CAwesomeWrite::OnNMClickWritetree)
END_MESSAGE_MAP()


// CAwesomeWrite �����Դϴ�.

#ifdef _DEBUG
void CAwesomeWrite::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeWrite::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeWrite �޽��� ó�����Դϴ�.
CAwesomeStudyDoc* CAwesomeWrite::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAwesomeStudyDoc)));
	return (CAwesomeStudyDoc*)m_pDocument;

}

void CAwesomeWrite::OnHome()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);

}


BOOL CAwesomeWrite::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeWrite::OnBnClickedWriteAllclear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int len = m_write.GetWindowTextLength();
	m_write.SetSel(0, len);
	m_write.Clear();
}



void CAwesomeWrite::OnBnClickedWriteSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	m_write.GetWindowText(str);
	CAwesomeStudyDoc* pDoc = GetDocument();
	CPicNameDialog dlg;
	CString name;
	if (dlg.DoModal() == IDOK) {
		name = dlg.m_str;
	}
	else return;
	//str�����ϸ��
	PicNode = m_treeWrite.InsertItem(name, TVI_ROOT);
	pDoc->WriteNodeToTextMap.SetAt(name, str);
	m_treeWrite.Select(PicNode, TVGN_CARET);
	int len = m_write.GetWindowTextLength();
	m_write.SetSel(0, len);
	m_write.Clear();
	//��Ʈ ����
	//pDoc->w.SetAt(name, m_font);
	//���� ����
	//pDoc->WriteNodeToColorMap.SetAt(name, m_color);
}


void CAwesomeWrite::OnBnClickedWriteClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//�������� ����� Home���� �̵�
	//���� ������ �ݱ��, �׳� ����
}


//�޴��� ó��


void CAwesomeWrite::OnWriteUndo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_write.Undo();
}

//----------------------------------------

void CAwesomeWrite::OnWriteCut()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_write.Cut();
}

void CAwesomeWrite::OnWriteCopy()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_write.Copy();
}

void CAwesomeWrite::OnWritePaste()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_write.Paste();
}

//----------------------------------------

void CAwesomeWrite::OnWriteFind()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (pFindDlg != NULL)
		pFindDlg->SetFocus();
	else {
		pFindDlg = new CFindReplaceDialog();
		pFindDlg->Create(TRUE, _T(""), _T(""), FR_DOWN, this);
	}
}

void CAwesomeWrite::OnWriteFindnext()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_find_next = true;
	OnFindReplaceCmd(0,0);
}

void CAwesomeWrite::OnWriteReplace()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (pFindDlg != NULL) {
		pFindDlg->SetFocus();
	}
	else {
		pFindDlg = new CFindReplaceDialog();
		m_replace_first = true;
		pFindDlg->Create(FALSE, _T(""), _T(""), FR_DOWN, this);
	}
}

void CAwesomeWrite::OnWriteGo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWriteGoLine dlg;
	int TotalLine = m_write.GetLineCount();
	int result = dlg.DoModal();

	if (result == IDOK) {
		if (dlg.m_line > TotalLine) {
			//����
			AfxMessageBox(_T("�ٹ�ȣ�� ��ü �� ���� �ѽ��ϴ�"),MB_ICONINFORMATION);
		}
		else {
			//go goline
			int index = m_write.LineIndex(dlg.m_line - 1);
			m_write.SetSel(index, index, true);
			Invalidate();
		}
	}
	else
		Invalidate();
}

//----------------------------------------

void CAwesomeWrite::OnWriteSelectall()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	m_write.SetSel(0, -1);
}

void CAwesomeWrite::OnWriteDatetime()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CTime tm;
	tm = CTime::GetCurrentTime();
	CString str_date;
	str_date.Format(_T("%d-%d-%d "), tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	CString str_am_pm;
	int Hour = tm.GetHour();
	if (Hour < 12) {
		str_am_pm = _T("���� ");
	}
	else {
		Hour -= 12;
		str_am_pm = _T("���� ");
	}
	if (Hour == 0)
		Hour = 12; // ���� 12�� ����ó��
	CString str_time;
	str_time.Format(_T("%d : %d "), Hour, tm.GetMinute());
	m_write.ReplaceSel(str_am_pm + str_time + str_date);
}

//----------------------------------------

void CAwesomeWrite::OnWriteFontstate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFontDialog FontDlg;
	
	if (FontDlg.DoModal() == IDOK) {
		//�Ź� ��Ʈ�� �������ϴ� ������ ���� // ����� �ذᰢ
		m_color = FontDlg.GetColor();
		LOGFONT lf;
		if (m_font.m_hObject != NULL)
			m_font.DeleteObject();
		FontDlg.GetCurrentFont(&lf);
		
		m_font.CreateFontIndirectW(&lf);
		m_write.SetFont(&m_font);

		// ���� ���ؾ���
		CDC *pDC = GetDC();
		CWnd *pWnd = AfxGetMainWnd();
		OnCtlColor(pDC, pWnd,m_color);
		//OnCtlColor()
	}
}

//-----------------------------------------------------------------------editâ ��ü �̺�Ʈ ��Ʈ��------------------------------------------------------

void CAwesomeWrite::OnEnChangeWrite()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���ڿ��� �ٲ�� Updata()? �Լ� ȣ�� // for ����
	// ���ڿ��� �ٲ�� ��ü�� ����ϱ�
	
	int total_line = m_write.GetLineCount();
	CString str;
	str.Format(_T("%d"), total_line);
	//AfxMessageBox(str);	
	//���¹ٿ� �߰��ϱ�
}


LRESULT CAwesomeWrite::OnFindReplaceCmd(WPARAM wParam, LPARAM lParam)
{
	if (pFindDlg->IsTerminating()) {
		pFindDlg = NULL;
		m_next_start = 0; // ������������
		return 0;
	}
	if (pFindDlg->FindNext() || m_find_next) {
		//�˻���String
		CString FindStr;
		FindStr = pFindDlg->GetFindString();
		int length = FindStr.GetLength();
		//��ü String
		CString TotalWrite;
		m_write.GetWindowText(TotalWrite); // ��üString ��������   // ã�������� ©���� �� // next_start������ string
		int total_length = TotalWrite.GetLength();

		//Sub String
		CString SubWrite;
		SubWrite = TotalWrite.Right(total_length - m_next_start); //�������� ã�� ���ڿ��� ����
		int start = SubWrite.Find(FindStr);
		if (start == -1) {
			AfxMessageBox(FindStr + _T("�� ã�� �� �����ϴ�"), /*MB_ICONINFORMATION*/MB_ICONWARNING);
			return 0;
		}
		int end = start + length;
		m_write.SetSel(m_next_start + start, m_next_start + end);
		m_next_start = m_next_start + end;
		m_find_next = false;
	}
	else if (pFindDlg->ReplaceCurrent() || m_find_next) {
		if (!m_replace_first) {
			m_write.ReplaceSel(pFindDlg->GetReplaceString());
		}

		//�˻���String
		CString FindStr;
		FindStr = pFindDlg->GetFindString();
		int length = FindStr.GetLength();
		//��ü String
		CString TotalWrite;
		m_write.GetWindowText(TotalWrite); // ��üString ��������   // ã�������� ©���� �� // next_start������ string
		int total_length = TotalWrite.GetLength();

		//Sub String
		CString SubWrite;
		SubWrite = TotalWrite.Right(total_length - m_next_start); //�������� ã�� ���ڿ��� ����
		int start = SubWrite.Find(FindStr);
		if (start == -1) {
			AfxMessageBox(FindStr + _T("�� ã�� �� �����ϴ�"), MB_ICONINFORMATION);
			return 0;
		}
		int end = start + length;
		m_write.SetSel(m_next_start + start, m_next_start + end);
		m_next_start = m_next_start + end;
		m_find_next = false;
		m_replace_first = false;
	}
	else if (pFindDlg->ReplaceAll()) {
		int start = 0;
		while (1) {
			//�˻���String
			CString FindStr;
			FindStr = pFindDlg->GetFindString();
			int length = FindStr.GetLength();
			//��ü String
			CString TotalWrite;
			m_write.GetWindowText(TotalWrite); // ��üString ��������   // ã�������� ©���� �� // next_start������ string
			int total_length = TotalWrite.GetLength();

			//Sub String
			CString SubWrite;
			SubWrite = TotalWrite.Right(total_length - m_next_start); //�������� ã�� ���ڿ��� ����
			int start = SubWrite.Find(FindStr);
			if (start == -1) {
				break;
			}
			int end = start + length;
			m_write.SetSel(m_next_start + start, m_next_start + end);
			m_next_start = m_next_start + end;
			m_find_next = false;

			m_write.ReplaceSel(pFindDlg->GetReplaceString());
		}
	}
	return LRESULT();
}

HBRUSH CAwesomeWrite::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (pWnd->GetDlgCtrlID() == IDC_WRITE /* �� �ٲٷ��� ��Ʈ���� id*/) {
		hbr = (HBRUSH)::GetSysColorBrush(COLOR_WINDOW);  // ��� �귯��
		pDC->SetBkColor(RGB(255, 255, 255)); // ����
		pDC->SetTextColor(m_color);  // �ؽ�Ʈ ��
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

// ��Ʈ�ѵ� ��ġ �� ������ ����

void CAwesomeWrite::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	double CenterRate = 0.8; // Center Rate : 1 - CenterRate    ���� 
	if (m_write.GetSafeHwnd() != NULL && m_treeWrite.GetSafeHwnd() != NULL)
	{
		CRect editLogRect; // ����Ʈ �ڽ��� ����
		m_write.GetWindowRect(editLogRect); // ����Ʈ �ڽ��� ��ũ�� ������ ����
														  // ����Ʈ �ڽ��� ��ũ�� ������ CMyFormView ��ü�� Ŭ���̾�Ʈ ������ �������� ����
		ScreenToClient(editLogRect);
		CRect clientRect;
		GetClientRect(clientRect); // CMyFormView ��ü�� Ŭ���̾�Ʈ ������ ����

		editLogRect.right = (long)(clientRect.right * CenterRate) - 15; // Ŭ���̾�Ʈ ������ �����ʿ� 15�ȼ��� ������ �д�.
		editLogRect.bottom = clientRect.bottom - 15; // Ŭ���̾�Ʈ ������ �ϴܿ� 15�ȼ��� ������ �д�.

		m_write.MoveWindow(editLogRect); // ����Ʈ �ڽ��� ������ ��ġ�� ������

		
		CRect treeLogRect;
		m_treeWrite.GetWindowRect(treeLogRect);
		ScreenToClient(treeLogRect);
		

		treeLogRect.left = editLogRect.right + 15;
		treeLogRect.right = clientRect.right -15;
		treeLogRect.bottom = clientRect.bottom - 15;

	
		m_treeWrite.MoveWindow(treeLogRect);
/*	
		CString str;
		str.Format(_T("Er %d Tl %d Tr %d"), editLogRect.right, treeLogRect.left, treeLogRect.right);
		AfxMessageBox(str);
		*/
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CAwesomeWrite::OnNMClickWritetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CAwesomeStudyDoc* pDoc = GetDocument();
	CPoint p;
	GetCursorPos(&p);
	UINT flag;
	m_treeWrite.ScreenToClient(&p);
	PicNode = m_treeWrite.HitTest(p, &flag);
	CString name = m_treeWrite.GetItemText(PicNode);
	CString str;
	pDoc->WriteNodeToTextMap.Lookup(name, str);
	m_write.SetWindowText(str);
	//pDoc->WriteNodeToFontMap.Lookup(name,m_font);
	//pDoc->WriteNodeToColorMap.Lookup(name, m_color);
	
	//m_write.SetFont(&m_font);

	/*CDC *pDC = GetDC();
	CWnd *pWnd = AfxGetMainWnd();
	OnCtlColor(pDC, pWnd, m_color);*/
	*pResult = 0;
}
