// VeiwPassDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "VeiwPassDialog.h"
#include "afxdialogex.h"


// CVeiwPassDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVeiwPassDialog, CDialog)

CVeiwPassDialog::CVeiwPassDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SET_PASSWORD, pParent)
	, m_password(_T(""))
{

}

CVeiwPassDialog::~CVeiwPassDialog()
{
}

void CVeiwPassDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_password);
}


BEGIN_MESSAGE_MAP(CVeiwPassDialog, CDialog)
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CVeiwPassDialog �޽��� ó�����Դϴ�.


void CVeiwPassDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nHitTest == HTCLOSE) {
		AfxMessageBox(_T("��й�ȣ�� �ݵ�� �����ϼž� �մϴ�!"));
	}
	//CDialog::OnNcLButtonDown(nHitTest, point);
}
