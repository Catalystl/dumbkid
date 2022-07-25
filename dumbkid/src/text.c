#include <string.h>
#include <ncurses.h>

#include "text.h"

int text_wrap;

// Add characters of a message to the screen, character by character, returns nonzero if text starts/stops being printed
int update_text(int y, int x, char *msg, int *pos)
{
	// Add characters
	if (*pos < strlen(msg))
	{
		move(y + (*pos / text_wrap), x + (*pos % text_wrap));
		addch(msg[*pos]);
		(*pos)++;
	}
	else
		return 0;

	if (*pos == 1)
		return TALK_START;
	else if (*pos == strlen(msg))
		return TALK_STOP;
	else
		return 0;
}

// Redraw all characters drawn so far
void draw_text(int y, int x, char *msg, int pos)
{
	int npos;

	move(y, x);
	npos = 0;
	while (npos < pos)
	{
		addch(msg[npos++]);

		if (npos % text_wrap == 0)
			move(y + (npos / text_wrap), x);
	}
}
