#include "stdafx.h"
#include "Idea.h"


CIdea & CIdea::operator=(const CIdea & data)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (this != &data) {
		//init
		//delete this->m_ideaRect;
		//delete this->m_ideaString;
		this->m_ideaColor = 0;
		this->m_ideaRect = new CRect();
		this->m_ideaString = _T("");
		//input
		this->m_bHighlighted = data.m_bHighlighted;
		this->m_ideaRect = data.m_ideaRect;
		this->m_ideaString = data.m_ideaString;
		this->m_ideaColor = RGB(66, 134, 244);
		this->m_ipParentNode = data.m_ipParentNode;
		this->m_ipSelfNode = data.m_ipSelfNode;
		//this->m_ipRightSibling = data.m_ipRightSibling;
		//this->m_ipLeftChild = data.m_ipLeftChild;
	}
	return *this;
}

BOOL CIdea::operator==(const CIdea & data)
{
	BOOL flag;
	flag = this->m_ideaColor == data.m_ideaColor
		&& this->m_ideaRect == data.m_ideaRect
		&& this->m_ideaString == data.m_ideaString
		&& this->m_ipParentNode == data.m_ipParentNode
		&& this->m_ipSelfNode == data.m_ipSelfNode;

	return flag;
}

BOOL CIdea::operator!=(const CIdea & data)
{
	BOOL flag;
	flag = this->m_ideaColor == data.m_ideaColor
		&& this->m_ideaRect == data.m_ideaRect
		&& this->m_ideaString == data.m_ideaString
		&& this->m_ipParentNode == data.m_ipParentNode
		&& this->m_ipSelfNode == data.m_ipSelfNode;

	return !flag;
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

CString CIdea::StringOutIdea()
{
	CString masterStr;
	CString str;
	CRect rect = this->m_ideaRect;
	str.Format(_T("m_ideaRect : %d %d\n"), rect.CenterPoint().x, rect.CenterPoint().y);
	masterStr.Append(str);
	str.Format(_T("m_ideaString : %s\n"), this->m_ideaString);
	masterStr.Append(str);
	str.Format(_T("m_ideaColor : R:%d, G:%d, B:%d\n"),
		GetRValue(this->m_ideaColor),
		GetGValue(this->m_ideaColor),
		GetBValue(this->m_ideaColor)
	);

	masterStr.Append(str);
	str.Format(_T("m_bHighlighted : %s\n"), 
		this->m_bHighlighted ? CString(_T("TRUE")) : CString(_T("FALSE")) 
	);
	masterStr.Append(str);
	str.Format(_T("myself : %d, parent : %d\n"),
		this->m_ipSelfNode,
		this->m_ipParentNode
		//this->m_ipLeftChild,
		//this->m_ipRightSibling
	);
	masterStr.Append(str);

	return masterStr;
}

void CIdea::SetHighlight(BOOL bl)
{
	this->m_bHighlighted = bl;
}



/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//생성자-------------------------------------
CIdea::CIdea()
{
	//static IndexPointer nodeIndex = 0;
	//this->m_ipSelfNode = ++nodeIndex;
	//this->m_ipLeftChild = 0;
	//this->m_ipRightSibling = 0;
	this->m_ipSelfNode = 0;
	this->m_ipParentNode = 0;
	this->m_bHighlighted = FALSE;
	this->m_ideaRect = *new CRect();
	this->m_ideaString = *new CString(_T(""));
	this->m_ideaColor = RGB(66, 134, 244);
}

CIdea::CIdea(CRect rect, CString str)
{
	CIdea();
	//this->m_bHighlighted = FALSE;
	//this->m_ideaColor = RGB(66, 134, 244);
	this->m_ideaRect = rect;
	this->m_ideaString = str;
}

CIdea::CIdea(CRect& rect, CString& str, CIdea &_parent)
{
	CIdea(rect, str);
	this->NewIdea();
	this->m_ipParentNode = _parent.m_ipSelfNode;
}

CIdea::CIdea(const CIdea & idea)
{
	this->m_bHighlighted = FALSE;
	this->m_ideaRect = idea.m_ideaRect;
	this->m_ideaString = idea.m_ideaString;
	this->m_ideaColor = idea.m_ideaColor;
	this->m_ipParentNode = idea.m_ipParentNode;
	this->m_ipSelfNode = idea.m_ipSelfNode;
	//this->m_ipLeftChild = idea.m_ipLeftChild;
	//this->m_ipRightSibling = idea.m_ipRightSibling;
}


CIdea::~CIdea()
{
	this->m_ideaRect.SetRectEmpty();
	this->m_ideaString.Delete(0, this->m_ideaString.GetLength());
	this->m_ideaColor = 0;
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
			<< this->m_ideaRect
			<< this->m_ideaString
			<< this->m_ipParentNode
			<< this->m_ipSelfNode
			//<< this->m_ipRightSibling
			//<< this->m_ipLeftChild
			;

	}
	else
	{
		ar
			>> this->m_ideaColor
			>> this->m_ideaRect
			>> this->m_ideaString
			>> this->m_ipParentNode
			>> this->m_ipSelfNode
			//>> this->m_ipLeftChild
			//>> this->m_ipRightSibling
			;
	}
}
