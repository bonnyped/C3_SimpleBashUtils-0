all: s21_grep
	
s21_grep: s21_grep.o function_grep.o common.o
	gcc --std=c11 -Wall -Werror -Wextra s21_grep.o function_grep.o common.o -o s21_grep

s21_grep.o: s21_grep.c 
	gcc --std=c11 -Wall -Werror -Wextra -c s21_grep.c

function_grep.o: function_grep.c function_grep.h
	gcc --std=c11 -Wall -Werror -Wextra -c function_grep.c

common.o: ../common/common.c ../common/common.h
	gcc --std=c11 -Wall -Werror -Wextra -c ../common/common.c

clang:
	clang-format -i -style=google s21_grep.c ../common/common.c ../common/common.h function_grep.c function_grep.h 

test: 
	./start_test.sh

clean: 
	rm - rf *.o
	
rebuild:
	all
