/** Read command-line arguments (argc, argv)
Call validate_arguments()
Decide whether to:
Show Help
View Tags
Edit Tags **/
#include "main.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    char new_data[100];
    char option[3];
    Mp3_info mp3;
    if (validate_arguments(argc, argv, &mp3) == FAILURE)
    {
        return FAILURE;
    }
    if (strcmp(argv[1],"-h") == 0)
    {
        help();
    }
    else if (strcmp(argv[1],"-v") == 0)
    {
        view(&mp3);
    }
    else if (strcmp(argv[1], "-e") == 0)
{
    strcpy(option, argv[2]);
    strcpy(new_data, argv[3]);

    if (edit(&mp3, option, new_data) == FAILURE)
    {
        printf("Edit failed\n");
        return FAILURE;
    }
    printf("Tag edited successfully\n");
}
    else
    {
        printf("Invalid option\n");

    }
    return SUCCESS;
}