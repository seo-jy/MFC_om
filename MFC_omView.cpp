
// MFC_omView.cpp: CMFComView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_om.h"
#endif

#include "MFC_omDoc.h"
#include "MFC_omView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFComView

IMPLEMENT_DYNCREATE(CMFComView, CView)

BEGIN_MESSAGE_MAP(CMFComView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMFComView::OnMyopen)
	ON_COMMAND(ID_32772, &CMFComView::OnMysave)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFComView 생성/소멸

CMFComView::CMFComView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	flag = 0;
	state = 0;
	CountA = 0;
	CountB = 0;
	CountC = 0;
	CountD = 0;
	result = 0;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			arr[i][j] = 0;
		}
	}
}

CMFComView::~CMFComView()
{
}

BOOL CMFComView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFComView 그리기

void CMFComView::OnDraw(CDC* /*pDC*/)
{
	CMFComDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CBrush bs1(RGB(0, 0, 0)), bs2(RGB(255, 255, 255));

	CPen MyPen(PS_SOLID, 0, RGB(244, 176, 77));
	dc.SelectObject(&MyPen);

	CBrush MyBrush(RGB(244, 176, 77));
	dc.SelectObject(&MyBrush);

	dc.Rectangle(20, 20, 20 + 20 * 18, 20 + 20 * 18);

	CPen MyPen2(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&MyPen2);

	for (int y = 0; y <= 18; y++) {
		dc.MoveTo(20, 20 + 20 * y);
		dc.LineTo(20 + 20 * 18, 20 + 20 * y);
	}
	for (int x = 0; x <= 18; x++) {
		dc.MoveTo(20 + 20 * x, 20);
		dc.LineTo(20 + 20 * x, 20 + 20 * 18);
	}

	CBrush MyBrush1(RGB(0, 0, 0));
	dc.SelectObject(&MyBrush1);
	dc.Ellipse(75, 75, 85, 85);
	dc.Ellipse(195, 75, 205, 85);
	dc.Ellipse(315, 75, 325, 85);
	dc.Ellipse(75, 195, 85, 205);
	dc.Ellipse(195, 195, 205, 205);
	dc.Ellipse(315, 195, 325, 205);
	dc.Ellipse(75, 315, 85, 325);
	dc.Ellipse(195, 315, 205, 325);
	dc.Ellipse(315, 315, 325, 325);

	for (int i = 0; i < ball.size(); i++) {
		{
			if (i % 2 == 0)
				dc.SelectObject(bs1);
			else
				dc.SelectObject(bs2);
		}
		dc.Ellipse(ball[i].x - 10, ball[i].y - 10, ball[i].x + 10, ball[i].y + 10);

		//flag = !flag;

		CString str;
			str.Format(L"(%4d, %4d) %s", ball[i].x, ball[i].y, (i % 2 == 0) ? L"흑돌" : L"백돌");
			dc.TextOutW(800, 20 * (i + 1), str);
	}
}


// CMFComView 인쇄

BOOL CMFComView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFComView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFComView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFComView 진단

#ifdef _DEBUG
void CMFComView::AssertValid() const
{
	CView::AssertValid();
}

void CMFComView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFComDoc* CMFComView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFComDoc)));
	return (CMFComDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFComView 메시지 처리기


void CMFComView::OnMyopen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ball.clear();  // 기존의 ball을 지우기
	ifstream fin("data.txt");  //f in
	int n;
	fin >> n;
	int x, y;
	for (int i = 0; i < n; i++) {
		fin >> x >> y;
		ball.push_back(CPoint(x, y));
	}
	fin.close();
	Invalidate();
}


void CMFComView::OnMysave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ofstream fout("data.txt");
	fout << ball.size() << endl;
	for (int i = 0; i < ball.size(); i++)
		fout << ball[i].x << " " << ball[i].y << endl; //x,y따로
	fout.close();
}


void CMFComView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (state == 0)
		state = 1;
	else
		state = 0;

	int x = point.x / 20;
	x += (point.x % 20) >= 10;
	int y = point.y / 20;
	y += (point.y % 20) >= 10;
	int xx = 0;
	int yy = 0;
	if ((x > 0 && x <= 19) && (y > 0 && y <= 19)) {
		if (arr[x - 1][y - 1] > 0)
			return; //돌이 겹치면 return
		arr[x - 1][y - 1] = state + 1;
		xx = x - 1; yy = y - 1;
		x *= 20;
		y *= 20;
	}

	else
		return;

	ball.push_back(CPoint(x, y));

	Shift1(xx, yy);
	Shift2(xx, yy);
	Shift3(xx, yy);
	Shift4(xx, yy);
	Shift5(xx, yy);
	Shift6(xx, yy);
	Shift7(xx, yy);
	Shift8(xx, yy);

	CountA = 0; CountB = 0; CountC = 0; CountD = 0;

	if (result == 1) {
		if (state == 0) MessageBoxW(L"백돌 승리");
		else MessageBoxW(L"흑돌 승리");

		result = 0;
		state = 0;
		ball.clear();
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 18; j++) {
				arr[i][j] = 0;
			}
		}
	}

	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CMFComView::Shift1(int x, int y)  // 왼쪽 위에서 오른쪽 아래로 대각선 방향으로 
{
	if (x - 1 < 0 || y - 1 < 0) {
	}
	else {
		if (arr[x - 1][y - 1] == (state + 1))
			CountA = CountA + 1;
		else return;
		if (CountA == 4)
			result = 1;
		else
			Shift1(x - 1, y - 1);
	}
}

void CMFComView::Shift2(int x, int y) //위에서 아래로 
{
	if (y - 1 < 0) {
	}
	else {
		if (arr[x][y - 1] == (state + 1))
			CountB = CountB + 1;
		else return;
		if (CountB == 4)
			result = 1;
		else
			Shift2(x, y - 1);
	}
}

void CMFComView::Shift3(int x, int y) //오른쪽 위에서 왼쪽 아래 대각선 방향으로 
{
	if (x + 1 > 19 || y - 1 < 0) {
	}
	else {
		if (arr[x + 1][y - 1] == (state + 1))
			CountC = CountC + 1;
		else return;
		if (CountC == 4)
			result = 1;
		else
			Shift3(x + 1, y - 1);
	}
}

void CMFComView::Shift4(int x, int y) //오른쪽에서 왼쪽으로 
{
	// TODO: 여기에 구현 코드 추가.
	if (x + 1 > 19) {
	}
	else {
		if (arr[x + 1][y] == (state + 1))
			CountD = CountD + 1;
		else return;
		if (CountD == 4)
			result = 1;
		else
			Shift4(x + 1, y);
	}
}

void CMFComView::Shift5(int x, int y) //오른쪽 아래에서 왼쪽 위 대각선 방향으로 
{
	// TODO: 여기에 구현 코드 추가.
	if (x + 1 > 19 || y + 1 > 19) {
	}
	else {
		if (arr[x + 1][y + 1] == (state + 1))
			CountA = CountA + 1;
		else return;
		if (CountA == 4)
			result = 1;
		else
			Shift5(x + 1, y + 1);
	}
}

void CMFComView::Shift6(int x, int y) //아래에서 위로
{
	// TODO: 여기에 구현 코드 추가.
	if (y + 1 > 19) {
	}
	else {
		if (arr[x][y + 1] == (state + 1))
			CountB = CountB + 1;
		else return;
		if (CountB == 4)
			result = 1;
		else
			Shift6(x, y + 1);
	}
}

void CMFComView::Shift7(int x, int y) //왼쪽 아래에서 오른쪽 위 대각선 방향으로 
{
	// TODO: 여기에 구현 코드 추가.
	if (x - 1 < 0 || y + 1 > 19) {
	}
	else {
		if (arr[x - 1][y + 1] == (state + 1))
			CountC = CountC + 1;
		else return;
		if (CountC == 4)
			result = 1;
		else
			Shift7(x - 1, y + 1);
	}
}

void CMFComView::Shift8(int x, int y) //왼쪽에서 오른쪽으로
{
	// TODO: 여기에 구현 코드 추가.
	if (x - 1 < 0) {
	}
	else {
		if (arr[x - 1][y] == (state + 1))
			CountD = CountD + 1;
		else return;
		if (CountD == 4)
			result = 1;
		else
			Shift8(x - 1, y);
	}
}