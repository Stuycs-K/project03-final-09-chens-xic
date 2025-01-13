#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "library.h"
#include "player.h"
#include "node.h"

int main(){
  // can call get_input when first command is -add?
  // if first command is -play, can loop through list and play songs
  struct song_node * list = NULL;
  list = get_input(list);
  list = get_input(list);
  list = get_input(list);
  play_list(list);
  print_list(list);

  char* song = "Rome.mp3";
  printf("Now playing song %s...\n", song);


  play(song);
  return 0;
}
