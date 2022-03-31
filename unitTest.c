#include "unitTest.h"
#include "maxHeap.h"
#include <string.h>

typedef struct
{
    int* array;
    int size;
    int capacity;
}Heap;

bool test_heapInit(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    if(hHeap)
    {
        char success[] = "[SUCCESS] heapInit successfully creates a heap data structure\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapInit doesn't create a heap data structure\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapInsert(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);

    Heap* pHeap = (Heap*)hHeap;
    if(pHeap->array[0] == 1)
    {
        char success[] = "[SUCCESS] heapInsert successfully adds data to heap\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapInsert doesn't add data to heap\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapRemove(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 2);
    heapInsert(hHeap, 3);
    heapRemove(hHeap, 1);

    Heap* pHeap = (Heap*)hHeap;
    bool found = false;

    for(int i = 0; i < pHeap->size; i++)
    {
        if(pHeap->array[i] == 1)
        {
            found = true;
            break;
        }
    }

    if(found == false)
    {
        char success[] = "[SUCCESS] heapRemove successfully removes given item\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemove doesn't remove the given item\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapRemoveTop(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 2);
    heapInsert(hHeap, 3);

    if(heapRemoveTop(hHeap) && heapGetMax(hHeap) == 2)
    {
        char success[] = "[SUCCESS] heapRemoveTop successfully removes greatest item\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemoveTop doesn't remove the greatest item\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapGetMax(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 2);

    if(heapGetMax(hHeap) == 2)
    {
        char success[] = "[SUCCESS] heapGetMax successfully returns the top of the heap\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapGetMax doesn't return the top of the heap\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapDestroy(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 2);
    heapInsert(hHeap, 3);

    heapDestroy(&hHeap);

    if(hHeap == NULL)
    {
        char success[] = "[SUCCESS] heapDestroy successfully destroys heap\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapDestroy doesn't destroy heap\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

/*******************************************************
 *                  test_heapInsert_
 * ****************************************************/

bool test_heapInsert_resize(char* buffer, int size)
{
    HEAP hHeap = heapInit();

    for(int i = 0; i < 16; i++)
        heapInsert(hHeap, i);

    Heap* pHeap = (Heap*)hHeap;

    if(pHeap->capacity == 30)
    {
        char success[] = "[SUCCESS] heapInsert correctly resizes array\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapInsert doesn't resize array\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapInsert_fixUp(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 9);
    heapInsert(hHeap, 2);
    heapInsert(hHeap, 10);
    heapInsert(hHeap, 3);

    if(heapGetMax(hHeap) == 10)
    {
        char success[] = "[SUCCESS] heapInsert properly implements max heap property\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapInsert doesn't properly implement max heap property\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false; 
}

bool test_heapInsert_incrementSize(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    for(int i = 0; i < 5; i++)
        heapInsert(hHeap, i);

    Heap* pHeap = (Heap*)hHeap;
    if(pHeap->size == 5)
    {
        char success[] = "[SUCCESS] heapInsert successfully increments heap size\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapInsert doesn't increment heap size\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

/*******************************************************
 *                  test_heapRemove_
 * ****************************************************/

bool test_heapRemove_onEmpty(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    if(heapRemoveTop(hHeap))
    {
        char success[] = "[SUCCESS] heapRemoveTop successfully handles a heap with no data\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemoveTop doesn't handle a heap with no data\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapRemove_fixDown(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 9);
    heapInsert(hHeap, 2);
    heapInsert(hHeap, 10);
    heapInsert(hHeap, 3);

    heapRemove(hHeap, 10);
    heapRemove(hHeap, 1);
    heapRemove(hHeap, 9);

    if(heapGetMax(hHeap) == 3)
    {
        char success[] = "[SUCCESS] heapRemove properly implements max heap property\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemove doesn't properly implement max heap property\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;  
}

bool test_heapRemove_decrementSize(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    for(int i = 0; i < 5; i++)
        heapInsert(hHeap, i);

    heapRemove(hHeap, 1);
    heapRemove(hHeap, 2);
    heapRemove(hHeap, 10); // shouldn't decrement because it is not in heap

    Heap* pHeap = (Heap*)hHeap;
    if(pHeap->size == 3)
    {
        char success[] = "[SUCCESS] heapRemove successfully decrements size\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemove doesn't decrement size\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

/*******************************************************
 *                test_heapRemoveTop_
 * ****************************************************/

bool test_heapRemoveTop_onEmpty(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    if(heapRemoveTop(hHeap))
    {
        char success[] = "[SUCCESS] heapRemoveTop successfully handles a heap with no data\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemoveTop doesn't handle a heap with no data\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}

bool test_heapRemoveTop_fixDown(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    heapInsert(hHeap, 1);
    heapInsert(hHeap, 9);
    heapInsert(hHeap, 2);
    heapInsert(hHeap, 10);
    heapInsert(hHeap, 3);

    heapRemoveTop(hHeap);
    heapRemoveTop(hHeap);
    heapRemoveTop(hHeap);

    if(heapGetMax(hHeap) == 2)
    {
        char success[] = "[SUCCESS] heapRemoveTop properly implements max heap property\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemoveTop doesn't properly implement max heap property\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;  
}

bool test_heapRemoveTop_decrementSize(char* buffer, int size)
{
    HEAP hHeap = heapInit();
    for(int i = 0; i < 5; i++)
        heapInsert(hHeap, i);

    for(int i = 0; i < 5; i++)
        heapRemoveTop(hHeap);

    Heap* pHeap = (Heap*)hHeap;
    if(pHeap->size == 0)
    {
        char success[] = "[SUCCESS] heapRemove successfully decrements size\n";
        strncpy(buffer, success, strlen(success));
        heapDestroy(&hHeap);
        return true;
    }

    char fail[] = "[FAILED] heapRemove doesn't decrement size\n";
    strncpy(buffer, fail, strlen(fail));
    heapDestroy(&hHeap);
    return false;
}