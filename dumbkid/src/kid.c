#include <ncurses.h>

#include "kid.h"

#define	EYE_TMR_RESET	3

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

static short eye_state = 0;
static short eye_tmr = 0;

void draw_kid(int y, int x)
{
	int line;

	for (line = 0; line < sizeof(kid_data) / sizeof(kid_data[0]); ++line)
	{
		move(y + line, x);
		addstr(kid_data[line]);
	}
}

void update_kid_eyes(int y, int x)
{
	if (--eye_tmr <= 0)
		eye_tmr = EYE_TMR_RESET;
	else
		return;
	
	if (++eye_state > 3)
		eye_state = 0;
	
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

void update_kid_mouth(int y, int x, int expression)
{
	
}
