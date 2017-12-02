// AwesomeWrite.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeWrite.h"
#include "MainFrm.h"

#include "WriteGoLine.h"


// CAwesomeWrite
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

IMPLEMENT_DYNCREATE(CAwesomeWrite, CFormView)

CAwesomeWrite::CAwesomeWrite()
	: CFormView(IDD_AWESOMEWRITE)
{
	pFindDlg = NULL;
	pReplaceDlg = NULL;
	m_next_start = 0;
	m_find_next = false;
}

CAwesomeWrite::~CAwesomeWrite()
{
}

void CAwesomeWrite::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WRITE, m_write);
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
	ON_COMMAND(ID_WRITE_DEL, &CAwesomeWrite::OnWriteDel)
	ON_COMMAND(ID_WRITE_FIND, &CAwesomeWrite::OnWriteFind)
	ON_COMMAND(ID_WRITE_FINDNEXT, &CAwesomeWrite::OnWriteFindnext)
	ON_COMMAND(ID_WRITE_REPLACE, &CAwesomeWrite::OnWriteReplace)
	ON_COMMAND(ID_WRITE_GO, &CAwesomeWrite::OnWriteGo)
	ON_COMMAND(ID_WRITE_DATETIME, &CAwesomeWrite::OnWriteDatetime)
	ON_COMMAND(ID_WRITE_FONTSTATE, &CAwesomeWrite::OnWriteFontstate)
	ON_EN_CHANGE(IDC_WRITE, &CAwesomeWrite::OnEnChangeWrite)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFindReplaceCmd)
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
	//���� �߰�
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

void CAwesomeWrite::OnWriteDel()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_write.Clear();
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
	//���ڿ� ã�°� �������� ��� �߰� --> viewedit.cpp ���� Ȯ��
	m_find_next = true;
	OnFindReplaceCmd(0,0);
}

void CAwesomeWrite::OnWriteReplace()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (pReplaceDlg != NULL)
		pReplaceDlg->SetFocus();
	else {
		pReplaceDlg = new CFindReplaceDialog();
		pReplaceDlg->Create(FALSE, _T(""), _T(""), FR_DOWN, this);
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
	//2��Ȯ��
}

//----------------------------------------

void CAwesomeWrite::OnWriteFontstate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//cfont dialog // å
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
}


LRESULT CAwesomeWrite::OnFindReplaceCmd(WPARAM wParam, LPARAM lParam)
{
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
			AfxMessageBox(FindStr + _T("�� ã�� �� �����ϴ�"), MB_ICONINFORMATION);
			return 0;
		}
		int end = start + length;
		m_write.SetSel(m_next_start + start, m_next_start + end);
		m_next_start = m_next_start + end; // aaa�׽�Ʈ�غ�����
		m_find_next = false;
	}
	return LRESULT();
}
