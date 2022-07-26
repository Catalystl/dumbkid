#include "convo.h"
#include "gui.h"

struct convo {
	char *p;
	char *k;
};
static const struct convo convo_data[3][1] = {
	{
		{
			.p="How's it going?",
			.k="Pretty good Sam."
		}
	},
	{
		{
			.p="You lookin' pretty fly today.",
			.k="Thanks!"
		}
	},
	{
		{
			.p="Fuck you kid!",
			.k="Fuck you bitch! I have more money than you will ever own, kid! Get fucked!"
		}
	}
};
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
