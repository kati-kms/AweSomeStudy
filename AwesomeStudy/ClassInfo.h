#pragma once
#include "afxwin.h"
class CAwesomeHome;

// CClassInfo 대화 상자입니다.

class CClassInfo : public CDialog
{
	DECLARE_DYNAMIC(CClassInfo)

public:
	CClassInfo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CClassInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_CLASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
