#include "hash.h"
#include "tokenizer.h"


int main(int argc, char *argv[]) 
{
  FILE* input_file;
  FILE* asm_file;
  char* filename;
  char* asm_string;
  
  if (argc < 4) { // both asm filename and j filename not written
    fprintf(stderr, "error 1: <filename.asm> <filename.j> <filename> does not exist\n");
    return -1;
  }

  input_file = fopen(argv[2], "r"); // open file in read
  if (input_file == NULL) {
    fprintf(stderr, "error 2: error reading <filename.j>\n");
    fclose(input_file);
    return -1; // -1 corresponds to error
  }
  
  asm_file = fopen(argv[1], "w"); // open file in write
  if (asm_file == NULL) {
    fprintf(stderr, "error 2: error reading <filename.asm>\n");
    fclose(asm_file);
    return -1; // -1 corresponds to error
  }  
  
  filename = argv[3];
  
  printf("%s\n", filename);
  
  read_token(input_file, asm_file, filename); // read/output first line of tokens
  
  fclose(input_file); // close j file
  fclose(asm_file); // close asm file
  
  return 0;
}
