#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
#define FAILURE 1
typedef struct
{
    char *file_name;
    FILE *fptr_real;
    FILE *fptr_temp;  

} Mp3_info;
typedef struct
{
    char frame_id[5];
    char title[100];
    char artist[100];
    char album[100];
    char year[10];
    char genre[50];
    char comment[200];

} frame_data;
int validate_arguments(int argc, char *argv[], Mp3_info *mp3);
int check_mp3_extension(char *file_name);
void help(void);
int edit(Mp3_info *mp3, char *option, char *new_data);
void edit_frame(Mp3_info *mp3, char *target_frame, char *new_data);
int view(Mp3_info *mp3);
#endif