#pragma once
#include "stdafx.h"

#define INDEX 300

#define LSINPUT 0
#define LSOUTPUT 1
#define LSAND 2


//enum변수입니다.
enum WhatGate { nothing, input, output, line };
enum WhereFixed { DEFAULT, SERO, GARO }; // 그림그릴 때 가로가 고정되었나 세로가 고정되었나?

class LogicSimulator
{

public:
//구조체입니다.
public: 

	struct PointInfo {

		//각각 몇번인가
		int input = -1; //입력
		int output = -1; //출력
		int and = -1;
		int or = -1;
		int xor = -1;
		int not = -1;
		int line = -1;


		BOOL gatein = FALSE; //게이트의 입력값으로 사용되는가
		BOOL gateout = FALSE; //게이트의 출력값으로 사용되는가
	
		BOOL lineok = FALSE;
		WhatGate gate = nothing;
		BOOL usingpoint = FALSE;

		int* value = NULL;
	}pinfo;

	struct Input {
		int* value = NULL; // 가지는 값.
		CString name;
		CPoint clicked{ -1, -1 }; // 사각형의 중점.
		CPoint min; // 사각형의 왼쪽 끝점
		CPoint max; // 사각형의 오른쪽 끝점
		CPoint output[4];  // 값을 내보낼 수 있는 점.
	};

	struct Output {
		int* value = NULL; 
		CString name;
		CPoint clicked{ -1, -1 }; 
		CPoint min; 
		CPoint max;
		CPoint input[4];
		CPoint points[9] = { (clicked.x - 1, clicked.y - 1), (clicked.x, clicked.y - 1), (clicked.x + 1, clicked.y - 1),
							 (clicked.x - 1, clicked.y) ,    (clicked.x, clicked.y) ,    (clicked.x + 1, clicked.y) ,
							 (clicked.x - 1, clicked.y + 1), (clicked.x, clicked.y + 1), (clicked.x + 1, clicked.y + 1) };
	};

	struct AndGate {
		int* value = NULL; // 가지는 값.
		CString name;
		CPoint clicked{ -1, -1 }; // 사각형의 중점.
		CPoint min; // 사각형의 왼쪽 끝점
		CPoint max; // 사각형의 오른쪽 끝점
		CPoint output[1];  // 값을 내보낼 수 있는 점.
		CPoint input[2];
	};

//변수입니다.
public:
	PointInfo pif[INDEX][INDEX];
	Input in[INDEX];
	Output out[INDEX];
	AndGate and[INDEX];

	CPoint downPoint;
	CPoint upPoint;

	struct TwoPt {

		CPoint firstPt;
		CPoint secondPt;
		TwoPt() {

		}

		TwoPt(CPoint a, CPoint b) {
			firstPt = a;
			secondPt = b;
		}

	};

	TwoPt GetTwoPt(CPoint a, CPoint b) {
		TwoPt *p;
		p = new TwoPt(a,b);
		return *p;
	}

	CArray<TwoPt, TwoPt&> line; // TwoPoint의 배열.
	void SavePointOnTheLine(CPoint old_start, CPoint old_end, WhereFixed old_wherefixed);


	WhereFixed wherefixed = DEFAULT;

	WhatGate whatgate = nothing;

	bool canDrawState = false;
	int count_input = -1;
	int count_output = -1;
	int count_and = -1;

	int create = -1; // 이 숫자에 따라 무엇을 생성할 지가 정해짐.

//함수입니다.
public:
	LogicSimulator::LogicSimulator();
	void OnePointClear(PointInfo pif);
	void AllPointClear();
	void print(LogicSimulator ls);
	void create_input(Input* in, CPoint clicked);
	void create_output(Output* out, CPoint clicked);
	void create_and(AndGate *and, CPoint clicked);
};