#include <signal.h>

#include <ncurses.h>

#include "main.h"
#include "sleep.h"
#include "kid.h"

#define	KID_Y	5
#define	KID_X	5

int main(int argc, char **argv)
{
	initscr();

	signal(SIGWINCH, resizeHandler);

	start_color();
	use_default_colors();

	addstr("welcome sick kid");
	draw_kid(5, 5);
	refresh();
	islp(1);

	clear();

	noecho();
	nodelay(stdscr, TRUE);
	
	draw_kid(KID_Y, KID_X);

	for (;;)
	{
		update_kid_eyes(KID_Y, KID_X);
		move(2, 14);

		if (getch() == 'q')
			break;

		fslp();
	}

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
