#pragma once


// CPicNameDialog ��ȭ �����Դϴ�.

class CPicNameDialog : public CDialog
{
	DECLARE_DYNAMIC(CPicNameDialog)

public:
	CPicNameDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPicNameDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_str;
};
