#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"
#include "node.h"
#include "library.h"
#define BSIZE 256

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

// takes a song_node pointer as parameter (list), reads user input and makes it into a song node, which is added to list
// user input should be in this format: song_name song_artist, song names and song artists should not have spaces
// input added to library or to list?
struct song_node * get_input(struct song_node * list){
  char buffer[BSIZE];
  char artist[BSIZE];
  char title[BSIZE];
  printf("Enter a song name and song artist in the format \"song_name song_artist\": ");
  fgets(buffer, BSIZE, stdin);
  sscanf(buffer, "%s %s", title, artist);
  return insert_front(list,artist,title);
}

// parses playlist from music library result into char* array
void parse(char * playlist, char** dest){

}

// stores song onto a file so user has a 'music history' file
void store_song(char* title){

}
