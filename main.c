#include <stdio.h>
#include "maxHeap.h"
#include <time.h>

int main(int argc, char* argv[])
{
	clock_t start, end;
	double time;
	int i, num = 10000;
	int successfulInserts = num;

	start = clock();
	HEAP hHeap = heapInit();

	for(i = 0; i < num; i++)
	{
		if(!heapInsert(hHeap, i))
		{
			printf("Failed to insert\n");
			successfulInserts--;
		}
	}

	heapDestroy(&hHeap);

	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Number of elements added: %d\n", successfulInserts);
	printf("Time elapsed: %f\n", time);
	return 0;
}
