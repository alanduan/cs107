#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INVERTED_BOX "\e[7m \e[0m"

// uncomment below to swap in "+" as definition of LIVE_STR if your
// terminal doesn't play nice with inverted box
//define LIVE_STR INVERTED_BOX
#define LIVE_STR "+"
#define EMPTY_STR " "
#define Bit(x) (1L << (x))
unsigned long advance(unsigned long cur_gen, unsigned char ruleset)
{
    unsigned long cur = cur_gen;
    int size = sizeof(unsigned long) * CHAR_BIT;
    int i;
    for(cur_gen = i = 0; i < size; i++) {
        if(ruleset & Bit(7 &((cur >>(i - 1))| (cur << (size + 1 - i)))))
		cur_gen |= Bit(i);
    } 
   return cur_gen;
}

void draw_generation(unsigned long gen)
{
    // each cell in gen is drawn as LIVE_STR or EMPTY_STR depending on whether cell is on or off
  int size = sizeof(unsigned long)*CHAR_BIT;
	for(int i = size - 1; i >= 0; i --) {
	   if(gen & Bit(i)) {
		printf(LIVE_STR);
		}
	   else {
		printf(EMPTY_STR);
		}
		
		
	}
	printf("\n");
 
}


// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------


unsigned long convert_arg(const char *str, unsigned long low, unsigned long high, const char *argname)
{
    char *end;
    unsigned long n = strtoul(str, &end, 0);
    if (*end != '\0') 
        error(1, 0, "Invalid number '%s' for %s", str, argname);
    if (n < low || n > high || errno == ERANGE) 
        error(1, 0, "%s %s is not in range [%#lx, %#lx]", argname, str, low, high);
    return n;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        error(1, 0, "Missing argument. Please supply ruleset and optional initial generation.");

    unsigned long gen_0 = 1L << 32;
    unsigned char ruleset = convert_arg(argv[1], 0, UCHAR_MAX, "ruleset");
    if (argc > 2) gen_0 = convert_arg(argv[2], 0, ULONG_MAX, "initial generation");

    if (ruleset == 0) {
        draw_generation(gen_0);
    } else {
        unsigned long cur_gen = gen_0;
        for (int i = 0; i < 32; i++) {
            draw_generation(cur_gen);
            unsigned long next_gen = advance(cur_gen, ruleset);
            if (next_gen == cur_gen) break;
            cur_gen = next_gen;
        }
    }
    return 0;
}
