#include <stdio.h>
//#include "someHeader.h"

void executableOnDisk(char someCommand);		    //execute command that is available on disk
void builtIn(char anotherCommand);		          //execute command that has been coded into shell
void errorInput();			                        //run if error detected


int main(){
	int continueMenu = 1; 			//function is for when true, continue to run program, else stop.
	

	while(continueMenu == 1){
		char selection = '';


		scanf("%f", &selection);
		getchar();					//strips off newline character
		if(selection == something){
			executableOnDisk(something);
		}
		else if(selection == something){
      builtIn(something);      
    }
    else if(selection == something){
      continueMenu = 0;      
    }
		else{ 								//test for invalid input
			errorInput();
		}
	}
	return 0;
};


void executableOnDisk(char someCommand);		    //execute command that is available on disk
void builtIn(char anotherCommand);		          //execute command that has been coded into shell
void errorInput();			                        //run if error detected
