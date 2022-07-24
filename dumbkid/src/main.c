#include <signal.h>

#include <ncurses.h>

#include "main.h"
#include "sleep.h"
#include "housing/home.h"

int main(int argc, char **argv)
{
	initscr();

	signal(SIGWINCH, resizeHandler);

	start_color();
	use_default_colors();

	init_pair(1, COLOR_GREEN, COLOR_RED);
	attron(COLOR_PAIR(1));

	islp(1);

	refresh();

	islp(1);

	addstr("hi guys");
	refresh();

	getch();

	clear();
	refresh();

	islp(2);

	endwin();

	return 0;
}

void resizeHandler(int sig)
{
	endwin();
	refresh();

	clear();
	wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
	refresh();
}
