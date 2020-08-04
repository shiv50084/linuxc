#include <stdio.h>

/* Code from LinuxProgramingByExample book */

#define TECHNIQUE4
#define ENABLE_DEBUG 0

/* TECHINQUE 1 SUCK don't care */

#ifdef TECHNIQUE2
/* TECHNIQUE 2, most portable, recommended */
/* In application header file: */
#ifdef MYAPPDEBUG
#define DPRINT(stuff) fprintf stuff
#else
#define DPRINT(stuff)
#endif
#endif

#ifdef TECHNIQUE3
/* TECHNIQUE 3, cleanest, but C99 only */
/* In application header file: */
#ifdef MYAPPDEBUG
#define DPRINT(mesg, ...) fprintf(stderr, mesg, __VA_ARGS__)
#else
#define DPRINT(mesg, ...)
#endif
#endif

/*
 * The best approach
 * Avoid bitrot in C macros
 * http://blog.vmsplice.net/2020/07/avoiding-bitrot-in-c-macros.html
 */
#ifdef TECHNIQUE4
#define DPRINT(mesg, ...) do { \
	if (ENABLE_DEBUG) { \
		fprintf(stderr, mesg, ## __VA_ARGS__); \
	} \
} while (0)
#endif

/*
 * Compile:
 * gcc -DTECHNIQUE2 -DMYAPPDEBUG
 * gcc -DMYAPPDEBUG
 */
int main(int argc, char *argv[])
{
#ifdef TECHNIQUE2
	int r = 911;

	/*
	 * what if rename r to radius ?
	 * could compiler find the syntax error ?
	 */
	DPRINT((stderr, "Technique 2 var = %d\n", r));
#endif

#ifdef TECHNIQUE3
	int r = 911;

	DPRINT("Technique 3 var = %d\n", r);
#endif

#ifdef TECHNIQUE4
	int r = 911;

	DPRINT("Technique 4 var = %d\n", r);
#endif
	return 0;
}
