#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "library.h"
#include "player.h"
#include "node.h"

void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\nClosing music player...\n");
    exit(0);
  }
}

int main()
{
  signal(SIGINT, sighandler);
  struct song_node *list = NULL;
  while (1)
  {
    list = prompt_input(list);
  }
  // print_playlist(list);

  // play(song);
  free(list);
  return 0;
}
