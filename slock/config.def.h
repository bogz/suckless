/* user and group to drop privileges to */
static const char *user  = "orbai";
static const char *group = "wheel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#3F3F3F",   /* during input */
	[FAILED] = "#CC9393",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
