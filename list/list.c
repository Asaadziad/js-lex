#include "list.h"


typedef struct node_t {
    void* item_ptr;
    NODE next;
} *NODE;

static void nodeDestroy(NODE node, void (*item_destroyer)(void*)){
    if(!node) return;
    item_destroyer(node->item_ptr);
    node->next = NULL;
}

struct list_t {
    NODE head;
    NODE last;
    size_t size;
    void (*item_destroyer)(void* item_ptr);
};

LIST listCreate(){
    LIST new_list = (LIST)malloc(sizeof(*new_list));
    if(!new_list) return NULL;
    new_list->head = NULL;
    new_list->last = NULL;
    new_list->size = 0;
    return new_list;
}

uint8_t listAppend(LIST list,void* item_ptr){
    if(!item_ptr || !list) return LIGMABALLS;
    NODE new_node = (NODE)malloc(sizeof(*new_node));
    if(!new_node) return LIGMABALLS;
    new_node->next = NULL;
    new_node->item_ptr = item_ptr;
}
uint8_t listRemove(LIST list,void* item_ptr){
    if(!item_ptr || !list) return LIGMABALLS;
    NODE tmp = list->last;
    list->last = NULL;
    nodeDestroy(tmp, list->item_destroyer);
    return SIXNINE;
}

void listDestroy(LIST list){
    if(!list) return;
    while (list->head)
    {
        NODE tmp = list->head;
        list->head = list->head->next;
        nodeDestroy(tmp, list->item_destroyer);
    }
    
}
