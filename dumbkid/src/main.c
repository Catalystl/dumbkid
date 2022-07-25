#include <ctype.h>
#include <signal.h>
#include <ncurses.h>

#include "util.h"
#include "sleep.h"
#include "kid.h"
#include "text.h"

#define SCREEN_TOO_SMALL_MSG	"The screen is too small to play this game."
#define MIN_SCREEN_X		50
#define MIN_SCREEN_Y		18
#define	KID_Y			1
#define	KID_X			4
#define TEXT_Y			15
#define TEXT_X 			16
#define CONTROLS_BOX_W		24
#define CONTROLS_BOX_H		9

#define reset_text_wrap()	text_wrap = getmaxx(stdscr) - TEXT_X

static char *urmsg = "Fuck you kid!";
static char *msg = "Fuck you bitch!";
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
	int my, mx;

	getmaxyx(stdscr, my, mx);

	draw_kid(KID_Y, KID_X);
	draw_text(TEXT_Y, TEXT_X, msg, msgpos);

	// Draw approach text
	attron(COLOR_PAIR(3));
	move(0, 0);
	addstr("A sick kid approaches... bruh!");
	attroff(COLOR_PAIR(3));

	// Draw Names
	attron(COLOR_PAIR(2));
	move(13, 4);
	addstr("You:");
	move(15, 4);
	addstr("Kid:");
	attroff(COLOR_PAIR(2));

	// Draw player's message
	move(13, 16);
	addstr(urmsg);

	// Draw controls box
	attron(COLOR_PAIR(1));
	move(1, mx - CONTROLS_BOX_W - 2);
	draw_box(CONTROLS_BOX_H, CONTROLS_BOX_W);
	attroff(COLOR_PAIR(1));

	move(2, mx - CONTROLS_BOX_W);
	addstr("CONTROLS:");
	move(4, mx - CONTROLS_BOX_W);
	addstr("T ... Talk");
	move(5, mx - CONTROLS_BOX_W);
	addstr("C ... Compliment");
	move(6, mx - CONTROLS_BOX_W);
	addstr("F ... Say Fuck You");
	move(7, mx - CONTROLS_BOX_W);
	addstr("A ... Attack");
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
