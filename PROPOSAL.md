# Final Project Proposal

## Group Members:

Cathleen and Stacey

# Intentions:

Our project will expand upon the previous music library project to include features that will play music and directly interact with music files. 	

# Intended usage:

The terminal will continuously prompt the user to input one of the following commands: play, add, or show. Typing 'add' will prompt the user to input a song title followed by a song artist. Currently, our program only supports one word song titles and one word artist names. Upon entering an entry, this song will be added to beginning of the current playlist and the terminal will prompt the user for another command. Typing 'show' will print the current playlist and typing 'play' will play the current playlist. Each song that the user plays will be stored on to a user history file. The program will end when the user hits ctrl c.When the program restarts, the user has the option to play their previous songs saved on the file.

# Technical Details:

This project will be using many of the topics we covered in class, such as processes. We will fork and exec to play music, and use stat to find information about the files (such file size). The user’s song lists and information about each song will be stored as text on files. The user will have to install mpg123.
Nice to Have features:

-Pause song

-Skip song

# Intended pacing:

A timeline with expected completion dates of parts of the project.

1/7 - reconstruct and optimize music library

1/9 - find music player and integrate with program

1/13 - store user and song data on files, finish minimum viable product
