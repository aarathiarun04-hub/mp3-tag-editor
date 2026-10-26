/**read_frame_header()

read_tag_size()

convert_size()

copy_file() **/
#include "main.h"

void help(void)
{
    printf("\n================ MP3 TAG READER & EDITOR ================\n");
    printf("\nUsage:\n");
    printf("./a.out -v <file_name.mp3>\n");
    printf("       To view MP3 tag details\n\n");
    printf("./a.out -e <modifier> <changed_value> <file_name.mp3>\n");
    printf("       To edit MP3 tag details\n\n");
    printf("Edit Modifiers:\n");
    printf("  -t   Edit Title\n");
    printf("  -a   Edit Artist\n");
    printf("  -A   Edit Album\n");
    printf("  -y   Edit Year\n");
    printf("  -g   Edit Genre\n");
    printf("  -c   Edit Comment\n\n");
    printf("./a.out -h\n");
    printf("Display Help Menu\n");
    printf("=========================================================\n");
}