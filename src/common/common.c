#include "common.h"

void file_reader(char *file_name, sett sett, int one_file,
                 callback_ line_thinker) {
  FILE *fp;
  size_t len = 0;
  int read;
  int last_line_is_spase = 0;
  int count = 0;
  var var;
  var.line = NULL;
  var.count = &count;
  var.last_line_is_spase = &last_line_is_spase;
  var.file_name = file_name;
  var.one_file = one_file;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    if (sett.fun == 'g' && sett.s == 1) {
      sett.fun = 'o';
    } else {
      perror("error\n");
    }
  } else {
    for (int n = 1; (read = getline(&var.line, &len, fp)) != -1; n++) {
      var.read = read;
      var.number_line = &n;
      (line_thinker)(sett, var);
    }
  }
  if (var.line) free(var.line);
  if (sett.fun != 'o') {
    if (sett.c) {
      if (!one_file && sett.h != 1) printf("%s:", file_name);
      printf("%d\n", (sett.l) ? !(!(*var.count)) : *var.count);
    }
    if (sett.l && *var.count != 0) printf("%s\n", file_name);
  }
}

sett upload_setting(int argc, char *const *argv, char *flags_string,
                    callback2_ reg_extenger, char fun) {
  sett settings = {0};
  settings.fun = fun;
  settings.pattern_size = 0;
  struct option option_long[4];
  if (settings.fun == 'c') {
    static struct option option_long1[] = {
        {"squeeze-blank", no_argument, 0, 's'},
        {"number-nonblank", no_argument, 0, 'b'},
        {"number", no_argument, 0, 'n'},
        {0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) {
      option_long[i] = option_long1[i];
    }
  } else {
    static struct option option_long2[] = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    for (int i = 0; i < 4; i++) option_long[i] = option_long2[i];
  }
  int c;
  while ((c = getopt_long(argc, argv, flags_string, option_long, 0)) != -1 &&
         settings.fun != 'o')
    our_switch(&settings, c, reg_extenger);
  if (settings.b) settings.n = 0;
  if (settings.fun == 'g') {
    if (settings.pattern_size == 0 && settings.f == 0) {
      reg_extenger(&settings, argv[optind]);
      optind++;
    }
  }
  return settings;
}

void our_switch(sett *settings, char c, callback2_ reg_extenger) {
  switch (c) {
    case 'b':
      settings->b = 1;
      break;
    case 'e':
      flag_e(settings, reg_extenger);
      break;
    case 'E':
      settings->e = 1;
      break;
    case 'n':
      settings->n = 1;
      break;
    case 's':
      settings->s = 1;
      break;
    case 't':
      settings->t = settings->v = 1;
      break;
    case 'T':
      settings->t = 1;
      break;
    case 'i':
      settings->i = 1;
      break;
    case 'v':
      settings->v = 1;
      break;
    case 'c':
      settings->c = 1;
      break;
    case 'l':
      settings->l = 1;
      break;
    case 'h':
      settings->h = 1;
      break;
    case 'f':
      flag_f(settings);
      break;
    case 'o':
      settings->o = 1;
      break;
    case '?':
      settings->fun = 'o';
      break;
  }
}

void flag_e(sett *settings, callback2_ reg_extenger) {
  settings->e = 1;
  if (settings->fun == 'c') {
    settings->v = 1;
  } else {
    reg_extenger(settings, optarg);
  }
}

void flag_f(sett *settings) {
  settings->f = 1;
  settings->file_name = (char *)malloc(sizeof(char) * 100);
#ifdef GREPCOM
  strcpy(settings->file_name, optarg);
#endif
}