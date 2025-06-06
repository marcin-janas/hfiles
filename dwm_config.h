/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Maple Mono NF Light:pixelsize=24:antialias=true:autohint=true" };
static const char dmenufont[]       = "Maple Mono NF Light:pixelsize=24:antialias=true:autohint=true";
static const char col_gray1[]       = "#dcdcdc";
static const char col_gray2[]       = "#dcdcdc";
static const char col_gray3[]       = "#666666";
static const char col_gray4[]       = "#666666";
static const char col_cyan[]        = "#ececec";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "◫₁", "◨₂", "◧₃", "■₄" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "⋮ ≡",      tile },    /* first entry is default */
	{ "⋮ ≋",      NULL },    /* no layout function means floating behavior */
	{ "⋮ ≢",      monocle },
};

/* key definitions */
// #define MODKEY Mod1Mask
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", "-e", "tmux",  NULL };
static const char *webcmd[]  = { "flatpak", "run", "com.google.Chrome", "--force-device-scale-factor=1.4", "--device=hid", NULL };
static const char *slackcmd[]  = { "flatpak", "run", "com.slack.Slack", "--force-device-scale-factor=1.4", NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *past2cmd[]  = { "xdotool", "click", "2", NULL };
static const char *poffcmd[]  = { "sudo", "systemctl", "poweroff", NULL };

static Key keys[] = {
	/* modifier                     key                            function        argument */
	{ MODKEY,                       XK_r,                          spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_l,                          spawn,          {.v = slockcmd } },
	{ MODKEY,                       XK_v,                          spawn,          {.v = past2cmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_q,                          spawn,          {.v = poffcmd } },
	{ MODKEY,                       XK_t,                          spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,                          spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_e,                          spawn,          {.v = slackcmd } },
	{ MODKEY,                       XK_b,                          togglebar,      {0} },
	{ MODKEY,                       XK_j,                          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                          focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,                          incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,                          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                          setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                     zoom,           {0} },
	{ MODKEY,                       XK_Tab,                        view,           {0} },
	{ MODKEY,                       XK_c,                          killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,                          setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,                          setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,                          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                      togglefloating, {0} },
	{ MODKEY,                       XK_0,                          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                          tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                     tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_a,                                          0)
	TAGKEYS(                        XK_s,                                          1)
	TAGKEYS(                        XK_d,                                          2)
	TAGKEYS(                        XK_f,                                          3)
	{ MODKEY|ShiftMask,             XK_q,                          quit,           {0} },
    // brightness and audio 
    {0,                             XK_Print,                      spawn,          SHCMD("shotgun $(hacksaw -f '-i %i -g %g') - | xclip -t 'image/png' -selection clipboard")},
    {0,                             XF86XK_ModeLock,               spawn,          SHCMD("pamixer -t")},
    {0,                             XF86XK_AudioMute,              spawn,          SHCMD("pamixer -t")},
    {0,                             XF86XK_AudioMicMute,           spawn,          SHCMD("pamixer -t")},
    {0,                             XF86XK_AudioRaiseVolume,       spawn,          SHCMD("pamixer -i 1")},
    {0,                             XF86XK_AudioLowerVolume,       spawn,          SHCMD("pamixer -d 1")},
    {0,                             XF86XK_MonBrightnessDown,      spawn,          SHCMD("brightnessctl s 1%-")},
    {0,                             XF86XK_MonBrightnessUp,        spawn,          SHCMD("brightnessctl s +1%")},
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

