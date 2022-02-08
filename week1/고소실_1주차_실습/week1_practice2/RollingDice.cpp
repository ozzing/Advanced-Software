#include "pch.h"
#include "tipsware.h"
#include "time.h"
#define _USE_MATH_DEFINES
#include "math.h"

NOT_USE_MESSAGE

#define MAX_TRY 100

int main()
{
	//srand(time(NULL));

	SelectPenObject(RGB(0, 0, 0));

	int hit = 0;
	int miss = 0;
	float relProb = 5.0 / 36.0;
	float prob = 0;
	int flag = 0;
	// TODO 
	for (int i = 0; i < MAX_TRY; i++) {
		int x = rand() % 6 + 1;
		int y = rand() % 6 + 1;
		if (x + y == 8) {
			hit++;
			flag = 1;
		}
		else {
			miss++;
			flag = 0;
		}
		if (flag == 1) {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d (hit!)", 0 + i, x, y);
		}
		else {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d", 0 + i, x, y);
		}
	}
	//
	prob = (double)hit / MAX_TRY;

	SetTextColor(RGB(128, 0, 0));
	// 실제 주사위 값
	TextOut(0, 420, "실제 값: %.6f", relProb);
	// 계산된 값
	TextOut(0, 440, "계산된 값: %.6f", prob);

	ShowDisplay();

	return 0;
}
