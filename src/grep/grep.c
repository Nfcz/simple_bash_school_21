#include "grep.h"
#define _POSIX_C_SOURSE 200809L

int main(int argc, char **argv) {
  sett sett = upload_setting(argc, argv, "e:ivclnhsf:o", &extended_line, 'g');
  check_pattern(&sett);
  // print_settings(sett);
  make_reg_from_array(&sett);
  for (int i = optind; i < argc && sett.fun != 'o'; i++) {
    file_reader(argv[i], sett, (optind + 1 == argc) ? 1 : 0, &deal_with_line);
  }
  free_all(&sett);
  return 0;
}

void print_line(char *line, sett sett, int number_line, int one_file,
                char *file_name) {
  if (!one_file && sett.h != 1) printf("%s:", file_name);
  if (sett.n) printf("%d:", number_line);
  printf("%s", line);
  putchar('\n');
}

void deal_with_line(sett sett, var var) {
  if (var.line[strlen(var.line) - 1] == '\n')
    var.line[strlen(var.line) - 1] = '\0';
  regex_t re;
  if (regcomp(&re, sett.pattern[0],
              REG_EXTENDED | ((sett.i) ? REG_ICASE : 0)) != 0) {
    printf("can't regcomp\n");
  }
  regmatch_t arr[1];
  int error = regexec(&re, var.line, 1, arr, 0);
  if (sett.v) {
    if (error == REG_NOMATCH)
      error = 0;
    else if (error == 0)
      error = 1;
  }
  if (sett.c || sett.l) {
    *var.count += (error) ? 0 : 1;
  } else if (!error) {
    if (sett.o) {
      print_only_match(var.line, re, arr, *var.number_line, var.one_file, sett,
                       var.file_name);
    } else {
      print_line(var.line, sett, *var.number_line, var.one_file, var.file_name);
    }
  }
  regfree(&re);
}

void print_only_match(char *line, regex_t re, regmatch_t *arr, int number_line,
                      int one_file, sett sett, char *file_name) {
  int reti = 0;
  int new_start = 0;

  if (sett.v)
    print_line(line, sett, number_line, one_file, file_name);
  else
    while ((reti = regexec(&re, &line[new_start], 1, arr, 0)) == 0) {
      if (!one_file && sett.h != 1) printf("%s:", file_name);
      if (sett.n) printf("%d:", number_line);
      for (int j = arr[0].rm_so + new_start; j < arr[0].rm_eo + new_start;
           j++) {
        putchar(line[j]);
      }
      new_start += arr[0].rm_so + 1;
      printf("\n");
    }
}

void check_pattern(sett *sett) {
  if (sett->f) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int read;
    fp = fopen(sett->file_name, "r");
    if (fp != NULL) {
      for (int n = 1; (read = getline(&line, &len, fp)) != -1; n++) {
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0) strcpy(line, ".*\0");
        // var_2 var;
        // strcpy(*var.old, sett->pattern);
        // var.new_str = line;
        // var.old_len = &sett->pattern_size;
        // var.new_len = strlen(line);
        extended_line(sett, line);
      }
      if (line) free(line);
    }
    fclose(fp);
  }
}

void extended_line(sett *sett, char *new) {
  if (strlen(new) >= 1) {
    strcpy(sett->pattern[sett->pattern_size++], new);
    // strcat(*var.old, "|");
    // strcat(*var.old, var.new_str);
    // *var.old_len = *var.old_len + var.new_len + 1;
  }
}

void free_all(sett *sett) {
  //   if (sett->pattern) free(sett->pattern);
  if (sett->file_name) free(sett->file_name);
}

void print_settings(sett sett) {
  for (int i = 0; i < sett.pattern_size; i++) {
    if (sett.pattern[i][0] != '\0') printf("pattern:%s\n", sett.pattern[0]);
  }
  printf("settings:");
  if (sett.e) {
    printf("e");
  }
  if (sett.i) {
    printf("i");
  }
  if (sett.v) {
    printf("v");
  }
  if (sett.c) {
    printf("c");
  }
  if (sett.l) {
    printf("l");
  }
  if (sett.n) {
    printf("n");
  }
  if (sett.h) {
    printf("h");
  }
  if (sett.s) {
    printf("s");
  }
  if (sett.f) {
    printf("f");
  }
  if (sett.o) {
    printf("o");
  }
  if (sett.f) {
    printf("\nfile with reg exp:%s", sett.file_name);
  }
  printf("\n");
}

void make_reg_from_array(sett *sett) {
  for (int i = 1; i < sett->pattern_size; i++) {
    strcat(sett->pattern[0], "|");
    strcat(sett->pattern[0], sett->pattern[i]);
  }
}