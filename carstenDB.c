#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() {
  printf("carstenDB > ");
}

// getline syntax: ssize_t getline(char **lineptr, size_t *n, FILE *stream);
void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  
  if(bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  
  input_buffer->input_length = bytes_read - 1;
  //strips the /n char added by getline()
  input_buffer->buffer[bytes_read - 1] = '\0';
}

// ensure no memory leaks
void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

// main loop: read-execute-print
int main(int argc, char* argv[]) {
  printf("carstenDB v1.0.0\n");

  InputBuffer* input_buffer = new_input_buffer();

  while(true) {
    print_prompt();
    read_input(input_buffer);

    if(strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'. \n", input_buffer->buffer);
    }
  }
}
