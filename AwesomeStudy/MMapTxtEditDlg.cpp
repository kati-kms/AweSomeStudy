// MMapTxtEditDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "MMapTxtEditDlg.h"
#include "afxdialogex.h"


// CMMapTxtEditDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMMapTxtEditDlg, CDialog)

CMMapTxtEditDlg::CMMapTxtEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MMAP_TXT_DLG, pParent)
	, m_str(_T(""))
{

}

CMMapTxtEditDlg::~CMMapTxtEditDlg()
{
}

void CMMapTxtEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STR, m_str);
}


BEGIN_MESSAGE_MAP(CMMapTxtEditDlg, CDialog)
END_MESSAGE_MAP()


// CMMapTxtEditDlg �޽��� ó�����Դϴ�.
