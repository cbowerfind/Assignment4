#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temporary arrays */
    int L[n1], R[n2];

    /* copy data to temporary arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = pData[l + i];
    for (j = 0; j < n2; j++)
        R[j] = pData[m + 1 + j];

    /* merge the temporary arrays back into pData[l..r]*/
    i = 0; /* initial index of first subarray */
    j = 0; /* initial index of second subarray */
    k = l; /* initial index of merged subarray */
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        } else {
            pData[k] = R[j];
            j++;
        }
        k++;
    }

    /* copy the remaining elements of L[], if there are any */
    while (i < n1) {
        pData[k] = L[i];
        i++;
        k++;
    }

    /* copy the remaining elements of R[], if there are any */
    while (j < n2) {
        pData[k] = R[j];
        j++;
        k++;
    }
    extraMemoryAllocated = (n1 + n2) * sizeof(int);
}

void mergeSortRecursion(int pData[], int l, int r) {
    if (l < r) {
        // same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;

        // sort first and second halves
        mergeSortRecursion(pData, l, m);
        mergeSortRecursion(pData, m + 1, r);

        merge(pData, l, m, r);
    }
}

void mergeSort(int pData[], int l, int r) {
    mergeSortRecursion(pData, l, r);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = pData[i];
        j = i - 1;

        /* Move elements of pData[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && pData[j] > key) {
            pData[j + 1] = pData[j];
            j = j - 1;
        }
        pData[j + 1] = key;
    }
    extraMemoryAllocated = 0;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    extraMemoryAllocated = 0;
    int i, j, temp;
    for(i = 0; i < n-1; ++i) {
        for(j = 0; j < n-i-1; ++j) {
            if(pData[j] > pData[j+1]) {
                // swap pData[j] and pData[j+1]
                temp = pData[j];
                pData[j] = pData[j+1];
                pData[j+1] = temp;
            }
        }
    }
}
   
void selectionSort(int* pData, int n)
{
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < n; j++)
        {
            if (pData[j] < pData[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            temp = pData[i];
            pData[i] = pData[minIndex];
            pData[minIndex] = temp;
        }
    }
}

int parseData(char *inputFileName, int **ppData)
            {
                FILE* inFile = fopen(inputFileName,"r");
                int dataSz = 0;
                *ppData = NULL;
                
                if (inFile)
                {
                    fscanf(inFile,"%d\n",&dataSz);
                    *ppData = (int *)malloc(sizeof(int) * dataSz);
                    for (int i = 0; i < dataSz; i++) {
                        fscanf(inFile, "%d", &(*ppData)[i]);
                    }
                }
                
                fclose(inFile);
                return dataSz;
            }

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
