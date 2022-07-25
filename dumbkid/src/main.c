#include <ctype.h>
#include <signal.h>
#include <ncurses.h>

#include "sleep.h"
#include "kid.h"
#include "text.h"

#define SCREEN_TOO_SMALL_MSG	"The screen is too small to play this game."
#define MIN_SCREEN_X		50
#define MIN_SCREEN_Y		16
#define	KID_Y			1
#define	KID_X			4
#define TEXT_Y			16
#define TEXT_X 			16

#define reset_text_wrap()	text_wrap = getmaxx(stdscr) - TEXT_X

static char *msg = "Fuck you kid! I eat cereal like cereal man these days (unfortunately he was rain down on by soup missile) but that means I am still better than you bro!";
static int msgpos = 0;

// Program status struct
struct {
	int screen_too_small : 1;
} progstat = {.screen_too_small = 0};

static void resize_handler(int);
static void draw_gui(void);
static void update_gui(void);

int main(int argc, char **argv)
{
	// Init ncurses
	initscr();

	// Use terminal colors
	start_color();
	use_default_colors();

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

	for (;;)
	{
		fslp();

		if (progstat.screen_too_small)
			continue;

		update_gui();

		switch (tolower(getch()))
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

	}
	
	end_game_loop:

	endwin();

	return 0;
}

static void resize_handler(int sig)
{
	int my, mx;

	endwin();
	refresh();

	getmaxyx(stdscr, my, mx);
	if (mx < MIN_SCREEN_X || my < MIN_SCREEN_Y)
	{
		clear();
		move(0, 0);
		addstr(SCREEN_TOO_SMALL_MSG);
		refresh();

		progstat.screen_too_small = 1;
		return;
	}
	else
		progstat.screen_too_small = 0;

	reset_text_wrap();
	clear();
	draw_gui();
	refresh();
}

static void draw_gui(void)
{
	draw_kid(KID_Y, KID_X);
	draw_text(TEXT_Y, TEXT_X, msg, msgpos);
}

static void update_gui(void)
{
	update_kid(KID_Y, KID_X);
	
	switch (update_text(TEXT_Y, TEXT_X, msg, &msgpos))
	{
		case TALK_START:
			set_kid_mouth(KID_Y, KID_X, MOUTH_TALK);
			break;
		case TALK_STOP:
			set_kid_mouth(KID_Y, KID_X, MOUTH_NORM);
			break;
	}
	move(TEXT_Y + (msgpos / text_wrap), TEXT_X + (msgpos % text_wrap));
}
