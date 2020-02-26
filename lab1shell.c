#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLINESIZE 1024
#define STPTKNREAD " \t\r\n\a"

/*Function for reading the input line for the shell*/

char *readLine(void){

	int size = MAXLINESIZE;
	int count = 0;
	char *buffer = malloc(sizeof(char) * size); //Allocate memory for the line to be interated through
	int c;

	if(!buffer){
		fprintf(stderr, "Memory error\n");
		exit(EXIT_FAILURE);
	}
	
	/*loop for iterating through the line.
	If end of file is found, exits shell.
	If the current character = new line, return the buffer to main
	Else current buffer position becomes c (current character in the IO)
	*/
	
	while(1){

		c = getchar();

		if(c == EOF){
			exit(EXIT_SUCCESS);
		}else if(c == '\n'){
			buffer[count] = '\0';
			return buffer;
		}else{
			buffer[count] = c;
		}

		count++;
	}
}

/*Function for parsing the line into tokens.
Allows command to be read with arguments*/

char **makeTokens(char *line){
	
	int size = 64;
	int count = 0;
	char **tokens = malloc(size * sizeof(char*)); //Allocates memory for tokens
	char *token;

	if(!tokens){
		fprintf(stderr, "Memory error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, STPTKNREAD); //Reads the line until one of the predefined stoping points is met
	//Loop reads the line, putting cmd into token[0] and args into token[2]
	while(token != NULL){
		tokens[count] = token;
		count++;
		token = strtok(NULL, STPTKNREAD);
	}

	tokens[count] = NULL;
	return tokens; //returns tokens to main to be passed to the runCmd function
}

/*Builtin function for cd.
Takes the arg after cd as the path*/ 

int cd(char *path){
	return chdir(path);
}

/*Function for executing the cmd put into the shell*/

int runCmd(char **args){
	
	pid_t pid; //PID of the process spawned from fork
	int status;
	
	//If args is empty, continue to main loop
	if(args[0] == NULL){
		return 1;
	}
	//If args and exit are equal, end the shell
	if(strcmp(args[0], "exit") == 0){
		return 0;
	}
	//If args and cd are equal, use builtin cd function
	if(strcmp(args[0], "cd") == 0){
		if (cd(args[1]) == -1){
			perror(args[1]);
		}
	}
	//If args is not cd, call fork to start a child process
	if(strcmp(args[0], "cd") !=0){
		pid = fork();
		if(pid == 0){
			if(execvp(args[0], args) == -1){ //Executes the cmd given in the shell, with arguments
				perror("Error");
			}
			exit(EXIT_FAILURE);
		}else if(pid < 0){
			perror("Error forking");
		}else{
			do{ //Causes shell to wait for the child to finish before continuing with parent processes
				waitpid(pid, &status, WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return 1;

}
	


int main(int arc, char **argv){

	char *line;
	char **args;
	int status;

	printf("\033[H\033[J"); //Clear screen on shell start

	printf("Welcome to Evan and Liam's shell.\n");
	printf("Type exit to end the shell\n");

	//Main shell loop
	do{
		printf("# ");
		line = readLine(); //Read the input line
		args = makeTokens(line); //Break line into tokens
		status = runCmd(args); //Run the cmd from the tokens that were made

		free(line); //free memory allocated for the input line
		free(args); //free memory allocated for tokens

	}while(status);
}
