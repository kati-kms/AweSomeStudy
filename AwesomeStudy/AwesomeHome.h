#pragma once
class CClassInfo;
class CInfoSave;
#include "InfoSave.h"
#include "afxwin.h"


// CAwesomeHome 폼 뷰입니다.

class CAwesomeHome : public CFormView
{
	DECLARE_DYNCREATE(CAwesomeHome)

public:
	CAwesomeHome();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
public:
	CClassInfo *m_pAddDlg;
	CString class_name; // EditBox > 강의명
	CString class_professor; // EditBox > 교수명
	int class_day; // ComboBox > 시간(요일)
	int class_start_hour; // ComboBox > 시간(시)
	int class_start_minute; // ComboBox > 시간(분)
	int class_end_hour; // ComboBox > 시간(시)
	int class_end_minute; // ComboBox > 시간(분)
	CString class_room; // EditBox > 강의장 
	BOOL IsAble[5][144];
	BOOL AddList;
	int Select_num;
	COLORREF m_color[10];
	int color_num;

	CArray <CInfoSave, CInfoSave&> m_array;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
	CButton m_delete;
	CListBox m_list;
	afx_msg void OnBnClickedDelete();
	CButton m_write;
	CButton m_pic;
	CButton m_map;
	afx_msg void OnUpdateHome(CCmdUI *pCmdUI);
};


