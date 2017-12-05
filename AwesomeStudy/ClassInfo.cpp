// ClassInfo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "ClassInfo.h"
#include "afxdialogex.h"
#include "AwesomeHome.h"


// CClassInfo 대화 상자입니다.

IMPLEMENT_DYNAMIC(CClassInfo, CDialog)

CClassInfo::CClassInfo(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ADD_CLASS, pParent)
	, m_class(_T(""))
	//, m_professro(_T(""))
	, m_professor(_T(""))
	//, m(0)
	, m_s_hour(0)
	, m_s_minute(0)
	, m_e_hour(0)
	, m_e_minute(0)
	, m_place(_T(""))
	, m_date(0)
{

}

CClassInfo::~CClassInfo()
{
}

void CClassInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CLASS, m_class);
	//DDX_Text(pDX, IDC_PROPESSOR, m_professro);
	DDX_Text(pDX, IDC_PROPESSOR, m_professor);
	//DDX_CBIndex(pDX, IDC_S_HOUR, m);
	DDX_CBIndex(pDX, IDC_S_HOUR, m_s_hour);
	DDX_CBIndex(pDX, IDC_S_MINUTE, m_s_minute);
	DDX_CBIndex(pDX, IDC_E_HOUR, m_e_hour);
	DDX_CBIndex(pDX, IDC_E_MINUTE, m_e_minute);
	DDX_Text(pDX, IDC_PLACE, m_place);
	DDX_CBIndex(pDX, IDC_DATE, m_date);
	//DDX_Control(pDX, IDC_ADD_TIME, m_add_time);
}


BEGIN_MESSAGE_MAP(CClassInfo, CDialog)
	ON_BN_CLICKED(IDOK, &CClassInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CClassInfo::OnBnClickedCancel)
	//ON_BN_CLICKED(IDC_ADD_TIME, &CClassInfo::OnBnClickedAddTime)
END_MESSAGE_MAP()


// CClassInfo 메시지 처리기입니다.


//BOOL CClassInfo::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	// TODO:  여기에 추가 초기화 작업을 추가합니다.
//	SetDlgItemText(IDC_STR, m_str)
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
//}


void CClassInfo::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CDialog::OnOK();
}


void CClassInfo::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(IDCANCEL);
	CDialog::OnCancel();
}

/*
void CClassInfo::OnBnClickedAddTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
*/