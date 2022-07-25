#include <ncurses.h>

#include "util.h"

void draw_box(int lines, int cols)
{
	int y, x;

	getyx(stdscr, y, x);
	addch(ACS_ULCORNER);
	move(y, x + cols - 1);
	addch(ACS_URCORNER);
	move(y + lines - 1, x);
	addch(ACS_LLCORNER);
	move(y + lines - 1, x + cols - 1);
	addch(ACS_LRCORNER);
	move(y, x + 1);
	hline(ACS_HLINE, cols - 2);
	move(y + 1, x);
	vline(ACS_VLINE, lines - 2);
	move(y + lines - 1, x + 1);
	hline(ACS_HLINE, cols - 2);
	move(y + 1, x + cols - 1);
	vline(ACS_VLINE, lines - 2);
}
