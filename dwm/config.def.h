/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"Source Code Pro:medium:size=10"
};
static const char dmenufont[]       = "iosevka:size=10";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#3C3F41";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#67b1ae";
static const char selbgcolor[]      = "#555555";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "base", "net", "media", "code" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "pycharm",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Skype",    NULL,       NULL,       1 << 2,       1,           -1 },
	{ "Atom",     NULL,       NULL,       1 << 3,       0,           -1 },
	{  NULL,      NULL,       "scratchpad",     0,      1,           -1 },
	{  NULL,      NULL,	 	 		"tmux",	  	0,	    			1,		 	 		 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const unsigned int gappx = 3; /* gap pixel between windows */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
 	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *lockcmd[]  = { "i3lock-fancy", NULL };
static const char *webcmd[]  = { "firefox", NULL};
static const char *thunarcmd[]  = { "thunar", NULL };
static const char *rebootcmd[] = { "systemctl", "reboot", NULL };
static const char *shutcmd[] = { "systemctl", "poweroff", NULL };
static const char *suspcmd[] = { "systemctl", "suspend", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "1%+", NULL };
static const char *voldwncmd[] = { "amixer", "-q", "set", "Master", "1%-",  NULL };
static const char *mpctoggle[] = { "mpc", "toggle", NULL };
static const char *mpcprev[] = { "mpc", "prev", NULL };
static const char *mpcnext[] = { "mpc", "next", NULL };
static const char *mpcstop[] = { "mpc", "stop", NULL };
static const char *padcmd[] = { "urxvtc", "-title", "scratchpad", "-geometry", "56x10-30+40", NULL };
static const char *tmuxcmd[] = { "urxvtc", "-geometry", "123x42-790+40","-title", "tmux", "-e", "tmux", "new", "-A", "-s", "local", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { ControlMask|Mod1Mask,         XK_r,      spawn,          {.v = rebootcmd } },
	{ ControlMask|Mod1Mask,         XK_q,      spawn,          {.v = shutcmd } },
	{ ControlMask|Mod1Mask,         XK_l,      spawn,          {.v = lockcmd } },
    { ControlMask|Mod1Mask,         XK_s,      spawn,          {.v = suspcmd } },
	{ ControlMask|Mod1Mask,			XK_Up,	   spawn,		   {.v = mpctoggle} },
	{ ControlMask|Mod1Mask,			XK_Down,   spawn,		   {.v = mpcstop} },
	{ ControlMask|Mod1Mask,			XK_Right,  spawn,		   {.v = mpcnext} },
	{ ControlMask|Mod1Mask,			XK_Left,   spawn,		   {.v = mpcprev} },
	{ Mod1Mask,                     XK_Up,     spawn,          {.v = volupcmd} },
	{ Mod1Mask,                     XK_Down,   spawn,          {.v = voldwncmd} },
	{ MODKEY,                       XK_q,      spawn,          {.v = webcmd} },
	{ MODKEY,                       XK_e,      spawn,          {.v = thunarcmd} },
	{ ControlMask|Mod1Mask,         XK_p,      spawn,          {.v = padcmd } },
	{ ControlMask|Mod1Mask,		    XK_u,	   spawn,	       {.v = tmuxcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,   cycle,          {.i = -1 } },
	{ MODKEY,                       XK_Right,  cycle,          {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   tagcycle,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,  tagcycle,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
