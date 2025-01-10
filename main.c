#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "library.h"
#include "player.h"
#include "node.h"

int main(){
  struct song_node ** lib = init();
  add(lib, "artist", "songname");
  print_library(lib);
  char* song = "Rome.mp3";
  printf("Now playing song %s...\n", song);
  // play(song);
  return 0;
}
