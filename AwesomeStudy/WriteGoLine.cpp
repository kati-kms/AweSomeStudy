// WriteGoLine.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "WriteGoLine.h"
#include "afxdialogex.h"


// CWriteGoLine ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CWriteGoLine, CDialog)

CWriteGoLine::CWriteGoLine(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WRITE_GOLINE, pParent)
	//, m_line(0)
{

}

CWriteGoLine::~CWriteGoLine()
{
}

void CWriteGoLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_line);
}


BEGIN_MESSAGE_MAP(CWriteGoLine, CDialog)
END_MESSAGE_MAP()


// CWriteGoLine �޽��� ó�����Դϴ�.
