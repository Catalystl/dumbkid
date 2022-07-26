#include <ncurses.h>

#include "text.h"
#include "kid.h"
#include "convo.h"
#include "gui.h"

struct screenstate screen = {.too_small = 0};

void draw_gui(void)
{
	int mx;

	mx = getmaxx(stdscr);
	draw_kid(KID_Y, KID_X);

	// Draw approach msg
	attron(COLOR_PAIR(3));
	move(0, 0);
	addstr(APPROACH_MSG);
	attroff(COLOR_PAIR(3));

	// Draw Names
	attron(COLOR_PAIR(2));
	move(CONVO_Y, CONVO_X);
	addstr("You:");
	move(CONVO_Y + 2, CONVO_X);
	addstr("Kid:");
	attroff(COLOR_PAIR(2));

	// Draw player's message
	draw_pmsg();

	// Draw kid's message
	draw_text(CONVO_Y + 2, CONVO_X + NAME_MSG_SPACING, kmsg, kmsgpos);

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

void update_gui(void)
{
	update_kid(KID_Y, KID_X);
	switch (update_text(CONVO_Y + 2, CONVO_X + NAME_MSG_SPACING, kmsg, &kmsgpos))
	{
		case TALK_START:
			set_kid_mouth(KID_Y, KID_X, MOUTH_TALK);
			break;
		case TALK_STOP:
			set_kid_mouth(KID_Y, KID_X, MOUTH_NORM);
			break;
	}
	move(CONVO_Y + 2 + (kmsgpos / text_wrap), CONVO_X + NAME_MSG_SPACING + (kmsgpos % text_wrap));
}

void draw_pmsg(void)
{
	move(CONVO_Y, CONVO_X + NAME_MSG_SPACING);
	addstr(pmsg);
}

void clear_convo(void)
{
	int linechars, chars, lines;
	
	linechars = getmaxx(stdscr) - (CONVO_X + NAME_MSG_SPACING);

	// Clearing player msg
	move(CONVO_Y, CONVO_X + NAME_MSG_SPACING);
	for (chars = 0; chars < linechars; ++chars)
		addch(' ');
	
	// Clearing kid msg
	for (lines = 0; lines <= kmsgpos / text_wrap; ++lines)
	{
		move(CONVO_Y + 2 + lines, CONVO_X + NAME_MSG_SPACING);
		for (chars = 0; chars < linechars; ++chars)
			addch(' ');
	}
}

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

void reset_text_wrap(void)
{
	text_wrap = getmaxx(stdscr) - (CONVO_X + NAME_MSG_SPACING);
}

void resize_handler(int sig)
{
	int my, mx;

	endwin();
	refresh();

	getmaxyx(stdscr, my, mx);
	if (mx < MIN_SCREEN_W || my < MIN_SCREEN_H)
	{
		clear();
		move(0, 0);
		addstr(SCREEN_TOO_SMALL_MSG);
		refresh();

		screen.too_small = 1;
		return;
	}
	else
		screen.too_small = 0;

	reset_text_wrap();
	clear();
	draw_gui();
	refresh();
}
