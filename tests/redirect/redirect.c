#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

static char *mytee(int size) {
   int shmid = shmget(IPC_PRIVATE, size + 1, 0660 | IPC_CREAT);
   int pipe_fds[2];
   pipe(pipe_fds);

   switch (fork()) {
      case -1:                      // = error
         perror("fork");
         exit(EXIT_FAILURE);
      case 0: {                     // = child
         char *out = shmat(shmid, 0, 0), c;
         int i = 0;
         out[0] = 0;
         dup2(pipe_fds[0], 0);      // redirect pipe to child's stdin
         close(pipe_fds[0]);
         close(pipe_fds[1]);
         setvbuf(stdout, 0, _IONBF, 0);
         while (read(0, &c, 1) == 1 && i < size) {
            write(1, &c, 1);        // pass parent's stdout to real stdout,
            out[i++] = c;           // and then buffer in mycapture buffer
            out[i] = 0;             // (the extra <> are just for clarity)
         }
         _exit(EXIT_SUCCESS);
      }
      default:                      // = parent
         dup2(pipe_fds[1], 1);      // replace stdout with output to child
         close(pipe_fds[0]);
         close(pipe_fds[1]);
         setvbuf(stdout, 0, _IONBF, 0);
         return shmat(shmid, 0, 0); // return the child's capture buffer
   }
}

int main(void) {
   char *mycapture = mytee(100);    // capture first 100 bytes
   printf("Hello World");           // sample test string
   sleep(1);
   fprintf(stderr, "\nCaptured: <%s>\n", mycapture);
   return 0;
} 
