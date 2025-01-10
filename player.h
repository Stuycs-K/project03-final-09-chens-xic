#ifndef player_h
#define player_h
//insert function headers here
void add_song(char* title);
void play(char *filename);
void store_song(char* title);
void parse(char * playlist, char** dest);
struct song_node get_input();
#endif
