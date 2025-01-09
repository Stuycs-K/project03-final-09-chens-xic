#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "library.h"
#include "player.h"

int main(){
  char* song = "Rome.mp3";
  printf("Now playing song %s...\n", song);
  play(song);
  return 0;
}
