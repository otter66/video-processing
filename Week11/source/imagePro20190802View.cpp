
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

#include<math.h>

#include "CAngleInputDlg.h"

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
	ON_COMMAND(ID_REGION_PREWITT, &CimagePro20190802View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CimagePro20190802View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CimagePro20190802View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CimagePro20190802View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CimagePro20190802View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CimagePro20190802View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CimagePro20190802View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CimagePro20190802View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_COLOR_TO_GRAY, &CimagePro20190802View::OnMopologyColorToGray)
	ON_COMMAND(ID_MOPOLOGY_OPENNING, &CimagePro20190802View::OnMopologyOpenning)
	ON_COMMAND(ID_MOPLOGY_CLOSING, &CimagePro20190802View::OnMoplogyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CimagePro20190802View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BINUERINTERPOLATION, &CimagePro20190802View::OnGeometryZoominBinuerinterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CimagePro20190802View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CimagePro20190802View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CimagePro20190802View::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CimagePro20190802View::OnGeometryRotate)
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

	if (pDoc->gResultImage != NULL) {
		if (pDoc->depth == 1) {	//흑백일 때 
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->gResultImage[y][x], pDoc->gResultImage[y][x], pDoc->gResultImage[y][x]));
		}
		else {	//컬러일 때
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->gResultImage[y][x * 3 + 0], pDoc->gResultImage[y][x * 3 + 1], pDoc->gResultImage[y][x * 3 + 2]));
		}
	}
	
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
			if (pDoc->depth == 1) {	 //흑백 이미지
				value = pDoc->inputImage[y][x] + 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {	 //컬러 이미지
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
			if (pDoc->depth == 1) {	 //흑백 이미지
				value = pDoc->inputImage[y][x] - 100;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {	 //컬러 이미지
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
			if (pDoc->depth == 1) {	 //흑백 이미지
				value = pDoc->inputImage[y][x] * 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {	 //컬러 이미지
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
			if (pDoc->depth == 1) {	 //흑백 이미지
				value = pDoc->inputImage[y][x] / 1.5;
				if (value >= 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {	 //컬러 이미지
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
	int rhist[256]{}, rsum[256]{}, ghist[256]{}, gsum[256]{}, bhist[256]{}, bsum[256]{};
	int acc_hist = 0;
	int r_acc_hist = 0, g_acc_hist = 0, b_acc_hist = 0;
	float N = (float)(pDoc->imageHeight * pDoc->imageWidth);	//영상의 전체 픽셀 수

	//명암값 빈도수 조사
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {	 //흑백 이미지
				hist[pDoc->inputImage[y][x]]++;
			}
			else {	 //컬러 이미지
				rhist[pDoc->inputImage[y][x * 3 + 0]]++;
				ghist[pDoc->inputImage[y][x * 3 + 1]]++;
				bhist[pDoc->inputImage[y][x * 3 + 2]]++;
			}
		}
	}

	//누적된 히스토그램 합 계산
	for (k = 0; k < 256; k++) {
		if (pDoc->depth == 1) {	 //흑백 이미지
			acc_hist += hist[k];
			sum[k] = acc_hist;
		}
		else {	 //컬러 이미지
			r_acc_hist += rhist[k];
			rsum[k] = r_acc_hist;

			g_acc_hist += ghist[k];
			gsum[k] = g_acc_hist;

			b_acc_hist += bhist[k];
			bsum[k] = b_acc_hist;
		}
	}

	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {	 //흑백 이미지
				k = pDoc->inputImage[y][x];
				pDoc->resultImage[y][x] = (unsigned char)(sum[k] / N * 255);
			}
			else {	 //컬러 이미지
				k = pDoc->inputImage[y][x * 3 + 0];
				pDoc->resultImage[y][x * 3 + 0] = (unsigned char)(rsum[k] / N * 255);

				k = pDoc->inputImage[y][x * 3 + 1];
				pDoc->resultImage[y][x * 3 + 1] = (unsigned char)(gsum[k] / N * 255);

				k = pDoc->inputImage[y][x * 3 + 2];
				pDoc->resultImage[y][x * 3 + 2] = (unsigned char)(bsum[k] / N * 255);
			}
		}
	} 

	Invalidate();
}


void CimagePro20190802View::OnPixelContrastStretching()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	//변수 선언
	int min = 256, max = -1;
	int rmin = 256, rmax = -1, gmin = 256, gmax = -1, bmin = 256, bmax = -1;
	int x, y;
	int p;

	//최대, 최소 값 검색
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {	 //흑백 이미지
				if (pDoc->inputImage[y][x] < min) min = pDoc->inputImage[y][x];
				if (pDoc->inputImage[y][x] > max) max = pDoc->inputImage[y][x];
			}
			else {	 //컬러 이미지
				if (pDoc->inputImage[y][x * 3 + 0] < rmin) rmin = pDoc->inputImage[y][x * 3 + 0];
				if (pDoc->inputImage[y][x * 3 + 0] > rmax) rmax = pDoc->inputImage[y][x * 3 + 0];

				if (pDoc->inputImage[y][x * 3 + 1] < gmin) gmin = pDoc->inputImage[y][x * 3 + 1];
				if (pDoc->inputImage[y][x * 3 + 1] > gmax) gmax = pDoc->inputImage[y][x * 3 + 1];

				if (pDoc->inputImage[y][x * 3 + 2] < bmin) bmin = pDoc->inputImage[y][x * 3 + 2];
				if (pDoc->inputImage[y][x * 3 + 2] > bmax) bmax = pDoc->inputImage[y][x * 3 + 2];
			}
		}
	}

	//P' = (float)(P-min)/(max-min)*255
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {	 //흑백 이미지
				p = pDoc->inputImage[y][x];
				pDoc->resultImage[y][x] = (float)(p - min) / (max - min) * 255;
			}
			else {	 //컬러 이미지
				p = pDoc->inputImage[y][x * 3 + 0];
				pDoc->resultImage[y][x * 3 + 0] = (float)(p - rmin) / (rmax - rmin) * 255;

				p = pDoc->inputImage[y][x * 3 + 1];
				pDoc->resultImage[y][x * 3 + 1] = (float)(p - gmin) / (gmax - gmin) * 255;

				p = pDoc->inputImage[y][x * 3 + 2];
				pDoc->resultImage[y][x * 3 + 2] = (float)(p - bmin) / (bmax - bmin) * 255;
			}
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
			if (pDoc->depth == 1) {	 //흑백 이미지
				if (pDoc->inputImage[y][x] > thresh)
					pDoc->resultImage[y][x] = 255;
				else
					pDoc->resultImage[y][x] = 0;
			}
			else {	 //컬러 이미지
				if (pDoc->inputImage[y][x * 3 + 0] + pDoc->inputImage[y][x * 3 + 1] + pDoc->inputImage[y][x * 3 + 2] > thresh) {
					pDoc->resultImage[y][x * 3 + 0] = 255;
					pDoc->resultImage[y][x * 3 + 1] = 255;
					pDoc->resultImage[y][x * 3 + 2] = 255;
				}
				else {
					pDoc->resultImage[y][x * 3 + 0] = 0;
					pDoc->resultImage[y][x * 3 + 1] = 0;
					pDoc->resultImage[y][x * 3 + 2] = 0;
				}
			}
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
				if (pDoc->depth == 1) {	 //흑백 이미지
					pDoc->resultImage[y][x] = 0.5 * pDoc->inputImage[y][x] + 0.5 * pDoc->inputImage2[y][x];
				}
				else {	 //컬러 이미지
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

		int x, y;
		for (y = 0; y < pDoc->imageHeight; y++) {
			for (x = 0; x < pDoc->imageWidth; x++) {
				if (pDoc->depth == 1) {	 //흑백 이미지
					pDoc->resultImage[y][x] = abs(pDoc->inputImage[y][x] - pDoc->inputImage2[y][x]);
				}
				else {	 //컬러 이미지
					pDoc->resultImage[y][x * 3 + 0] = abs(pDoc->inputImage[y][x * 3 + 0] - pDoc->inputImage2[y][x * 3 + 0]);
					pDoc->resultImage[y][x * 3 + 1] = abs(pDoc->inputImage[y][x * 3 + 1] - pDoc->inputImage2[y][x * 3 + 1]);
					pDoc->resultImage[y][x * 3 + 2] = abs(pDoc->inputImage[y][x * 3 + 2] - pDoc->inputImage2[y][x * 3 + 2]);
				}
			}
		}

		Invalidate();
	}
}


void CimagePro20190802View::convolve(unsigned char** inputImage, unsigned char** resultImage, int cols, int rows, float mask[3][3], int bias, int depth)
{
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	//테두리 제외를  위해 1 until len-1
	for (y = 1; y < rows - 1; y++) {
		for (x = 1; x < cols - 1; x++) {
			if (depth == 1) {  //흑백 이미지
				sum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						sum += inputImage[y + j - 1][x + i - 1] * mask[j][i];
					}
				}
				sum += bias;
				//if (sum > 255) sum = 255;
				//else if (sum < 0) sum = 0;

				resultImage[y][x] = sum;
			}
			else {  //컬러 이미지
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
		{1 / 9.0f, 1 / 9.0f, 1 / 9.0f},
		{1 / 9.0f, 1 / 9.0f, 1 / 9.0f},
		{1 / 9.0f, 1 / 9.0f, 1 / 9.0f}
	};

	convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
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


void CimagePro20190802View::OnRegionEmbossing()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	//float kernel[3][3] = {
	//	{-2, -1, 0},
	//	{-1, 0, 1},
	//	{0, 1, 2}
	//};
	float kernel[3][3] = {
		{-1, 0, 0},
		{0, 0, 0},
		{0, 0, 1}
	};

	convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, kernel, 128, pDoc->depth);

	Invalidate();
}


void CimagePro20190802View::OnRegionPrewitt()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	float maskH[3][3] = {
		{-1, -1, -1},
		{ 0,  0,  0},
		{ 1,  1,  1}
	};
	float maskV[3][3] = {
		{1, 0, -1},
		{1, 0, -1},
		{1, 0, -1}
	};

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImage, Er, pDoc->imageWidth, pDoc->imageHeight, maskH, 128, pDoc->depth);
	convolve(pDoc->inputImage, Ec, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);
	//convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				pDoc->resultImage[y][x] = sum;
			}
			else {
				rsum = sqrt((Er[y][x * 3 + 0] - 128) * (Er[y][x * 3 + 0] - 128) + (Ec[y][x * 3 + 0] - 128) * (Ec[y][x * 3 + 0] - 128));
				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;

				gsum = sqrt((Er[y][x * 3 + 1] - 128) * (Er[y][x * 3 + 1] - 128) + (Ec[y][x * 3 + 1] - 128) * (Ec[y][x * 3 + 1] - 128));
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;

				bsum = sqrt((Er[y][x * 3 + 2] - 128) * (Er[y][x * 3 + 2] - 128) + (Ec[y][x * 3 + 2] - 128) * (Ec[y][x * 3 + 2] - 128));
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				pDoc->resultImage[y][x * 3 + 0] = sum;
				pDoc->resultImage[y][x * 3 + 1] = sum;
				pDoc->resultImage[y][x * 3 + 2] = sum;
			}
		}
	}

	for (i = 0; i < pDoc->imageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CimagePro20190802View::OnRegionRoberts()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	float maskH[3][3] = {
		{-1, 0, 0},
		{ 0,  1,  0},
		{ 0,  0,  0}
	};
	float maskV[3][3] = {
		{0, 0, -1},
		{0, 1, 0},
		{0, 0, 0}
	};

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImage, Er, pDoc->imageWidth, pDoc->imageHeight, maskH, 128, pDoc->depth);
	convolve(pDoc->inputImage, Ec, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);
	//convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				pDoc->resultImage[y][x] = sum;
			}
			else {
				rsum = sqrt((Er[y][x * 3 + 0] - 128) * (Er[y][x * 3 + 0] - 128) + (Ec[y][x * 3 + 0] - 128) * (Ec[y][x * 3 + 0] - 128));
				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;

				gsum = sqrt((Er[y][x * 3 + 1] - 128) * (Er[y][x * 3 + 1] - 128) + (Ec[y][x * 3 + 1] - 128) * (Ec[y][x * 3 + 1] - 128));
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;

				bsum = sqrt((Er[y][x * 3 + 2] - 128) * (Er[y][x * 3 + 2] - 128) + (Ec[y][x * 3 + 2] - 128) * (Ec[y][x * 3 + 2] - 128));
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				pDoc->resultImage[y][x * 3 + 0] = sum;
				pDoc->resultImage[y][x * 3 + 1] = sum;
				pDoc->resultImage[y][x * 3 + 2] = sum;
			}
		}
	}

	for (i = 0; i < pDoc->imageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CimagePro20190802View::OnRegionSobel()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	float maskH[3][3] = {
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};
	float maskV[3][3] = {
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}
	};

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->imageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImage, Er, pDoc->imageWidth, pDoc->imageHeight, maskH, 128, pDoc->depth);
	convolve(pDoc->inputImage, Ec, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);
	//convolve(pDoc->inputImage, pDoc->resultImage, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			if (pDoc->depth == 1) {
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				//이진화를 통해 경계선이 뚜렷한 부분만 남김
				if (sum > 128) sum = 255;
				else sum = 0;

				pDoc->resultImage[y][x] = sum;
			}
			else {
				rsum = sqrt((Er[y][x * 3 + 0] - 128) * (Er[y][x * 3 + 0] - 128) + (Ec[y][x * 3 + 0] - 128) * (Ec[y][x * 3 + 0] - 128));
				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;

				gsum = sqrt((Er[y][x * 3 + 1] - 128) * (Er[y][x * 3 + 1] - 128) + (Ec[y][x * 3 + 1] - 128) * (Ec[y][x * 3 + 1] - 128));
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;

				bsum = sqrt((Er[y][x * 3 + 2] - 128) * (Er[y][x * 3 + 2] - 128) + (Ec[y][x * 3 + 2] - 128) * (Ec[y][x * 3 + 2] - 128));
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				//이진화를 통해 경계선이 뚜렷한 부분만 남김
				if (sum > 128) sum = 255;
				else sum = 0;

				pDoc->resultImage[y][x * 3 + 0] = sum;
				pDoc->resultImage[y][x * 3 + 1] = sum;
				pDoc->resultImage[y][x * 3 + 2] = sum;
			}
		}
	}

	for (i = 0; i < pDoc->imageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CimagePro20190802View::OnRegionAverageFiltering()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	int x, y;
	int j, i;
	int sum, rsum, gsum, bsum;

	// 5 * 5 영역의 평균값
	for (y = 2; y < pDoc->imageHeight - 2; y++) {
		for (x = 2; x < pDoc->imageWidth - 2; x++) {
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = 0; j < 5; j++) {
					for (i = 0; i < 5; i++) {
						sum += pDoc->inputImage[y + j - 2][x + i - 2];
					}
				}
				sum /= 25;

				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				pDoc->resultImage[y][x] = sum;
			}
			else {
				rsum = gsum = bsum = 0;
				for (j = 0; j < 5; j++) {
					for (i = 0; i < 5; i++) {
						rsum += pDoc->inputImage[y + j - 2][(x + i - 2) * 3 + 0];
						gsum += pDoc->inputImage[y + j - 2][(x + i - 2) * 3 + 1];
						bsum += pDoc->inputImage[y + j - 2][(x + i - 2) * 3 + 2];
					}
				}
				rsum /= 25;
				gsum /= 25;
				bsum /= 25;

				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				pDoc->resultImage[y][x * 3 + 0] = rsum;
				pDoc->resultImage[y][x * 3 + 1] = gsum;
				pDoc->resultImage[y][x * 3 + 2] = bsum;
			}
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnRegionMedianFiltering()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	int x, y, i, j;
	int n[9], temp;

	for (y = 1; y < pDoc->imageHeight - 1; y++) {
		for (x = 1; x < pDoc->imageWidth - 1; x++) {
			if (pDoc->depth == 1) {
				n[0] = pDoc->inputImage[y - 1][x - 1];
				n[1] = pDoc->inputImage[y - 1][x + 0];
				n[2] = pDoc->inputImage[y - 1][x + 1];
				n[3] = pDoc->inputImage[y + 0][x - 1];
				n[4] = pDoc->inputImage[y + 0][x + 0];
				n[5] = pDoc->inputImage[y + 0][x + 1];
				n[6] = pDoc->inputImage[y + 1][x - 1];
				n[7] = pDoc->inputImage[y + 1][x + 0];
				n[8] = pDoc->inputImage[y + 1][x + 1];

				//sorting = 오름차순
				for (i = 8; i >= 0; i--) {
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				}

				pDoc->resultImage[y][x] = n[4];
			}
			else {
				n[0] = pDoc->inputImage[y - 1][(x - 1) * 3 + 0];
				n[1] = pDoc->inputImage[y - 1][(x + 0) * 3 + 0];
				n[2] = pDoc->inputImage[y - 1][(x + 1) * 3 + 0];
				n[3] = pDoc->inputImage[y + 0][(x - 1) * 3 + 0];
				n[4] = pDoc->inputImage[y + 0][(x + 0) * 3 + 0];
				n[5] = pDoc->inputImage[y + 0][(x + 1) * 3 + 0];
				n[6] = pDoc->inputImage[y + 1][(x - 1) * 3 + 0];
				n[7] = pDoc->inputImage[y + 1][(x + 0) * 3 + 0];
				n[8] = pDoc->inputImage[y + 1][(x + 1) * 3 + 0];

				//sorting = 오름차순
				for (i = 8; i >= 0; i--) {
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				}

				pDoc->resultImage[y][x * 3 + 0] = n[4];

				//-----------
				n[0] = pDoc->inputImage[y - 1][(x - 1) * 3 + 1];
				n[1] = pDoc->inputImage[y - 1][(x + 0) * 3 + 1];
				n[2] = pDoc->inputImage[y - 1][(x + 1) * 3 + 1];
				n[3] = pDoc->inputImage[y + 0][(x - 1) * 3 + 1];
				n[4] = pDoc->inputImage[y + 0][(x + 0) * 3 + 1];
				n[5] = pDoc->inputImage[y + 0][(x + 1) * 3 + 1];
				n[6] = pDoc->inputImage[y + 1][(x - 1) * 3 + 1];
				n[7] = pDoc->inputImage[y + 1][(x + 0) * 3 + 1];
				n[8] = pDoc->inputImage[y + 1][(x + 1) * 3 + 1];

				//sorting = 오름차순
				for (i = 8; i >= 0; i--) {
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				}

				pDoc->resultImage[y][x * 3 + 1] = n[4];

				//-----------
				n[0] = pDoc->inputImage[y - 1][(x - 1) * 3 + 2];
				n[1] = pDoc->inputImage[y - 1][(x + 0) * 3 + 2];
				n[2] = pDoc->inputImage[y - 1][(x + 1) * 3 + 2];
				n[3] = pDoc->inputImage[y + 0][(x - 1) * 3 + 2];
				n[4] = pDoc->inputImage[y + 0][(x + 0) * 3 + 2];
				n[5] = pDoc->inputImage[y + 0][(x + 1) * 3 + 2];
				n[6] = pDoc->inputImage[y + 1][(x - 1) * 3 + 2];
				n[7] = pDoc->inputImage[y + 1][(x + 0) * 3 + 2];
				n[8] = pDoc->inputImage[y + 1][(x + 1) * 3 + 2];

				//sorting = 오름차순
				for (i = 8; i >= 0; i--) {
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				}

				pDoc->resultImage[y][x * 3 + 2] = n[4];
			}
		}
	}


	Invalidate();
}


void CimagePro20190802View::OnMopologyErosion()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int min;

	for (y = 1; y < pDoc->imageHeight - 1; y++) {
		for (x = 1; x < pDoc->imageWidth - 1; x++) {
			if (pDoc->depth == 1) {	//흑백
				min = 255;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (min > pDoc->inputImage[y + j - 1][x + i - 1])
							min = pDoc->inputImage[y + j - 1][x + i - 1];
					}
				}
				pDoc->resultImage[y][x] = min;
			}
			else {	//컬러
				min = 255;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (min > pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 0])
							min = pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 0];
					}
				}
				pDoc->resultImage[y][x * 3 + 0] = min;

				min = 255;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (min > pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 1])
							min = pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 1];
					}
				}
				pDoc->resultImage[y][x * 3 + 1] = min;

				min = 255;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (min > pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 2])
							min = pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 2];
					}
				}
				pDoc->resultImage[y][x * 3 + 2] = min;
			}
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnMopologyDilation()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int max;

	for (y = 1; y < pDoc->imageHeight - 1; y++) {
		for (x = 1; x < pDoc->imageWidth - 1; x++) {
			if (pDoc->depth == 1) {	//흑백
				max = 0;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (max < pDoc->inputImage[y + j - 1][x + i - 1])
							max = pDoc->inputImage[y + j - 1][x + i - 1];
					}
				}
				pDoc->resultImage[y][x] = max;
			}
			else {	//컬러
				max = 0;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (max < pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 0])
							max = pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 0];
					}
				}
				pDoc->resultImage[y][x * 3 + 0] = max;

				max = 0;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (max < pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 1])
							max = pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 1];
					}
				}
				pDoc->resultImage[y][x * 3 + 1] = max;

				max = 0;
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < 3; i++) {
						if (max < pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 2])
							max = pDoc->inputImage[y + j - 1][(x + i - 1) * 3 + 2];
					}
				}
				pDoc->resultImage[y][x * 3 + 2] = max;
			}
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnMopologyColorToGray()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 1; y < pDoc->imageHeight - 1; y++) {
		for (x = 1; x < pDoc->imageWidth - 1; x++) {
			gray = ((pDoc->inputImage[y][x * 3 + 0] + pDoc->inputImage[y][x * 3 + 1] + pDoc->inputImage[y][x * 3 + 0]) / 3);
			pDoc->inputImage[y][x * 3 + 0] = gray;
			pDoc->inputImage[y][x * 3 + 1] = gray;
			pDoc->inputImage[y][x * 3 + 2] = gray;
		}
	}
	
	Invalidate();
}


void CimagePro20190802View::OnMopologyBinarization()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int th = 100;

	for (y = 1; y < pDoc->imageHeight - 1; y++) {
		for (x = 1; x < pDoc->imageWidth - 1; x++) {
			if(pDoc->depth == 1) {
				if (pDoc->inputImage[y][x] > th)
					pDoc->inputImage[y][x] = 255;
				else
					pDoc->inputImage[y][x] = 0;
			}
			else {
				if (pDoc->inputImage[y][x * 3 + 0] > th) {
					pDoc->inputImage[y][x * 3 + 0] = 255;
					pDoc->inputImage[y][x * 3 + 1] = 255;
					pDoc->inputImage[y][x * 3 + 2] = 255;
				}
				else {
					pDoc->inputImage[y][x * 3 + 0] = 0;
					pDoc->inputImage[y][x * 3 + 1] = 0;
					pDoc->inputImage[y][x * 3 + 2] = 0;
				}
			}
		}
	}

	Invalidate();
}


void CimagePro20190802View::CopyResultToInput()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;

	for (y = 1; y < pDoc->imageHeight - 1; y++) {
		for (x = 1; x < pDoc->imageWidth * pDoc->depth; x++) {
			pDoc->inputImage[y][x] = pDoc->resultImage[y][x];
		}
	}
}


void CimagePro20190802View::OnMopologyOpenning()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();

	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
}


void CimagePro20190802View::OnMoplogyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();

	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
}


void CimagePro20190802View::OnGeometryZoominPixelCopy()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	int x, y, i, j;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImage != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);	
	}

	pDoc->gImageWidth = pDoc->imageWidth * xscale;
	pDoc->gImageHeight = pDoc->imageHeight * yscale;

	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	/*
	//전방향사상
	for (y = 0; y < pDoc->imageHeight; y++) {
		for (x = 0; x < pDoc->imageWidth; x++) {
			for (j = 0; j < yscale; j++) {
				for (i = 0; i < xscale; i++) {
					if (pDoc->depth == 1) {
						pDoc->gResultImage[yscale * y + j][xscale * x + i] = pDoc->inputImage[y][x];
					}
					else {
						pDoc->gResultImage[yscale * y + j][(xscale * x + i) * 3 + 0] = pDoc->inputImage[y][x * 3 + 0];
						pDoc->gResultImage[yscale * y + j][(xscale * x + i) * 3 + 1] = pDoc->inputImage[y][x * 3 + 1];
						pDoc->gResultImage[yscale * y + j][(xscale * x + i) * 3 + 2] = pDoc->inputImage[y][x * 3 + 2];
					}
				}
			}
		}
	}
	*/

	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++) {
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->gResultImage[y][x] = pDoc->inputImage[y / yscale][x / xscale];
			}
			else {
				pDoc->gResultImage[y][x * 3 + 0] = pDoc->inputImage[y / yscale][(x / xscale) * 3 + 0];
				pDoc->gResultImage[y][x * 3 + 1] = pDoc->inputImage[y / yscale][(x / xscale) * 3 + 1];
				pDoc->gResultImage[y][x * 3 + 2] = pDoc->inputImage[y / yscale][(x / xscale) * 3 + 2];
			}
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnGeometryZoominBinuerinterpolation()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	int x, y, i, j;

	float xscale = 2.3;	//3 . . .
	float yscale = 1.7;	//2 . . .
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImage != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) 
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = pDoc->imageWidth * xscale;
	pDoc->gImageHeight = pDoc->imageHeight * yscale;
	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향 사상 (여기서 전방향 사상은 안됨. 중간중간 연산이 안될 수 있음)
	for (y = 0; y < pDoc->gImageHeight; y++) {
		for (x = 0; x < pDoc->gImageWidth; x++) {
			src_x = x / xscale;
			src_y = y / yscale;

			/*alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;*/
			alpha = src_x - src_x;
			beta = src_y - src_y;

			/*Ax = (int)src_x;
			Ay = (int)src_y;*/
			Ax = src_x;
			Ay = src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ax + 1;

			if (Bx > pDoc->imageWidth - 1) Bx = pDoc->imageWidth - 1;
			if (Cy > pDoc->imageHeight - 1) Cy = pDoc->imageHeight - 1;
			if (Dx > pDoc->imageWidth - 1) Dx = pDoc->imageWidth - 1;
			if (Dy > pDoc->imageHeight - 1) Dy = pDoc->imageHeight - 1;

			if (pDoc->depth == 1) {
				E = (1 - alpha) * pDoc->inputImage[Ay][Ax] + alpha * pDoc->inputImage[By][Bx];
				F = (1 - alpha) * pDoc->inputImage[Cy][Cx] + alpha * pDoc->inputImage[Dy][Dx];
				pDoc->gResultImage[y][x] = (1 - beta) * E + beta * F;
			}
			else {
				E = (1 - alpha) * pDoc->inputImage[Ay][Ax * 3 + 0] + alpha * pDoc->inputImage[By][Bx * 3 + 0];
				F = (1 - alpha) * pDoc->inputImage[Cy][Cx * 3 + 0] + alpha * pDoc->inputImage[Dy][Dx * 3 + 0];
				pDoc->gResultImage[y][x * 3 + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->inputImage[Ay][Ax * 3 + 1] + alpha * pDoc->inputImage[By][Bx * 3 + 1];
				F = (1 - alpha) * pDoc->inputImage[Cy][Cx * 3 + 1] + alpha * pDoc->inputImage[Dy][Dx * 3 + 1];
				pDoc->gResultImage[y][x * 3 + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->inputImage[Ay][Ax * 3 + 2] + alpha * pDoc->inputImage[By][Bx * 3 + 2];
				F = (1 - alpha) * pDoc->inputImage[Cy][Cx * 3 + 2] + alpha * pDoc->inputImage[Dy][Dx * 3 + 2];
				pDoc->gResultImage[y][x * 3 + 2] = (1 - beta) * E + beta * F;
			}
		}
	}

	Invalidate();
}


void CimagePro20190802View::OnGeometryZoomoutSubsampling()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	int x, y, i, j;

	int xscale = 3;	
	int yscale = 2;	

	if (pDoc->gResultImage != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = pDoc->imageWidth / xscale;
	pDoc->gImageHeight = pDoc->imageHeight / yscale;
	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향
	for (y = 0; y < pDoc->gImageHeight; y++) {
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->gResultImage[y][x] = pDoc->inputImage[y * yscale][x * xscale];
			}
			else {
				pDoc->gResultImage[y][x * 3 + 0] = pDoc->inputImage[y * yscale][(x * xscale) * 3 + 0];
				pDoc->gResultImage[y][x * 3 + 1] = pDoc->inputImage[y * yscale][(x * xscale) * 3 + 1];
				pDoc->gResultImage[y][x * 3 + 2] = pDoc->inputImage[y * yscale][(x * xscale) * 3 + 2];
			}

		}
	}

	Invalidate();
}


void CimagePro20190802View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmoothing();	//흐리게하기 meaning
	CopyResultToInput();	
	OnGeometryZoomoutSubsampling();
}




void CimagePro20190802View::OnGeometryZoomoutAvg()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	int x, y, i, j;
	int src_x, src_y;
	int sum; 
	int rsum, gsum, bsum;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImage != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = pDoc->imageWidth / xscale;
	pDoc->gImageHeight = pDoc->imageHeight / yscale;
	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향
	for (y = 0; y < pDoc->imageHeight - yscale; y += yscale) {
		for (x = 0; x < pDoc->imageWidth - xscale; x += xscale) {
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = 0; j < yscale; j++) {
					for (i = 0; i < xscale; i++) {
						src_x = x + i;
						src_y = y + j;
						sum += pDoc->inputImage[src_y][src_x];
					}
				}
				pDoc->gResultImage[y / yscale][x / xscale] = sum / (xscale * yscale);
			}
			else {
				rsum = gsum = bsum = 0;
				for (j = 0; j < yscale; j++) {
					for (i = 0; i < xscale; i++) {
						src_x = x + i;
						src_y = y + j;
						rsum += pDoc->inputImage[src_y][src_x * 3 + 0];
						gsum += pDoc->inputImage[src_y][src_x * 3 + 1];
						bsum += pDoc->inputImage[src_y][src_x * 3 + 2];
					}
				}
				pDoc->gResultImage[y / yscale][(x / xscale) * 3 + 0] = rsum / (xscale * yscale);
				pDoc->gResultImage[y / yscale][(x / xscale) * 3 + 1] = gsum / (xscale * yscale);
				pDoc->gResultImage[y / yscale][(x / xscale) * 3 + 2] = bsum / (xscale * yscale);
			}
		}
	}

	Invalidate();
}


#define PI 3.141592653589793238

void CimagePro20190802View::OnGeometryRotate()
{
	CimagePro20190802Doc* pDoc = GetDocument();
	CAngleInputDlg dlg;

	int angle = 0; //degree
	float radian;
	int x, y, i;
	int Cx, Cy, Hy;
	int x_source, y_source;
	int xdiff, ydiff;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	radian = PI / 180 * angle;

	if (pDoc->gResultImage != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = pDoc->imageHeight * fabs(cos(PI / 2 - radian)) + pDoc->imageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->imageHeight * fabs(cos(radian)) + pDoc->imageWidth * fabs(cos(PI / 2 - radian));
	//메모리 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//중심점
	Cx = pDoc->imageWidth / 2;
	Cy = pDoc->imageHeight / 2;
	//y의 마지막좌표
	Hy = pDoc->imageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->imageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->imageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++) {
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++) {
			
			x_source = ((Hy - y) - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - (((Hy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1) {
				if (x_source < 0 || x_source > pDoc->imageWidth - 1 || y_source < 0 || y_source > pDoc->imageHeight - 1) {
					pDoc->gResultImage[y + ydiff][x + xdiff] = 255;
				}
				else {
					pDoc->gResultImage[y + ydiff][x + xdiff] = pDoc->inputImage[y_source][x_source];
				}
			}
			else{
				if (x_source < 0 || x_source > pDoc->imageWidth - 1 || y_source < 0 || y_source > pDoc->imageHeight - 1) {
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 0] = 255;
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 1] = 255;
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 2] = 255;
				}
				else {
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 0] = pDoc->inputImage[y_source][x_source * 3 + 0];
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 1] = pDoc->inputImage[y_source][x_source * 3 + 1];
					pDoc->gResultImage[y + ydiff][(x + xdiff) * 3 + 2] = pDoc->inputImage[y_source][x_source * 3 + 2];
				}
			}
		}
	}

	Invalidate();
}
