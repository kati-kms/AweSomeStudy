// AwesomeWrite.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeWrite.h"
#include "MainFrm.h"


// CAwesomeWrite

IMPLEMENT_DYNCREATE(CAwesomeWrite, CFormView)

CAwesomeWrite::CAwesomeWrite()
	: CFormView(IDD_AWESOMEWRITE)
{

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
	CFindReplaceDialog *pFindDlg = NULL;
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
}

void CAwesomeWrite::OnWriteReplace()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFindReplaceDialog *pReplaceDlg = NULL;
	if (pReplaceDlg != NULL)
		pReplaceDlg->SetFocus();
	else {
		pReplaceDlg = new CFindReplaceDialog();
		pReplaceDlg->Create(FALSE, _T(""), _T(""), FR_DOWN, this);
	}
	//���ڿ� ã�°� �������� ��� �߰� --> viewedit.cpp ���� Ȯ��
}

void CAwesomeWrite::OnWriteGo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//ã�Ƽ� �����ŷ� ���°�. // ���̾�α� �� ��������
	//��ü �� ����ϴ� ���� ����� // enchanged �̺�Ʈ ó���⿡�� ó��
	//Ŀ���̵��� ����Ʈ! > viewedit.cpp
}

//----------------------------------------

void CAwesomeWrite::OnWriteSelectall()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	int len = m_write.GetWindowTextLength();
	m_write.SetSel(0, len);
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

}
