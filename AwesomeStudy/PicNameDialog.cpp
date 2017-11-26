// PicNameDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "PicNameDialog.h"
#include "afxdialogex.h"


// CPicNameDialog 대화 상자입니다.

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


// CPicNameDialog 메시지 처리기입니다.
