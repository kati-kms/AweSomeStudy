#pragma once


// CWriteGoLine ��ȭ �����Դϴ�.

class CWriteGoLine : public CDialog
{
	DECLARE_DYNAMIC(CWriteGoLine)

public:
	CWriteGoLine(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWriteGoLine();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WRITE_GOLINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_line;
};
