// PicNameDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "PicNameDialog.h"
#include "afxdialogex.h"


// CPicNameDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPicNameDialog, CDialog)

CPicNameDialog::CPicNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_str(_T(""))
{

}

CPicNameDialog::~CPicNameDialog()
{
}

void CPicNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(CPicNameDialog, CDialog)
END_MESSAGE_MAP()


// CPicNameDialog �޽��� ó�����Դϴ�.
