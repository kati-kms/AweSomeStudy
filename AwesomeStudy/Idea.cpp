#include "stdafx.h"
#include "Idea.h"


CIdea & CIdea::operator=(const CIdea & data)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (this != &data) {
		//init
		//delete this->m_ideaRect;
		//delete this->m_ideaString;
		//this->m_pParent = NULL;
		this->m_ideaColor = 0;
		this->m_bHighlighted = FALSE;

		this->m_ideaRect = new CRect();
		this->m_ideaString = _T("");
		//this->m_pParent = NULL;
		//input
		this->m_ideaRect = data.m_ideaRect;
		this->m_ideaString = data.m_ideaString;
		this->m_ideaColor = RGB(66, 134, 244);
		//this->m_pParent = NULL;
	}
	return *this;
}

CRgn & CIdea::MakeIdeaRgn()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	this->m_ideaRegion.CreateRoundRectRgn(
		this->m_ideaRect.left
		, this->m_ideaRect.top
		, this->m_ideaRect.right
		, this->m_ideaRect.bottom
		, this->m_ideaRect.Width() * roundRate
		, this->m_ideaRect.Height() * roundRate
	);

	return m_ideaRegion;
}

void CIdea::DeleteIdeaRgn()
{
	this->m_ideaRegion.DeleteObject();
	return;
}

CIdea::CIdea()
{
	this->m_bHighlighted = FALSE;
	this->m_ideaRect = *new CRect();
	this->m_ideaString = *new CString(_T(""));
	this->m_ideaColor = RGB(66, 134, 244);
	//this->m_pParent = NULL;
}

CIdea::CIdea(CRect rect, CString str)
{
	this->m_bHighlighted = FALSE;
	this->m_ideaRect = rect;
	this->m_ideaString = str;
	this->m_ideaColor = RGB(66, 134, 244);
	//this->m_pParent = NULL;
}

CIdea::CIdea(CRect rect, CString str, CIdea * _parent)
{
	this->m_bHighlighted = FALSE;
	this->m_ideaRect = rect;
	this->m_ideaString = str;
	this->m_ideaColor = RGB(66, 134, 244);
	//this->m_pParent = _parent;
}

CIdea::CIdea(const CIdea & idea)
{
	this->m_bHighlighted = FALSE;
	this->m_ideaRect = idea.m_ideaRect;
	this->m_ideaString = idea.m_ideaString;
	this->m_ideaColor = idea.m_ideaColor;
	//this->m_pParent = idea.m_pParent;
}


CIdea::~CIdea()
{
	this->m_ideaRect.SetRectEmpty();
	this->m_ideaString.Delete(0, this->m_ideaString.GetLength());
	this->m_ideaColor = 0;
	//this->m_pParent = NULL;
	//free(this->m_pParent);
}

IMPLEMENT_SERIAL(CIdea, CObject, 1);

void CIdea::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		this->DeleteIdeaRgn();
		ar
			<< this->m_ideaColor
			<< this->m_bHighlighted
			<< this->m_ideaRect
			<< this->m_ideaString
			;

	}
	else
	{
		ar
			>> this->m_ideaColor
			>> this->m_bHighlighted
			>> this->m_ideaRect
			>> this->m_ideaString
			;
	}
}