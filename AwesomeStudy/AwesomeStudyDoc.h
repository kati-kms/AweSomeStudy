
// AwesomeStudyDoc.h : CAwesomeStudyDoc Ŭ������ �������̽�
//


#pragma once


class CAwesomeStudyDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CAwesomeStudyDoc();
	DECLARE_DYNCREATE(CAwesomeStudyDoc)

// Ư���Դϴ�.
public:
	CMapStringToString PicNodeToPathMap;
	CMapStringToString PicNodeToTextMap;
	int PicIsSaved;
	CString PicPath;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CAwesomeStudyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int PicGetIndentLevel(HTREEITEM hItem);
	HTREEITEM PicGetNextItem(HTREEITEM hItem);
};