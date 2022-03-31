#ifndef MAXHEAP_H
#define MAXHEAP_H
#include "status.h"

typedef void* HEAP;

/**
 * @brief Creates a maximum heap data structure
 * 
 * @return HEAP returns a handle to a HEAP object
 * or NULL if the creation fails
 */
HEAP heapInit(void);

/**
 * @brief Adds data into the heap specified by hHeap
 * 
 * @param hHeap A handle to a heap object
 * @param data element that is to be added to heap
 * @return Status SUCCESS is returned on successful completion
 * FAILURE is returned on failure
 */
Status heapInsert(HEAP hHeap, int data);

/**
 * @brief Removes a specified item from the heap,
 * if multiple of data are present the first one
 * is removed.
 * 
 * @param hHeap A handle to a heap object
 * @param data element that is to be removed from heap
 * @return Status 
 */
Status heapRemove(HEAP hHeap, int data);

/**
 * @brief removes the item at the top of the heap
 * 
 * @param hHeap A handle to a heap object
 * @return Status 
 */
Status heapRemoveTop(HEAP hHeap);

/**
 * @brief returns the item at the top of the heap
 * 
 * @param hHeap A handle to a heap object
 * @return int 
 */
int heapGetMax(HEAP hHeap);

/**
 * @brief Prints the heap from top to bottom
 * left to right
 * 
 * @param hHeap A handle to a heap object
 */
void printHeap(HEAP hHeap);

/**
 * @brief frees all memory associated with a heap object
 * and makes the handle a NULL pointer
 * 
 * @param phHeap The address of a handle to a heap object
 */
void heapDestroy(HEAP* phHeap);

#endif