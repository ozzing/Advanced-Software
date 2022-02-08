#include "pch.h"
#include "tipsware.h"
#include <random>


NOT_USE_MESSAGE

#define MAX_POINTS 10000
#define RADIUS 10
#define POINTS_RADIUS 3

#define GRAPH_WIDTH   600
#define GRAPH_HEIGHT  600

#define CENTER_X      (GRAPH_WIDTH/2)
#define CENTER_Y      (GRAPH_HEIGHT/2)

#define ZOOM_LEVEL    10

using namespace std;

inline void MyMoveTo(int a_x, int a_y)
{
	MoveTo(a_x * ZOOM_LEVEL + CENTER_X, -(a_y * ZOOM_LEVEL - CENTER_Y));
}

inline void MyLineTo(int a_x, int a_y)
{
	LineTo(a_x * ZOOM_LEVEL + CENTER_X, -(a_y * ZOOM_LEVEL - CENTER_Y));
}


void DrawBackgroundOfGraph()
{
	Rectangle(0, 0, GRAPH_WIDTH, GRAPH_HEIGHT, RGB(232, 248, 248), RGB(87, 101, 126));

	Line(CENTER_X, 0, CENTER_X, GRAPH_HEIGHT, RGB(232, 248, 248));
	for (int i = 0; i < GRAPH_HEIGHT / ZOOM_LEVEL; i++) {
		Line(CENTER_X - 2, i * ZOOM_LEVEL, CENTER_X + 3, i * ZOOM_LEVEL, RGB(182, 198, 198));
	}
	Line(0, CENTER_Y, GRAPH_WIDTH, CENTER_Y, RGB(232, 248, 248));
	for (int i = 0; i < GRAPH_WIDTH / ZOOM_LEVEL; i++) {
		Line(i * ZOOM_LEVEL, CENTER_Y - 2, i * ZOOM_LEVEL, CENTER_Y + 3, RGB(182, 198, 198));
	}

	SelectFontObject("굴림", 20, 1);
	SetTextColor(RGB(255, 255, 255));
	TextOut(560, 310, "x축");
	TextOut(310, 5, "y축");
}

int main()
{
	srand(time(NULL));
	DrawBackgroundOfGraph();

	SelectPenObject(RGB(0, 0, 0));

	MyMoveTo(RADIUS, RADIUS);
	MyLineTo(RADIUS, -RADIUS);
	MyMoveTo(-RADIUS, RADIUS);
	MyLineTo(-RADIUS, -RADIUS);
	MyMoveTo(-RADIUS, -RADIUS);
	MyLineTo(RADIUS, -RADIUS);
	MyMoveTo(RADIUS, RADIUS);
	MyLineTo(-RADIUS, RADIUS);

	double calPi = 0;
	double count = 0;
	//TODO
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<> random(- RADIUS * ZOOM_LEVEL, RADIUS * ZOOM_LEVEL);

	double x[MAX_POINTS] = { 0, };
	double y[MAX_POINTS] = { 0, };
	for (int i = 0; i < MAX_POINTS; i++) {	
		x[i] = random(mt);
		y[i] = random(mt);
	}
	for (int i = 0; i < MAX_POINTS; i++) {
		if (pow(x[i], 2) + pow(y[i], 2) <= pow(RADIUS * ZOOM_LEVEL, 2)) {
			count++;
			Ellipse(CENTER_X + x[i], CENTER_Y + y[i], CENTER_X + x[i] + POINTS_RADIUS, CENTER_Y + y[i] + POINTS_RADIUS, RGB(255, 0, 0), RGB(255, 0, 0));
		}
		else
			Ellipse(CENTER_X + x[i], CENTER_Y + y[i], CENTER_X + x[i] + POINTS_RADIUS, CENTER_Y + y[i] + POINTS_RADIUS, RGB(255, 255, 0), RGB(255, 255, 0));
	}
	//
	calPi = (double)count / MAX_POINTS * 4;
	TextOut(20, 20, "계산된 pi 값: %lf", calPi);
	TextOut(20, 40, "실제 pi 값: %f", M_PI);
	TextOut(20, 60, "오차율: %.2lf%c", fabs(((calPi / M_PI)-1.0)*100.0), 37);

	ShowDisplay();
	return 0;
}