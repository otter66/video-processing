
// imagePro20190802View.cpp: CimagePro20190802View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imagePro20190802.h"
#endif

#include "imagePro20190802Doc.h"
#include "imagePro20190802View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CimagePro20190802View

IMPLEMENT_DYNCREATE(CimagePro20190802View, CScrollView)

BEGIN_MESSAGE_MAP(CimagePro20190802View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CimagePro20190802View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_PIXEL_ADD, &CimagePro20190802View::OnUpdatePixelAdd)
	ON_COMMAND(ID_PIXEL_MUL, &CimagePro20190802View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_ADD, &CimagePro20190802View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CimagePro20190802View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_DIV, &CimagePro20190802View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HIST_EQU, &CimagePro20190802View::OnPixelHistEqu)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCHING, &CimagePro20190802View::OnPixelContrastStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CimagePro20190802View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CimagePro20190802View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CimagePro20190802View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CimagePro20190802View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTHING, &CimagePro20190802View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_EMBOSSING, &CimagePro20190802View::OnRegionEmbossing)
END_MESSAGE_MAP()

// CimagePro20190802View 생성/소멸

CimagePro20190802View::CimagePro20190802View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CimagePro20190802View::~CimagePro20190802View()
{
}

BOOL CimagePro20190802View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CimagePro20190802View 그리기

void CimagePro20190802View::OnDraw(CDC* pDC)
{
	CimagePro20190802Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int x, y;

	if (pDoc->inputImage != NULL) {
		if (pDoc->depth == 1) {	//흑백일 때
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImage[y][x], pDoc->inputImage[y][x], pDoc->inputImage[y][x]));
		}
		else {	//컬러일 때
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImage[y][x * 3 + 0], pDoc->inputImage[y][x * 3 + 1], pDoc->inputImage[y][x * 3 + 2]));
		}
		
	}
	if (pDoc->inputImage2 != NULL) {
		if (pDoc->depth == 1) {	//흑백일 때
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(pDoc->imageWidth + 20 + x, y, RGB(pDoc->inputImage2[y][x], pDoc->inputImage2[y][x], pDoc->inputImage2[y][x]));
		}
		else {	//컬러일 때
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(pDoc->imageWidth + 20 + x, y, RGB(pDoc->inputImage2[y][x * 3 + 0], pDoc->inputImage2[y][x * 3 + 1], pDoc->inputImage2[y][x * 3 + 2]));
		}
	}


	if (pDoc->resultImage != NULL) {
		if (pDoc->depth == 1) {	//흑백일 때 
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->resultImage[y][x], pDoc->resultImage[y][x], pDoc->resultImage[y][x]));
		}
		else {	//컬러일 때
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->resultImage[y][x * 3 + 0], pDoc->resultImage[y][x * 3 + 1], pDoc->resultImage[y][x * 3 + 2]));
		}
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CimagePro20190802View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CimagePro20190802View 인쇄


void CimagePro20190802View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CimagePro20190802View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CimagePro20190802View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CimagePro20190802View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CimagePro20190802View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CimagePro20190802View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CimagePro20190802View 진단

#ifdef _DEBUG
void CimagePro20190802View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CimagePro20190802View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CimagePro20190802Doc* CimagePro20190802View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CimagePro20190802Doc)));
	return (CimagePro20190802Doc*)m_pDocument;
}
#endif //_DEBUG


// CimagePro20190802View 메시지 처리기


void CimagePro20190802View::OnUpdatePixelAdd(CCmdUI* pCmdUI)
{
}


void CimagePro20190802View::OnPixelAdd()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	if (pDoc->inputImage == NULL) return;

	int x, y;
	int value;
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				value = pDoc->inputImage[y][x] + 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {
				value = pDoc->inputImage[y][x * 3 + 0] + 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 0] = value;

				value = pDoc->inputImage[y][x * 3 + 1] + 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 1] = value;

				value = pDoc->inputImage[y][x * 3 + 2] + 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 2] = value;
			}
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelSub()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				value = pDoc->inputImage[y][x] - 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {
				value = pDoc->inputImage[y][x * 3 + 0] - 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 0] = value;

				value = pDoc->inputImage[y][x * 3 + 1] - 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 1] = value;

				value = pDoc->inputImage[y][x * 3 + 2] - 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 2] = value;
			}
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelMul()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				value = pDoc->inputImage[y][x] * 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {
				value = pDoc->inputImage[y][x * 3 + 0] * 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 0] = value;

				value = pDoc->inputImage[y][x * 3 + 1] * 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 1] = value;

				value = pDoc->inputImage[y][x * 3 + 2] * 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 2] = value;
			}
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelDiv()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				value = pDoc->inputImage[y][x] / 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {
				value = pDoc->inputImage[y][x * 3 + 0] / 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 0] = value;

				value = pDoc->inputImage[y][x * 3 + 1] / 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 1] = value;

				value = pDoc->inputImage[y][x * 3 + 2] / 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x * 3 + 2] = value;
			}
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelHistEqu()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y, k;
	int hist[256]{}, sum[256]{};
	int acc_hist = 0;
	float N = (float)(pDoc->imageHeight * pDoc->imageWidth);	//영상의 전체 픽셀 수

	for (k = 0; k < 256; k++) hist[k] = 0;

	//명암값 빈도수 조사
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			hist[pDoc->inputImage[y][x]]++;
		}
	}

	//누적된 히스토그램 합 계산
	for (k = 0; k < 256; k++) {
		acc_hist += hist[k];
		sum[k] = acc_hist;
	}

	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			k = pDoc->inputImage[y][x];
			pDoc->resultImage[y][x] = (unsigned char) (sum[k] / N * 255);
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnPixelContrastStretching()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	//변수 선언
	int min = 256, max = -1;
	int x, y;

	//최대, 최소 값 검색
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->inputImage[y][x] < min) min = pDoc->inputImage[y][x];
			if (pDoc->inputImage[y][x] > max) max = pDoc->inputImage[y][x];
		}
	}

	//P' = (float)(P-min)/(max-min)*255
	for (y = 0; y < pDoc->imageHeight; y++) {	
		for (x = 0; x < pDoc->imageWidth; x++) {
			int p = pDoc->inputImage[y][x];
			pDoc->resultImage[y][x] = (float)(p - min) / (max - min) * 255;
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnPixelBinarization()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int thresh = 150;
	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->inputImage[y][x] > thresh)
				pDoc->resultImage[y][x] = 255;
			else
				pDoc->resultImage[y][x] = 0;
		}
	}

	Invalidate();

}


void CimagePro20190802View::OnPixelTwoImageAdd()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK) {
	
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;
		for (y = 0; y < pDoc->imageHeight; y++) {
			for (x = 0; x < pDoc->imageWidth; x++) {
				if (pDoc->depth == 1) {
					pDoc->resultImage[y][x] = 0.5 * pDoc->inputImage[y][x] + 0.5 * pDoc->inputImage2[y][x];
				}
				else {
					pDoc->resultImage[y][x * 3 + 0] = 0.5 * pDoc->inputImage[y][x * 3 + 0] + 0.5 * pDoc->inputImage2[y][x * 3 + 0];
					pDoc->resultImage[y][x * 3 + 1] = 0.5 * pDoc->inputImage[y][x * 3 + 1] + 0.5 * pDoc->inputImage2[y][x * 3 + 1];
					pDoc->resultImage[y][x * 3 + 2] = 0.5 * pDoc->inputImage[y][x * 3 + 2] + 0.5 * pDoc->inputImage2[y][x * 3 + 2];
				}
			}
		}

		Invalidate();
	}
}


void CimagePro20190802View::OnPixelTwoImageSub()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK) {

		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();
		int value;

		int x, y;
		for (y = 0; y < pDoc->imageHeight; y++) {
			for (x = 0; x < pDoc->imageWidth; x++) {
				if (pDoc->depth == 1) {
					value = abs(pDoc->inputImage[y][x] -  pDoc->inputImage2[y][x]);
					if (value > 64) value = 255;
					else value = 0;
					pDoc->resultImage[y][x] = value;
				}
				else {
					value = abs(pDoc->inputImage[y][x * 3 + 0] - pDoc->inputImage2[y][x * 3 + 0]);
					if (value > 64) value = 255;
					else value = 0;
					pDoc->resultImage[y][x * 3 + 0] = value;

					value = abs(pDoc->inputImage[y][x * 3 + 1] - pDoc->inputImage2[y][x * 3 + 1]);
					if (value > 64) value = 255;
					else value = 0;
					pDoc->resultImage[y][x * 3 + 1] = value;

					value = abs(pDoc->inputImage[y][x * 3 + 2] - pDoc->inputImage2[y][x * 3 + 2]);
					if (value > 64) value = 255;
					else value = 0;
					pDoc->resultImage[y][x * 3 + 2] = value;
				}
			}
		}

		Invalidate();
	}

	//if (dlg.DoModal() == IDOK) {
	//	int x, y;
	//	int value;
	//	file.Open(dlg.GetPathName(), CFile::modeRead);
	//	CArchive ar(&file, CArchive::load);

	//	ar.Read(pDoc->inputImage2, 256 * 256);

	//	file.Close();

	//	for (y = 0; y < 256; y++) {
	//		for (x = 0; x < 256; x++) {

	//			value = abs(pDoc->inputImage[y][x] -  pDoc->inputImage2[y][x]);

	//			if (value > 64) value = 255;
	//			else value = 0;

	//			pDoc->resultImage[y][x] = value;
	//		}
	//	}

	//	Invalidate();
	//}
}


void CimagePro20190802View::OnRegionSharpening()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	float kernel[3][3] = {
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};

	convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CimagePro20190802View::convolve(unsigned char** inputImage, unsigned char** resultImage, int cols, int rows, float mask[3][3], int bias, int depth)
{
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	//테두리 제외를  위해 1 until len-1
	for (y = 1; y < rows - 1; y++) {
		for (x = 1; x < cols - 1; x++) {
			if (depth == 1) {  //흑백
				sum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						sum += inputImage[y + j - 1][x + i - 1] * mask[j][i];
					}
				}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				resultImage[y][x] = sum;
			}
			else {  //컬러
				rsum = gsum = bsum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						rsum += inputImage[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i];
						gsum += inputImage[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i];
						bsum += inputImage[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i];
					}
				}
				rsum += bias;
				gsum += bias;
				bsum += bias;

				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				resultImage[y][3 * x + 0] = rsum;
				resultImage[y][3 * x + 1] = gsum;
				resultImage[y][3 * x + 2] = bsum;
			}
		
		}
	}
}


void CimagePro20190802View::OnRegionSmoothing()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	float kernel[3][3] = {
		{1/9.0f, 1/9.0f, 1/9.0f},
		{1/9.0f, 1/9.0f, 1/9.0f},
		{1/9.0f, 1/9.0f, 1/9.0f}
	};

	convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CimagePro20190802View::OnRegionEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}
