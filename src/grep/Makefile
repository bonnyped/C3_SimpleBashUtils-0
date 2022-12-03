All:
	gcc -g s21_grep.c ../common/common.c -o s21_grep
	clang-format -i -style=google s21_grep.c ../common/common.c ../common/common.h
	valgrind --leak-check=full ./s21_grep -e while test_1_grep.txt 
	./start_test.sh
