#include <czmq.h>

zsock_t *sub;

void cleanup (int signum){
  printf ("\nCleaning up\n");
  zsock_destroy (&sub);
  exit (0);
}

int main (int argc, char *argv[]) {
 if (argc != 2) {
    printf ("Usage: echo <url>\n");
    return 0;
  }
  zsys_handler_set (NULL);
  signal (SIGINT, cleanup);

  zmsg_t *msg;
  struct timespec end;
  char *topic, *nanos, *frame;
  sub = zsock_new_sub (argv[1], "topic");     
  assert(sub);
  while (true) {
    int rc = zsock_recv (sub, "ssm", &topic, &nanos, &msg);
    assert(rc == 0);
    clock_gettime (CLOCK_MONOTONIC, &end);
    double start_time = atof(nanos);
    double end_time = (double)end.tv_sec + 1.0e-9*end.tv_nsec;
    printf("%f\n", (end_time - start_time) * 1000);   // ms
    while(frame = zmsg_popstr(msg)) {
      free(frame);
    }
    free(topic);
    zmsg_destroy(&msg);
  }
  return 0;
}
