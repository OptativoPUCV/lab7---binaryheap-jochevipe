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

  if (pq->size == 0) {
        // Si el montículo está vacío, no se realiza ninguna operación
        return;
    }

    // Reemplazar la raíz con el último elemento del montículo
    pq->heapArray[0] = pq->heapArray[pq->size - 1];
    pq->size--;

    // Realizar el reordenamiento hacia abajo para mantener la propiedad del montículo
    int i = 0;
    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int smallest = i;

        // Encontrar el índice del hijo con la prioridad más pequeña
        if (leftChild < pq->size && pq->heapArray[leftChild].priority < pq->heapArray[smallest].priority) {
            smallest = leftChild;
        }
        if (rightChild < pq->size && pq->heapArray[rightChild].priority < pq->heapArray[smallest].priority) {
            smallest = rightChild;
        }

        if (smallest != i) {
            // Intercambiar el elemento actual con el hijo de menor prioridad
            heapElem temp = pq->heapArray[i];
            pq->heapArray[i] = pq->heapArray[smallest];
            pq->heapArray[smallest] = temp;

            i = smallest; // Actualizar el índice al hijo de menor prioridad
        } else {
            // Si no se requiere intercambio, se ha restaurado la propiedad del montículo
            break;
        }
    }
}

Heap* createHeap(){

  Heap *m = (Heap*) malloc(sizeof(Heap));

  m->size = 0;
  m->capac = 3;
  m->heapArray = (heapElem*)malloc(m->capac * sizeof(heapElem));
  
  return m;
}
