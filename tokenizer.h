#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include "hash.h"
#include <string.h>
#include <ctype.h>

//helper functions (implement these)

int stack_pos;
// Parse token to populate
void parse_token (token* theToken, char* tok);

int max_if;
int final_if;
int max_pow;
int max_cmp;
int max_min;
int max_abs;
int in_defun;
int offset;
// Write assembly for current token
void write_assembly (token* theToken, FILE* asm_file, char* filename, hash_struct* LOOPS);

//theToken is the token to be populated
void read_token (FILE* j_file, FILE* asm_file, char* filename);

//used for debugging
void print_token (token *theToken);

#endif
