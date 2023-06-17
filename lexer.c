#include "lexer.h"


struct lexer_t {
    const char* buffer;
    int buffer_len;
    int pos;
    int reading_pos;
    char character;
};


struct token_t {
    TokenType type;
    char* literal;
};

/* PRIVATE FUNCTIONS */
static void _readChar(LEXER lexer);
static char _lexerPeek(LEXER lexer);
/* END OF PRIVATE FUNCTIONS */


LEXER lexerCreate(const char* buffer){
    if(!buffer) return NULL;

    LEXER lexer = (LEXER) malloc(sizeof(*lexer));
    if(!lexer) return NULL;
    lexer->buffer = buffer;
    lexer->buffer_len = strlen(buffer);
    lexer->pos = 0;
    lexer->reading_pos = 0;

    _readChar(lexer);

    return lexer;
}

TOKEN tokenCreate(TokenType type, char* literal){

    TOKEN token = (TOKEN)malloc(sizeof(*token));
    if(!token) return NULL;
    token->literal = literal;
    token->type = type;

    return token;
}

TOKEN lexerGetNext(LEXER lexer){
    if(!lexer) return NULL;
    TOKEN token;
    switch (lexer->character)
    {
    case '+':
        token = tokenCreate(tokenPLUS,"+");
        break;
    case '*':
        token = tokenCreate(tokenMUL, "*");
        break;
    case '=':
        if(_lexerPeek(lexer) == '='){
            token = tokenCreate(tokenEQUAL,"==");
            break;
        }
        token = tokenCreate(tokenASSIGN, "=");
        break;
    case '-':
        token = tokenCreate(tokenMINUS,"-");
        break;
    case ';':
        token = tokenCreate(tokenSEMICOLON,";");
        break;
    case '{':
        token = tokenCreate(tokenLSQUIRLY,"{");
        break;
    case '}':
        token = tokenCreate(tokenRSQUIRLY, "}");
        break;
    case '(':
        token = tokenCreate(tokenLPAREN,"(");
        break;
    case ')':
        token = tokenCreate(tokenRPAREN,")");
        break;
    case '\0':
        token = tokenCreate(tokenEOF,"EOF");
        break;    
    }

    _readChar(lexer);
    return token;
}

void tokenPrint(TOKEN token){
    printf("{ type: '%d', value: '%s' }\n", token->type, token->literal);
}

TokenType getTokenType(TOKEN token){
    return token->type;
}

void lexerPrintInfo(LEXER lexer){
    printf("Buffer: %s , Len: %d , reading position: %d , position: %d , character: %c\n", 
    lexer->buffer,lexer->buffer_len,lexer->reading_pos,lexer->pos,lexer->character);
}

void lexerDestroy(LEXER lexer){
    if(!lexer) return;
    free(lexer);
}

/* PRIVATE FUNCTIONS */
static void _readChar(LEXER lexer){
    if(lexer->reading_pos >= lexer->buffer_len){
        lexer->character = '\0';
    } else {
        lexer->character = lexer->buffer[lexer->reading_pos];
    }
    lexer->pos = lexer->reading_pos;
    lexer->reading_pos++;
}
static char _lexerPeek(LEXER lexer){
    if(lexer->reading_pos >= lexer->buffer_len){
        return '\0';
    } else {
        return lexer->buffer[lexer->reading_pos];
    }
}
/* END OF PRIVATE FUNCTIONS */
