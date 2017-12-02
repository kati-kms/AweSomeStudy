#pragma once


// CWriteGoLine 대화 상자입니다.

class CWriteGoLine : public CDialog
{
	DECLARE_DYNAMIC(CWriteGoLine)

public:
	CWriteGoLine(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWriteGoLine();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WRITE_GOLINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_line;
};
