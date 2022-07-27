#define CONVO_TALK	0
#define CONVO_COMP	1
#define CONVO_FUCK	2
#define	CONVO_ATK	3
extern char *pmsg;
extern char *kmsg;
extern int kmsgpos;
void start_convo(int, int);
struct convo {
	char *p;
	char *k;
};
static const struct convo convo_data[4][8] = {
	{
		{
			.p="How's it going?",
			.k="Pretty good Sam."
		},
		{
			.p="How's the weather today lad?",
			.k="Non-existent as usual."
		},
		{
			.p="Smells good today right",
			.k="Yeh."
		},
		{
			.p="You come by here often?",
			.k="Yes."
		},
		{
			.p="Hi.",
			.k="Hi."
		},
		{
			.p="You good?",
			.k="Yes."
		},
		{
			.p="How's life?",
			.k="Good."
		},
		{
			.p="Hello.",
			.k="Hi."
		}
	},
	{
		{
			.p="You lookin' pretty fly today.",
			.k="Thanks!"
		},
		{
			.p="You um... are good.",
			.k="Wow!"
		},
		{
			.p="Nice outfit.",
			.k="Thanks."
		},
		{
			.p="You're a good guy you know that right?",
			.k="Yes."
		},
		{
			.p="You have a nicely shaped skull.",
			.k="Thanks.   ...what?"
		},
		{
			.p="Did you get a haircut recently?",
			.k="Yes. Thanks for noticing."
		},
		{
			.p="You're a good fellow around these parts.",
			.k="Yes."
		},
		{
			.p="You good.",
			.k="Yeah."
		}
	},
	{
		{
			.p="Fuck you kid!",
			.k="Fuck you bitch! I have more money than you will ever own, kid! Get fucked!"
		},
		{
			.p="You! Fuck You!",
			.k="I'll kill you!"
		},
		{
			.p="You smell bad man!",
			.k="Fuck you you smell like shit as well!"
		},
		{
			.p="You suck !",
			.k="No! Shut up! Stop it! No!"
		},
		{
			.p="You have low iq, man!",
			.k="Fuck you man! Not true man!"
		},
		{
			.p="Fuck... You! Fuck You Dude!",
			.k="No! No!"
		},
		{
			.p="I'll kick you're shin!",
			.k="I'll bonk your head!"
		},
		{
			.p="I do not like you man!",
			.k="No!!!"
		}
	},
	{
		{
			.p="*brandishes sword*",
			.k="Bruh! You think you can kill me with that? Lmao! *whips out gun*"
		},
		{
			.p="*shoots missile*",
			.k="*teleports behind you* nothing personnel kid."
		},
		{
			.p="*parkours around kid waving knife around*",
			.k="What? Bruh how are you so fast!!!"
		},
		{
			.p="*quickly swipes swords many times*",
			.k="*metal clinking sounds as swords are blocked*"
		},
		{
			.p="*kicks kid's shin*",
			.k="Ow."
		},
		{
			.p="No!",
			.k="Punche's you're left elbow"
		},
		{
			.p="Ow!",
			.k="*sets off a trap that causes a wood block to fall on stuffed elmo that knocks him into fire which causes smoke alarms to be set off which causes a thingy to launch a fork at you*"
		},
		{
			.p="No! Stop it!",
			.k="*shoot's gun, missing every shot*"
		}
	}
};
