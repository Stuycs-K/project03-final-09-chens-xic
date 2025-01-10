#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


// adds the song specified to the queue
void add_song(char* title){

}

// plays the playlist by using execvp and the mpg123 library(?)
void play(char *filename){
  char* args[4];
  char* program = "mpg123";
  args[0] = program;
  args[1] = "-q";
  args[2] = filename;
  args[3] = NULL;
  execvp(args[0], args);
}

// stores song onto a file so user has a 'music history' file

// creates/opens backup file
// gets stat information of mp3
// append song name and stat info into one string
//write to file
void store_song(char* song_title){
  int fd = open("Backup", O_WRONLY | O_APPEND | O_CREAT, 0666);
  if(fd < 0) printf("%s\n", strerror(errno));


  //songPath = catPath("/MUSICFOLDER/", song_title); for when we move music into folder
  //struct dirent *entry;
  struct stat * stat_buffer;
  stat_buffer = malloc(sizeof(struct stat));
  stat(song_title, stat_buffer);
  printf("song size: %ld\n", stat_buffer->st_size);
  char buff[100];
  sprintf(buff, "SONG: %s | SIZE: %ld\n", song_title, stat_buffer->st_size);

  printf("%s", buff);
  int bytesWritten = write(fd, buff, strlen(buff)+1);
  printf("bytes written: %d, sizeof buff: %ld\n", bytesWritten, sizeof(buff));

}


char* catPath(char *PATH, char *entryName){
    int size = strlen(PATH) + strlen(entryName);
    char str[size];
    char *buffer = str;
    strcpy(buffer, PATH);
    strncat(buffer, "/", strlen(buffer)+2);
    strncat(buffer, entryName, size+2);
  //printf("%s\n", buffer);
    return buffer;
}
