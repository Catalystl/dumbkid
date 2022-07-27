#define SCREEN_TOO_SMALL_MSG	"The screen is too small to play this game."
#define	APPROACH_MSG		"A sick kid approaches... bruh!"
#define MIN_SCREEN_W		50
#define MIN_SCREEN_H		22
#define	KID_Y			1
#define	KID_X			4
#define CONVO_Y			13
#define CONVO_X 		4	
#define NAME_MSG_SPACING	11
#define CONTROLS_BOX_W		24
#define CONTROLS_BOX_H		9
struct screenstate {
	int too_small : 1;
};
extern struct screenstate screen;
void draw_gui(void);
void update_gui(void);
void draw_pmsg(void);
void clear_convo(void);
void draw_box(int, int);
void reset_text_wrap(void);
void resize_gui(void);
