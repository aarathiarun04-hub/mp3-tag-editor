/** view_tags()

read_header()

read_frame()

display_title()

display_artist()

display_album() **/
#include "main.h"

int view(Mp3_info *mp3)
{
    mp3->fptr_real=fopen(mp3->file_name,"rb");
     printf("\n***************************************\n");
    printf("MP3 TAG READER AND EDITOR FOR ID3v2");
    printf("\n***************************************\n");
        if (mp3->fptr_real == NULL)
    {
          printf("File opening failed\n");
        return FAILURE;
    }
char byte[4];
fread(byte, 1, 3, mp3->fptr_real); //reads first 3 bytes
byte[3] = '\0';
  if (strcmp(byte, "ID3") != 0)
    {
        printf("Not a valid ID3 MP3 file\n");
         fclose(mp3->fptr_real);
        return FAILURE;
    }
     printf("Header : %s\n", byte);
//when i peint ill gwt id3 
//now to print version
unsigned char ch;
fread(&ch,1,1,mp3->fptr_real);
printf("Version : ID3v2.%d\n",ch);
 printf("\n***************************************\n");
//printed version
//now check frame id
fseek(mp3->fptr_real, 6, SEEK_CUR);//3+1=4 to reach 10 ...6 jump
frame_data data;
while(1)
{
    if(fread(data.frame_id,1,4,mp3->fptr_real) != 4)
    {
        break;
    }
    data.frame_id[4]='\0';

        if(data.frame_id[0]=='\0')
        {
            break;
        }

//read frame sizee
unsigned char size[4];
 if(fread(size,1,4,mp3->fptr_real) != 4)
        {
            break;
        }
//now all ll be in hex format 00 00 00 09 etc ,,so to convert to integer we cant typecast or use another pointer so using bitwise v solce it
unsigned int frame_size;
//4 bytes hex to integer
    frame_size = ((unsigned int)size[0]<<24) |
                 ((unsigned int)size[1]<<16) |
                 ((unsigned int)size[2]<<8) |
                  size[3];

    
fseek(mp3->fptr_real,2,SEEK_CUR);//flag skipped
if(strcmp(data.frame_id,"TIT2")==0)
{
    fgetc(mp3->fptr_real); 
fread(data.title,1,frame_size-1,mp3->fptr_real);
data.title[frame_size-1]='\0';
        printf("Title : %s\n",data.title);
        printf("\n");
}
else if(strcmp(data.frame_id,"TPE1")==0)
{
      fgetc(mp3->fptr_real);

    fread(data.artist,1,frame_size-1,mp3->fptr_real);
data.artist[frame_size-1]='\0';

        printf("Artist : %s\n",data.artist);
         printf("\n");
}
else if(strcmp(data.frame_id,"TALB")==0)
{
      fgetc(mp3->fptr_real);
    fread(data.album,1,frame_size-1,mp3->fptr_real);
 data.album[frame_size-1]='\0';
        printf("Album : %s\n",data.album);
         printf("\n");
    }
    else if(strcmp(data.frame_id,"TYER")==0 ||
        strcmp(data.frame_id,"TDRC")==0)
{
    fgetc(mp3->fptr_real);
    fread(data.year,1,frame_size-1,mp3->fptr_real);
    data.year[frame_size-1]='\0';
    printf("Year : %s\n",data.year);
}
else if(strcmp(data.frame_id,"TCON")==0)
{
    fgetc(mp3->fptr_real);
    fread(data.genre,1,frame_size-1,mp3->fptr_real);
    data.genre[frame_size-1]='\0';
    printf("Genre   : %s\n",data.genre);
}

else if(strcmp(data.frame_id,"COMM") == 0)
{
    fseek(mp3->fptr_real, 5, SEEK_CUR);   // Skip encoding + "eng" + empty description
    fread(data.comment, 1, frame_size - 5, mp3->fptr_real);
    data.comment[frame_size - 5] = '\0';
    printf("Comment : %s\n", data.comment);
}
     else
    {
        fseek(mp3->fptr_real,frame_size,SEEK_CUR);
         printf("\n");
    }
}
printf("********************DATA DISPLAYED SUCCESSFULLY**********************");
 fclose(mp3->fptr_real);
    return SUCCESS;
}