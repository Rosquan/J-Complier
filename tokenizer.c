#include "tokenizer.h"


//theToken is the token to be populated
void read_token (FILE* j_file, FILE* asm_file, char* filename) {
  char* tok; // store current token
  char line[MAX_TOKEN_LENGTH]; // store current line
  
  token* theToken = init_token(); // Initialize token
  theToken -> type = EMPTY; // Initialize as empty
  strcpy(theToken -> str, ""); // Initialize as empty
  theToken -> literal_value = 0; // Initialize as 0
  theToken -> arg_no = 0; // Initialize as 0
  hash_struct* LOOPS = initTable(100); // Initialize hash table of size 100
  
  while (1) { // until end of file
    
    if (feof(j_file)) { 
      break; 
    } // break at end of file
    
    while(1) {
      if (fgets(line, MAX_TOKEN_LENGTH, j_file) == NULL) {

        fprintf(stderr, "Error: No more tokens to read\n");
        return;

      } else { // parse to find token type

        //if (isspace(line[0])) { continue; } // Empty Line

        tok = strtok(line, " \t\n"); // separate token based on either space or newline

        if (tok == NULL) { continue; } // Empty line
        if (tok[0] == ';') { continue; } // End of line

        parse_token(theToken, tok);
        write_assembly(theToken, asm_file, filename, LOOPS);
        break;
      }

    }
  
    while(1) {
      tok = strtok(NULL, " \t\n");
      if (tok == NULL || tok[0] == ';') { break; } // End of line

      parse_token(theToken, tok);
      write_assembly(theToken, asm_file, filename, LOOPS);

    }
  }
  
  delete_token(theToken); // delete_token
  done(LOOPS); // finished with LOOPS hash_struct
    
  }
  
//used for debugging
void print_token (token* theToken) {
  
  char* token; // store token
  
  switch (theToken -> type) {
      
    case(DEFUN): token = "DEFUN";
      break;
      
    case(IDENT): token = "IDENT";
      break;
      
    case(RETURN): token = "RETURN";
      break;
      
    case(PLUS): token = "PLUS";
      break;
      
    case(MINUS): token = "MINUS";
      break;

    case(MUL): token = "MUL";
      break;

    case(DIV): token = "DIV";
      break;

    case(MOD): token = "MOD";
      break;

    case(AND): token = "AND";
      break;

    case(OR): token = "OR";
      break;

    case(NOT): token = "NOT";
      break;

    case(LT): token = "LT";
      break;

    case(LE): token = "LE";
      break;

    case(EQ): token = "EQ";
      break;

    case(GE): token = "GE";
      break;

    case(GT): token = "GT";
      break;

    case(IF): token = "IF";
      break;

    case(ELSE): token = "ELSE";
      break;

    case(ENDIF): token = "ENDIF";
      break;

    case(DROP): token = "DROP";
      break;

    case(DUP): token = "DUP";
      break;

    case(SWAP): token = "SWAP";
      break;

    case(ARG): token = "ARG";
      break;

    case(ABS): token = "ABS";
      break;

    case(POW): token = "POW";
      break;

    case(LITERAL): token = "LITERAL";
      break;

    case(XOR): token = "XOR";
      break;

    case(MIN): token = "MIN";
      break;

    case(AVG): token = "AVG";
      break;

    case(BROKEN_TOKEN): token = "BROKEN_TOKEN";
      break;

    case(EMPTY): token = "EMPTY";
      break;
      
  }
  
  printf("Type: %s, Literal: %d, Arg: %d, String: %s\n",
         token, theToken -> literal_value, theToken -> arg_no, theToken -> str);
}

void parse_token(token* theToken, char* tok) {
  int value; // store literal value
  
  if (tok[0] == '-' && isdigit(tok[1])) { // - literal

    theToken -> type = LITERAL; // literal type
    
    sscanf(tok, "-%d", &value); // store decimal in value
    
    theToken -> literal_value = value; // value of literal
    
  } else if (isdigit(tok[0])) { // decimal format

    theToken -> type = LITERAL; // literal type
    
    sscanf(tok, "%d", &value); // store decimal in value
    
    theToken -> literal_value = value; // value of literal
    
  } else if (tok[0] == '0' && tok[1] == 'x') { // hex format

    theToken -> type = LITERAL; // literal type

    sscanf(tok, "0x%x", &value); // store decimal in value

    theToken -> literal_value = value; // value of literal
    
  } else if (strcmp(tok, "-") == 0) { // sub operation

    theToken -> type = MINUS; // minus type
    
  } else if (strcmp(tok, "+") == 0) { // add operation

    theToken -> type = PLUS; // plus type
    
  } else if (strcmp(tok, "*") == 0) { // mul operation

    theToken -> type = MUL; // mul type
    
  } else if (strcmp(tok, "/") == 0) { // div operation

    theToken -> type = DIV; // div type
    
  } else if (strcmp(tok, "%") == 0) { // mod operation

    theToken -> type = MOD; // mod type
    
  } else if (strcmp(tok, "^") == 0) { // exponent operation

    theToken -> type = POW; // pow type
    
  } else if (strcmp(tok, "lt") == 0) { // less than operation

    theToken -> type = LT; // lt type
    
  } else if (strcmp(tok, "le") == 0) { // less than or equal to operation

    theToken -> type = LE; // le type
    
  } else if (strcmp(tok, "eq") == 0) { // equal to operation

    theToken -> type = EQ; // EQ type
    
  } else if (strcmp(tok, "ge") == 0) { // greater than or equal to operation

    theToken -> type = GE; // GE type
    
  } else if (strcmp(tok, "gt") == 0) { // greater than operation

    theToken -> type = GT; // GT type
    
  } else if (strcmp(tok, "and") == 0) { // and operation

    theToken -> type = AND; // and type
    
  } else if (strcmp(tok, "or") == 0) { // or operation

    theToken -> type = OR; // or type
    
  } else if (strcmp(tok, "not") == 0) { // not operation

    theToken -> type = NOT; // not type

  } else if (strcmp(tok, "xor") == 0) { // xor operation

    theToken -> type = XOR; // xor type
    
  } else if (strcmp(tok, "drop") == 0) { // drop operation

    theToken -> type = DROP; // drop type
    
  } else if (strcmp(tok, "dup") == 0) { // duplicate operation

    theToken -> type = DUP; // dup type
    
  } else if (strcmp(tok, "swap") == 0) { // swap operation

    theToken -> type = SWAP; // swap type

  } else if (strcmp(tok, "min") == 0) { // minimum operation

    theToken -> type = MIN; // min type
        
  } else if (strcmp(tok, "abs") == 0) { // absolute value operation

    theToken -> type = ABS; // abs type

  } else if (strcmp(tok, "avg") == 0) { // average operation

    theToken -> type = AVG; // avg type
    
  } else if (strlen(tok) > 3 && tok[0] == 'a' && tok[1] == 'r' && tok[2] == 'g' && isdigit(tok[3])) { // argN operation

    theToken -> type = ARG; // arg type
    theToken -> arg_no = tok[3]; // stack position of value to be copied
    
  } else if (strcmp(tok, "if") == 0) { // if operation

    theToken -> type = IF; // if type

  } else if (strcmp(tok, "else") == 0) { // else operation

    theToken -> type = ELSE; // else type

  } else if (strcmp(tok, "endif") == 0) { // endif operation

    theToken -> type = ENDIF; // endif type

  } else if (strcmp(tok, "defun") == 0) { // define function operation

    theToken -> type = DEFUN; // defun type

  } else if (isalpha(tok[0]) && strcmp(tok, "return") != 0) { // identifier operation

    theToken -> type = IDENT; // ident type

  } else if (strcmp(tok, "return") == 0) { // return operation

    theToken -> type = RETURN; // return type

  } else { // does not match any

    theToken -> type = BROKEN_TOKEN; // broken token

  }
  
  strcpy(theToken -> str, tok); // store token in string
  
}

int max_if = -1; // Global Var for max_if value
int final_if = -1; // Global Var for final_if value
int max_pow = 0; // Global Var for max_pow value
int max_cmp = 0; // Global Var for max_cmp value
int max_min = 0; // Global Var for max_min value
int max_abs = 0; // Global Var for max_abs value
int in_defun = 0; // Global Var for checking if we are defining a function
int offset = 0; // for during subroutines

void write_assembly (token* theToken, FILE* asm_file, char* filename, hash_struct* LOOPS) {
  
  if (theToken -> type == IF) { // if conditional
    
    put(LOOPS, max_if + 1, final_if); // store in hash table
    max_if = max_if + 1; // increment max_if
    final_if = max_if; // final_if = max_if
    
    // Display branch and label
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6 = R6 + 1
    fprintf(asm_file, "CMPI R0 #0\n"); // checks if R0 = 0 or 1
    fprintf(asm_file, "BRz %s_ELSE_%d\n", filename, final_if);
    fprintf(asm_file, "%s_IF_%d\n", filename, final_if);
    
  } else if (theToken -> type == ELSE) { // else conditional
    
    // Display label and Jump for IF section
    fprintf(asm_file, "JMP %s_ENDIF_%d\n", filename, final_if);
    fprintf(asm_file, "%s_ELSE_%d\n", filename, final_if);
    
  } else if (theToken -> type == ENDIF) { // endif conditional
    
    // Display end label
    fprintf(asm_file, "%s_ENDIF_%d\n", filename, final_if);
    
    final_if = get(LOOPS, final_if) -> value; // final_if = parent final_if
    
  } else if (theToken -> type == LITERAL) { // literal value
    
    fprintf(asm_file, "CONST R0 #%d\n", (theToken -> literal_value) & 0xFF); // print value in constant
    fprintf(asm_file, "HICONST R0 #%d\n", (theToken -> literal_value) >> 8 ); // print value in constant
    fprintf(asm_file, "STR R0 R6 #-1\n"); // Store value into stack
    fprintf(asm_file, "ADD R6 R6 #-1\n"); // R6--
    
    
  } else if (theToken -> type == PLUS) { // addition operation
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "ADD R0 R0 R1\n"); // R0 = R0 + R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == MINUS) { // subtraction operation
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "SUB R0 R0 R1\n"); // R0 = R0 - R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == MUL) { // multiplication operation
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "MUL R0 R0 R1\n"); // R0 = R0 * R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == DIV) { // division operation
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "DIV R0 R0 R1\n"); // R0 = R0 / R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == MOD) { // modulo operation
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "MOD R0 R0 R1\n"); // R0 = R0 % R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == POW) { // power operation
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "POW_%d\n", max_pow); // POW label
    fprintf(asm_file, "CMPI R1 #1\n"); // Check if R1 = 1
    fprintf(asm_file, "BRz POW_END_%d\n", max_pow); // JMP POW_END
    fprintf(asm_file, "MUL R0 R0 R0\n"); // R0 = R0 * R0
    fprintf(asm_file, "ADD R1 R1 #-1\n"); // R1 = R1 - 1
    fprintf(asm_file, "JMP POW_%d\n", max_pow); // Jump back to POW
    fprintf(asm_file, "POW_END_%d\n", max_pow); // POW_END label
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == LT) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "CMP R0 R1\n"); // set nzp R0 - R1
    fprintf(asm_file, "BRzp FALSE_%d\n", max_cmp); // JUMP to FALSE if np
    fprintf(asm_file, "CONST R0 #1\n"); // R0 = 1 (TRUE)
    fprintf(asm_file, "JMP END_CMP_%d\n", max_cmp); // jump to end of cmp
    fprintf(asm_file, "FALSE_%d\n", max_cmp); // FALSE label
    fprintf(asm_file, "CONST R0 #0\n"); // R0 = 0 (FALSE)
    fprintf(asm_file, "END_CMP_%d\n", max_cmp); // end of cmp
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
    max_cmp = max_cmp + 1; // increment cmp value
    
  } else if (theToken -> type == LE) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "CMP R0 R1\n"); // set nzp R0 - R1
    fprintf(asm_file, "BRp FALSE_%d\n", max_cmp); // JUMP to FALSE if p
    fprintf(asm_file, "CONST R0 #1\n"); // R0 = 1 (TRUE)
    fprintf(asm_file, "JMP END_CMP_%d\n", max_cmp); // jump to end of cmp
    fprintf(asm_file, "FALSE_%d\n", max_cmp); // FALSE label
    fprintf(asm_file, "CONST R0 #0\n"); // R0 = 0 (FALSE)
    fprintf(asm_file, "END_CMP_%d\n", max_cmp); // end of cmp
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
    max_cmp = max_cmp + 1; // increment cmp value
    
  } else if (theToken -> type == EQ) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "CMP R0 R1\n"); // set nzp R0 - R1
    fprintf(asm_file, "BRnp FALSE_%d\n", max_cmp); // JUMP to FALSE if nz
    fprintf(asm_file, "CONST R0 #1\n"); // R0 = 1 (TRUE)
    fprintf(asm_file, "JMP END_CMP_%d\n", max_cmp); // jump to end of cmp
    fprintf(asm_file, "FALSE_%d\n", max_cmp); // FALSE label
    fprintf(asm_file, "CONST R0 #0\n"); // R0 = 0 (FALSE)
    fprintf(asm_file, "END_CMP_%d\n", max_cmp); // end of cmp
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
    max_cmp = max_cmp + 1; // increment cmp value
    
  } else if (theToken -> type == GE) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "CMP R0 R1\n"); // set nzp R0 - R1
    fprintf(asm_file, "BRn FALSE_%d\n", max_cmp); // JUMP to FALSE if n
    fprintf(asm_file, "CONST R0 #1\n"); // R0 = 1 (TRUE)
    fprintf(asm_file, "JMP END_CMP_%d\n", max_cmp); // jump to end of cmp
    fprintf(asm_file, "FALSE_%d\n", max_cmp); // FALSE label
    fprintf(asm_file, "CONST R0 #0\n"); // R0 = 0 (FALSE)
    fprintf(asm_file, "END_CMP_%d\n", max_cmp); // end of cmp
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
    max_cmp = max_cmp + 1; // increment cmp value
    
  } else if (theToken -> type == GT) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "CMP R0 R1\n"); // set nzp R0 - R1
    fprintf(asm_file, "BRnz FALSE_%d\n", max_cmp); // JUMP to FALSE if nz
    fprintf(asm_file, "CONST R0 #1\n"); // R0 = 1 (TRUE)
    fprintf(asm_file, "JMP END_CMP_%d\n", max_cmp); // jump to end of cmp
    fprintf(asm_file, "FALSE_%d\n", max_cmp); // FALSE label
    fprintf(asm_file, "CONST R0 #0\n"); // R0 = 0 (FALSE)
    fprintf(asm_file, "END_CMP_%d\n", max_cmp); // end of cmp
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
    max_cmp = max_cmp + 1; // increment cmp value
    
  } else if (theToken -> type == AND) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "AND R0 R0 R1\n"); // R0 = R0 & R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == OR) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "OR R0 R0 R1\n"); // R0 = R0 | R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == NOT) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "NOT R0 R0\n"); // R0 = ~R0
    fprintf(asm_file, "STR R0 R6 #0\n"); // store on stack
    
  } else if (theToken -> type == XOR) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "XOR R0 R0 R1\n"); // R0 = R0 ^ R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == DROP) {
    
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
  } else if (theToken -> type == DUP) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // get top stack
    fprintf(asm_file, "STR R0 R6 #-1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #-1\n"); // R6--
    
  } else if (theToken -> type == SWAP) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack in new spot
    fprintf(asm_file, "STR R1 R6 #0\n"); // store on stack in new spot
    
  } else if (theToken -> type == MIN) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "CMP R0 R1\n"); // set nzp R0 - R1
    fprintf(asm_file, "BRzp MIN_%d\n", max_min); // jump to MIN if R0 > R1
    fprintf(asm_file, "STR R0 R6 #1\n"); // store on stack
    fprintf(asm_file, "JMP END_MIN_%d\n", max_min); // jump to end of min
    fprintf(asm_file, "MIN_%d\n", max_min); // MIN label
    fprintf(asm_file, "STR R1 R6 #1\n"); // store on stack
    fprintf(asm_file, "END_MIN_%d\n", max_min); // end of MIN
    fprintf(asm_file, "ADD R6 R6 #1\n"); // R6++
    
    max_min = max_min + 1; // increment max_min
    
  } else if (theToken -> type == ABS) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "CMPI R0 #0\n"); // set nzp R0 - 0
    fprintf(asm_file, "BRzp ABS_%d\n", max_abs); // jump to ABS if R0 >= 0
    fprintf(asm_file, "CONST R1 #-1\n"); // R1 = -1
    fprintf(asm_file, "MUL R0 R0 R1\n"); // R0 = R0 * R1
    fprintf(asm_file, "ABS_%d\n", max_abs); // ABS label
    fprintf(asm_file, "STR R0 R6 #0\n"); // store on stack
    
    max_abs = max_abs + 1; // increment max_abs
    
  } else if (theToken -> type == AVG) {
    
    fprintf(asm_file, "LDR R0 R6 #0\n"); // pop top stack
    fprintf(asm_file, "LDR R1 R6 #1\n"); // pop top stack
    fprintf(asm_file, "LDR R2 R6 #2\n"); // pop top stack
    fprintf(asm_file, "ADD R0 R0 R1\n"); // R0 = R0 + R1
    fprintf(asm_file, "ADD R0 R0 R2\n"); // R0 = R0 + R2
    fprintf(asm_file, "CONST R1 #3\n"); // R1 = 3
    fprintf(asm_file, "DIV R0 R0 R1\n"); // R0 = R0 / R1
    fprintf(asm_file, "STR R1 R6 #2\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #2\n"); // R6 = R6 + 2
    
  } else if (theToken -> type == ARG) {
    
    fprintf(asm_file, "LDR R0 R6 #%c\n", theToken -> arg_no + offset); // get value at arg_no below top of stack
    fprintf(asm_file, "STR R0 R6 #-1\n"); // store on stack
    fprintf(asm_file, "ADD R6 R6 #-1\n"); // R6 = R6 - 1
    
  } else if (theToken -> type == DEFUN) {
    
    in_defun = 1; // Defining a function
    
  } else if (theToken -> type == IDENT) {
    
    if (in_defun == 1) {
      // Write prologue
      fprintf(asm_file, ".CODE\n"); // .CODE
      fprintf(asm_file, ".FALIGN\n"); // .CODE
      fprintf(asm_file, "%s\n", theToken -> str); // Subroutine label
      fprintf(asm_file, "STR R7 R6 #-2\n"); // save return address
      fprintf(asm_file, "STR R5 R6 #-3\n"); // save frame pointer
      fprintf(asm_file, "ADD R6 R6 #-3\n"); // update stack pointer
      fprintf(asm_file, "ADD R5 R6 #0\n"); // create/update frame pointer
      offset = 2;
      in_defun = 0; // No longer defining
    } else {
      // Call TRAP
      fprintf(asm_file, "JSR %s\n", theToken -> str); // call JSR
    }
    
  } else if (theToken -> type == RETURN) {
    
    fprintf(asm_file, "LDR R7 R5 #-1\n"); // get return value into R7
    // Write Epilogue
    fprintf(asm_file, "ADD R6 R5 #0\n"); // pop local variables
    fprintf(asm_file, "ADD R6 R6 #3\n"); // update stack pointer
    fprintf(asm_file, "STR R7 R6 #-1\n"); // save return value
    
    fprintf(asm_file, "LDR R5 R6 #-3\n"); // restore base ptr
    fprintf(asm_file, "LDR R7 R6 #-2\n"); // restore R7
    fprintf(asm_file, "ADD R6 R6 #-1\n"); // R6 = R6 - 1
    fprintf(asm_file, "RET\n"); // call RET
    offset = 0;
    
  }
}

