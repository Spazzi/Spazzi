#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


//#include "someHeader.h"

void type_prompt();

void executableOnDisk(char someCommand); 	//execute command that is available on disk
void builtIn(char anotherCommand);		//execute command that has been coded into shell
void errorInput();			    	//run if error detected


int main(){
	int continueMenu = 1; 			//function is for when true, continue to run program, else stop.
	
	char cmd[100], command[100], *parameters[20]; //environment variables

	while(continueMenu == 1){
		type_prompt();
		
		read_command(command, parameters);


		scanf("%s", &selection);
		getchar();			//strips off newline character
		
		if(selection == something){
			executableOnDisk(something);
		}
		else if(selection == something){
			builtIn(something);      
		}
		else if(selection == something){
			continueMenu = 0;      
		 }
		else{ 				//test for invalid input
			errorInput();
		}
	}
	return 0;
};


void executableOnDisk(char someCommand); 	//execute command that is available on disk
void builtIn(char anotherCommand);		//execute command that has been coded into shell
void errorInput(){			        //run if error detected
	fprintf("Invalid input.\n");
}

void type_prompt(){
	static int firstTime = 1;
	if(firstTime == 1){
		const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI,12);
		firstTime = 0;
	}
	printf("#");
}
