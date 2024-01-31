/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char norm_fg[]           = "#447a6c";
static const char norm_bg[]           = "#1b1d1b";
static const char sel_fg[]            = "#1b1d1b";
static const char sel_bg[]            = "#7d4b23";
static const char norm_border[]       = "#c0ffee";
static const char sel_border[]        = "#bada55";
static const unsigned int baralpha    = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_fg },
	[SchemeSel]  = { sel_fg,  sel_bg,  sel_bg  },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
  	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title   tags mask     isfloating   monitor */
	{ "Gimp",       NULL,       NULL,         0,            1,         -1 },
	{ "dropdown",   NULL,       NULL,        ~0,            1,         -1 },
	{ "matplotlib", NULL,       NULL,    1 << 1,            1,         -1 },
	{ "discord",    NULL,       NULL,    1 << 7,            0,         -1 },
	{ "Cider",      NULL,       NULL,    1 << 8,            0,         -1 },
	{ NULL,NULL,"Picture-in-Picture",        ~0,            1,         -1 },
	// { "Firefox",    NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int mainmon = 0; /* xsetroot will only change the bar on this monitor */


/* Devide dependent configurations */
#ifdef _HOST_BATTLESTATION
  // Main desktop uses a 4k monitor (good to have a bigger font)
  static const char *fonts[] = { "monospace:size=16" };
  /* LayoutPerMonitor:       4k->tile, ultrawide->tilewide */
  static const int lpm[] = { 0,        4 };
  /* Gaps are nice on a big monitor */
  static       int smartgaps = 0;  /* 1 means no outer gap when there is only one window */

#else // _HOST_DEFAULT
  // Smaller font for laptop form factor
  static const char *fonts[] = { "monospace:size=14" }; // HiDPI Framework laptop
  /* LayoutPerMonitor:       main->tile */
  static const int lpm[] = { 0 };
  /* Gaps are nice on a big monitor */
  static       int smartgaps = 1;  /* 1 means no outer gap when there is only one window */

#endif // host dependent configurations

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "=oo",      monocle },
	{ "|v|",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ "||=",      tilewide },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define STATUSBAR "dwmblocks"

static const Key keys[] = { /* All other keys have migrated to sxhkd */
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
  { "rotatestack",    rotatestack },
  { "setcfact",       setcfact },
  { "movestack",      movestack },
  { "incrgaps",       incrgaps },
  { "incrigaps",      incrigaps },
  { "incrogaps",      incrogaps },
  { "incrihgaps",     incrihgaps },
  { "incrivgaps",     incrivgaps },
  { "incrohgaps",     incrohgaps },
  { "incrovgaps",     incrovgaps },
  { "togglegaps",     togglegaps },
  { "defaultgaps",    defaultgaps },
  { "sigstatusbar",   sigstatusbar },
  { "fullscreen",     fullscreen },
};
