#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include "node.h"
#include "player.h"
#include "library.h"
#define BSIZE 256

// group ID 6

// takes a string (the name of the song file to be played) as an argument
// plays a single song by using execvp and mpg123
// void
void play(char *filename)
{
  char *args[4];
  char *program = "mpg123";
  args[0] = program;
  args[1] = "-q";
  args[2] = filename;
  args[3] = NULL;
  execvp(args[0], args);
}

// takes a pointer to the beginning of the song_node list (the playlist built from user input) as argument
// plays the playlist built from user input by forking and calling the play() function
// void
void play_list(struct song_node *list)
{
  if (list == NULL)
  {
    printf("You currently have no songs in your playlist.\n");
  }
  while (list != NULL)
  {
    pid_t p = fork();
    if (p < 0)
    {
      perror("Fork failed.\n");
      exit(1);
    }
    else if (p == 0)
    {
      char filename[BSIZE];
      sprintf(filename, "./song_lib/%s_by_%s.mp3", list->title, list->artist);
      printf("Now playing song %s_by_%s.mp3...\n", list->title, list->artist);
      play(filename);
    }
    else
    {
      int status;
      pid_t child = wait(&status);
      if (child == -1)
      {
        perror("Wait failed.\n");
        exit(1);
      }
      if (WIFEXITED(status))
      {
        list = list->next;
      }
    }
  }
}

//  takes a pointer to the beginning of the song_node list (the playlist built from user input) as argument
// keeps asking user to put one of the commands: play add show remove history and calls following function
// returns a pointer to the beginning of the song_node list
struct song_node *prompt_input(struct song_node *list)
{
  char buffer[BSIZE];
  printf("Input a command (play   add    show    remove    history): ");
  fgets(buffer, BSIZE, stdin);
  if (!strcmp(buffer, "add\n"))
  {
    valid_songs();
    return get_input(list);
  }
  else if (!strcmp(buffer, "play\n"))
  {
    play_list(list);
  }
  else if (!strcmp(buffer, "show\n"))
  {
    print_playlist(list);
  }
  else if (!strcmp(buffer, "remove\n"))
  {
    printf("Current playlist:\n");
    printf("\033[0;32m"); // makes text green
    print_playlist(list);
    printf("\033[0m"); // resets text color
    return remove_from_queue(list);
  }
  else if (!strcmp(buffer, "history\n"))
  {
    play_history();
  }
  else
  {
    printf("Please input a valid command.\n");
  }
  return list;
}

// takes a song_node pointer as argument (list), reads user input and makes it into a song node, which is added to list
// user input should be in this format: song_name song_artist, song names and song artists should not have spaces
// input added to library or to list?
struct song_node *get_input(struct song_node *list)
{
  char buffer[BSIZE];
  char artist[BSIZE];
  char title[BSIZE];
  printf("Enter a song name and song artist in the format \"song_name song_artist\": ");
  // catch an error if song is not on playlist
  fgets(buffer, BSIZE, stdin);
  sscanf(buffer, "%s %s", title, artist);
  store_song(title, artist);
  return insert_front(list, artist, title);
}

// stores song onto a file so user has a 'music history' file

// creates/opens backup file
// gets stat information of mp3
// append song name and stat info into one string
// write to file
void store_song(char *title, char *artist)
{
  int fd = open("Backup", O_WRONLY | O_APPEND | O_CREAT, 0666);
  if (fd < 0)
    printf("%s\n", strerror(errno));

  char filename[BSIZE];
  sprintf(filename, "%s_by_%s.mp3", title, artist);
  //  printf("%s\n", filename);
  char *songPath;
  songPath = catPath("song_lib/", filename);
  // printf("%s\n", songPath);
  struct stat *stat_buffer;
  stat_buffer = malloc(sizeof(struct stat));
  stat(songPath, stat_buffer);
  //  printf("song size: %ld\n", stat_buffer->st_size);
  char buff[BSIZE];
  sprintf(buff, "%s %s %ld\n", title, artist, stat_buffer->st_size);

  //  printf("%s\n", buff);
  int bytesWritten = write(fd, buff, strlen(buff));
  //  printf("bytes written: %d sizeof buff: %ld\n", bytesWritten, sizeof(buff));
}

char *catPath(char *PATH, char *entryName)
{
  int size = strlen(PATH) + strlen(entryName) + 1;
  char str[size];
  char *buffer = (char *)malloc(size);
  if (buffer == NULL)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }
  strcpy(buffer, PATH);
  strncat(buffer, entryName, strlen(entryName));
  // printf("%s\n", buffer);
  return buffer;
}

// plays songs on Backup file
void play_history()
{
  FILE *backup = fopen("Backup", "r");
  if (backup == NULL)
  {
    printf("No previous history\n");
    return;
  }
  char buff[100];
  struct song_node *list = NULL;
  while (fgets(buff, 100, backup))
  {
    long int bytes;
    char title[100];
    char artist[100];
    // printf("about to sscanf\n");
    sscanf(buff, "%s %s %ld", title, artist, &bytes);
    list = insert_front(list, artist, title);
  }
  print_playlist(list);
  play_list(list);
}

// void function, takes no argument
// prints the song files contained in our music library by forking and execvping ls
void valid_songs()
{
  char *args[3];
  args[0] = "ls";
  args[1] = "./song_lib";
  args[2] = NULL;
  pid_t p = fork();
  if (p < 0)
  {
    perror("Fork failed.\n");
    exit(1);
  }
  if (p == 0)
  {
    printf("\033[0;35m"); // makes text purple
    printf("Song files available: \n");
    execvp(args[0], args);
  }
  else
  {
    int status;
    pid_t child = wait(&status);
    if (child == -1)
    {
      perror("Wait failed.\n");
      exit(1);
    }
    printf("\033[0m"); // resets text color
  }
}

// takes a song_node pointer as argument (list), reads user input removes the song from the list
// user input should be in this format: song_name song_artist, song names and song artists should not have spaces
// returns a pointer to the beginning of the song_node list
struct song_node *remove_from_queue(struct song_node *list)
{
  char buffer[BSIZE];
  char artist[BSIZE];
  char title[BSIZE];
  printf("To remove a song, enter the song name and song artist in the format \"song_name song_artist\": ");
  fgets(buffer, BSIZE, stdin);
  sscanf(buffer, "%s %s", title, artist);
  return remove_by_song(list, artist, title);
}
