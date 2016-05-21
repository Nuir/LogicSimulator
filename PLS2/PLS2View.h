
// PLS2View.h : CPLS2View Ŭ������ �������̽�
//

#pragma once
#include "LogicSimulator.h"

class CPLS2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CPLS2View();
	DECLARE_DYNCREATE(CPLS2View)

// Ư���Դϴ�.
public:
	CPLS2Doc* GetDocument() const;

//���� �ùķ����� �����Դϴ�.
public:
	LogicSimulator ls;
	BOOL drawline = FALSE;
	CPoint startline;
	
	CPoint oldpoint;
	int garo = 0, sero = 0;
	

//���� �ùķ����� �Լ��Դϴ�.
	CPoint DividedByTen(CPoint point);

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CPLS2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void Create_Input_BCLK();
	afx_msg void Create_Output_BCLK();
};

#ifndef _DEBUG  // PLS2View.cpp�� ����� ����
inline CPLS2Doc* CPLS2View::GetDocument() const
   { return reinterpret_cast<CPLS2Doc*>(m_pDocument); }
#endif

