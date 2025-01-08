#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

// adds the song specified to the queue
void add_song(char* title){

}

// plays the playlist by using execvp and the mpg123 library(?)
void play(char *filename){
  //execvp
}

// stores song onto a file so user has a 'music history' file
// creates/opens backup file
// gets stat information of mp3
// append song name and stat info into one string
//write to file
void store_song(char* song_title){
  int fd = open("/Backup", O_WRONLY | O_APPEND | O_CREAT, 0666);

  struct dirent *entry;
  struct stat * stat_buffer;
  stat_buffer = malloc(sizeof(struct stat));

  stat(songPath, stat_buffer);
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
