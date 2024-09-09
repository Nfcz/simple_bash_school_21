#ifndef GREP
#define GREP
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"

// typedef struct settings {
//   int e, i, v, c, l, n, h, s, f, o;
//   char *pattern;
//   size_t pattern_size;
//   char *file_name;
// } sett;

// sett upload_setting(int argc, char **argv);
// void file_reader(char *file_name, sett sett, int one_file);
void deal_with_line(sett sett, var var);
// void deal_with_line(char *line, sett sett, int *count, int number_line,
//                     char *file_name, int one_file);
void print_line(char *line, sett sett, int number_line, int one_file,
                char *file_name);
void print_settings(sett setts);
void print_only_match(char *line, regex_t re, regmatch_t *arr, int number_line,
                      int one_file, sett sett, char *file_name);

void check_pattern(sett *sett);
void free_all(sett *sett);
// char *extended_line(char *old, size_t *old_len, char *new_str, int new_len);
void extended_line(sett *, char *);
void make_reg_from_array(sett *sett);

#endif