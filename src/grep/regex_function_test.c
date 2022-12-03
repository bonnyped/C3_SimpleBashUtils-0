#include <stdio.h>
#include <regex.h>

int main(int argc, char **argv) {
    regex_t re; 
    int success;

    char *test_string = "Hello, my name is Denchik chik chik";
    regcomp(&re, argv[1], REG_ICASE);
    if ((success = regexec(&re, test_string, 0, NULL, 0)) == 0) {
        printf("%s\n", test_string);
    }
    regfree(&re);   
}