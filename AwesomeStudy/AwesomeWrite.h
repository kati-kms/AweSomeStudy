#pragma once


// CAwesomeWrite ���Դϴ�.

class CAwesomeWrite : public CRichEditView
{
	DECLARE_DYNCREATE(CAwesomeWrite)

public:
	CAwesomeWrite();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAwesomeWrite();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHome();
};


