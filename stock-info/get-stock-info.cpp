
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char* getStockPrice(char* ticker) {
  // Create a pipe to redirect the output of the command to the calling process
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    return 1;
  }

  // Fork the current process
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    // Child process: execute the command

    // Close the reading end of the pipe
    close(pipefd[0]);

    // Redirect the output of the command to the writing end of the pipe
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
      perror("dup2");
      return 1;
    }

    // Execute the command
    char *const cmd[] = {"ls", "-l", NULL};
    execvp(cmd[0], cmd);

    // execvp only returns on error
    perror("execvp");
    return 1;
  } else {
    // Parent process: read the output of the command from the pipe

    // Close the writing end of the pipe
    close(pipefd[1]);

    // Read the output of the command from the pipe
    char buf[1024];
    ssize_t n;
    while ((n = read(pipefd[0], buf, sizeof(buf))) > 0) {
	//TODO Parse stock price.
    }
    if (n == -1) {
      perror("read");
      return 1;
    }

    // Wait for the child process to exit
    int status;
    if (waitpid(pid, &status, 0) == -1) {
      perror("waitpid");
      return 1;
    }

    return 0;
  }
}
