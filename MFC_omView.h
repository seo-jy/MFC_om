
// MFC_omView.h: CMFComView 클래스의 인터페이스
//

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class CMFComView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFComView() noexcept;
	DECLARE_DYNCREATE(CMFComView)

// 특성입니다.
public:
	CMFComDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFComView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	vector<CPoint> ball;
	int flag;
	int arr[19][19];
	int state;
	int CountA;
	int CountB;
	int CountC;
	int CountD;
	int result;
	afx_msg void OnMyopen();
	afx_msg void OnMysave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void Shift1(int x, int y);
	void Shift2(int x, int y);
	void Shift3(int x, int y);
	void Shift4(int x, int y);
	void Shift5(int x, int y);
	void Shift6(int x, int y);
	void Shift7(int x, int y);
	void Shift8(int x, int y);

};

#ifndef _DEBUG  // MFC_omView.cpp의 디버그 버전
inline CMFComDoc* CMFComView::GetDocument() const
   { return reinterpret_cast<CMFComDoc*>(m_pDocument); }
#endif

