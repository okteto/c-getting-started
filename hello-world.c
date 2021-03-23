/**
 * hello-world.c
 * Small Hello World! Example based on the getting started example at https://github.com/babelouest/ulfius
 * gcc -o hello-world hello-world.c -lulfius
 */
#include <signal.h>
#include <stdio.h>
#include <ulfius.h>

#define PORT 8080

volatile sig_atomic_t sigint_received = 0;

void sigint_handler(int s) {
    sigint_received = 1;
}

int callback_hello_world (const struct _u_request * request, struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 200, "Hello World!");
  return U_CALLBACK_CONTINUE;
}

int callback_healthz (const struct _u_request * request, struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 200, "ok");
  return U_CALLBACK_CONTINUE;
}

/**
 * main function
 */
int main(void) {
  setbuf(stdout, NULL);
  
  struct _u_instance instance;

  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return 1;
  }

  ulfius_add_endpoint_by_val(&instance, "GET", "/", NULL, 0, &callback_hello_world, NULL);
  ulfius_add_endpoint_by_val(&instance, "GET", "/healthz", NULL, 0, &callback_healthz, NULL);

  if (ulfius_start_framework(&instance) == U_OK) {
    printf("Starting hello-world server on port %d\n", instance.port);
    printf("press ctrl+c to exit...\n");
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    while (!sigint_received) {}
    printf("SIGINT received, exiting...\n");
  } else {
    fprintf(stderr, "Error starting server\n");
    return 1;
  }
  
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
  printf("bye\n");
  return 0;
}