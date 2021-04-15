#include <stdio.h>
#include <czmq.h>

zsock_t *pub;

void cleanup (int signum){
  printf ("\nCleaning up\n");
  zsock_destroy (&pub);
  exit (0);
}

int main (int argc, char *argv[]) {
  if (argc != 4) {
    printf ("Usage: ping <url> <delay-ms> <msg-sz>\n");
    return 0;
  }
  int ms = atoi (argv[2]);
  int msg_sz = atoi (argv[3]);
  zsys_handler_set (NULL);
  signal (SIGINT, cleanup);

  struct timespec start, delay;
  char buf[100];
  delay.tv_sec = 0;
  delay.tv_nsec = ms * 1000 * 1000;
  char payload[msg_sz];
  for (int i = 0; i < msg_sz; i++) {
    payload[i] = '0' + rand() % 72;
  }
  payload[msg_sz] = '\0';
  pub = zsock_new_pub (argv[1]);     
  assert(pub);
  while (true) {
    clock_gettime (CLOCK_MONOTONIC, &start);
    double start_time = (double)start.tv_sec + 1.0e-9*start.tv_nsec;
    gcvt(start_time, 12, buf); 
    zsock_send (pub, "sss", "topic", buf, payload);
    nanosleep (&delay, NULL);
  }
  return 0;
}
