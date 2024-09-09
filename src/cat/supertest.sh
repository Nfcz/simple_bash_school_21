./s21_cat cat.c >> s21_cat.txt
cat cat.c >> cat.txt
diff -s cat.txt cat.txt
rm s21_cat.txt cat.txt

./s21_cat -b cat.c >> s21_cat.txt
cat -b cat.c >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

./s21_cat -e cat.c >> s21_cat.txt
cat -e cat.c >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

./s21_cat -n cat.c >> s21_cat.txt
cat -n cat.c >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

./s21_cat -s cat.c >> s21_cat.txt
cat -s cat.c >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

./s21_cat -t cat.c >> s21_cat.txt
cat -t cat.c >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt