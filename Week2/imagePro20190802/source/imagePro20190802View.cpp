﻿
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

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(x, y, RGB(pDoc->inputImage[y][x], pDoc->inputImage[y][x], pDoc->inputImage[y][x]));
		}
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(x, 256 + 20 + y, RGB(pDoc->resultImage1[y][x], pDoc->resultImage1[y][x], pDoc->resultImage1[y][x]));
		}
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(256 + 20 + x, 256 + 20 + y, RGB(pDoc->resultImage2[y][x], pDoc->resultImage2[y][x], pDoc->resultImage2[y][x]));
		}
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(x, 256 + 20 + 256 + 20 + y, RGB(pDoc->resultImage3[y][x], pDoc->resultImage3[y][x], pDoc->resultImage3[y][x]));
		}
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(256 + 20 + x, 256 + 20 + 256 + 20 + y, RGB(pDoc->resultImage4[y][x], pDoc->resultImage4[y][x], pDoc->resultImage4[y][x]));
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

	int x, y;
	int value;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			value = pDoc->inputImage[y][x] + 100;
			if (value >= 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImage1[y][x] = value;
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelSub()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			value = pDoc->inputImage[y][x] - 100;
			if (value >= 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImage2[y][x] = value;
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelMul()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			value = pDoc->inputImage[y][x] * 1.5;
			if (value >= 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImage3[y][x] = value;
		}
	}
	Invalidate();
}


void CimagePro20190802View::OnPixelDiv()
{
	CimagePro20190802Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			value = pDoc->inputImage[y][x] / 1.5;
			if (value >= 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImage4[y][x] = value;
		}
	}
	Invalidate();
}
