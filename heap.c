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
    //SE INGRESA DATO AL ARREGLO
    pq->heapArray[posicion].data = data;
    pq->heapArray[posicion].priority = priority;
    pq->size++;
    heapElem aux;

    while (1){
        //PADRE : (x-1)/2
        int posicionPadre = (posicion - 1)/2;
        //COMPARAR CON PADRE
        if (pq->heapArray[posicion].priority > pq->heapArray[posicionPadre].priority){
            //SWAP
            aux = pq->heapArray[posicionPadre];
            pq->heapArray[posicionPadre] = pq->heapArray[posicion];
            pq->heapArray[posicion] = aux;
            posicion = posicionPadre;
        }
        else{break;}
    }
    //AUMENTAR ARREGLO
    if (pq->capac == pq->size){
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = (heapElem*)realloc(pq->heapArray,sizeof(heapElem) * pq->capac);
    }
}


void heap_pop(Heap* pq){
    //BORRADO
    int ultimaPosicion = pq->size - 1;
    heapElem aux = pq->heapArray[0];
    pq->heapArray[0] = pq->heapArray[ultimaPosicion];
    pq->heapArray[ultimaPosicion] = aux;
    pq->size--;

    
    int posicion = 0;
    if (pq != NULL){
        while (1){
            int posicionHijo = (2 * posicion) + 1;
            int posicionHijoDos = (2 * posicion) + 2;
            if (pq->heapArray[posicion].priority < pq->heapArray[posicionHijo].priority || pq->heapArray[posicion].priority < pq->heapArray[posicionHijoDos].priority){
    
                    if (pq->heapArray[posicionHijo].priority < pq->heapArray[posicionHijoDos].priority){
                        aux = pq->heapArray[posicion];
                        pq->heapArray[posicion] = pq->heapArray[posicionHijoDos];
                        pq->heapArray[posicionHijoDos] = aux;
                        posicion = posicionHijoDos;
                }
                else{
                        aux = pq->heapArray[posicion];
                        pq->heapArray[posicion] = pq->heapArray[posicionHijo];
                        pq->heapArray[posicionHijo] = aux;
                        posicion = posicionHijo;
                }
                    
            }
            printf("POSICION : %d\n",posicion);
            break;
        }
    }
}

Heap* createHeap(){
    Heap *nuevoHeap;
    nuevoHeap = (Heap*)malloc(sizeof(Heap));
    nuevoHeap->size = 0;
    nuevoHeap->heapArray = (heapElem*)malloc(3 * sizeof(heapElem));
    nuevoHeap->capac = 3;
    return nuevoHeap;
}
