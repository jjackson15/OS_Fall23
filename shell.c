#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[1000] = "> ";
char delimiters[] = " \t\r\n=";
extern char **environ;

int x;
pid_t pid;
bool background = false;
int satus;

void signal_handler(int signo) {
    if (signo == SIGINT) {
			printf("\n");
    }
}

void kill_process(pid_t pid){
	kill(pid, SIGTERM);
  printf("Process terminated: Execution time exceeded the limit.\n");
}

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  	signal(SIGINT, signal_handler);
		signal(SIGALRM, kill_process);
		alarm(10);
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    	
    while (true) {
        do{ 
            // Print the shell prompt.
		if (getcwd(prompt, sizeof(prompt))==NULL){
			perror("error: getcwd");
			exit(0);
		}
		printf("%s> ", prompt);
	        fflush(stdout);
		if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
			fprintf(stderr, "fgets error");
	                exit(0);
	            }

        }while(command_line[0] == 0x0A);  // while just ENTER pressed
	    if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }
	    arguments[0] = strtok(command_line, delimiters);
	    x = 0;
	    while(arguments[x] != NULL){
		    x++;
		    arguments[x] = strtok(NULL, delimiters);
	}
	    if(strcmp(arguments[0], "cd") == 0) {
		    chdir(arguments[1]);
	} 
	    else if (strcmp(arguments[0], "pwd") == 0) {
	            printf("%s\n", prompt);
	} 
	    else if (strcmp(arguments[0], "echo") == 0) {
		    int i;
		    i = 1;
		    while (arguments[i] != NULL){
			    if (arguments[i][0] == '$'){
				    printf("%s", getenv(arguments[i]+1));
			}
			    else{
				    printf("%s ", arguments[i]);
			}
			    i++;
		}
		    printf("\n");
	}
	    else if (strcmp(arguments[0], "exit") == 0){
		    exit(0);
	}
	    else if (strcmp(arguments[0], "env") == 0){
		    if (arguments[1] != NULL){
		    char **env = environ;
		    for(x = 0; env[x] != NULL; x++) {
			    char *variable = strtok(env[x], delimiters);
			    if(strncmp(variable, arguments[1], strlen(arguments[1])) == 0){
				    printf("%s\n", strtok(NULL, ""));
			}
			}
			}
		    else{
			    for(x = 0; environ[x] != NULL; x++) {
				    printf("%s\n", environ[x]);
			}
				}
		}
		    else if (strcmp(arguments[0], "setenv") == 0){
			    int x;
			    x = 0;
			    if (arguments[x+1] != NULL && arguments[x+2] != NULL){
				    if (setenv(arguments[x+1], arguments[x+2], 1) != 0){
					perror("setenv");
				} 
				    else {
					    printf("Variable set successfully!\n");
			}
			}
			    else {
				    printf("Missing arguments.\n");
			}
			}
		    else{
			    pid_t  pid1 = fork();
			    if (pid1 == 0){
				    execvp(arguments[0], arguments);
				    perror("execvp");
				    exit(1);
			}
			    else if (pid1 > 0) {
				    int status;
				    wait(&status);
			}
			    else{
				    if(background == false) {
					    wait(NULL);
				}
			}
	}
		}
    return -1;
}
