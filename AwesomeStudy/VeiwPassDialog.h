#pragma once


// CVeiwPassDialog ��ȭ �����Դϴ�.

class CVeiwPassDialog : public CDialog
{
	DECLARE_DYNAMIC(CVeiwPassDialog)

public:
	CVeiwPassDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVeiwPassDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_PASSWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
