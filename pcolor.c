/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 30/10/2017
**/

#include <stdio.h>
#include "pcolor.h"

void print_red(char c) {
    printf("%s%c", RED, c);
    printf("%s", NORMAL);
}

void print_green(char c) {
    printf("%s%c", GREEN, c);
    printf("%s", NORMAL);
}

void print_yellow(char c) {
    printf("%s%c", YELLOW, c);
    printf("%s", NORMAL);
}

void print_blue(char c) {
    printf("%s%c", BLUE, c);
    printf("%s", NORMAL);
}

void print_magenta(char c) {
    printf("%s%c", MAGENTA, c);
    printf("%s", NORMAL);
}

void print_cyan(char c) {
    printf("%s%c", MAGENTA, c);
    printf("%s", NORMAL);
}

void printstr_red(char *str) {
  printf("%s%s", RED, str);
  printf("%s", NORMAL);
}

void printstr_green(char *str) {
  printf("%s%s", GREEN, str);
  printf("%s", NORMAL);
}