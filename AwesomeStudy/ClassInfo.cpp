// ClassInfo.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "ClassInfo.h"
#include "afxdialogex.h"
#include "AwesomeHome.h"


// CClassInfo ��ȭ �����Դϴ�.

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


// CClassInfo �޽��� ó�����Դϴ�.


//BOOL CClassInfo::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
//	SetDlgItemText(IDC_STR, m_str)
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
//}


void CClassInfo::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CDialog::OnOK();
}


void CClassInfo::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(IDCANCEL);
	CDialog::OnCancel();
}

/*
void CClassInfo::OnBnClickedAddTime()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
*/