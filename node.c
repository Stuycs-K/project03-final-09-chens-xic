#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "node.h"

struct song_node *createnode(char *artist, char *title, struct song_node *next) {
    struct song_node *x = malloc(sizeof(struct song_node));
    if (!x) return NULL;
    strcpy(x->artist, artist);
    strcpy(x->title, title);
    x->next = next;
    return x;
}
void print(struct song_node * m){
  //modified from original lab
    printf("%s by %s", m->title, m->artist);
}


void print_list(struct song_node *list) {
 //need to fix formatting
    printf("[");
    while (list->next != NULL) {
        printf(" {");
        print(list);
        printf("} |");
        list = list->next;
    }
    printf(" {");
    print(list);
    printf("} ]");
}

void print_playlist(struct song_node *list) {
  int i = 1;
  if (list == NULL){
    printf("Playlist is empty.\n");
  }
    while (list != NULL) {
        printf(" [%d] ", i);
        i++;
        print(list);
        printf("\n");
        list = list->next;
    }
}

struct song_node *insert_front(struct song_node *list, char *artist, char *title) {
    return createnode(artist, title, list);
}

struct song_node *free_list(struct song_node *list) {
    struct song_node *start = list;
    struct song_node *nextnode = list;
    while (list != NULL) {
        nextnode = list->next;
        free(list);
        list = nextnode;
    }
    return start;
}


struct song_node * find_artist(struct song_node * list, char *artist){
    while(list != NULL){
        if(strcmp(list->artist, artist) == 0){
            return list;
        }
        list = list->next;
    }
    return NULL;
}

struct song_node * find_song(struct song_node * list, char *artist, char *title){
    //printf("reached end of pass\n");
    while(list != NULL){
            if(strcmp(list->artist, artist) == 0 && strcmp(list->title, title) == 0){
                return list;
            }
        printf("reached end of pass\n");
        list = list->next;
    }



    return NULL;
}

int listSize(struct song_node *list){
    int count = 0;
    while(list != NULL){
        count += 1;
        list = list->next;
    }
    return count;
}

struct song_node * chooseRandom(struct song_node * list){
    // DON'T FORGET ABOUT EMPTY LISTS
    if (listSize(list) == 0){
        return NULL;
    } // can use this to check for empty buckets in library
    int index = rand() % (listSize(list));
    for(int i = 0; i < index; i++){
        list = list-> next;
    }
    return list;

}
// HELPER/DEBUGGING METHOD
int songIndex(struct song_node *list, char *artist, char *title){
    int count = 0;
    while(list != NULL){
            if(strcmp(list->artist, artist) == 0 && strcmp(list->title, title) == 0){
                return count;
            }
        count += 1;
        list = list->next;
    }
    return -1; //returns -1 if can't find
}

struct song_node * remove_node_by_index(struct song_node * list, int index){

    if(index < 0 || list == NULL){
        return list;
    }

    struct song_node * x;
    if(index == 0){
        x = list->next;
        free(list);
        return x;
    }
    struct song_node *start = list;
    for (int i = 0; i < index - 1; i++) {
        if (list == NULL || list->next == NULL) return start;
        list = list->next;
    }
    struct song_node *node_to_remove = list->next;
    if (node_to_remove == NULL) return start;
    list->next = node_to_remove->next;
    free(node_to_remove);
    return start;
}

int compare(struct song_node *a, struct song_node *b) {
    int artist_cmp = strcasecmp(a->artist, b->artist);
    if (artist_cmp != 0) return artist_cmp;
    return strcasecmp(a->title, b->title);
}

struct song_node *insert_alph(struct song_node *list, char *artist, char *title) {
    struct song_node *new = createnode(artist, title, NULL);
    if (!new) return list;
    if (!list || compare(new, list) < 0) {
        new->next = list;
        return new;
    }
    struct song_node *current = list;
    while (current->next && compare(current->next, new) < 0) {
        current = current->next;
    }
    new->next = current->next;
    current->next = new;
    return list;
}

struct song_node * remove_by_song(struct song_node *list, char *artist, char *title){
    return remove_node_by_index(list, songIndex(list, artist, title));
}
