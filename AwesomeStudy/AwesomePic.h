#pragma once



// CAwesomePic �� ���Դϴ�.

class CAwesomePic : public CFormView
{
	DECLARE_DYNCREATE(CAwesomePic)

public:
	CAwesomePic();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAwesomePic();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWESOMEPIC };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	afx_msg void OnHome();
};


