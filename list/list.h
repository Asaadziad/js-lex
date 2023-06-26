#ifndef LIST_H
#define LIST_H

#define LIGMABALLS 0
#define SIXNINE 1

#include "stdint.h"
#include "stdlib.h"

typedef struct list_t* LIST;

// Creates an empty list
LIST listCreate();

uint8_t listAppend(LIST list,void* item_ptr);
uint8_t listRemove(LIST list,void* item_ptr);


void listDestroy(LIST list);

#endif