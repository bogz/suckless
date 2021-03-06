/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=7",
					"Font Awesome 5 Free Regular-8",
					"Font Awesome 5 Free Solid-8"
};
static const char dmenufont[]       = "Cascadia Code:size=7";
static const char col_black[]	    = "#282828";
static const char col_red[]	    = "#cc241d";
static const char col_green[]	    = "#98971a";
static const char col_yellow[]	    = "#d79921";
static const char col_blue[]	    = "#458588";
static const char col_cyan[]	    = "#689d6a";
static const char col_purle[]	    = "#b16286";
static const char col_white[]	    = "#ebdbb2";
static const char col_gray1[]	    = "#a89984";
static const char col_gray2[]	    = "#928374";

static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_gray1, col_black, col_black },
        [SchemeSel]  = { col_white, col_black, col_black  },
};

/* tagging */
static const char *tags[] = { "base", "net", "term", "code"};

static const Rule rules[] = {
        /* xprop(1):
         *	WM_CLASS(STRING) = instance, class
         *	WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            0,           -1 },
        { "surf",     NULL,       NULL,       1 << 1,       0,           -1 },
	{ "st",       NULL,       NULL,       1 << 2,       0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
        { "pycharm",  NULL,       NULL,       1 << 3,       0,           -1 },
        { "clion",    NULL,       NULL,       1 << 3,       0,           -1 },
        { "Skype",    NULL,       NULL,       1 << 0,       1,           -1 },
        { "subl4",    NULL,       NULL,       1 << 3,       0,           -1 },
        { "mplayer",  NULL,       NULL,       1 << 0,       0,           -1 },
        { "Atom",     NULL,       NULL,       1 << 3,       0,           -1 },
	{ NULL,       NULL,      "scratchpad",     0,       1,           -1 },
        { NULL,       NULL,      "tmux",           0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_black, "-sf", col_blue, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[]  = { "slock", NULL };
static const char *webcmd[]  = { "firefox-nightly", NULL};
static const char *fmanagercmd[]  = { "nemo", NULL };
static const char *rebootcmd[] = { "systemctl", "reboot", NULL };
static const char *shutcmd[] = { "systemctl", "poweroff", NULL };
static const char *suspcmd[] = { "systemctl", "suspend", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "1%+", NULL };
static const char *voldwncmd[] = { "amixer", "-q", "set", "Master", "1%-",  NULL };
static const char *mpctoggle[] = { "mpc", "toggle", NULL };
static const char *mpcprev[] = { "mpc", "prev", NULL };
static const char *mpcnext[] = { "mpc", "next", NULL };
static const char *mpcstop[] = { "mpc", "stop", NULL };
static const char *padcmd[] = { "st", "-t", "scratchpad", "-g", "66x10-30+40", NULL };
static const char *tmuxcmd[] = { "st", "-g", "123x42-790+40", "-t", "tmux", "tmux",  "new", "-A", "-s", "local", NULL};
static const char *turfcmd[] = { "tabbed", "-c", "surf", "-e", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ ControlMask|Mod1Mask,         XK_r,      spawn,          {.v = rebootcmd } },
	{ ControlMask|Mod1Mask,         XK_q,      spawn,          {.v = shutcmd } },
	{ ControlMask|Mod1Mask,         XK_l,      spawn,          {.v = lockcmd } },
	{ ControlMask|Mod1Mask,         XK_s,      spawn,          {.v = suspcmd } },
	{ ControlMask|Mod1Mask,		XK_Up,	   spawn,	   {.v = mpctoggle} },
	{ ControlMask|Mod1Mask,		XK_Down,   spawn,	   {.v = mpcstop} },
	{ ControlMask|Mod1Mask,		XK_Right,  spawn,	   {.v = mpcnext} },
	{ ControlMask|Mod1Mask,		XK_Left,   spawn,	   {.v = mpcprev} },
	{ Mod1Mask,                     XK_Up,     spawn,          {.v = volupcmd} },
	{ Mod1Mask,                     XK_Down,   spawn,          {.v = voldwncmd} },
	{ MODKEY,                       XK_q,      spawn,          {.v = webcmd} },
	{ MODKEY,			XK_w,	   spawn,	   {.v = turfcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = fmanagercmd} },
	{ ControlMask|Mod1Mask,         XK_p,      spawn,          {.v = padcmd } },
	{ ControlMask|Mod1Mask,		XK_u,	   spawn,	   {.v = tmuxcmd } },
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
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
