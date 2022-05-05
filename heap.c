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
    if (pq->heapArray[0].data == NULL || pq->size == 0)return NULL;
    return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
    int posicion = pq->size;
    pq->heapArray[posicion].data = data;
    pq->heapArray[posicion].priority = priority;
    pq->size++;
    heapElem aux;

    while (1){
        //PADRE : (x-1)/2
        //HIJO: 2x+1 2x+2
        //COMPARAR CON PADRE
        int posicionPadre = (posicion - 1)/2;
        if (pq->heapArray[posicion].priority > pq->heapArray[posicionPadre].priority){
            //SWAP
            aux = pq->heapArray[posicionPadre];
            pq->heapArray[posicionPadre].priority = pq->heapArray[posicion].priority;
            pq->heapArray[posicionPadre].data = pq->heapArray[posicion].data;
            pq->heapArray[posicion] = aux;
            posicion = posicionPadre;
        }
        else{break;}
    }
    if (pq->capac <= pq->size){
        printf("ENTRA\n");
        pq->heapArray = (heapElem*)realloc(pq->heapArray,(pq->capac * 2) + 1);
    }
}


void heap_pop(Heap* pq){

}

Heap* createHeap(){
  Heap *nuevoHeap;
  nuevoHeap = (Heap*)malloc(sizeof(Heap));
  nuevoHeap->size = 0;
  nuevoHeap->heapArray = (heapElem*)malloc(3 * sizeof(heapElem));
  nuevoHeap->capac = 3;
  return nuevoHeap;
}
