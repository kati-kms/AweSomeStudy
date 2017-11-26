#include "AwesomeWrite.h"
#include "AwesomePic.h"
#include "AwesomeMmap.h"
#include "AwesomeHome.h"

#define VIEWID_DEFAULT AFX_IDW_PANE_FIRST
#define VIEWID_WRITE AFX_IDW_PANE_FIRST+10
#define VIEWID_PIC AFX_IDW_PANE_FIRST+20
#define VIEWID_Mmap AFX_IDW_PANE_FIRST+30
#define VIEWID_HOME AFX_IDW_PANE_FIRST+40 // login ȭ��
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	CAwesomeWrite * m_pwndWrite;
	CAwesomePic * m_pwndPic;
	CAwesomeMmap * m_pwndMmap;
	CAwesomeHome * m_pwndHome;
// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	void SwitchView(int nID);
};


