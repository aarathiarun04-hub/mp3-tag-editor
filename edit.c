#include "main.h"

int edit(Mp3_info *mp3, char *option, char *new_data)
{
    mp3->fptr_real = fopen(mp3->file_name, "rb");
    mp3->fptr_temp = fopen("temp.mp3", "wb");
    if (mp3->fptr_real == NULL || mp3->fptr_temp == NULL)
    {
        printf("File opening failed\n");
        return FAILURE;
    }
    char frame_id[5];
    if(strcmp(option,"-t")==0)
        strcpy(frame_id,"TIT2");
    else if(strcmp(option,"-a")==0)
        strcpy(frame_id,"TPE1");
    else if(strcmp(option,"-A")==0)
        strcpy(frame_id,"TALB");
    else if(strcmp(option,"-y")==0)
        strcpy(frame_id,"TYER");
    else if(strcmp(option,"-g")==0)
        strcpy(frame_id,"TCON");
    else if(strcmp(option,"-c")==0)
        strcpy(frame_id,"COMM");
    else
    {
        printf("Invalid Edit Option\n");
        fclose(mp3->fptr_real);
        fclose(mp3->fptr_temp);
        return FAILURE;
    }
    edit_frame(mp3, frame_id, new_data);
    fclose(mp3->fptr_real);
    fclose(mp3->fptr_temp);
    remove(mp3->file_name);
    rename("temp.mp3", mp3->file_name);
    return SUCCESS;
}
void edit_frame(Mp3_info *mp3, char *target_frame, char *new_data)
{
    unsigned char header[10];
    char frame_id[5];
    unsigned char size[4];
    unsigned char flags[2];
    unsigned char encoding;
    unsigned int frame_size;
    fread(header,1,10,mp3->fptr_real);
    fwrite(header,1,10,mp3->fptr_temp);
    while(1)
    {
        if(fread(frame_id,1,4,mp3->fptr_real)!=4)
            break;
        frame_id[4]='\0';
        if(frame_id[0]=='\0')
        {
            fseek(mp3->fptr_real, -4, SEEK_CUR);
            break;
        }
        fread(size,1,4,mp3->fptr_real);
        frame_size=((unsigned int)size[0]<<24) |((unsigned int)size[1]<<16) |((unsigned int)size[2]<<8)  |size[3];
        fread(flags,1,2,mp3->fptr_real);
        if(strcmp(frame_id,target_frame)==0)
        {
            fread(&encoding,1,1,mp3->fptr_real);
            char *buffer = malloc(frame_size);  
            if(buffer == NULL)
            {
                printf("Memory allocation failed\n");
                return;
            }

            fread(buffer,1,frame_size-1,mp3->fptr_real);
            buffer[frame_size-1]='\0';
            printf("Old Data : %s\n",buffer);
            free(buffer);
            unsigned int new_size=1+strlen(new_data);
            unsigned char temp[4];
            temp[0]=(new_size>>24)&0xFF;
            temp[1]=(new_size>>16)&0xFF;
            temp[2]=(new_size>>8)&0xFF;
            temp[3]=new_size&0xFF;
            fwrite(frame_id,1,4,mp3->fptr_temp);
            fwrite(temp,1,4,mp3->fptr_temp);
            fwrite(flags,1,2,mp3->fptr_temp);
            fwrite(&encoding,1,1,mp3->fptr_temp);
            fwrite(new_data,1,strlen(new_data),mp3->fptr_temp);
             printf("New Data : %s\n", new_data);
        }
        else
        {
            fwrite(frame_id,1,4,mp3->fptr_temp);
            fwrite(size,1,4,mp3->fptr_temp);
            fwrite(flags,1,2,mp3->fptr_temp);
            char chunk[1024];
            unsigned int remaining = frame_size;
            while(remaining > 0)
            {
                unsigned int to_read = (remaining > sizeof(chunk)) ? sizeof(chunk) : remaining;
                size_t got = fread(chunk,1,to_read,mp3->fptr_real);
                if(got == 0) break;
                fwrite(chunk,1,got,mp3->fptr_temp);
                remaining -= got;
            }
        }
    }
    char ch;
    while(fread(&ch,1,1,mp3->fptr_real))
    {
        fwrite(&ch,1,1,mp3->fptr_temp);
    }
}