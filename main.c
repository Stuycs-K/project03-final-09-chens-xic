#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "library.h"
#include "player.h"
#include "node.h"

struct song_node *list = NULL;
void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\nClosing music player...\n");
    free_list(list);
    exit(0);
  }
}

int main()
{
  signal(SIGINT, sighandler);

  while (1)
  {
    list = prompt_input(list);
  }
  // print_playlist(list);

  // play(song);

  return 0;
}
