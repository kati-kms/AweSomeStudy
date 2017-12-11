// InfoSave.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "InfoSave.h"

IMPLEMENT_SERIAL(CInfoSave, CObject, 2);
// CInfoSave

CInfoSave & CInfoSave::operator=(const CInfoSave & data)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (this != &data) {
		//init
		this->m_class = _T("");
		this->m_professor = _T("");
		this->m_date = 0;
		this->m_s_hour = 0;
		this->m_s_minute = 0;
		this->m_e_hour = 0;
		this->m_e_minute = 0;
		this->m_place = _T("");
		this->m_color = RGB(0, 0, 0);
		this->rect = new CRect();

		//input
		this->m_class = data.m_class;
		this->m_professor = data.m_professor;
		this->m_date = data.m_date;
		this->m_s_hour = data.m_s_hour;
		this->m_s_minute = data.m_s_minute;
		this->m_e_hour = data.m_e_hour;
		this->m_e_minute = data.m_e_minute;
		this->m_place = data.m_place;
		this->m_color = data.m_color;
		this->rect = data.rect;
	}
	return *this;
}

CInfoSave::CInfoSave()
{
	m_class = _T("");
	m_professor = _T("");
	m_date = 0;
	m_s_hour = 0;
	m_s_minute = 0;
	m_e_hour = 0;
	m_e_minute = 0;
	CString m_place = _T("");
	COLORREF m_color = RGB(0, 0, 0);
	CRect rect = new CRect();
}

CInfoSave::~CInfoSave()
{
}


// CInfoSave 멤버 함수


void CInfoSave::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar
			<< this->m_class
			<< this->m_professor
			<< this->m_date
			<< this->m_s_hour
			<< this->m_s_minute
			<< this->m_e_hour
			<< this->m_e_minute
			<< this->m_place
			<< this->m_color
			<< this->rect
			;

	}
	else
	{
		ar
			>> this->m_class
			>> this->m_professor
			>> this->m_date
			>> this->m_s_hour
			>> this->m_s_minute
			>> this->m_e_hour
			>> this->m_e_minute
			>> this->m_place
			>> this->m_color
			>> this->rect
			;
	}
}