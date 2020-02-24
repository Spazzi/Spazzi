#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLINESIZE 1024
#define STPTKNREAD " \t\r\n\a"

char *readLine(void){

	int size = MAXLINESIZE;
	int count = 0;
	char *buffer = malloc(sizeof(char) * size);
	int c;

	if(!buffer){
		fprintf(stderr, "Memory error\n");
		exit(EXIT_FAILURE);
	}

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


char **makeTokens(char *line){
	
	int size = 64;
	int count = 0;
	char **tokens = malloc(size * sizeof(char*));
	char *token;

	if(!tokens){
		fprintf(stderr, "Memory error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, STPTKNREAD);	
	while(token != NULL){
		tokens[count] = token;
		count++;
		token = strtok(NULL, STPTKNREAD);
	}

	tokens[count] = NULL;
	return tokens;
}

int cd(char *path){
	return chdir(path);
}


int runCmd(char **args){
	
	pid_t pid;
	int status;

	if(args[0] == NULL){
		return 1;
	}
	
	if(strcmp(args[0], "exit") == 0){
		return 0;
	}

	if(strcmp(args[0], "cd") == 0){
		if (cd(args[1]) == -1){
			perror(args[1]);
		}
	}
	if(strcmp(args[0], "cd") !=0){
		pid = fork();
		if(pid == 0){
			if(execvp(args[0], args) == -1){
				perror("Error");
			}
			exit(EXIT_FAILURE);
		}else if(pid < 0){
			perror("Error forking");
		}else{
			do{
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

	printf("\033[H\033[J");

	printf("Welcome to Evan and Liam's shell.\n");
	printf("Type exit to end the shell\n");

	do{
		printf("# ");
		line = readLine();
		args = makeTokens(line);
		status = runCmd(args);

		free(line);
		free(args);

	}while(status);
}
