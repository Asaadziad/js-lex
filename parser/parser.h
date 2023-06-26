#ifndef PARSER_H
#define PARSER_H

typedef struct parser_t* PARSER;

PARSER createParser();

void parserInit(PARSER parser);

#endif