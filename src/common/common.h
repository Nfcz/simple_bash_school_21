#ifndef COMMON
#define COMMON
#define _GNU_SOURCE
#define MAX_SIZE 10000

#include <getopt.h>
#ifdef GREPCOM
#include <regex.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef GREPCOM
#include <string.h>
#endif

typedef struct sett {
  int b, e, s, t, i, v, c, l, n, h, f, o;
  char fun;
  char pattern[100][MAX_SIZE];
  int pattern_size;
  char *file_name;
} sett;

typedef struct variables {
  int read, *number_line, *count, *last_line_is_spase, one_file;
  char *file_name, *line;
} var;

typedef void (*callback_)(sett, var);
typedef void (*callback2_)(sett *, char *);

void file_reader(char *file_name, sett sett, int one_file,
                 callback_ line_thinker);
sett upload_setting(int argc, char *const *argv, char *flags_string,
                    callback2_ reg_extenger, char fun);
void our_switch(sett *settings, char c, callback2_ reg_extenger);
void flag_e(sett *settings, callback2_ reg_extenger);
void flag_f(sett *settings);
void make_long_ooption(struct option **option_long, char c);

#endif