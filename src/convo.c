#include "convo.h"
#include "gui.h"

char *pmsg = "Hi.";
char *kmsg = "Hi.";
int kmsgpos = 0;

void start_convo(int type, int num)
{
	clear_convo();
	kmsgpos = 0;
	kmsg = convo_data[type][num].k;
	pmsg = convo_data[type][num].p;
	draw_pmsg();
}
