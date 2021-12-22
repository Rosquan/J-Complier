#include "token.h"

token* init_token() 
{
    //make sure you initialize char* in token. The length of str will be MAX_TOKEN_LENGTH
  
  token* new_token = malloc(sizeof(token)); // allocate memory for a token
  new_token -> str = (char*)malloc(sizeof(char) * MAX_TOKEN_LENGTH); // allocate memory for string in token
  return new_token; // Return allocated token
}

void delete_token(token* theToken)
{
    //make sure you delete char* in token
  
  free(theToken -> str); // free up string portion of token
  free(theToken); // free up token memory
}
