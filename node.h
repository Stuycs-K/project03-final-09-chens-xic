#ifndef NODE_H
#define NODE_H

struct song_node {char artist[100]; char title[100]; struct song_node *next;};

void print(struct song_node * m);
struct song_node* createnode(char *artist, char *title, struct song_node *next);

void print_list(struct song_node *list);
void print_playlist(struct song_node *list);
struct song_node * insert_front(struct song_node * list, char *artist, char* title);
struct song_node * free_list(struct song_node * list);
struct song_node * remove_node_by_index(struct song_node * list, int index);
struct song_node * find_artist(struct song_node * list, char *artist);
struct song_node * find_song(struct song_node * list, char *artist, char *title);
int listSize(struct song_node *list);
struct song_node * chooseRandom(struct song_node * list);
struct song_node * remove_by_song(struct song_node *list, char *artist, char *title);
int songIndex(struct song_node *list, char *artist, char *title);
int compare(struct song_node *a, struct song_node *b);
struct song_node *insert_alph(struct song_node *list, char *artist, char *title);


#endif
