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

    if (pq->capac == pq->size){
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = (heapElem*)realloc(pq->heapArray,sizeof(heapElem) * pq->capac);
    }
}


void heap_pop(Heap* pq){
    //INTERCAMBIAR ULTIMO CON EL PRIMERO
    int posicionUltimo = pq->size - 1;
    if (pq->size != 0){
        pq->heapArray[0] = pq->heapArray[posicionUltimo];
        pq->size--;

        //HACER SWAPS
        //Hijos 2x+1 o 2x+2
        int posicionHijoUno = 1;
        int posicionHijoDos = 2;
        int posicionInicio = 0;
        heapElem aux;
        while (1){
            if (pq->heapArray[posicionHijoUno].priority > pq->heapArray[posicionInicio].priority){
                aux = pq->heapArray[posicionInicio];
                pq->heapArray[posicionInicio] = pq->heapArray[posicionHijoUno];
                pq->heapArray[posicionHijoUno] = aux;
                posicionInicio = posicionHijoUno;
              
            }
            else{
                if (pq->heapArray[posicionHijoDos].priority > pq->heapArray[posicionInicio].priority){
                    aux = pq->heapArray[posicionInicio];
                    pq->heapArray[posicionInicio] = pq->heapArray[posicionHijoDos];
                    pq->heapArray[posicionHijoDos] = aux;
                    posicionInicio = posicionHijoDos;
                }
                break;
            }
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
