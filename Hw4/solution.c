
int CHILD = 0;
/* 
 * A function that executes a command using fork and execv
 */
void execute_plain(char *cmd, char *const argv[]) {
//   fprintf(stdout,"Error: %s() is not implemented!\n\n", __FUNCTION__);

  // WRITE CODE HERE
  pid_t pid;
  int status = 0;
  int error;

  pid = fork();

  /////////////
  // Child
  /////////////
  if (pid == CHILD){
      
      // Redirect STDERR
      freopen("/dev/null", "w", stderr);
      error = execv(cmd,argv);

      if(error == -1){
          exit(1);
      }

      exit(0);
  }

  //////////
  // Parent
  //////////
  else{
      // wait child
      wait(&status);

      // if child ended fine, status should be 0, else STDERR.
      if(status == 0){
          printf("  ** Command successful  **\n");
      }
      // else, if error STDERR
      else{
          printf(" ** Command failed  **\n");
      }

  }
}

/* 
 * A function that executes a command using fork and execv, but
 * that redirects the command's output to a file
 */
void execute_output_to_file(char *cmd, char *const argv[], char *filename) {
//  fprintf(stdout,"Error: %s() is not implemented!\n\n", __FUNCTION__);

  // WRITE CODE HERE
  pid_t pid;
  int status = 0;
  int error;


  pid = fork();

  /////////////
  // Child
  /////////////
  if (pid == CHILD){

	// Open file /tmp/stuff, which will be assigned file descriptor 1
    FILE *file = fopen(filename, "w");
	if (!file) {
		exit(1);
	}

      // close pipe
      close(1);
      dup(fileno(file));
      // Redirect STDERR
      freopen("/dev/null", "w", stderr);
      error = execv(cmd,argv);

      if(error == -1){
          exit(1);
      }

      exit(0);
  }

  //////////
  // Parent
  //////////
  else{
      // wait child
      wait(&status);

      // if child ended fine, status should be 0, else STDERR.
      if(status == 0){
          printf("  ** Command successful  **\n");
      }
      // else, if error STDERR
      else{
          printf(" ** Command failed  **\n");
      }

  }
}

/* 
 * A function that executes a command using fork and execv, but
 * that redirects the command's output to another command
 */
void execute_output_to_other(char *cmd1, char *const argv1[], char *cmd2_with_argv2) {
//   fprintf(stdout,"Error: %s() is not implemented!\n\n", __FUNCTION__);

  // WRITE CODE HERE
  pid_t pid;
  int status = 0;
  int error;


FILE * file = popen(cmd2_with_argv2, "w");

  pid = fork();

  /////////////
  // Child
  /////////////
  if (pid == CHILD){
      
      // close pipe
      close(1);
      dup(fileno(file));
      // Redirect STDERR
      freopen("/dev/null", "w", stderr);
      error = execv(cmd1, argv1);


      if(error == -1){
          exit(1);
      }

      exit(0);
  }

  //////////
  // Parent
  //////////
  else{
      // wait child
      wait(&status);
      // if child ended fine, status should be 0, else STDERR.
      if(status == 0){
          printf("  ** Command successful  **\n");
      }
      // else, if error STDERR
      else{
          printf(" ** Command failed  **\n");
      }

  }

   pclose(file);

}


