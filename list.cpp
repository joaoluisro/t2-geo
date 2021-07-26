#include <iostream>
#include "voronoi.h"

using namespace std;

int size(edge **list){
    edge *first = *list;
    if(first == NULL) return 0;
    edge *aux = first;
    int size = 0;

    do{
        size++;
        aux = aux->next;
    }while(aux != first);
    return size;
}

void append(edge **list, edge *elem){
    edge *first = *list;

    if(first == NULL){
        first = elem;
        first->next = first;
        first->prev = first;
    }
    else{
        edge *last = first->prev;
        first->prev = elem;
        elem->next = first;
        last->next = elem;
        elem->prev = last;
    }
    *list = first;
}

void remove(edge **list, edge *elem){
    edge *aux1, *aux2;
    aux1 = elem->next;
    aux2 = elem->prev;
    aux1->prev = aux2;
    aux2->next = aux1;
    if(elem == *list) *list = aux1;
    elem->next = NULL;
    elem->prev = NULL;

}

void print_list(edge **list){
    cout << "dcel : \n";
    edge *first = *list;
    edge *aux = first;
    do{
        aux->vert->print();
        aux = aux->next;
    }while(aux != first);

}
