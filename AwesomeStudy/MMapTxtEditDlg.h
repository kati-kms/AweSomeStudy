#pragma once


// CMMapTxtEditDlg ��ȭ �����Դϴ�.

class CMMapTxtEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CMMapTxtEditDlg)

public:
	CMMapTxtEditDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMMapTxtEditDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MMAP_TXT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_str;
};
