#pragma once


// CVeiwPassDialog 대화 상자입니다.

class CVeiwPassDialog : public CDialog
{
	DECLARE_DYNAMIC(CVeiwPassDialog)

public:
	CVeiwPassDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVeiwPassDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_PASSWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
