#ifndef player_h
#define player_h
//insert function headers here
void play(char *filename);
void store_song(char *title, char *artist);
char* catPath(char *PATH, char *entryName);
struct song_node * get_input(struct song_node * list);
void play_list(struct song_node *list);
struct song_node * prompt_input(struct song_node *list);
void play_history(struct song_node * list);
#endif
