#include "lexer.h"


struct lexer_t {
    const char* buffer;
    unsigned int buffer_len;
    unsigned int pos;
    unsigned int reading_pos;
    char character;
};


struct token_t {
    TokenType type;
    char* literal;
};

/* PRIVATE FUNCTIONS */
static void _skipWhiteSpaces(LEXER lexer);

static void _readChar(LEXER lexer);
static char _lexerPeek(LEXER lexer);

static const char* _readIdentifier(LEXER lexer,unsigned int* len);
static const char* _readInt(LEXER lexer,unsigned int* len);

TokenType _getTokenTypeFromLiteral(char* literal,unsigned int len);

static uint8_t _isLetter(char ch);
static uint8_t _isNumber(char ch);
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
    
    _skipWhiteSpaces(lexer);

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
            _readChar(lexer);
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
        token = tokenCreate(tokenRSQUIRLY, "{");
        break;
    case '}':
        token = tokenCreate(tokenLSQUIRLY, "}");
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

    if(_isLetter(lexer->character)){
        unsigned int len;
        
        const char* ident = _readIdentifier(lexer,&len);
        
        char* literal = (char*) malloc(sizeof(*literal) * (len));
        strncpy(literal,ident, len);
        TokenType type = _getTokenTypeFromLiteral(literal, len);
        token = tokenCreate(type, literal);
        return token;
    } else if(_isNumber(lexer->character)){
        unsigned int len;
        const char* ident = _readInt(lexer,&len);
        char* literal = (char*) malloc(sizeof(*literal) * (len));
        strncpy(literal,ident, len);
        TokenType type = _getTokenTypeFromLiteral(literal, len);
        token = tokenCreate(type, literal);
        return token;
    }

    if(!token){
        token = tokenCreate(tokenILLEGAL,NULL);
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
static void _skipWhiteSpaces(LEXER lexer){
    while(lexer->character == ' ' || lexer->character == '\t' || lexer->character == '\r'
        || lexer->character == '\n'){
            
            _readChar(lexer);
        }
}

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

static const char* _readIdentifier(LEXER lexer,unsigned int* len){
    if(!lexer) return NULL;
    unsigned int position = lexer->pos;
    while (_isLetter(lexer->character))
    {
        _readChar(lexer);
    }

    if(len){
        *len = lexer->reading_pos - position - 1;
    }
    
    return lexer->buffer + position; 
}

static const char* _readInt(LEXER lexer,unsigned int* len){
    if(!lexer) return NULL;
    unsigned int position = lexer->pos;
    while (_isNumber(lexer->character))
    {
        _readChar(lexer);
    }

    if(len){
        *len = lexer->reading_pos - position - 1;
    }
    
    return lexer->buffer + position; 
}

TokenType _getTokenTypeFromLiteral(char* literal,unsigned int len){
    if(!literal) return tokenILLEGAL;
    if(!strncmp(literal, "if",len)){
        return tokenIF;
    } else if(!strncmp(literal,"else",len)){
        return tokenELSE;
    } else if(!strncmp(literal,"function",len)){
        return tokenFUNCTION;
    } else if (!strncmp(literal,"for",len)){
        return tokenFOR;
    } else if (!strncmp(literal,"while",len)){
        return tokenWHILE;
    } else if(!strncmp(literal,"return", len)){
        return tokenRETURN;
    }

    return tokenIDENT;
}

static uint8_t _isLetter(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
static uint8_t _isNumber(char ch){
    return (ch >= '0' && ch <= '9');
}
/* END OF PRIVATE FUNCTIONS */
