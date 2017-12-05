/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char col_gray1[]       = "#dcdcdc";
static const char col_gray2[]       = "#dcdcdc";
static const char col_gray3[]       = "#666666";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#ececec";
//static const char *colors[SchemeLast][3]      = {
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel] =  { col_gray3, col_cyan,  col_cyan  },
};

static const char *fonts[] = { "xos4 Terminus:pixelsize=18:antialias=false:autohint=false", };
static const char dmenufont[] = "xos4 Terminus:pixelsize=18:antialias=false:autohint=false";

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            True,        -1 },
    { "Firefox",  NULL,       NULL,       1 << 1,            False,       -1 },
    { "st",       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* first entry is default */
    { "[F]",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MOD4 Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "st", "-e", "tmux",  NULL };
static const char *browsercmd[]  = { "firefox", NULL };
// static const char *rangercmd[]  = { "st", "-e", "ranger", NULL };
// static const char *qemucmd[]  = { "xinit", ".xqemurc", "--", ":1", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *xkillcmd[]  = { "xkill", NULL };
static const char *past2cmd[]  = { "xdotool", "click", "2", NULL };
static const char *clipmenucmd[]  = { "clipmenu", NULL };
static const char *gtrcmd[]  = { "gtr.sh", NULL };
static const char *monitorlcmd[]  = { "xdotool", "mousemove", "960", "600", NULL };
static const char *monitorrcmd[]  = { "xdotool", "mousemove", "2880", "600", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MOD4,                         XK_1,      spawn,          {.v = termcmd } },
    { MOD4,                         XK_2,      spawn,          {.v = browsercmd } },
    { MOD4,                         XK_r,      spawn,          {.v = dmenucmd } },
    { MOD4,                         XK_l,      spawn,          {.v = slockcmd } },
    { MOD4,                         XK_x,      spawn,          {.v = xkillcmd } },
    { MOD4,                         XK_v,      spawn,          {.v = past2cmd } },
    { MOD4,                         XK_t,      spawn,          {.v = gtrcmd } },
    { MOD4|ShiftMask,               XK_v,      spawn,          {.v = clipmenucmd } },
    { MOD4|ShiftMask,               XK_h,      spawn,          {.v = monitorlcmd } },
    { MOD4|ShiftMask,               XK_l,      spawn,          {.v = monitorrcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MOD4,                         XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    { MOD4|ShiftMask,               XK_q,      quit,           {0} },
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

