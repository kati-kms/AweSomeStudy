#pragma once



// CAwesomeHome �� ���Դϴ�.

class CAwesomeHome : public CFormView
{
	DECLARE_DYNCREATE(CAwesomeHome)

public:
	CAwesomeHome();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAwesomeHome();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWESOMEHOME };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public :
	CString class_name; // EditBox > ���Ǹ�
	CString class_professor; // EditBox > ������
	int class_day; // ComboBox > �ð�(����)
	int class_start_hour; // ComboBox > �ð�(��)
	int class_start_minute; // ComboBox > �ð�(��)
	int class_end_hour; // ComboBox > �ð�(��)
	int class_end_minute; // ComboBox > �ð�(��)
	CString class_room; // EditBox > ������ 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnBnClickedHomeWrite();
	afx_msg void OnBnClickedHomePic();
	afx_msg void OnBnClickedHomeMindmap();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnAdd();
};


