#include <stdio.h>
#include <stdlib.h>
#include "maxHeap.h"

typedef struct
{
    int* array;
    int size;
    int capacity;
}Heap;

/********************************
 *  Helper Function Declaration
 * *****************************/
void fixUp(Heap* pHeap, int index);     //Heapify Up
void fixDown(Heap* pHeap, int index);   //Heapify Down
void swap(int* a, int* b);

/***************************************************
 *                  Heap Functions
 * ************************************************/

/**
 * @brief Creates a heap that is represented as an array.
 * The array's size(number of elements currently in the array),
 * and capacity(number of elements the array can hold) are
 * initialized to 0 and 15 respectively.
 * 
 * @return HEAP returns a pointer to a Heap structure if all allocations
 * are successful, otherwise a NULL pointer is returned.
 */
HEAP heapInit(void)
{
    Heap* pHeap = malloc(sizeof(Heap));
    if(pHeap)
    {
        pHeap->size = 0;
        pHeap->capacity = 15;
        pHeap->array = malloc(sizeof(int) * pHeap->capacity);
        if(!pHeap->array)
        {
            fprintf(stderr, "Failed to allocate space for heap\n");
            free(pHeap);
            return NULL;
        }
    }
    return pHeap;
}

/**
 * @brief Inserts a new element into the end of the heap array.
 * If the array is full when the insertion is attempted the 
 * function attempts to double the size of the array. The new
 * element is added, and fixUp is called to mantain the max heap
 * property.
 * 
 * @param hHeap A handle to a heap object
 * @param data element that is to be added to heap
 * @return Status SUCCESS is returned if data is successfully
 * added to heap, otherwise FAILURE is returned.
 */
Status heapInsert(HEAP hHeap, int data)
{
    Heap* pHeap = (Heap*)hHeap;

    if(pHeap)
    {
        if(pHeap->size >= pHeap->capacity)
        {
            int* temp = realloc(pHeap->array, sizeof(int) * (pHeap->capacity * 2));
            if(!temp)
            {
                fprintf(stderr, "Failed to resize heap\n");
                return FAILURE;
            }

            pHeap->capacity *= 2;
            for(int i = pHeap->size; i < pHeap->capacity; i++)
                temp[i] = 0;

            pHeap->array = temp;
        }

        pHeap->array[pHeap->size] = data;
        fixUp(pHeap, pHeap->size);
        pHeap->size++;

        return SUCCESS;
    }
    return FAILURE;
}

/**
 * @brief Removes elements specified by data from the heap.
 * If there are multiple elements of data then the first one
 * is removed. Element is moved to the end of the array and
 * removed from the heap. fixDown is called to maintain the 
 * max heap property.
 * 
 * @param hHeap A handle to a heap object
 * @param data Element that is to be removed from the heap
 * @return Status SUCCESS is returned if data is successfully
 * removed from heap, otherwise FAILURE is returned.
 */
Status heapRemove(HEAP hHeap, int data)
{
    Heap* pHeap = (Heap*)hHeap;
    int i;

    if(pHeap == NULL)
        return FAILURE;
        
    if(pHeap->size == 0)
        return SUCCESS;

    for(i = 0; i < pHeap->size; i++)
    {
        if(pHeap->array[i] == data)
            break;
    }

    if(pHeap->array[i] == data)
    {
        swap(&pHeap->array[i], &pHeap->array[pHeap->size - 1]);
        pHeap->array[pHeap->size - 1] = 0;
        fixDown(pHeap, i);
        pHeap->size--;
        return SUCCESS;
    }

    return FAILURE;
}

/**
 * @brief Removes the element at the top of the heap.
 * Swaps the first and last element of heap. The last
 * element is then removed and fixDown is called to
 * maintain the max heap property
 * 
 * @param hHeap A handle to a heap object
 * @return Status SUCCESS returned if the top is successfully
 * removed, otherwise FAILURE is returned.
 */
Status heapRemoveTop(HEAP hHeap)
{
    Heap* pHeap = (Heap*)hHeap;

    if(pHeap == NULL)
        return FAILURE;

    if(pHeap->size == 0)
        return SUCCESS;

    swap(&pHeap->array[0], &pHeap->array[pHeap->size - 1]);
    pHeap->array[pHeap->size - 1] = 0;
    fixDown(pHeap, 0);
    pHeap->size--;
    return SUCCESS;
}

/**
 * @brief Returns the greatest element in the heap
 * 
 * @param hHeap 
 * @return int first element of array is returned
 * if hHeap is valid and there is at least one element
 * in the heap, otherwise 0 is returned
 */
int heapGetMax(HEAP hHeap)
{
    Heap* pHeap = (Heap*)hHeap;
    if(pHeap && pHeap->size > 0)
        return pHeap->array[0];

    return 0;
}

/**
 * @brief Prints heap in the order elements
 * appear in the array
 * 
 * @param hHeap A handle to a heap object
 */
void printHeap(HEAP hHeap)
{
    Heap* pHeap = (Heap*)hHeap;
    
	if(pHeap)
    {
		for(int i = 0; i < pHeap->size; i++)
        {
            printf("%d ", pHeap->array[i]);
            if(i % 30 == 0)
                printf("\n");
        }
        printf("\n");
    }
}

/**
 * @brief Frees all memory associated with heap.
 * frees the array that stores all the data of
 * the heap. Then frees the pointer to the Heap
 * structure, and sets the handle pointer to NULL
 * 
 * @param phHeap The address of the handle to heap
 */
void heapDestroy(HEAP* phHeap)
{
    Heap* pHeap = (Heap*)*phHeap;
    if(pHeap)
    {
        free(pHeap->array);
        free(pHeap);
        *phHeap = NULL;
    }
}

/********************************
 *  Helper Function Definitions
 * *****************************/

/**
 * @brief Function to maintain the max heap property
 * Recursively traverse up the heap while array[index]
 * is greater than array[indexOfParent] swapping those
 *  elements as neccesary
 * 
 * @param pHeap pointer to a Heap structure
 * @param index index of an element that is potentially out
 * of place.
 */
void fixUp(Heap* pHeap, int index)
{
    int indexOfParent = (index - 1) / 2;
    if(index > 0)
    {
        if(pHeap->array[index] > pHeap->array[indexOfParent])
        {
            swap(&(pHeap->array[index]), &(pHeap->array[indexOfParent]));
            fixUp(pHeap, indexOfParent);
        }
    }
}

/**
 * @brief Function to maintain the max heap property
 * Recursively traverse down the heap while array[index]
 * is less than array[indexOfLeftChild] or
 * array[indexOfRightChild]swapping those elements as neccesary
 * 
 * @param pHeap pointer to a Heap structure
 * @param index index of an element that is potentially out
 * of place
 */
void fixDown(Heap* pHeap, int index)
{
    int indexOfLeftChild  = (index * 2) + 1;
    int indexOfRightChild = (index * 2) + 2;
    int indexOfLargestChild;

    if(indexOfLeftChild >= pHeap->size)
        return;
    
    else if(indexOfRightChild < pHeap->size)
        indexOfLargestChild = (pHeap->array[indexOfLeftChild] > pHeap->array[indexOfRightChild]) ? indexOfLeftChild : indexOfRightChild;
    
    else
        indexOfLargestChild = indexOfLeftChild;

    if(pHeap->array[index] < pHeap->array[indexOfLargestChild])
    {
        swap(&(pHeap->array[index]), &(pHeap->array[indexOfLargestChild]));
        fixDown(pHeap, indexOfLargestChild);
    }
}

/**
 * @brief swap elements a and b
 * 
 * @param a element of the heap
 * @param b element of the heap
 */
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
