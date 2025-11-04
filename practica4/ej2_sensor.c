#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h> // For pid_t
#include <sys/stat.h>  // For mkfifo
#include <fcntl.h>     // For O_WRONLY

#define PIPE_NAME "/tmp/temp_pipe"
#define NSEC_PER_SEC 1000000000L

// Sleep until the next absolute time point
void sleep_until(struct timespec *next_release, long delay_ns)
{
  next_release->tv_nsec += delay_ns;
  while (next_release->tv_nsec >= NSEC_PER_SEC)
  {
    next_release->tv_nsec -= NSEC_PER_SEC;
    next_release->tv_sec++;
  }
  clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, next_release, NULL);
}

int main()
{
  FILE *file = fopen("sensor_data.txt", "r");
  if (!file)
  {
    perror("Error opening input file");
    return 1;
  }

  // Create the named pipe (FIFO)
  mkfifo(PIPE_NAME, 0666);
  
  // Open pipe for writing
  int pipe_fd = open(PIPE_NAME, O_WRONLY);
  if (pipe_fd == -1)
  {
    perror("Error opening the pipe for writing");
    fclose(file);
    return 1;
  }

  long delay_ns;
  float temperature;
  struct timespec next_release;

  // Initialize the reference time
  clock_gettime(CLOCK_MONOTONIC, &next_release);

  // Read each line: <delay_ns><tab><temperature>
  while (fscanf(file, "%ld\t%f", &delay_ns, &temperature) == 2)
  {
    sleep_until(&next_release, delay_ns);        // Wait the specified nanoseconds
    write(pipe_fd, &temperature, sizeof(float)); // Send temperature
    printf("Sent temperature: %.2f°C after %f secs\n", temperature, delay_ns / 1000000000.0);
    fflush(stdout);
  }

  printf("All data sent.\n");

  close(pipe_fd);
  fclose(file);
  unlink(PIPE_NAME);

  return 0;
}
