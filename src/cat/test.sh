#!/bin/bash
./s21_cat $1 > cat21_test.txt
cat $1 > cat_test.txt
diff cat21_test.txt cat_test.txt
echo -e "-------------------SUCCESS! : $1\n"