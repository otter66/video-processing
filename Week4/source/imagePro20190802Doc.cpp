
// imagePro20190802Doc.cpp: CimagePro20190802Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imagePro20190802.h"
#endif

#include "imagePro20190802Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CimagePro20190802Doc

IMPLEMENT_DYNCREATE(CimagePro20190802Doc, CDocument)

BEGIN_MESSAGE_MAP(CimagePro20190802Doc, CDocument)
END_MESSAGE_MAP()


// CimagePro20190802Doc 생성/소멸

CimagePro20190802Doc::CimagePro20190802Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	inputImage = NULL;
	inputImage2 = NULL;
	resultImage = NULL;
}

CimagePro20190802Doc::~CimagePro20190802Doc()
{
	int i;

	if (inputImage != NULL) {
		for (i = 0; i < imageHeight; i++) free(inputImage[i]);
		free(inputImage);
	}
	if (inputImage2 != NULL) {
		for (i = 0; i < imageHeight; i++) free(inputImage2[i]);
		free(inputImage2);
	}
	if (resultImage != NULL) {
		for (i = 0; i < imageHeight; i++) free(resultImage[i]);
		free(resultImage);
	}
}

BOOL CimagePro20190802Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CimagePro20190802Doc serialization

void CimagePro20190802Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CimagePro20190802Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CimagePro20190802Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CimagePro20190802Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CimagePro20190802Doc 진단

#ifdef _DEBUG
void CimagePro20190802Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CimagePro20190802Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CimagePro20190802Doc 명령


int CimagePro20190802Doc::LoadImageFile(CArchive& ar)
{
	int maxValue, i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	//strcmp(strchr(fname, '.'), ".ppm");	// == 0 => 확장자가 ppm
	if (!strcmp(strchr(fname, '.'), ".ppm") || !strcmp(strchr(fname, '.'), ".PPM") ||
		!strcmp(strchr(fname, '.'), ".pgm") || !strcmp(strchr(fname, '.'), ".PGM")) {

		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &imageWidth, &imageHeight);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (!strcmp(type, "P5")) depth = 1;
		else depth = 3;
	} 
	else if (!strcmp(strchr(fname, '.'), ".raw") || !strcmp(strchr(fname, '.'), ".RAW")) {
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}

	//메모리 할당
	inputImage = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImage = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) {
		inputImage[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImage[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	//파일에서 읽어서 저장
	for (i = 0; i < imageHeight; i++) 
		ar.Read(inputImage[i], imageWidth * depth);

	return 0;
}


int CimagePro20190802Doc::LoadSecondImageFile(CArchive& ar)
{
	int w, h, d;
	int maxValue, i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	if (!strcmp(strchr(fname, '.'), ".ppm") || !strcmp(strchr(fname, '.'), ".PPM") ||
		!strcmp(strchr(fname, '.'), ".pgm") || !strcmp(strchr(fname, '.'), ".PGM")) {

		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &w, &h);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (!strcmp(type, "P5")) d = 1;
		else d = 3;
	}
	else if (!strcmp(strchr(fname, '.'), ".raw") || !strcmp(strchr(fname, '.'), ".RAW")) {
		w = 256;
		h = 256;
		d = 1;
	}

	if (imageWidth != w || imageHeight != h || depth != d) {
		AfxMessageBox("가로, 세로 색상 수가 같아야만 처리할 수 있습니다.");
		return;
	}

	//메모리 할당
	inputImage2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) {
		inputImage2[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	//파일에서 읽어서 저장
	for (i = 0; i < imageHeight; i++)
		ar.Read(inputImage2[i], imageWidth * depth);

	return 0;
}
