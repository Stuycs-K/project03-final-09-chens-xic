#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"

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
void store_song(char* title){

}
