SHELL := /bin/bash
FLAG = gcc -g -Wall -Werror -Wextra -std=c11
FILE = text.txt ascii.txt

all: s21_cat cf

s21_cat: cat.c
	$(FLAG) cat.c ../common/common.c -DCATCOM -c
	gcc cat.o common.o -o s21_cat

cat:
	$(FLAG) cat.c -o s21_cat

test: s21_cat
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))

clean:
	rm -rf *.o

rebuild: delete clean all

delete:
	rm -rf s21_cat

cf:
	-clang-format -i ../*/*.c
	-clang-format -i ../*/*.h

leaks:
	leaks -atExit -- ./s21_cat -benstET --number-nonblank --squeeze-blank --number $(FILE)

valgrind:
	valgrind ./s21_cat $(FILE)
	valgrind ./s21_cat -b $(FILE)
	valgrind ./s21_cat -e $(FILE)
	valgrind ./s21_cat -n $(FILE)
	valgrind ./s21_cat -s $(FILE)
	valgrind ./s21_cat -t $(FILE)
	valgrind ./s21_cat --number-nonblank $(FILE)
	valgrind ./s21_cat --squeeze-blank $(FILE)
	valgrind ./s21_cat --number $(FILE)
