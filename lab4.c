#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

long long countbubble = 0;
long long countinsertion = 0;
long long countmerge = 0;


void BubbleSort(int* arr, int n) {
	countbubble = 0;
	bool swapped;

	for (int i = 0; i < n - 1; i++) {
        	swapped = false;
        	for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
                		int temp = arr[j];
                		arr[j] = arr[j + 1];
                		arr[j + 1] = temp;
                		countbubble++;
				swapped = true;
            		}
        	}
		if (!swapped) break;
	}
}

void InsertionSort(int* arr, int n) {
	countinsertion = 0;

        for (int i = 1; i < n; i++) {
		int k = arr[i];
                int j = i - 1;
                while (j >= 0 && arr[j] > k) {
			arr[j + 1] = arr[j];
                        j--;
                        countinsertion++;
		}
                arr[j + 1] = k;
	}
}

void merge(int* arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
	int n2 = right - mid;

        int *L = (int*)malloc(n1 * sizeof(int));
        int *R = (int*)malloc(n2 * sizeof(int));

        if (L == NULL || R == NULL) {
                printf("Ошибка выделения памяти!\n");
                exit(1);
        }

        for (int i = 0; i < n1; i++)
                L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
                R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
                if (L[i] <= R[j]) {
                        arr[k] = L[i];
			i++;
        	} else {
                	arr[k] = R[j];
               		j++;
        	}
        	k++;
        	countmerge++;
    	}

    	while (i < n1) {
        	arr[k] = L[i];
        	i++; k++;
    	}
    		while (j < n2) {
        	arr[k] = R[j];
        	j++; k++;
    	}

    	free(L);
    	free(R);
}

void mergeSortRecursive(int* arr, int left, int right) {
    	if (left >= right) return;
	int mid = left + (right - left) / 2;
   	 mergeSortRecursive(arr, left, mid);
   	 mergeSortRecursive(arr, mid + 1, right);
   	 merge(arr, left, mid, right);
}

void mergeSort(int* arr, int n) {
	countmerge = 0;
   	mergeSortRecursive(arr, 0, n - 1);
}

void generateRandomArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
        	arr[i] = rand() % 10000;
    	}
}

void copyArray(int* dest, const int* src, int size) {
    	for (int i = 0; i < size; i++) {
        	dest[i] = src[i];
    	}
}

int main() {
srand((unsigned int)time(NULL));
	int sizes[] = {10, 1000, 10000, 100000};
    	int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    	printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n",
		"Размер", "    Пузырёк(сек)", "   Вставки(сек)", "   Слияние(сек)",
        	"  Перест.пузырёк", " Сдвиги вставки", " Слияния");
    	for(int i=0; i<115; i++) printf("-");
    	printf("\n");

    	for (int s = 0; s < numSizes; s++) {
        	int size = sizes[s];
        	int* original = (int*)malloc(size * sizeof(int));
        	int* arrbubble = (int*)malloc(size * sizeof(int));
        	int* arrinsertion = (int*)malloc(size * sizeof(int));
        	int* arrmerge = (int*)malloc(size * sizeof(int));

        	if (original == NULL || arrbubble == NULL || arrinsertion == NULL || arrmerge == NULL) {
            		printf("Ошибка выделения памяти!\n");
            		return 1;
        	}

        	generateRandomArray(original, size);
        	copyArray(arrbubble, original, size);
        	copyArray(arrinsertion, original, size);
        	copyArray(arrmerge, original, size);

	clock_t start, end;
	start = clock();
	BubbleSort(arrbubble, size);
	end = clock();
	double sbubble = (double)(end - start)/CLOCKS_PER_SEC;

	start = clock();
        InsertionSort(arrinsertion, size);
        end = clock();
        double sinsertion = (double)(end - start)/CLOCKS_PER_SEC;

	start = clock();
        mergeSort(arrmerge, size);
        end = clock();
        double smerge = (double)(end - start)/CLOCKS_PER_SEC;
	printf("%-10d %-15.6f %-15.6f %-15.6f %-15lld %-15lld %-15lld\n",
               size,
               sbubble,
               sinsertion,
               smerge,
               countbubble,
               countinsertion,
               countmerge);
	free(original);
	free(arrbubble);
	free(arrinsertion);
	free(arrmerge);
}
	return 0;
}
