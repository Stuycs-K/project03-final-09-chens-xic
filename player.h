#ifndef player_h
#define player_h
//insert function headers here
void play(char *filename);
void store_song(char* title);
struct song_node * get_input(struct song_node * list);
void play_list(struct song_node *list);
#endif
