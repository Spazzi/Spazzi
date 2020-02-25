Liam Olson (olso6996@umn.edu)
Evan Skaar (skaar097@umn.edu)

This program recreates a shell by altering the interface to appear as a shell would. Input given by the user is broken into commands via entering the commands into an array, which is later broken down and interpreted as commands and arguments. This program uses fork() to produce new parallel executions and strtok() to maneuver through this list in order to execute. Integrated commands are simply hardcoded versions of commands a user would enter. Finally, clone is used to produce child shells that execute much the same as the parent.
