#pragma once
class CClassInfo;


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
	CClassInfo *m_pAddDlg;
	CString class_name; // EditBox > ���Ǹ�
	CString class_professor; // EditBox > ������
	int class_day; // ComboBox > �ð�(����)
	int class_start_hour; // ComboBox > �ð�(��)
	int class_start_minute; // ComboBox > �ð�(��)
	int class_end_hour; // ComboBox > �ð�(��)
	int class_end_minute; // ComboBox > �ð�(��)
	CString class_room; // EditBox > ������ 
	BOOL IsAble[5][144];
	struct MyClass {
		CString m_class;
		CString m_professor;
		int m_s_hour;
		int m_s_minute;
		int m_e_hour;
		int m_e_minute;
		CString m_place;
		int m_date;
		COLORREF m_color;
		CRect rect;
		MyClass() {};
		MyClass(CString m_class, CString m_professor, int m_s_hour, int m_s_minute, int m_e_hour, int m_e_minute,
			CString m_place, int m_date, COLORREF m_color, CRect rect) {
			m_class = _T("");
			m_professor = "";
			m_date = 0;
			m_s_hour = 0;
			m_s_minute = 0;
			m_e_hour = 0;
			m_e_minute = 0;
			m_place = "";
			m_color = 0;
			rect = NULL;
		}
	};
	CArray <MyClass, MyClass&> m_array;

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
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


