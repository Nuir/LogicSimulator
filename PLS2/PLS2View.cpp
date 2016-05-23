
// PLS2View.cpp : CPLS2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CPLS2View::Create_Input_BCLK)
	ON_COMMAND(ID_32772, &CPLS2View::Create_Output_BCLK)
	ON_COMMAND(ID_32773, &CPLS2View::Create_AndGate_BCLK)
END_MESSAGE_MAP()

// CPLS2View 생성/소멸

CPLS2View::CPLS2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPLS2View::~CPLS2View()
{
}

BOOL CPLS2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPLS2View 그리기

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

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i = 0;

	//격자를 그림
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 300; j++)
			pDC->SetPixel(i * 10, j * 10, RGB(0, 0, 0));

	//그려진 선을 그림
	for (int i = 0; i < pDoc->ls.line.GetSize(); i++) {
		pDC->MoveTo(pDoc->ls.line[i].firstPt);
		pDC->LineTo(pDoc->ls.line[i].secondPt);
	}

	//존재하는 input단자의 개수만큼 그려줌.(Rectangle이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
	for (i = 0; i <= pDoc->ls.count_input; i++) {
		if (pDoc->ls.in[i].clicked.x != 0 && pDoc->ls.in[i].clicked.y != 0)
		{
			pDC->Rectangle(pDoc->ls.in[i].min.x*10, pDoc->ls.in[i].min.y*10, pDoc->ls.in[i].max.x*10, pDoc->ls.in[i].max.y*10);
		}
	}
	//존재하는 output단자의 개수만큼 그려줌.(Ellipse이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
	for (i = 0; i <= pDoc->ls.count_output; i++) {
		if (pDoc->ls.out[i].clicked.x != 0 && pDoc->ls.out[i].clicked.y != 0)
		{
			pDC->Ellipse(pDoc->ls.out[i].min.x * 10, pDoc->ls.out[i].min.y * 10, pDoc->ls.out[i].max.x * 10, pDoc->ls.out[i].max.y * 10);
		}
	}
	//존재하는 and게이트의 개수만큼 그려줌.(min(왼쪽끝)점과 max(오른쪽)점을 가짐)

	for (i = 0; i <= pDoc->ls.count_and; i++) {
		if (pDoc->ls.and[i].clicked.x != 0 && pDoc->ls.and[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_BITMAP4);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->BitBlt(pDoc->ls.and[i].min.x*10, pDoc->ls.and[i].min.y*10, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		}
	}
}


// CPLS2View 인쇄

BOOL CPLS2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPLS2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPLS2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPLS2View 진단

#ifdef _DEBUG
void CPLS2View::AssertValid() const
{
	CView::AssertValid();
}

void CPLS2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPLS2Doc* CPLS2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPLS2Doc)));
	return (CPLS2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPLS2View 메시지 처리기
void CPLS2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	pDoc->ls.downPoint = DividedByTen(point); //마우스를 누르기 시작한 지점의 좌표를 받을 수 있음.
	
	// 단자 또는 게이트를 생성한다고 할고있을 때.
	if (pDoc->ls.create >= 0) {
		switch (pDoc->ls.create) {
		case LSINPUT:
			pDoc->ls.create_input(&pDoc->ls.in[pDoc->ls.count_input], pointofpif);
			pDoc->ls.create = -1; // 마우스를 누르는 순간 그 위치에 그려지게 되므로 초기값으로 돌려줌.
			Invalidate();
			break;
		case LSOUTPUT:
			pDoc->ls.create_output(&pDoc->ls.out[pDoc->ls.count_output], pointofpif);
			pDoc->ls.create = -1;
			Invalidate();
			break;
		case LSAND:
			pDoc->ls.create_and(&pDoc->ls.and[pDoc->ls.count_and], pointofpif); // 만드는 함수 호출.
			pDoc->ls.create = -1;
			Invalidate();
			break;
		}
	}

	else {
		if (pDoc->ls.pif[p1.x / 10][p1.y / 10].lineok == TRUE)
			pDoc->ls.canDrawState = TRUE;
	}
	/* //여기서 선을 그릴 수 있는 곳인지 판단.
	else { // 그밖에 선을 그린다고 알고있을 때.
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
	*/
	CView::OnLButtonDown(nFlags, point);
}


void CPLS2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CDC* pDC = GetDC();

	pDoc->ls.upPoint = DividedByTen(point); //마우스를 누르기 시작한 지점의 좌표를 받을 수 있음.


	if(pDoc->ls.canDrawState == TRUE)
		pDoc->ls.SavePointOnTheLine(old_start, old_end, old_wherefixed); // 선에대한 점을 저장.

	Invalidate();

	//이게 있어야 이전에 그렸던게 안없어짐.
	old_start.x = 0;
	old_start.y = 0;
	old_end.x = 0;
	old_end.y = 0;
	pDoc->ls.canDrawState = FALSE;
	CView::OnLButtonUp(nFlags, point);
}



void CPLS2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	CPoint movedFirstPoint = DividedByTen(p1); // 마우스를 처음 누른 뒤 움직인 첫 위치
	CPoint startPoint = DividedByTen(pDoc->ls.downPoint);

	CDC* pDC = GetDC();


	//"pDoc->ls.create >= 0" 이 상태는 단자 또는 게이트를 메뉴에서 클릭하여 그리려고 하는 상태임.
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
		case LSAND:
			if (point.x % 5 == 0 || point.y % 5 == 0) {
				Invalidate();
			}
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_BITMAP4);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);

			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			dc.BitBlt(p1.x-40, p1.y-20, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
			break;
		}
		
	}


	//"pDoc->ls.create < 0 && nFlags & MK_LBUTTON" 이 상태는 메뉴의 게이트 또는 단자를 클릭하지 않은 상태이며 마우스가 눌린상태,, 선을 그릴 수 있음. 
	if (pDoc->ls.create < 0 && nFlags & MK_LBUTTON && pDoc->ls.canDrawState == TRUE) {
		//pDoc->ls.pif[p1.x / 10][p1.y / 10]->linevalue = pDoc->ls.pif[startline.x / 10][startline.y / 10]->linevalue;
		//pDoc->ls.pif[p1.x / 10][p1.y / 10].gate = pDoc->ls.  /*->ls->isline*/;

		//(초기상태)그림을 그릴때 어디가(가로,세로) 고정되는지 정해져 있지 않고 마우스를 누른위치와 현재마우스의 위치가 다르다면 가로 세로 중에서 한쪽으로 고정을 시켜줌.
		if (pDoc->ls.wherefixed == DEFAULT &&  startPoint != p1) {

			if (startPoint.y == p1.y) // 가로로 고정되어서 그려지는 경우
				pDoc->ls.wherefixed = GARO;

			else if (startPoint.x == p1.x) // 세로로 고정되어서 그려지는 경우
				pDoc->ls.wherefixed = SERO;
		}

		//선을 저장하지는 않고 움진인 위치로 그리기만 함.
		drawingline(startPoint, p1, pDoc->ls.wherefixed);

		//고정된 것을 초기상태로 돌려줘야 할 때 (초기상태)로 돌려줌.
		if (pDoc->ls.wherefixed == GARO && startPoint.x == p1.x || startPoint == p1) 
			pDoc->ls.wherefixed = DEFAULT;

		else if (pDoc->ls.wherefixed == SERO && startPoint.y == p1.y || startPoint == p1)
			pDoc->ls.wherefixed = DEFAULT;
	}
	CView::OnMouseMove(nFlags, point);
}


void CPLS2View::drawingline(CPoint start, CPoint end, WhereFixed wherefixed) {
	CPLS2Doc* pDoc = GetDocument();

	CDC* pDC = GetDC();

	CPen pen1(PS_SOLID, 1, RGB(0, 0, 0)); // 검정펜
	CPen pen2(PS_SOLID, 1, RGB(255, 255, 255)); //흰펜

	pDC->SelectObject(pen2);

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1줄만 그리는경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end);
		}

		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end.x, old_start.y);

			pDC->MoveTo(old_end.x, old_start.y);
			pDC->LineTo(old_end);
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1줄만 그리는경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end);
		}
		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_start.x, old_end.y);

			pDC->MoveTo(old_start.x, old_end.y);
			pDC->LineTo(old_end);
		}
	}

	pDC->SelectObject(pen1);

	if (wherefixed == GARO)
		if (start.y == end.y) { // 1줄만 그리는경우.
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}

		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(start);
			pDC->LineTo(end.x, start.y);

			pDC->MoveTo(end.x, start.y);
			pDC->LineTo(end);
		}
	else if (wherefixed == SERO){
		if (start.x == end.x) { // 1줄만 그리는경우.
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}
		else {//두줄을 그려줘야 하는 경우.
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


void CPLS2View::Create_Input_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_input++;
	pDoc->ls.create = LSINPUT; //  create를 LSINPUT(0)으로 만들어 input단자를 만들겠다고 알림.
}


void CPLS2View::Create_Output_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_output++;
	pDoc->ls.create = LSOUTPUT; //  create를 LSOUTPUT(1)으로 만들어 output단자를 만들겠다고 알림.
}


void CPLS2View::Create_AndGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_and++;
	pDoc->ls.create = LSAND; //  create를 LSOUTPUT(1)으로 만들어 output단자를 만들겠다고 알림.
}
