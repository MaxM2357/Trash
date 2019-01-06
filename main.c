#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static Node *removeList(Node *first, int key) {
    Node *cur = first;
    Node *next = first->next;
    if(cur->data == key){
        free(first);
        return next;
    }
    while(next){
        cur = next;
        next = cur->next;
        if(cur->data == key){
            Node *temp = NULL;
            if(next->next) temp = next->next;
            //next peut etre null et donc next->next ne pas exister
            free(cur);
            cur->next = temp;
            return first;
        }
    }
    return first;
}

static Node *inverseList(Node *first) {
    if(!first->next) return first;
    Node *prev;
    Node *cur = first;
    Node *next = cur->next;
    cur->next = NULL;
    prev = cur;
    cur = next;
    next = cur->next;
    cur->next = prev;
    first = cur;
    while(next){
        prev = cur;
        cur = next;
        next = cur->next;
        cur->next = prev;
        first = cur;
    }
    return first;
}

static void printList(Node *first) {
    Node *cur = first;
    while (cur) {
        Node *next = cur->next;
        printf("%d->", cur->data);
        cur = next;
    }
    printf("\n");
    return;
}

int main() {
    Node *l = createList(5);
    int tmp;
    Node *head = l;
    for (int i = 0; i < 20; i++) {
        head = addList(head, rand()%100);
        if (i == 10)
            tmp = head->data;
    }
    printList(head);
    printf("remove: %d\n",tmp);
    head = removeList(head, tmp);
    printList(head);
    head = inverseList(head);
    printList(head);
    freeList(head);
    return 0;
}
