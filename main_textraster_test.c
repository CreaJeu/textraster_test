
#include "curses.h"
#include <stdlib.h>

#include "textRaster.h"

void initCurses()
{
#ifdef XCURSES
    Xinitscr(argc, argv);//??
#else
    initscr();
#endif
//    nl();
    noecho();
    curs_set(0);
    timeout(-1);// for getch(), or breakpoint at the end
    keypad(stdscr, TRUE);
}

int endCurses()
{
    getch();// or breakpoint at the end without timeout(-1)
	curs_set(1);
	endwin();
	return EXIT_SUCCESS;
}

wchar_t shade(float s)
{
	//arbitrary palette with 30 shades (unicode characters)
	static wchar_t* shades = L"      ░░░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓███";
	//convert [O..1] to [0..29]
	int i = ((int)(s*299)) / 10;
	return shades[i];
}

void drawLine(float yStart, float xStart, float yEnd, float xEnd)
{
	struct LineDrawer d;
	lineDrawerStart(&d, yStart, xStart, yEnd, xEnd);
	while(!lineDrawerHasFinished(&d))
	{
		mvaddch(d._currY, d._currX, shade(d._currDist));
		mvaddch(d._currYbis, d._currXbis, shade(d._currDistBis));
		lineDrawerNext(&d);
	}
}

int main()
{
	initCurses();

	drawLine(16.8, 45, 3.5, 45);

	drawLine(17.5, 50.2, 3.3, 56);
	drawLine(20.1, 54, 15, 97);

	drawLine(23, 54, 23, 97);

	drawLine(29, 54, 32, 97);
	drawLine(32, 49, 45, 54);

	drawLine(33, 45, 45, 45);

	drawLine(32, 42, 45, 37);
	drawLine(29, 38, 31, 3);

	drawLine(23, 37, 23, 2);

	drawLine(20, 38, 17, 3);
	drawLine(17, 42, 3, 37);

    refresh();

	return endCurses();
}

