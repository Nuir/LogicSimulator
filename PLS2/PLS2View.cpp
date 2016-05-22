
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
	for (i = 0; i <= pDoc->ls.count_input; i++) {
		if (pDoc->ls.in[i].clicked.x != 0 && pDoc->ls.in[i].clicked.y != 0)
		{
			pDC->Rectangle(pDoc->ls.in[i].min.x*10, pDoc->ls.in[i].min.y*10, pDoc->ls.in[i].max.x*10, pDoc->ls.in[i].max.y*10);
		}
	}
	for (i = 0; i <= pDoc->ls.count_output; i++) {
		if (pDoc->ls.out[i].clicked.x != 0 && pDoc->ls.out[i].clicked.y != 0)
		{
			pDC->Ellipse(pDoc->ls.out[i].min.x * 10, pDoc->ls.out[i].min.y * 10, pDoc->ls.out[i].max.x * 10, pDoc->ls.out[i].max.y * 10);
		}
	}
	////////////////////////////////////////////////////////////
	for (int i = 0; i < pDoc->ls.line.GetSize(); i++){
		pDC->MoveTo(pDoc->ls.line[i].firstPt);
		pDC->LineTo(pDoc->ls.line[i].secondPt);
	}
	/////////////////////////////////////////////////////////////
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
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	//////////////////////////////////////////
	pDoc->ls.downPoint = DividedByTen(point); //���콺�� ������ ������ ������ ��ǥ�� ���� �� ����.
	//////////////////////////////////////////

	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	if (pDoc->ls.create >= 0) {
		switch (pDoc->ls.create) {
		case LSINPUT:
			pDoc->ls.create_input(&pDoc->ls.in[pDoc->ls.count_input], pointofpif);
			pDoc->ls.create = -1;
			Invalidate();
			break;
		case LSOUTPUT:
			pDoc->ls.create_output(&pDoc->ls.out[pDoc->ls.count_output], pointofpif);
			pDoc->ls.create = -1;
			Invalidate();
			break;
		}
	}
	else {
		if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == input) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.in[pDoc->ls.pif[p1.x / 10][p1.y / 10].input].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == output) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.out[pDoc->ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == line) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.out[pDoc->ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPLS2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	///////////////////////////////////////////////////
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);

	pDoc->ls.upPoint = DividedByTen(point); //���콺�� ������ ������ ������ ��ǥ�� ���� �� ����.

	SavePointOnTheLine(); // �������� ���� ����.

	Invalidate();
	///////////////////////////////////////////////////

	CView::OnLButtonUp(nFlags, point);
}

void CPLS2View::SavePointOnTheLine() {
	CPLS2Doc* pDoc = GetDocument();

	CPoint tempP;

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1�ٸ� �׸��°��.
			pDoc->ls.line.Add(pDoc->ls.GetTwoPt(old_start, old_end));
		}

		else {//������ �׷���� �ϴ� ���.
			tempP.x = old_end.x;
			tempP.y = old_start.y;
			pDoc->ls.line.Add(pDoc->ls.GetTwoPt(old_start, tempP));

			tempP.x = old_end.x;
			tempP.y = old_start.y;
			pDoc->ls.line.Add(pDoc->ls.GetTwoPt(tempP, old_end));
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1�ٸ� �׸��°��.
			pDoc->ls.line.Add(pDoc->ls.GetTwoPt(old_start, old_end));
		}
		else {//������ �׷���� �ϴ� ���.
			tempP.x = old_start.x;
			tempP.y = old_end.y;
			pDoc->ls.line.Add(pDoc->ls.GetTwoPt(old_start, tempP));

			tempP.x = old_start.x;
			tempP.y = old_end.y;
			pDoc->ls.line.Add(pDoc->ls.GetTwoPt(tempP, old_end));
		}
	}
}

void CPLS2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };

	if (pDoc->ls.create >= 0) {
		switch (pDoc->ls.create) {
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

	/////////////////////////////////////////
	CPoint movedFirstPoint = DividedByTen(p1); // ���콺�� ó�� ���� �� ������ ù ��ġ
	CPoint startPoint = DividedByTen(pDoc->ls.downPoint);


	if (pDoc->ls.create < 0 && nFlags & MK_LBUTTON) { //�׸��� ���� �׸� �� ������ , �巡���ؼ� �� ���� �� ���� �� ����.
		//pDoc->ls.pif[p1.x / 10][p1.y / 10]->linevalue = pDoc->ls.pif[startline.x / 10][startline.y / 10]->linevalue;
		//pDoc->ls.pif[p1.x / 10][p1.y / 10].gate = pDoc->ls.  /*->ls->isline*/;


		//�׸��� �׸��� ��� �����Ǵ��� ������ ���� �ʰ� ���콺�� ������ġ�� ���縶�콺�� ��ġ�� �ٸ��ٸ�.
		if (pDoc->ls.wherefixed == DEFAULT &&  startPoint != p1) {

			if (startPoint.y == p1.y) {// ���η� �����Ǿ �׷����� ���
				pDoc->ls.wherefixed = GARO;
			}

			else if (startPoint.x == p1.x) {// ���η� �����Ǿ �׷����� ���
				pDoc->ls.wherefixed = SERO;
			}
		}

		drawingline(startPoint, p1, pDoc->ls.wherefixed); // downPoint: ���콺�� ���� ������ġ  p1 : ���콺 Ŀ���� ������ġ

		if (pDoc->ls.wherefixed == GARO && startPoint.x == p1.x || startPoint == p1) 
			pDoc->ls.wherefixed = DEFAULT;

		else if (pDoc->ls.wherefixed == SERO && startPoint.y == p1.y || startPoint == p1)
			pDoc->ls.wherefixed = DEFAULT;
	}
	/////////////////////////////////////////
	CView::OnMouseMove(nFlags, point);
}

///////////////////////////////////////
void CPLS2View::drawingline(CPoint start, CPoint end, WhereFixed wherefixed) {
	CPLS2Doc* pDoc = GetDocument();

	CDC* pDC = GetDC();

	CPen pen1(PS_SOLID, 1, RGB(0, 0, 0)); // ������
	CPen pen2(PS_SOLID, 1, RGB(255, 255, 255)); //����

	pDC->SelectObject(pen2);

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1�ٸ� �׸��°��.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end);
		}

		else {//������ �׷���� �ϴ� ���.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end.x, old_start.y);

			pDC->MoveTo(old_end.x, old_start.y);
			pDC->LineTo(old_end);
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1�ٸ� �׸��°��.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end);
		}
		else {//������ �׷���� �ϴ� ���.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_start.x, old_end.y);

			pDC->MoveTo(old_start.x, old_end.y);
			pDC->LineTo(old_end);
		}
	}

	pDC->SelectObject(pen1);

	if (wherefixed == GARO)
		if (start.y == end.y) { // 1�ٸ� �׸��°��.
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}

		else {//������ �׷���� �ϴ� ���.
			pDC->MoveTo(start);
			pDC->LineTo(end.x, start.y);

			pDC->MoveTo(end.x, start.y);
			pDC->LineTo(end);
		}
	else if (wherefixed == SERO){
		if (start.x == end.x) { // 1�ٸ� �׸��°��.
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}
		else {//������ �׷���� �ϴ� ���.
			pDC->MoveTo(start);
			pDC->LineTo(start.x, end.y);

			pDC->MoveTo(start.x, end.y);
			pDC->LineTo(end);
		}
	}

	old_start = start;
	old_end = end;
	old_wherefixed = wherefixed;
}
///////////////////////////////////////


void CPLS2View::Create_Input_BCLK()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_input++;
	pDoc->ls.create = LSINPUT;
}


void CPLS2View::Create_Output_BCLK()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_output++;
	pDoc->ls.create = LSOUTPUT;
}

