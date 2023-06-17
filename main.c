#include "stdio.h"
#include "stdlib.h"
#include "lexer.h"

int main(){
   const char* input = "+=*(){()};";
    LEXER lexer = lexerCreate(input);
    TOKEN tok = lexerGetNext(lexer);
    while (getTokenType(tok) != tokenEOF)
    {
        tokenPrint(tok);
        tok = lexerGetNext(lexer);
    }
    
    
    lexerDestroy(lexer);
    return 0;
}