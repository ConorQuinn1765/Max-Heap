#include <stdio.h>
#include <string.h>
#include "unitTest.h"

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

int main(void)
{
    bool (*tests[])(char*, int) = 
    {
        test_heapInit,
        test_heapInsert,
        test_heapRemove,
        test_heapRemoveTop,
        test_heapGetMax,
        test_heapDestroy,
        test_heapInsert_resize,
        test_heapInsert_fixUp,
        test_heapInsert_incrementSize,
        test_heapRemove_onEmpty,
        test_heapRemove_fixDown,
        test_heapRemove_decrementSize,
        test_heapRemoveTop_onEmpty,
        test_heapRemoveTop_fixDown,
        test_heapRemoveTop_decrementSize
    };
    int successCount = 0;

    for(int i = 0; i < ARR_SIZE(tests); i++)
    {
        const int bufSize = 500;
        char buffer[bufSize];
        memset(buffer, 0, bufSize);

        if(tests[i](buffer, bufSize))
            successCount++; 

        printf("%s\n", buffer);
    }

    printf("%d/%ld tests succeeded\n", successCount, ARR_SIZE(tests));

    return 0;
}