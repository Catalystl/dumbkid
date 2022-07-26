#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>

#include <ncurses.h>

#include "util.h"
#include "convo.h"
#include "kid.h"
#include "gui.h"

// Returns a conversation number based on whether or not the type of conversation has been triggered before
#define	get_convo_num(event)	event ? randc() : event++

static struct {
	int talk : 1;
	int comp : 1;
	int fuck : 1;
	int atk : 1;
} event = {0, 0, 0, 0};

static int randc(void);

int main(int argc, char **argv)
{
	char c;

	// Init ncurses
	if (initscr() == NULL)
		perror("initscr");

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

	// Set random seed
	srand(time(NULL));

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

		// Controls
		switch (c = getch())
		{
			case 't':
				start_convo(CONVO_TALK, get_convo_num(event.talk));
				break;
			case 'c':
				start_convo(CONVO_COMP, get_convo_num(event.comp));
				break;
			case 'f':
				start_convo(CONVO_FUCK, get_convo_num(event.fuck));
				break;
			case 'a':
				start_convo(CONVO_ATK, get_convo_num(event.atk));
				break;
			case 'o':
				set_kid_mouth(KID_Y, KID_X, MOUTH_SHOCK);
				break;
			case 'n':
				set_kid_mouth(KID_Y, KID_X, MOUTH_NONE);
				break;
			case 'q':
				goto end_game_loop;
		}

		if (isupper(c))
			kid_eye = c;

		update_gui();
	}
	
	end_game_loop:
	endwin();

	return 0;
}

// Returns a valid random conversation number (1-7)
static int randc(void)
{
	return rand() % 7 + 1;
}
