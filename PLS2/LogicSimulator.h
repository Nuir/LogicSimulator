#pragma once
#include "stdafx.h"

#define INDEX 300

#define LSINPUT 0
#define LSOUTPUT 1

//enum�����Դϴ�.
enum WhatGate { nothing, input, output, line };

class LogicSimulator
{

public:
//����ü�Դϴ�.
public: 

	struct PointInfo {

		//���� ����ΰ�
		int input = -1; //�Է�
		int output = -1; //���
		int and = -1;
		int or = -1;
		int xor = -1;
		int not = -1;
		int line = -1;


		BOOL gatein = FALSE; //����Ʈ�� �Է°����� ���Ǵ°�
		BOOL gateout = FALSE; //����Ʈ�� ��°����� ���Ǵ°�
	
		BOOL lineok = FALSE;
		WhatGate gate = nothing;
		BOOL usingpoint = FALSE;

		int* value = NULL;
	}pinfo;

	struct Input {
		int* value = NULL;
		CString name;
		CPoint clicked{ -1, -1 };
		CPoint min;
		CPoint max;
		CPoint output[4];
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

//�����Դϴ�.
public:
	PointInfo pif[INDEX][INDEX];
	Input in[INDEX];
	Output out[INDEX];

	WhatGate whatgate = nothing;

	int count_input = -1;
	int count_output = -1;

	int create = -1;

//�Լ��Դϴ�.
public:
	LogicSimulator::LogicSimulator();
	void OnePointClear(PointInfo pif);
	void AllPointClear(PointInfo pif[INDEX][INDEX]);
	void print(LogicSimulator ls);
	void create_input(Input* in, CPoint clicked);
	void create_output(Output* out, CPoint clicked);
};