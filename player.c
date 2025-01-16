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


// plays a single song by using execvp and the mpg123 library(?)
void play(char *filename){
  char* args[4];
  char* program = "mpg123";
  args[0] = program;
  args[1] = "-q";
  args[2] = filename;
  args[3] = NULL;
  execvp(args[0], args);
}

// plays the playlist built from user input
void play_list(struct song_node *list){
  while (list != NULL) {
      pid_t p = fork();
      if (p<0){
        perror("Fork failed.\n");
        exit(1);
      }
      else if (p==0){
        char filename[BSIZE];
        sprintf(filename, "%s_by_%s.mp3", list->title, list->artist);
        printf("Now playing song %s...\n", filename);
        play(filename);
      }
      else{
        int status;
        pid_t child = wait(&status);
        if (child == -1) {
          perror("Wait failed.\n");
          exit(1);
        }
        if (WIFEXITED(status)){
          list = list->next;
        }
      }
  }
}

// keeps asking user to put one of the commands: play add remove(?) save(?) and calls following function
struct song_node * prompt_input(struct song_node *list){
  char buffer[BSIZE];
  printf("Input a command (play   add    show): ");
  fgets(buffer, BSIZE, stdin);
  if (!strcmp(buffer, "add\n")){
    return get_input(list);
  }
  else if (!strcmp(buffer, "play\n")){
    play_list(list);
  }
  else if (!strcmp(buffer, "show\n")){
    print_playlist(list);
  }
  else{
    printf("Please input a valid command.\n");
  }
  return list;
}

// takes a song_node pointer as parameter (list), reads user input and makes it into a song node, which is added to list
// user input should be in this format: song_name song_artist, song names and song artists should not have spaces
// input added to library or to list?
struct song_node * get_input(struct song_node * list){
  char buffer[BSIZE];
  char artist[BSIZE];
  char title[BSIZE];
  printf("Enter a song name and song artist in the format \"song_name song_artist\": ");
  // catch an error if song is not on playlist
  fgets(buffer, BSIZE, stdin);
  sscanf(buffer, "%s %s", title, artist);
  return insert_front(list,artist,title);
}

// stores song onto a file so user has a 'music history' file

// creates/opens backup file
// gets stat information of mp3
// append song name and stat info into one string
//write to file
void store_song(struct song_node * song){
  int fd = open("Backup", O_WRONLY | O_APPEND | O_CREAT, 0666);
  if(fd < 0) printf("%s\n", strerror(errno));


  //songPath = catPath("/MUSICFOLDER/", song_title); for when we move music into folder
  //struct dirent *entry;
  char artist[BSIZE];
  strcpy(song->artist, artist);
  char title[BSIZE];
  strcpy(song->title, title);
  char filename[BSIZE];
  sprintf(filename, "%s_by_%s.mp3", title, artist);

  struct stat * stat_buffer;
  stat_buffer = malloc(sizeof(struct stat));
  stat(filename, stat_buffer);
  printf("song size: %ld\n", stat_buffer->st_size);
  char buff[BSIZE];
  sprintf(buff, "%s ,%s ,%ld\n", title, artist, stat_buffer->st_size);

  printf("%s\n", buff);
  int bytesWritten = write(fd, buff, strlen(buff)+1);
  printf("bytes written: %d, sizeof buff: %ld\n", bytesWritten, sizeof(buff));

}


char* catPath(char *PATH, char *entryName){
    int size = strlen(PATH) + strlen(entryName);
    char str[size];
    char *buffer = str;
    strcpy(buffer, PATH);
    strncat(buffer, "/", strlen(buffer)+2);
    strncat(buffer, entryName, size+2);
  //printf("%s\n", buffer);
    return buffer;
}

//plays the user old list from backup file
// malloc new song_node list
// read from Backup, parse string into nodes and add to list
//call play_list with new list.
/*
void play_history(){
  struct song_node * list = NULL;
  int backup = open("Backup", O_RDONLY, 0666);
  char buff[100];

  int bytesRead;
  while(bytesRead = read(backup, buff, 100)){
    if(bytesRead == -1) printf("%s", strerror(errno));

    list = insert_front(list, artist, title);
  }
}
*/
