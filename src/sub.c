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
  char *topic;
  char *frame;
  zmsg_t *msg;
  sub = zsock_new_sub (argv[1], "topic");     
  assert(sub);
  // zsock_set_affinity (rep, 1); // io thread cpu affinity
  // zsock_set_tos (rep, 0b00110000); // DSCP: priority, low latency
  while (true) {
    int rc = zsock_recv (sub, "sm", &topic, &msg);
    assert(rc == 0);
    while(frame = zmsg_popstr(msg)) {
      printf("> %s", frame);
      free(frame);
    }
    printf("\n");
    free(topic);
    zmsg_destroy(&msg);
  }
  return 0;
}
