#include <czmq.h>

zsock_t *rep;

void cleanup (int signum){
  printf ("\nCleaning up\n");
  zsock_destroy (&rep);
  exit (0);
}

int main (int argc, char *argv[]) {
 if (argc != 2) {
    printf ("Usage: echo <url>\n");
    return 0;
  }
  zsys_handler_set (NULL);
  signal (SIGINT, cleanup);
  rep = zsock_new_rep (argv[1]);     
  assert(rep);
  // zsock_set_affinity (rep, 1); // io thread cpu affinity
  // zsock_set_tos (rep, 0b00110000); // DSCP: priority, low latency
  while (true) {
    char *string = zstr_recv (rep);
    assert (string);
    int rc = zstr_send (rep, string);
    assert (rc == 0);
    zstr_free (&string);
   }
  return 0;
}
