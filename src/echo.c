#include <czmq.h>

zsock_t *rep;

void cleanup (int signum){
  printf ("\nCleaning up\n");
  zsock_destroy (&rep);
  exit (0);
}

int main (void) {
  zsys_handler_set (NULL);
  signal (SIGINT, cleanup);
  rep = zsock_new_rep ("tcp://*:5555");      // rep -> bind
  zsock_set_affinity (rep, 1); // io thread cpu affinity
  zsock_set_tos (rep, 0b00110000); // DSCP: priority, low latency
  while (true) {
    char *string = zstr_recv (rep);
    zstr_send (rep, string);
    zstr_free (&string);
   }
  return 0;
}