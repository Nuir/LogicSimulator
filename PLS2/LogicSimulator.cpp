

#include "stdafx.h"
#include "LogicSimulator.h"

LogicSimulator::LogicSimulator() 
{

}

void LogicSimulator::OnePointClear(PointInfo pif)
{
	pif.input = -1;
	pif.output = -1;
	pif. and = -1;
	pif. or = -1;
	pif. xor = -1;
	pif. not = -1;
	pif.line = -1;


	pif.gatein = FALSE;
	pif.gateout = FALSE;
	
	pif.lineok = FALSE;
	pif.gate = nothing;
	pif.usingpoint = FALSE;
	pif.value = 0;
}

void LogicSimulator::AllPointClear()
{
	for (int i = 0; i < INDEX; i++)
		for (int j = 0; j < INDEX; j++)
			OnePointClear(pif[i][j]);
}

void LogicSimulator::print(LogicSimulator ls)
{
}

void LogicSimulator::create_input(Input *in, CPoint clicked)
{
	int a = 0;
	in->value = &a;
	in->clicked = clicked; // ���콺�� ���� ��ġ.
	//�簢���� �׸��� ���� left�� right
	in->min = { clicked.x - 1, clicked.y - 1 };
	in->max = { clicked.x + 1, clicked.y + 1 };
	//���� ������ �� �ִ� ��.
	in->output[0] = { clicked.x, clicked.y - 1 };
	in->output[1] = { clicked.x - 1, clicked.y };
	in->output[2] = { clicked.x + 1, clicked.y };
	in->output[3] = { clicked.x, clicked.y + 1 };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			pif[in->min.x + i][in->min.y + j].usingpoint = TRUE;
	for (int i = 0; i < 4; i++) {
		pif[in->output[i].x][in->output[i].y].lineok = TRUE;
		pif[in->output[i].x][in->output[i].y].value = pif[clicked.x][clicked.y].value;
	}
}

void LogicSimulator::create_output(Output *out, CPoint clicked)
{
	int a = 0;
	out->value = &a;
	out->clicked = clicked;
	out->min = { clicked.x - 1, clicked.y - 1 };
	out->max = { clicked.x + 1, clicked.y + 1 };
	out->input[0] = { clicked.x, clicked.y - 1 };
	out->input[1] = { clicked.x - 1, clicked.y };
	out->input[2] = { clicked.x + 1, clicked.y };
	out->input[3] = { clicked.x, clicked.y + 1 };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			pif[out->min.x + i][out->min.y + j].usingpoint = TRUE;
	for (int i = 0; i < 4; i++) {
		pif[out->input[i].x][out->input[i].y].lineok = TRUE;
		pif[out->input[i].x][out->input[i].y].value = pif[clicked.x][clicked.y].value;
	}
}

void LogicSimulator::create_and(AndGate *and, CPoint clicked)
{
	int a = 0;
	and->value = &a;
	and->clicked = clicked; // ���콺�� ���� ��ġ.
	and->min = { clicked.x -4, clicked.y - 2 }; // ��Ʈ���� ���� ����ϴ� left��ǥ
	and->output[0] = { clicked.x, clicked.y};//���� ������ �� �ִ� ��.
	and->input[0] = { clicked.x-4, clicked.y - 1 }; // ���� �޴� ��.
	and->input[1] = { clicked.x-4, clicked.y + 1 };
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			pif[and->min.x + i][and->min.y + j].usingpoint = TRUE; // �׷����� ������ ����� �ΰ��� pif�� ����.

		pif[and->output[0].x][and->output[0].y].lineok = TRUE; // �� �������� ���� �׷��� �� �ֵ�����. 
		//pif[and->output[0].x][and->output[0].y].value = pif[clicked.x][clicked.y].value; // pif�� ���� 

		pif[and->input[0].x][and->input[0].y].lineok = TRUE; // �� �������� ���� �׷��� �� �ֵ�����.

		pif[and->input[1].x][and->input[1].y].lineok = TRUE; // �� �������� ���� �׷��� �� �ֵ�����. 
}

void LogicSimulator::SavePointOnTheLine(CPoint old_start, CPoint old_end, WhereFixed old_wherefixed) { // �׷��� ���� ���� ���� �����Ѵ�.

	CPoint tempP;

	if (old_start == old_end)
		return;

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1�ٸ� �׸��°��.
			 line.Add( GetTwoPt(old_start, old_end));
			 pif[old_start.x/10][old_start.y/10].lineok = TRUE;
			 pif[old_end.x/10][old_end.y/10].lineok = TRUE;
		}

		else {//������ �׷���� �ϴ� ���.
			tempP.x = old_end.x;
			tempP.y = old_start.y;
			 line.Add( GetTwoPt(old_start, tempP));
			 pif[old_start.x / 10][old_start.y / 10].lineok = TRUE;
			 pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;

			tempP.x = old_end.x;
			tempP.y = old_start.y;
			 line.Add( GetTwoPt(tempP, old_end));
			 pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;
			 pif[old_end.x / 10][old_end.y / 10].lineok = TRUE;
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1�ٸ� �׸��°��.
			 line.Add( GetTwoPt(old_start, old_end));
			 pif[old_start.x / 10][old_start.y / 10].lineok = TRUE;
			 pif[old_end.x / 10][old_end.y / 10].lineok = TRUE;
		}
		else {//������ �׷���� �ϴ� ���.
			tempP.x = old_start.x;
			tempP.y = old_end.y;
			 line.Add( GetTwoPt(old_start, tempP));
			 pif[old_start.x / 10][old_start.y / 10].lineok = TRUE;
			 pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;

			tempP.x = old_start.x;
			tempP.y = old_end.y;
			 line.Add( GetTwoPt(tempP, old_end));
			 pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;
			 pif[old_end.x / 10][old_end.y / 10].lineok = TRUE;
		}
	}
}


