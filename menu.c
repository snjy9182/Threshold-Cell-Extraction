/*  File: menu.c
    Homework 6, 600.120(04) Spring 2017
    Date: April 9, 2017
    Name: Sun Jay Yoo
    ID: syoo21
    Email: syoo21@jhu.edu
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"

void menu_prompt(){
    printf(
        "Main menu:\n"
        "r <filename> - read image from <filename>\n"
        "w <filename> - write image to <filename>\n"
        "x <RED>, <GREEN>, <BLUE> - extract color of particular RGB values\n"
        "q - quit\n");
}
