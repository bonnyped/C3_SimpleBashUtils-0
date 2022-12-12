#!/bin/bash
./s21_grep $1 > grep21_test.txt
grep $1 > grep_test.txt
diff grep21_test.txt grep_test.txt
echo -e "\n\n\n\n\n-------------------SUCCESS! : $1\n\nvalgrind below, need uncooment\n"

#valgrind --leak-check=full --trace-children=yes --track-fds=yes --track-origins=yes --show-leak-kinds=all ./s21_grep $1 > grep21_test.txt
