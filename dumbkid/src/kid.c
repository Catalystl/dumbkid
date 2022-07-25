#include <ncurses.h>

#include "kid.h"

#define	EYE_TMR_RESET	3
#define	MOUTH_TMR_RESET	2


static const char *kid_data[] = {
"  ______",
" /     /",
"|     |",
"|     |",
"|     >",
"|",
"|     |",
"|  __ |",
"| \\  | \\",
"|__\\ |__\\"
};

static short mouth_state = MOUTH_NONE;
static short mouth_frame = 0;

static void update_kid_eyes(int, int);
static void update_kid_mouth(int, int);
static void draw_kid_static_mouth(int, int);

void draw_kid(int y, int x)
{
	int line;

	// Draw the kid line by line
	for (line = 0; line < sizeof(kid_data) / sizeof(kid_data[0]); ++line)
	{
		move(y + line, x);
		addstr(kid_data[line]);
	}

	draw_kid_static_mouth(y, x);
}

static void update_kid_eyes(int y, int x)
{
	static short eye_state = 0;
	if (++eye_state > 3)
		eye_state = 0;
	
	// Erase last eye, draw new eye
	switch (eye_state)
	{
		case 0:
			move(y + 2, x + 3);
			addstr(" o");
			break;
		case 1:
			move(y + 2, x + 4);
			addch(' ');
			move(y + 3, x + 4);
			addch('o');
			break;
		case 2:
			move(y + 3, x + 3);
			addstr("o ");
			break;
		case 3:
			move(y + 3, x + 3);
			addch(' ');
			move(y + 2, x + 3);
			addch('o');
			break;
	}
}

static void update_kid_mouth(int y, int x)
{
	mouth_frame = mouth_frame ? 0 : 1;

	switch (mouth_state)
	{
		case MOUTH_TALK:
			move(y + 5, x + 4);
			addstr(mouth_frame ? ")==" : "(__");
			break;
		case MOUTH_SHOCK:
			move(y + 5, x + 5);
			addch(mouth_frame ? '(' : '<');
			break;
	}
}

void update_kid(int y, int x)
{
	static short eye_tmr = 0, mouth_tmr = 0;

	// Update eyes
	if (--eye_tmr <= 0)
	{
		eye_tmr = EYE_TMR_RESET;
		update_kid_eyes(y, x);
	}

	// Update mouth
	if (--mouth_tmr <= 0)
	{
		mouth_tmr = MOUTH_TMR_RESET;
		update_kid_mouth(y, x);
	}
}

// Change mouth state and draw a static mouth (note: this should be called AFTER update_kid)
void set_kid_mouth(int y, int x, int state)
{
	mouth_state = state;
	draw_kid_static_mouth(y, x);
}

// Redraws non-animated mouths if the screen was previously cleared
static void draw_kid_static_mouth(int y, int x)
{
	move(y + 5, x + 4);
	switch (mouth_state)
	{
		case MOUTH_NORM:
			addstr("---");
			break;
		default:		
			addstr("   ");
	}
}
