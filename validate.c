/** validate_arguments()

check_mp3_extension()

check_file_exists() **/
#include "main.h"
#include<stdio.h>
#include<string.h>
int validate_arguments(int argc, char *argv[], Mp3_info *mp3)
{
    if (argc < 2)
    {
        return FAILURE;
    }
    
      if (strcmp(argv[1], "-v") == 0)
    {
        if (argc != 3)
        {
            printf("Usage : ./a.out -v <file_name.mp3>\n");
            return FAILURE;
        }

        mp3->file_name = argv[2];

        if (check_mp3_extension(mp3->file_name) == FAILURE)
        {
            printf("ERROR: Invalid MP3 file\n");
            return FAILURE;
        }

        mp3->fptr_real = fopen(mp3->file_name, "rb");

        if (mp3->fptr_real == NULL)
        {
            printf("ERROR: Unable to open file\n");
            return FAILURE;
        }

        return SUCCESS;
    }

    /* Edit Operation */
    else if (strcmp(argv[1], "-e") == 0)
    {
        if (argc != 5)
        {
            printf("Usage : ./a.out -e <option> <new_value> <file_name.mp3>\n");
            return FAILURE;
        }

        mp3->file_name = argv[4];

        if (check_mp3_extension(mp3->file_name) == FAILURE)
        {
            printf("ERROR: Invalid MP3 file\n");
            return FAILURE;
        }

        mp3->fptr_real = fopen(mp3->file_name, "rb");

        if (mp3->fptr_real == NULL)
        {
            printf("ERROR: Unable to open file\n");
            return FAILURE;
        }

        return SUCCESS;
    }

else if(strcmp(argv[1], "-h") == 0)
{
    if(argc!=2)
    {
        printf("Less arguments\n");
        return FAILURE;
    }
    return SUCCESS;
}
else
{
    return FAILURE;
}
}

int check_mp3_extension(char *file_name)
{
    char *ext = strrchr(file_name, '.');//strrchr from right checks . ext * ll point to . when u print it ll be .mp3

if (ext == NULL)
{
    return FAILURE;
}

if (strcmp(ext, ".mp3") != 0)
{
    return FAILURE;
}

return SUCCESS;
}
