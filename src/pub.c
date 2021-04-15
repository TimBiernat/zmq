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

  struct timespec start, end, delay;
  delay.tv_sec = 0;
  delay.tv_nsec = ms * 1000 * 1000;
  char payload[msg_sz];
  for (int i = 0; i < msg_sz; i++) {
    payload[i] = '0' + rand() % 72;
  }
  payload[msg_sz] = '\0';
  pub = zsock_new_pub (argv[1]);     
  assert(pub);
  // zsock_set_affinity (pub, 1); // io thread cpu affinity
  // zsock_set_tos (pub, 0b00110000); // DSCP: priority, low latency
  while (true) {
    zsock_send (pub, "ss", "topic", payload);
    nanosleep (&delay, NULL);
  }
  return 0;
}
