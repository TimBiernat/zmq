#include <czmq.h>

zsock_t *req;

void cleanup (int signum) {
  printf ("\nCleaning up\n");
  zsock_destroy (&req);
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
  req = zsock_new_req (argv[1]); // req -> connect
  assert(req);
  // zsock_set_affinity (req, 1); // io thread cpu affinity
  // zsock_set_tos (req, 0b00110000); // DSCP priority, low latency
  while(true) {
    clock_gettime (CLOCK_MONOTONIC, &start);
    zstr_send (req, payload);
    char *string = zstr_recv (req);
    assert (string);
    clock_gettime (CLOCK_MONOTONIC, &end);
    int result = strcmp (payload, string);
    zstr_free (&string);
    if (result) {
      printf (">>>>FAIL<<<<");
      cleanup (0);
    } else {
      double start_time = (double)start.tv_sec + 1.0e-9*start.tv_nsec;
      double end_time = (double)end.tv_sec + 1.0e-9*end.tv_nsec;
      printf ("%5.3f\n", (end_time - start_time)*1000);  // ms
    }
    nanosleep (&delay, NULL);
  }
  return 0;
}
