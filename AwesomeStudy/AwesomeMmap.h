#pragma once



// CAwesomeMmap �� ���Դϴ�.

class CAwesomeMmap : public CFormView
{
	DECLARE_DYNCREATE(CAwesomeMmap)

public:
	CAwesomeMmap();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAwesomeMmap();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWESOMEMMAP };
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
	virtual void OnDraw(CDC* pDC);
	afx_msg void OnHome();
};


