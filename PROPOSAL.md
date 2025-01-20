# Final Project Proposal

## Group Members:

Cathleen and Stacey

# Intentions:

Our project will expand upon the previous music library project to include features that will play music and directly interact with music files. 	

# Intended usage:

The terminal will continuously prompt the user to input one of the following commands: play, add, show, remove, or history. Typing 'add' will show a list of mp3 files included in our song library and prompt the user to input a song title followed by a song artist. Currently, our program only supports one word song titles and one word artist names. Upon entering an entry, this song will be added to beginning of the current playlist and the terminal will prompt the user for another command. Remove will operate in a similar fashion, but with the song entry being removed. Typing 'show' will print the current playlist and typing 'play' will play the current playlist. The user can also press the 'q' key on their keyboard to skip a song(feature from mpg123) while the playlist is playing. Each song that the user plays will be stored on to a user history file. The program will end when the user hits ctrl c. When the program restarts, the user has the option to play their previous songs saved on the file by typing 'history'.

# Technical Details:

This project will be using many of the topics we covered in class, such as processes. We will fork and exec 'mpg123' to play music as well as 'ls' to display the valid song files, and use stat to find information about the files (such file size). The user’s song lists and information about each song will be stored as text on files. We will interact with this file to allow the user to listen to their previous playlists. Additionally, we will allocate memory to store our playlist and information about the music files. Finally, we also used signals to print out a message and free memory once the user hits ctrl c. The user will have to install mpg123. We used array/linked lists to store the playlist and we used structs to store information about singular songs.

Breakdown:
- reconstruct and optimize music library - all
- find music player and integrate with program - all
- gather song files - all
- store user and song data on files - Cathleen
- play previous playlist from file (history function) - Cathleen
- add/remove song function - Stacey
- show function - Stacey
- play song/playlist function - Stacey
- prompt_input function to receive player input and call according command - all

# Intended pacing:

A timeline with expected completion dates of parts of the project.

1/7 - reconstruct and optimize music library, set up files

1/8 - find music player and integrate with program

1/13 - get most of the basic functions to work (play/add/show/remove/history), finish minimum viable product

1/15 - work on linking all of the functions together (prompt_input function)

1/17 - final debugging

1/19 - complete video
