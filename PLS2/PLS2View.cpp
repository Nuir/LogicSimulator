
// PLS2View.cpp : CPLS2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "PLS2.h"
#endif

#include "PLS2Doc.h"
#include "PLS2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLS2View

IMPLEMENT_DYNCREATE(CPLS2View, CView)

BEGIN_MESSAGE_MAP(CPLS2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CPLS2View::Create_Input_BCLK)
	ON_COMMAND(ID_32772, &CPLS2View::Create_Output_BCLK)
END_MESSAGE_MAP()

// CPLS2View ����/�Ҹ�

CPLS2View::CPLS2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CPLS2View::~CPLS2View()
{
}

BOOL CPLS2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CPLS2View �׸���

CPoint CPLS2View::DividedByTen(CPoint point)
{
	CPoint currentPoint;
	if (point.x % 10 <= 4)
		currentPoint.x = point.x - point.x % 10;
	else
		currentPoint.x = point.x + (10 - (point.x % 10));

	if (point.y % 10 <= 4)
		currentPoint.y = point.y - point.y % 10;
	else
		currentPoint.y = point.y + (10 - (point.y % 10));

	return currentPoint;
}

void CPLS2View::OnDraw(CDC* pDC)
{
	CPLS2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	int i = 0;
	for (i = 0; i <= ls.count_input; i++) {
		if (ls.in[i].clicked.x != 0 && ls.in[i].clicked.y != 0)
		{
			pDC->Rectangle(ls.in[i].min.x*10, ls.in[i].min.y*10, ls.in[i].max.x*10, ls.in[i].max.y*10);
		}
	}
	for (i = 0; i <= ls.count_output; i++) {
		if (ls.out[i].clicked.x != 0 && ls.out[i].clicked.y != 0)
		{
			pDC->Ellipse(ls.out[i].min.x * 10, ls.out[i].min.y * 10, ls.out[i].max.x * 10, ls.out[i].max.y * 10);
		}
	}
}


// CPLS2View �μ�

BOOL CPLS2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CPLS2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CPLS2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CPLS2View ����

#ifdef _DEBUG
void CPLS2View::AssertValid() const
{
	CView::AssertValid();
}

void CPLS2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPLS2Doc* CPLS2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPLS2Doc)));
	return (CPLS2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPLS2View �޽��� ó����


void CPLS2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	if (ls.create >= 0) {
		switch (ls.create) {
		case LSINPUT:
			ls.create_input(&ls.in[ls.count_input], pointofpif);
			ls.create = -1;
			Invalidate();
			break;
		case LSOUTPUT:
			ls.create_output(&ls.out[ls.count_output], pointofpif);
			ls.create = -1;
			Invalidate();
			break;
		}
	}
	else {
		if (ls.pif[p1.x / 10][p1.y / 10].gate == input) {
			ls.pif[p1.x / 10][p1.y / 10].value = ls.in[ls.pif[p1.x / 10][p1.y / 10].input].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (ls.pif[p1.x / 10][p1.y / 10].gate == output) {
			ls.pif[p1.x / 10][p1.y / 10].value = ls.out[ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (ls.pif[p1.x / 10][p1.y / 10].gate == line) {
			ls.pif[p1.x / 10][p1.y / 10].value = ls.out[ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPLS2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonUp(nFlags, point);
}


void CPLS2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	if (ls.create >= 0) {
		switch (ls.create) {
		case LSINPUT:
			if (point.x % 5 == 0 || point.y % 5 == 0) {
				Invalidate();
			}
			dc.Rectangle(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			break;
		case LSOUTPUT:
			if(point.x % 5 == 0 || point.y % 5 == 0) {
				Invalidate();
			}
			dc.Ellipse(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CPLS2View::Create_Input_BCLK()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ls.count_input++;
	ls.create = LSINPUT;
}


void CPLS2View::Create_Output_BCLK()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ls.count_output++;
	ls.create = LSOUTPUT;
}
