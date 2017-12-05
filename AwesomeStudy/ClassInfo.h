#pragma once
#include "afxwin.h"
class CAwesomeHome;

// CClassInfo ��ȭ �����Դϴ�.

class CClassInfo : public CDialog
{
	DECLARE_DYNAMIC(CClassInfo)

public:
	CClassInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClassInfo();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_CLASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CAwesomeHome *m_pHome;
	CString m_class;
	//CString m_professror;
	CString m_professor;
	//int m;
	int m_s_hour;
	int m_s_minute;
	int m_e_hour;
	int m_e_minute;
	CString m_place;
	int m_date;
//	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_add_time;
	afx_msg void OnBnClickedAddTime();
};
