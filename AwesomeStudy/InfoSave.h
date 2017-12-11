#pragma once
#include "AwesomeHome.h"
#include <afxtempl.h>
// CInfoSave 명령 대상입니다.

class CInfoSave : public CObject
{
	DECLARE_SERIAL(CInfoSave);
public:
	CInfoSave & operator=(const CInfoSave & data);
	CInfoSave();
	virtual ~CInfoSave();

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
	virtual void Serialize(CArchive& ar);
};