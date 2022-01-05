
// imagePro20190802Doc.h: CimagePro20190802Doc 클래스의 인터페이스
//


#pragma once


class CimagePro20190802Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CimagePro20190802Doc() noexcept;
	DECLARE_DYNCREATE(CimagePro20190802Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CimagePro20190802Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 입력 이미지
	unsigned char **inputImage;		//[y][x]
	unsigned char **inputImage2;	//[y][x]

	// 출력 이미지
	unsigned char **resultImage;	//[y][x]

	int imageWidth;
	int imageHeight;
	int depth;

	int gImageWidth;
	int gImageHeight;
	unsigned char** gResultImage;
	unsigned char** morphedImage[10];

	int LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
};
