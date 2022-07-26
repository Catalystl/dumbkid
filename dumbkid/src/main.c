#include <ctype.h>
#include <signal.h>
#include <ncurses.h>

#include "util.h"
#include "convo.h"
#include "gui.h"

int main(int argc, char **argv)
{
	// Init ncurses
	initscr();

	// Use terminal colors & define some color pairs with them
	start_color();
	use_default_colors();
	init_pair(1, COLOR_BLUE, -1);
	init_pair(2, COLOR_RED, -1);
	init_pair(3, COLOR_GREEN, -1);

	// Don't echo keys typed by user, don't queue key presses, and don't delay the program waiting for input
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);

	// Function to call on window resize
	struct sigaction sa;
	sa.sa_handler = resize_handler;
	sigaction(SIGWINCH, &sa, NULL);

	// Set text wrap and draw the gui for the first time
	reset_text_wrap();
	draw_gui();

	// Game loop
	for (;;)
	{
		fslp();

		// Don't progress through the game when the screen is too small
		if (screen.too_small)
			continue;

		update_gui();

		// Controls
		switch (tolower(getch()))
		{
			case 't':
				start_convo(CONVO_TALK, 0);
				break;
			case 'c':
				start_convo(CONVO_COMP, 0);
				break;
			case 'f':
				start_convo(CONVO_FUCK, 0);
				break;
			case 'q':
				goto end_game_loop;
		}

	}
	
	end_game_loop:
	endwin();

	return 0;
}
