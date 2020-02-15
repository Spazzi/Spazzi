#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


//#include "someHeader.h"

void type_prompt();

void executableOnDisk(char cmd[], char *par[]); 	//execute command that is available on disk
//void builtIn(char anotherCommand);		//execute command that has been coded into shell


int main(){
	int continueMenu = 1; 			//function is for when true, continue to run program, else stop.
	
	char cmd[100], command[100], *parameters[20]; //environment variables
	
	char *envp[] = {(char *) "PATH=/bin", 0};

	while(1){
		type_prompt();
		
		executableOnDisk(command, parameters);

		
		if(fork() != 0){
			wait ( NULL)
		}
		else{
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execvpe(cmd, parameters, envp);
		}
		
		if(strcmp(command, "exit") == 0)
			break;
	}
	return 0;
};




void type_prompt(){ 				//clear screen for shell
	static int firstTime = 1;
	if(firstTime == 1){
		const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI,12);
		firstTime = 0;
	}
	printf("#");
}

void executableOnDisk(char cmd[], char *par[]){	//execute command that is available on disk
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;
	
	//read one line
	for(;;){
		int c = fgetc(stdin);
		line[count++] = (char) c;
		if(c == '\n')
			break;
	}
	if(count == 1)
		return;
	pch = strtok(line, "\n");
	
	//parse line into words
	while(pch!=NULL){
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}
	//first word is the command
	strcpy(cmd, array[0]);
	
	//others are parameters
	for(int j = 0; j<i; j++)
		par[j] = array[j];
	par[i] = NULL; //NULL to terminate the parameter list
}

//void builtIn(char anotherCommand);		//execute command that has been coded into shell

