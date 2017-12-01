// VeiwPassDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "VeiwPassDialog.h"
#include "afxdialogex.h"


// CVeiwPassDialog 대화 상자입니다.

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


// CVeiwPassDialog 메시지 처리기입니다.


void CVeiwPassDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nHitTest == HTCLOSE) {
		AfxMessageBox(_T("비밀번호를 반드시 설정하셔야 합니다!"));
	}
	//CDialog::OnNcLButtonDown(nHitTest, point);
}
