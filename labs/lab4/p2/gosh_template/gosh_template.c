#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <gosh.h>

extern int errno;

main() {

  int retval;
  
  struct command_t command_a;

  /* Problem 3
     retval = start_sig_catchers();
  */
	setvbuf(stdout, NULL, _IONBF, 0);
  while(1) {

    retval = init_command(&command_a);

    printf("gosh> ");


    retval = simple_accept_input(&command_a);

    print_command(&command_a, "c1");

    if (retval == 0) {      
	 simple_fork_command(&command_a);
    } else if (retval == 1) {
      exit(0);
    }
    
  }
  exit(0);
}

/* Helper Function.  Initialized a command_t struct */
int init_command(struct command_t *cmd) {
  cmd->num_args = 0;
  cmd->args[0] = NULL;
  cmd->outfile[0] = '\0';
  cmd->infile[0] = '\0';
  return(0);
}

/* Helper Function.  Print out relevent info stored in a command_t struct */
int print_command(struct command_t *cmd, const char *tag) {
  int i;
  
  for (i=0; i<cmd->num_args; i++) {
    printf("%s %d: %s\n", tag, i, cmd->args[i]);
  }

  if (cmd->outfile[0] != '\0') {
    printf("%s outfile: %s\n", tag, cmd->outfile);
  }

  if (cmd->infile[0] != '\0') {
    printf("%s infile: %s\n", tag, cmd->infile);
  }

  return(0);
}


/* Problem 1: read input from stdin and split it up by " " characters.
   Store the pieces in the passed in cmd_a->args[] array.  If the user
   inputs 'exit', return a 1.  If the user inputs nothing (\n), return
   a value > 1.  If the user inputs somthing else, return a 0. */
int simple_accept_input(struct command_t *cmd_a) {
	char *cmdline=(char *)malloc(200);
	
	memset(cmdline, 0, 200);
	read(0, cmdline, 200);
	
	if(strcmp(cmdline, "\n")==0)
		return 2;
	if(strcmp(cmdline, "exit\n")==0)
		return 1;

	char *token, *str= cmdline;
	while((token= strsep(&str, " "))){
		cmd_a->args[cmd_a->num_args]=token;
		cmd_a->num_args++;
	}

	if(cmd_a->num_args==0)
		return 0;
	cmd_a->args[cmd_a->num_args-1][strlen(cmd_a->args[cmd_a->num_args-1])-1]=0;
	return 0;
}

/* Problem 2: write a simple fork/exec/wait procedure that executes
   the command described in the passed in 'cmd' pointer. */
int simple_fork_command(struct command_t *cmd) {
 	if(cmd->num_args==0)
	      return 0;
	pid_t pid = fork();
	if(pid==0){
		execvp(cmd->args[0], cmd->args);
	}else{
		int stat_val;
		pid_t child_pid;

		child_pid=wait(&stat_val);
	}
	return 0;	
}

/* Problem 3: set up all of your signal actions here */
int start_sig_catchers(void) {
  return(0);
}
