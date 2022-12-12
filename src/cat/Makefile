all:
	s21_cat 

s21_cat: s21_cat.o function_cat.o common.o
	gcc --std=c11 -Wall -Werror -Wextra s21_cat.o function_cat.o common.o -o s21_cat

s21_cat.o: s21_cat.c
	gcc --std=c11 -Wall -Werror -Wextra -c s21_cat.c 

function_cat.o: function_cat.c function_cat.h
	gcc --std=c11 -Wall -Werror -Wextra -c function_cat.c 

common.o: ../common/common.c ../common/common.h
	gcc --std=c11 -Wall -Werror -Wextra -c ../common/common.c 

clang:
	clang-format -i -style=google s21_cat.c ../common/common.c ../common/common.h function_cat.c function_cat.h 

test:
	./start_test.sh

clean:
	rm -rf *.o
	
rebuild:
	all
	
