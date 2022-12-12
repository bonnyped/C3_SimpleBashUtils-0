#ifndef COMMON_H
#define COMMON_H
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(int argc, char *name_of_program);
FILE *open_file(char *file_to_open);

#endif
