#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include <stdbool.h>

bool test_heapInit(char* buffer, int size);
bool test_heapInsert(char* buffer, int size);
bool test_heapRemove(char* buffer, int size);
bool test_heapRemoveTop(char* buffer, int size);
bool test_heapGetMax(char* buffer, int size);
bool test_heapDestroy(char* buffer, int size);

bool test_heapInsert_resize(char* buffer, int size);
bool test_heapInsert_fixUp(char* buffer, int size);
bool test_heapInsert_incrementSize(char* buffer, int size);

bool test_heapRemove_onEmpty(char* buffer, int size);
bool test_heapRemove_fixDown(char* buffer, int size);
bool test_heapRemove_decrementSize(char* buffer, int size);

bool test_heapRemoveTop_onEmpty(char* buffer, int size);
bool test_heapRemoveTop_fixDown(char* buffer, int size);
bool test_heapRemoveTop_decrementSize(char* buffer, int size);

#endif