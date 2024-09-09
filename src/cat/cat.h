#ifndef CAT
#define CAT

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"

// typedef struct settings {
//   int b, e, n, s, t, v;
// } sett;

// sett upload_setting(int argc, char *const *argv);
void print_settings(sett settings);
// void file_reader(char *file_name, sett sett);
void print_line(sett sett, var var);
void visible_char(char c, char *next);
void fiction(sett *, char *);

#endif