#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "library.h"
#include "player.h"
#include "node.h"

int main()
{
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
