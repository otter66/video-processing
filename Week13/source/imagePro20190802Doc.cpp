
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

	gResultImage = NULL;
	
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
	if (gResultImage != NULL) {
		for (i = 0; i < gImageHeight; i++) free(gResultImage[i]);
		free(gResultImage);
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
	bool isbmp = false;

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
	else if (!strcmp(strchr(fname, '.'), ".bmp") || !strcmp(strchr(fname, '.'), ".BMP")) {
		//bmp파일은 4의 배수 단위로 처리되어야 함
		//rgb가 아니라 bgr

		//bitmap file 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read(&bmfh, sizeof(bmfh));	//전체 바이트 수 계산 후 저장

		//bmp파일임을 나타내는"BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) 
			return 0;

		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read(&bih, sizeof(bih));	//구조체의 시작 번지, 구조체의 크기

		imageWidth = bih.biWidth;
		imageHeight = bih.biHeight;
		depth = bih.biBitCount / 8; //비트 수로 이루어져있디때문에 바이프로 바꿔주려고 (/ 8) 해줌

		if (depth == 1) {
			// palette 존재
			BYTE palette[256 * 4];	//흑백이니까 (* 4)
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}

	//메모리 할당
	inputImage = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImage = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	for (i = 0; i < imageHeight; i++) {
		inputImage[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImage[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	//파일에서 읽어서 저장
	if (!isbmp) {
		for (i = 0; i < imageHeight; i++)
			ar.Read(inputImage[i], imageWidth * depth);
	}
	else {
		BYTE nu[4];
		int widthfile;

		widthfile = (imageWidth * 8 + 31) / 32 * 4;	//32(4의 배수) - 1 = 31

		for (i = 0; i < imageHeight; i++) {
			if(depth == 1)
				ar.Read(inputImage[imageHeight - 1 - i], imageWidth * depth);	//뒤집어서 (밑부터)
			else {
				for (int j = 0; j < imageWidth; j++) {
					BYTE b, g, r;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);
					inputImage[imageHeight - 1 - i][j * 3 + 0] = r;
					inputImage[imageHeight - 1 - i][j * 3 + 1] = g;
					inputImage[imageHeight - 1 - i][j * 3 + 2] = b;
				}
			}

			if (widthfile - imageWidth != 0) {
				ar.Read(nu, (widthfile - imageWidth) * depth);
			}
		}
	}

	return 0;
}


void CimagePro20190802Doc::LoadSecondImageFile(CArchive& ar)
{
	int w, h, d;
	int maxValue, i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

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
	else if (!strcmp(strchr(fname, '.'), ".bmp") || !strcmp(strchr(fname, '.'), ".BMP")) {
		//bmp파일은 4의 배수 단위로 처리되어야 함
		//rgb가 아니라 bgr

		//bitmap file 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read(&bmfh, sizeof(bmfh));	//전체 바이트 수 계산 후 저장

		//bmp파일임을 나타내는"BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))
			return;

		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read(&bih, sizeof(bih));	//구조체의 시작 번지, 구조체의 크기

		w = bih.biWidth;
		h = bih.biHeight;
		d = bih.biBitCount / 8; //비트 수로 이루어져있디때문에 바이프로 바꿔주려고 (/ 8) 해줌

		if (depth == 1) {
			// palette 존재
			BYTE palette[256 * 4];	//흑백이니까 (* 4)
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
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
	if (!isbmp) {
		for (i = 0; i < imageHeight; i++)
			ar.Read(inputImage2[i], imageWidth * depth);
	}
	else {
		BYTE nu[4];
		int widthfile;

		widthfile = (imageWidth * 8 + 31) / 32 * 4;	//32(4의 배수) - 1 = 31

		for (i = 0; i < imageHeight; i++) {
			if (depth == 1)
				ar.Read(inputImage2[imageHeight - 1 - i], imageWidth * depth);	//뒤집어서 (밑부터)
			else {
				for (int j = 0; j < imageWidth; j++) {
					BYTE b, g, r;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);
					inputImage2[imageHeight - 1 - i][j * 3 + 0] = r;
					inputImage2[imageHeight - 1 - i][j * 3 + 1] = g;
					inputImage2[imageHeight - 1 - i][j * 3 + 2] = b;
				}
			}

			if (widthfile - imageWidth != 0) {
				ar.Read(nu, (widthfile - imageWidth) * depth);
			}
		}
	}

	return;
}
