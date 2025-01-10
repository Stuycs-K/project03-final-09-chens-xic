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

// reads user input and makes it into a song node
// user input should be in this format: song_name song_artist, song names and song artists should not have spaces
struct song_node get_input(){
  char buffer[256];
  struct song_node song;
  printf("Enter a song name and song artist in the format \"song_name song_artist\": ");
  fgets(buffer, 256, stdin);
  sscanf(buffer, "%s %s", &(song.title), &(song.artist));
  return song;

}

// parses playlist from music library result into char* array
void parse(char * playlist, char** dest){

}

// stores song onto a file so user has a 'music history' file
void store_song(char* title){

}
