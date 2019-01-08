#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"

typedef struct Node_t {
    char key[1000];
    unsigned int nbMsg;
    struct Node_t *next;
} Node;

struct Set_t {
    Node **array;
    unsigned int arraySize;
    unsigned int nKeys;
};


Set *setCreate(int size) {
    Set *s = malloc(sizeof(Set));
    if (s == NULL)
        exit(-1);
    s -> array = calloc(size, sizeof(Node *));
    if (s -> array == NULL)
        exit(-1);
    for(int i=0; i<size; i++) s->array[i]=NULL;
    s -> arraySize = size;
    s -> nKeys = 0;
    return s;
}

void setFree(Set *s) {
    for (int i = 0; i < (int)s -> arraySize; i++) {
        Node *p = s -> array[i];
        while (p != NULL) {
            Node *nextp = p -> next;
            free(p);
            p = nextp;
        }
    }
    free(s -> array);
    free(s);
}

/* Hash function djb2 (http://www.cse.yorku.ca/~oz/hash.html) */

static size_t hash(Set *s, char *key) {
    size_t hash = 5381;
    
    while (*key != '\0') {
        hash = ((hash << 5) + hash) + *key; // hash = hash * 33 + *key
        key++;
    }
    
    return hash % (s -> arraySize);
}

int setContains(Set *s, char *key) {
    size_t hc = hash(s, key);
    
    for (Node *p = s -> array[hc]; p != NULL; p = p -> next) {
        if (strcmp(key, p -> key) == 0) {
            return 1;
        }
    }
    return 0;
}

void setPrintStat(Set *s){
    Node *p;
    printf("\n");
    for(unsigned int i=0; i<s->arraySize; i++){
        printf("%u\n",i);
        for(p = s->array[i]; p!=NULL; p=p->next){
            printf("%s a envoyé %u messages\n", p->key, p->nbMsg);
        }
    }
    return;
}

void setAdd(Set *s, char *key) {
    size_t hc = hash(s, key);
    if(s->array[hc] == NULL){
        Node *q = malloc(sizeof(Node *));
        if(q == NULL) exit(-1);
        s->array[hc] = q;
        strcpy(q->key, key);
        q->nbMsg = 1;
        q->next = NULL;
        fprintf(stderr,"Successfully added to %s Total msg: %u\n", q->key, q->nbMsg);
        return;
    }
    
    Node *p;
    for(p = s->array[hc]; p->next != NULL; p=p->next){
        if(strcmp(key, p->key) == 0){
            p->nbMsg++;
            fprintf(stderr,"Successfully added to %s Total msg: %u\n", p->key, p->nbMsg);

            return;
        }
    }
    if(strcmp(key, p->key) == 0){
        p->nbMsg++;
        fprintf(stderr,"Successfully added to %s Total msg: %u\n", p->key, p->nbMsg);
        return;
    }
    
    Node *q = malloc(sizeof(Node *));
    if(q == NULL) exit(-1);
    p->next = q;
    strcpy(q->key, key);
    q->nbMsg = 1;
    q->next = NULL;
    fprintf(stderr,"Successfully added to %s Total msg: %u\n", q->key, q->nbMsg);
    
    return;
}
