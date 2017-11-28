// AwesomePic.cpp : 구현 파일입니다.
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


// CAwesomePic 진단입니다.

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


// CAwesomePic 메시지 처리기입니다.


BOOL CAwesomePic::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CAwesomePic::OnHome()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_HOME);
}


void CAwesomePic::OnInitialUpdate()
{

	CFormView::OnInitialUpdate();
	CAwesomeStudyDoc* pDoc = GetDocument();
	if (pDoc->PicIsSaved == 0) {
		CAwesomeStudyDoc* pDoc = GetDocument();
		HTREEITEM root_branch = m_PicTree.InsertItem(_T("고급컴퓨터수학"), TVI_ROOT);
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
	IsPic = 0;                 //사진이 아닐때를 위해 초기화
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
	if (SUCCEEDED(image.Load(PicNodePath))) {    //사진이라고 판명나면 check=1;
		IsPic = 1;
		Invalidate();
	}
	else if (PicNodePath.Compare(_T("1"))) {
		return;
	}
	else {
		AfxMessageBox(_T("그림 파일이 아니거나 파일이 이동되었습니다."));
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
		AfxMessageBox(_T("파일지정을 취소하셨습니다."));
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
	if (IsPic == 1) {   //노드를 클릭해서 사진을 띄워야하면 사진띄우기
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
