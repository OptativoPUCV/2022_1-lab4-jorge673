#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

  long position=hash(key,map->capacity);
  
  while(map->buckets[position]!=NULL && map->buckets[position]->key!=NULL){
    if(is_equal(key,map->buckets[position]->key))return;

    position=((position+1)%map->capacity);
  }
  if(map->buckets[position]!=NULL){
    map->buckets[position]->key=key;
    map->buckets[position]->value=value;
  }else{
    map->buckets[position]=createPair(key,value);
  }
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap* map=(HashMap*)malloc(sizeof(HashMap));
    Pair** buck=(Pair**)malloc(capacity*sizeof(Pair));

    map->buckets=buck;
    map->capacity=capacity;
    map->size=0;
    map->current=-1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {  

  Pair* aux=searchMap(map,key);
  
  if(aux==NULL)return;
  
  long pos=map->current;
  aux->key=NULL;

  map->buckets[pos]=aux;
  map->size--;
  
}

Pair * searchMap(HashMap * map,  char * key) {   

    long position=hash(key,map->capacity);

    while(map->buckets[position]!=NULL && map->buckets[position]->key!=NULL){

        if(is_equal(key,map->buckets[position]->key)){
          map->current=position;
          return map->buckets[position];
        }
          

        position=((position+1)%map->capacity);
    }

    if(map->buckets[position]!=NULL){
        
      map->current=position;
      return map->buckets[position];
        
    }else{
        return NULL;
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {

  long pos=0;
  int wlc=0;
  long size=map->size;
  
  while(wlc==0){
    
    if(map->buckets[pos]!=NULL && map->buckets[pos]->key!=NULL){
      map->current=pos;
      wlc=1;
      return map->buckets[pos];
    }
    pos++;
    if(map->buckets[pos]!=NULL)size--;
    
    if(size==0)break;
  }
  
  return NULL;
}

Pair * nextMap(HashMap * map) {
  
  long pos=map->current+1;
  long size=map->size;
  int wlc=0;
  
  while(wlc==0){
    
    if(map->buckets[pos]!=NULL){
      map->current=pos;
      wlc=1;
      return map->buckets[pos];
    }
  }
  
  return NULL;
}
