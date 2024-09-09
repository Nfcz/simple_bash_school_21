#include "cat.h"

int main(int argc, char **argv) {
  sett settings = upload_setting(argc, argv, "beEnstT", fiction, 'c');
  // print_settings(settings);
  for (int i = optind; i < argc && settings.fun != 'o'; i++) {
    file_reader(argv[i], settings, 1, &print_line);
  }
  return 0;
}

void print_line(sett sett, var var) {
  int good = 1;
  if (sett.s) {
    if (*var.last_line_is_spase && 1 == var.read) {
      good = 0;
    }
    if (1 == var.read) {
      *var.last_line_is_spase = 1;
    } else {
      *var.last_line_is_spase = 0;
    }
  }

  if ((sett.b && '\n' == var.line[0]) || !good) {
    *var.number_line -= 1;
  }

  if (good) {
    if (sett.n || (sett.b && '\n' != var.line[0])) {
      printf("%6d\t", *var.number_line);
    } else if ((sett.b || sett.n) && sett.t) {
      printf("      \t");
    }
  }

  for (int i = 0; i < var.read && good; i++) {
    if (var.line[i] == '\t' && 1 == sett.t) {
      printf("^I");
    } else if (var.line[i] == '\n' && 1 == sett.e) {
      printf("$\n");
    } else if (sett.v) {
      visible_char(var.line[i], &var.line[i + 1]);
    } else {
      putchar(var.line[i]);
    }
  }
}

void visible_char(char c, char *next) {
  if (c == '\t' || c == '\n') {
    putchar(c);
  } else if (c < 0) {
    printf("M-");
    *next = *next * -1;
  } else if (c >= 0 && c <= 31) {
    putchar('^');
    putchar(c + 64);
  } else if (c == 127) {
    putchar('^');
    putchar('?');
  } else {
    putchar(c);
  }
}

void fiction(sett *, char *) {}

void print_settings(sett setts) {
  if (setts.b) {
    printf("b");
  }
  if (setts.e) {
    printf("e");
  }
  if (setts.n) {
    printf("n");
  }
  if (setts.s) {
    printf("s");
  }
  if (setts.t) {
    printf("t");
  }
  if (setts.v) {
    printf("v");
  }
  printf("\n");
}