#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){

if(pq->size == 0) return NULL;
  
  return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){

  if(pq->size == pq->capac){

    pq->capac = (pq->capac* 2) +1;
    pq->heapArray = (heapElem*) realloc(pq->heapArray, pq->capac * sizeof(heapElem));
  }

  if(pq->size == 0){

    pq->heapArray[0].data = data;
    pq->heapArray[0].priority = priority;
    pq->size++;

    return;
  }
  
  int indice = pq->size;
  pq->size++;

  pq->heapArray[indice].priority = priority;
  pq->heapArray[indice].data = data;
  
  while(1){
    
    if(pq->heapArray[indice].priority > pq->heapArray[(indice-1)/2].priority){

      heapElem aux = pq->heapArray[(indice-1)/2];
      pq->heapArray[(indice-1)/2] = pq->heapArray[indice];
      pq->heapArray[indice] = aux;

      indice = (indice-1)/2;
    }else{
      return;
    }
  }
}
  


void heap_pop(Heap* pq){

  if(pq->size == 0) return;

  
  pq->heapArray[0] = pq->heapArray[pq->size];
  pq->size--;
  
   int pos = 0;
  int posI = 1;
  int posD = 2;
  
  while(posI < pq->size){
    int hijo = posI;
    if(posD < pq->size && pq->heapArray[posD].priority > pq->heapArray[posI].priority) hijo = posD;
    if(pq->heapArray[pos].priority >= pq->heapArray[hijo].priority) break;
    
    heapElem aux = pq->heapArray[pos];
    pq->heapArray[pos] = pq->heapArray[hijo];
    pq->heapArray[hijo] = aux;
    
    pos = hijo;
    posI = (posI * 2) + 1;
    posD = (posD * 2) + 2;
    
  }

}

Heap* createHeap(){

  Heap *m = (Heap*) malloc(sizeof(Heap));

  m->size = 0;
  m->capac = 3;
  m->heapArray = (heapElem*)malloc(m->capac * sizeof(heapElem));
  
  return m;
}
