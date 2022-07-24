#include <ncurses.h>

#include "newtest.h"
#include "housing/home.h"

int main(int argc, char **argv)
{
	initscr();

	start_color();
	use_default_colors();

	init_pair(1, COLOR_GREEN, COLOR_RED);
	attron(COLOR_PAIR(1));

	addstr("hi guys");

	wprintw(stdscr, "We bruh %d games: (y/n): ", COLORS);

	
	getch();

	endwin();

	return 0;
}
