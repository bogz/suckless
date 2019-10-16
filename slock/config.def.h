/* user and group to drop privileges to */
static const char *user  = "orbai";
static const char *group = "wheel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#1E1F23",   /* during input */
	[FAILED] = "#CC241d",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 0;
