./s21_grep $1 > grep21_test.txt
grep $1 > grep_test.txt
diff grep21_test.txt grep_test.txt
echo "\n-------------------SUCCESS! : $1\n"
