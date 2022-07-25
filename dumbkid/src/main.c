#include <signal.h>

#include <ncurses.h>

#include "main.h"
#include "sleep.h"
#include "kid.h"

#define	KID_Y	1
#define	KID_X	4

int main(int argc, char **argv)
{
	initscr();
	start_color();
	use_default_colors();
	noecho();
	nodelay(stdscr, TRUE);
	signal(SIGWINCH, resizeHandler);

	char *msg = "Fuck you kid!";
	
	draw_gui();
	for (;;)
	{
		update_gui();

		switch (getch())
		{
			case 'x':
				set_kid_mouth(KID_Y, KID_X, MOUTH_NONE);
				break;
			case 'n':
				set_kid_mouth(KID_Y, KID_X, MOUTH_NORM);
				break;
			case 't':
				set_kid_mouth(KID_Y, KID_X, MOUTH_TALK);
				break;
			case 'o':
				set_kid_mouth(KID_Y, KID_X, MOUTH_SHOCK);
				break;
			case 'q':
				goto end_game_loop;
		}

		fslp();
	}
	
	end_game_loop:

	endwin();

	return 0;
}

void resizeHandler(int sig)
{
	endwin();
	refresh();

	clear();
	draw_gui();
	refresh();
}

void draw_gui(void)
{
	draw_kid(KID_Y, KID_X);
}

void update_gui(void)
{
	update_kid(KID_Y, KID_X);
	move(2, 14);
}
