#ifndef LEXER_H
#define LEXER_H

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"


typedef enum {
    /*OPERATORS*/
    tokenPLUS,
    tokenMINUS,
    tokenMUL,
    tokenASSIGN,
    tokenEQUAL,


    tokenLSQUIRLY,
    tokenRSQUIRLY,
    tokenLPAREN,
    tokenRPAREN,
    tokenSEMICOLON,

    /* KEYWORDS */
    tokenIF,
    tokenELSE,
    tokenFUNCTION,
    tokenFOR,
    tokenWHILE,
    tokenRETURN,
    
    tokenIDENT,
    tokenINT,

    tokenILLEGAL,
    tokenEOF
}TokenType;

typedef struct lexer_t* LEXER;
typedef struct token_t* TOKEN;

LEXER lexerCreate(const char* buffer);

TOKEN lexerGetNext(LEXER lexer);


void tokenPrint(TOKEN token);

TokenType getTokenType(TOKEN token);

void lexerDestroy(LEXER lexer);
void lexerPrintInfo(LEXER lexer);


#endif