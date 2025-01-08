#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "node.h"
#include "library.h"

struct song_node **init() {
    struct song_node **library = malloc(27 * sizeof(struct song_node *));
    for (int i = 0; i < 27; i++) {
        library[i] = NULL;
    }
    return library;
}

void add(struct song_node **library, char *artist, char *title) {
    int index;
    if (artist[0] >= 'A' && artist[0] <= 'Z') {
        index = artist[0] - 'A';
    } else {
        index = 26; // For non-letter artists
    }
    library[index] = insert_alph(library[index], artist, title);
}

struct song_node *search_song(struct song_node **library, char *artist, char *title) {
    int index;
    if (artist[0] >= 'A' && artist[0] <= 'Z') {
        index = artist[0] - 'A';
    } else {
        index = 26; // For non-letter artists
    }
    return find_song(library[index], artist, title);
}

struct song_node *search_artist(struct song_node **library, char *artist) {
    int index;
    if (artist[0] >= 'A' && artist[0] <= 'Z') {
        index = artist[0] - 'A';
    } else {
        index = 26; // For non-letter artists
    }
    return find_artist(library[index], artist);
}

void print_letter(struct song_node **library, char letter) {
    int index = (letter >= 'A' && letter <= 'Z') ? letter - 'A' : 26;
    print_list(library[index]);
}

void print_artist(struct song_node ** library, char* artist){
    struct song_node * singer = search_artist(library, artist);
    if(singer ==NULL) return;
    printf("[");

    while(singer != NULL){
        if(strcmp(singer->artist, artist) == 0){

            printf(" {");
            print(singer);
            printf("} ");

            singer = singer->next;

            if(singer != NULL){
                if(strcmp(singer->artist, artist) == 0) printf("|");
            }
            continue;
            //printf("reaches end of pass\n");
        }
        singer = singer->next;

    }
    printf("]");
}

void print_library(struct song_node ** library){
    for(int i = 0; i< 27; i++){
        if (listSize(*(library+i)) != 0) {
            if(i != 26) printf("%c: ", i+65);
          print_letter(library, i + 65);
           printf("\n");

        }
    }
}



//HELPER
int numFilled(struct song_node ** library){
    struct song_node * curr;
    int size = 0;  // need to take care of none filled


    for(int i = 0; i<27;i++){
        curr = *(library + i);
        if (listSize(curr) != 0) size += 1;
    }
    return size;
}
int *filledSlots(struct song_node ** library){
    struct song_node * curr;
    int size = numFilled(library);

    int * indices = malloc(size*sizeof(int));
    if(indices == NULL) return NULL; // figure out what do

    int count = 0;
    for(int i = 0; i<27;i++){
        curr = *(library + i);
        if(listSize(curr) != 0){
            *(indices + count) = i;
            count += 1;
        }
    }

    return indices;
}
void shuffle (struct song_node ** library, int n){
    srand(time(NULL));
    int ind;
    int indX;
    int *validind = filledSlots(library);
    struct song_node * chosen;
    for(int i = 0; i<n; i++){
        if(validind != NULL){
            indX = rand() % (numFilled(library));
            ind = *(validind+indX);
            chosen = chooseRandom(*(library+ind));
            printf("{");
            print(chosen);
            printf("}\n");
        }
    }
    free(validind);
}
int delete_song(struct song_node ** library, char* artist, char* title ){
    if (search_song(library, artist, title) == NULL){
        return 1;
    }
    int index;
    if (artist[0] >= 'A' && artist[0] <= 'Z') {
        index = artist[0] - 'A';
    } else {
        index = 26; // For non-letter artists
    }
    library[index] = remove_by_song(library[index], artist, title);
    return 0;
}

void reset(struct song_node ** library){
    for(int i = 0; i< 27; i++){
        if(library[i] != NULL) {
            free_list(library[i]);
            //printf("just freed %d", i);
        }
    }
    free(library);
}
