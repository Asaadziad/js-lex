#include "stdio.h"
#include "stdlib.h"
#include "lexer/lexer.h"

int main(){
   const char* input = "+==*()=     {()};function mul(x){return 9+9;}";//
    LEXER lexer = lexerCreate(input);
    TOKEN tok = lexerGetNext(lexer);
    while (getTokenType(tok) != tokenEOF)
    {
        tokenPrint(tok);
        tokenDestroy(tok);
        tok = lexerGetNext(lexer);
    }
    
    tokenDestroy(tok);
    lexerDestroy(lexer);
    return 0;
}