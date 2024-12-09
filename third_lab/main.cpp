#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <chrono>
#include <fstream>
void shakerSort(int *arr, int a,int n, bool flag, int size);
void gen_rand(int* arr,int size);
void printArray(int arr[], int n);
void gen_up(int *arr, int arrLength);
void gen_down(int *arr, int arrLength);
void printArray(int arr[], int n);
int partitionLast(int arr[], int low, int high);
void quickSortLast(int arr[], int low, int high, bool flag, int size);
int medianOfThree(int arr[], int low, int high);
int partitionMedian(int arr[], int low, int high);
void quickSortMedian(int arr[], int low, int high, bool flag, int size);
int partitionHoare(int arr[], int low, int high);
void quickSortHoare(int arr[], int low, int high, bool flag, int size);


typedef void(*FUNC)(int*, int, int, bool, int);
FUNC functions[4] = {&shakerSort, &quickSortLast, &quickSortMedian, &quickSortHoare};

int pl = 0;
int pm = 0;
int ph = 0;


int main(){
	int size[5] = {15, 500, 1000, 10000, 50000};
	const char names[5][10] = {"15.txt","500.txt","1000.txt","10000.txt","50000.txt"};
	for(int i = 0; i < 5; ++i){
		bool print = false;
		if (i == 0)
			print = true;//for printing data of 15 size
		int array[3][4][size[i]];//0 - random, 1 - sorted, 2 - reverse sorted ////// 0 - shaker, 1 -quick(last), 2 - quick(median), 3 - quick(hoare)
		/*----------------filling arrays------------------*/
		gen_rand(array[0][0], size[i]);
		gen_up(array[1][0], size[i]);
		gen_down(array[2][0], size[i]);

		for (int j = 1; j < 4; j++)
		{
			std::memcpy(array[0][j],array[0][0], size[i]*sizeof(int));
			std::memcpy(array[1][j],array[1][0], size[i]*sizeof(int));
			std::memcpy(array[2][j],array[2][0], size[i]*sizeof(int));
		}
		/*-------------------------------------------------*/
		std::chrono::__enable_if_is_duration<std::chrono::duration<long int, std::ratio<1, 1000000> > > time[12];


		for (int j = 0; j < 4; j++)
		{
			if(print){//print header
				switch (j)
				{
				case 0:
					printf("\nShaker\n");
					break;
				case 1:
					printf("\nQuick(last)\n");
					break;
				case 2:
					printf("\nQuick(med)\n");
					break;
				case 3:
					printf("\nQuick(Hoare)\n");
					break;
				default:
					break;
				}
			}
			if(print)
				printf("Random: \n");
			auto begin = std::chrono::steady_clock::now();
			functions[j](array[0][j], 0, size[i],print, size[i]);
			auto end = std::chrono::steady_clock::now();
			time[j*3] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);//writing time in variable for random data
			if(print)
				printf("Sorted: \n");
			begin = std::chrono::steady_clock::now();
			functions[j](array[1][j], 0, size[i],print, size[i]);
			end = std::chrono::steady_clock::now();
			time[j*3+1] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);//writing time in variable for sorted data
			if(print)
				printf("Reversed sorted: \n");
			begin = std::chrono::steady_clock::now();
			functions[j](array[2][j], 0, size[i],print, size[i]);
			end = std::chrono::steady_clock::now();
			time[j*3+2] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);//writing time in variable for reverse sorted data

		}
		if(time[0]<time[9]){
			printf("Shaker is faster!\n");
		}
		else{
			printf("Quick is faster!\n");
		}
		
		FILE *file;//writing time in file
		file = fopen(names[i], "w+");
		for (int j = 0; j < 12; ++j)
		{
			fprintf(file,"\t%d\t", time[j]);
		}
		fclose(file);
	}
	return 0;
}

/*---------------------------SHAKER SORT-----------------------------*/
void shakerSort(int* arr, int a, int n, bool flag, int size) {
    bool swapped = true;//check status
    int start = 0;
    int end = n - 1;
	int k = 0;

    while (swapped) {
        swapped = false;//going forward
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
				k++;
                swapped = true;
            }
        }
        if(flag)
			printArray(arr, size);
		//printf("%d", flag);
        if (!swapped) break;
        swapped = false;
        --end;//going backward
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
				k++;
                swapped = true;
            }
        }
        if(flag)
			printArray(arr, size);
        ++start;
    }
	printf("shaker swaps:%d\n", k);
}
/*-------Generators--------------------------------*/
void gen_rand(int* arr, int size){
	for(int i = 0; i < size; ++i){
		arr[i] = rand()%10000;
	}
}

void gen_up(int *arr, int arrLength) {
	for(int i = 0; i <  arrLength; ++i)
		arr[i] = i*double(10000)/double(arrLength);
}

void gen_down(int *arr, int arrLength) {
	for(int i = 0; i < arrLength; ++i)
		arr[i] = (arrLength - i)*double(10000)/double(arrLength);
}

/*-------------Prints----------------*/
void printArray(int arr[], int n){
	for (int i = 0; i < n; ++i) {
		 std::cout << arr[i] << " ";
	} std::cout << std::endl;
}

/*---------------------------QUICK SORT----------------------------------------*/
/*--------------------------Last element--------------------------------*/

int partitionLast(int arr[], int low, int high) {//partition of array in two arrays by getting last element
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {//swapping elements that are less than pivot
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
			pl++;
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortLast(int arr[], int low, int high, bool flag, int size) {
    if (low < high) {
        int pi = partitionLast(arr, low, high);
        if(flag)
			printArray(arr, size);
        quickSortLast(arr, low, pi - 1, flag, size);
        quickSortLast(arr, pi + 1, high, flag, size);
    }
}

/*-----------------------------Median Element-------------------------*/
int medianOfThree(int arr[], int low, int high) {//searching median element
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
    return mid;
}

int partitionMedian(int arr[], int low, int high) {//partition of array in two arrays by getting median
    int medianIndex = medianOfThree(arr, low, high);
    std::swap(arr[medianIndex], arr[high]);
	pm++;
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {//swapping elements that are less than pivot
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortMedian(int arr[], int low, int high, bool flag, int size) {
    if (low < high) {
        int pi = partitionMedian(arr, low, high);
        if(flag)
			printArray(arr,size);
        quickSortMedian(arr, low, pi - 1, flag, size);
        quickSortMedian(arr, pi + 1, high, flag, size);
    }
}

/*------------------Hoare Element--------------------*/
int partitionHoare(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            ++i;
        } while (arr[i] < pivot);

        do {
            --j;
        } while (arr[j] > pivot);

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
		ph++;
    }
}

void quickSortHoare(int arr[], int low, int high, bool flag, int size) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        if(flag)
			printArray(arr, size); //
        quickSortHoare(arr, low, pi, flag, size);
        quickSortHoare(arr, pi + 1, high, flag, size);
    }
}




