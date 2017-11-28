// AwesomePic.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomePic.h"
#include "MainFrm.h"
#include "AwesomeStudyDoc.h"
#include "PicNameDialog.h"



// CAwesomePic

IMPLEMENT_DYNCREATE(CAwesomePic, CFormView)

CAwesomePic::CAwesomePic()
	: CFormView(IDD_AWESOMEPIC)
{
	IsPic = 0;
}

CAwesomePic::~CAwesomePic()
{
}

void CAwesomePic::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PicTree, m_PicTree);
	DDX_Control(pDX, IDC_EDIT1, m_PicMemo);
}

BEGIN_MESSAGE_MAP(CAwesomePic, CFormView)
	ON_COMMAND(IDC_HOME, &CAwesomePic::OnHome)
	ON_NOTIFY(NM_CLICK, IDC_PicTree, &CAwesomePic::OnNMClickPictree)
	ON_BN_CLICKED(IDC_PIC_ADD_FOLDER, &CAwesomePic::OnBnClickedPicAddFolder)
	ON_BN_CLICKED(IDC_PIC_ADD_FILE, &CAwesomePic::OnBnClickedPicAddFile)
	ON_BN_CLICKED(IDC_PIC_DELETE, &CAwesomePic::OnBnClickedPicDelete)
	ON_BN_CLICKED(ID_FILE_SAVE, &CAwesomePic::OnBnClickedFileSave)
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


void CAwesomePic::OnInitialUpdate()
{

	CFormView::OnInitialUpdate();
	CAwesomeStudyDoc* pDoc = GetDocument();
	if (pDoc->PicIsSaved == 0) {
		CAwesomeStudyDoc* pDoc = GetDocument();
		HTREEITEM root_branch = m_PicTree.InsertItem(_T("�����ǻ�ͼ���"), TVI_ROOT);
		pDoc->PicNodeToPathMap.SetAt(m_PicTree.GetItemText(root_branch), _T("1"));
		m_PicTree.Select(root_branch, TVGN_CARET);
	}
}


CAwesomeStudyDoc* CAwesomePic::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAwesomeStudyDoc)));
	return (CAwesomeStudyDoc*)m_pDocument;

}


void CAwesomePic::OnNMClickPictree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CAwesomeStudyDoc* pDoc = GetDocument();
	IsPic = 0;                 //������ �ƴҶ��� ���� �ʱ�ȭ
	CPoint p;
	GetCursorPos(&p);
	UINT flag;
	m_PicTree.ScreenToClient(&p);
	PicNode = m_PicTree.HitTest(p, &flag);
	CString name = m_PicTree.GetItemText(PicNode);
	pDoc->PicNodeToPathMap.Lookup(name, PicNodePath);
	CString str;
	pDoc->PicNodeToTextMap.Lookup(name, str);
	m_PicMemo.SetWindowText(str);
	CImage image;
	if (SUCCEEDED(image.Load(PicNodePath))) {    //�����̶�� �Ǹ��� check=1;
		IsPic = 1;
		Invalidate();
	}
	else if (PicNodePath.Compare(_T("1"))) {
		return;
	}
	else {
		AfxMessageBox(_T("�׸� ������ �ƴϰų� ������ �̵��Ǿ����ϴ�."));
		pDoc->PicNodeToPathMap.RemoveKey(m_PicTree.GetItemText(PicNode));
		m_PicTree.DeleteItem(PicNode);
	}
	*pResult = 0;
}


void CAwesomePic::OnBnClickedPicAddFolder()
{
	CAwesomeStudyDoc* pDoc = GetDocument();
	HTREEITEM pnode = m_PicTree.GetSelectedItem();
	CPicNameDialog dlg;
	CString name;
	if (dlg.DoModal() == IDOK) {
		name = dlg.m_str;
	}
	else return;
	PicNode = m_PicTree.InsertItem(name, pnode);
	pDoc->PicNodeToPathMap.SetAt(name, _T("1"));
	m_PicTree.Select(PicNode, TVGN_CARET);

}


void CAwesomePic::OnBnClickedPicAddFile()
{
	CAwesomeStudyDoc* pDoc = GetDocument();
	CString strFileName;
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_READONLY, _T("ALL Files(*.*)|*.*|"));

	int iRet = fDlg.DoModal();
	strFileName = fDlg.GetPathName();
	if (iRet != IDOK) {
		AfxMessageBox(_T("���������� ����ϼ̽��ϴ�."));
		return;
	}
	pDoc->PicPath = strFileName;
	pDoc->PicIsSaved = 1;
	HTREEITEM pnode = m_PicTree.GetSelectedItem();
	CPicNameDialog dlg;
	CString name;
	if (dlg.DoModal() == IDOK) {
		name = dlg.m_str;
	}
	else return;
	PicNode = m_PicTree.InsertItem(name, pnode);
	pDoc->PicNodeToPathMap.SetAt(name, pDoc->PicPath);
	m_PicTree.Select(PicNode, TVGN_CARET);
}


void CAwesomePic::OnBnClickedPicDelete()
{
	CAwesomeStudyDoc* pDoc = GetDocument();
	pDoc->PicNodeToPathMap.RemoveKey(m_PicTree.GetItemText(PicNode));
	m_PicTree.DeleteItem(PicNode);
}


void CAwesomePic::OnBnClickedFileSave()
{
	CAwesomeStudyDoc* pDoc = GetDocument();
	CString str;
	m_PicMemo.GetWindowText(str);
	pDoc->PicNodeToTextMap.SetAt(m_PicTree.GetItemText(PicNode), str);
}


void CAwesomePic::OnDraw(CDC* pDC)
{
	CAwesomeStudyDoc* pDoc = GetDocument();
	if (IsPic == 1) {   //��带 Ŭ���ؼ� ������ ������ϸ� ��������
		CImage Image;
		Image.Load(PicNodePath);
		//Image.BitBlt(pDC->m_hDC, 700, 5, SRCCOPY);
		Image.StretchBlt(pDC->m_hDC, 700, 5, 500, 500, SRCCOPY);
		CSize size;
		size.cx = Image.GetWidth()+700;
		size.cy = Image.GetHeight();
		SetScrollSizes(MM_TEXT, size);
	}
}
