#include <ios>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <chrono>
int BLS(int *array, int size, int target);
int SLS(int *array, int size, int target);
int OAS(int *array, int size, int target);
int BS(int *array, int size, int target);


void generate_random(int *arr, int arrLength,int mod);
void generate_up(int *arr, int arrLength, int mod);

typedef int(*FUNC)(int*, int, int);


FUNC functions_ord[2] = {&OAS,BS};
FUNC functions_rand[2] = {&BLS,&SLS};


int main(){
	int target = 100005;
	printf("\t\tOAS\tBS\t\t\tBLS\tSLS\n");
	FILE *file;
	file = fopen("ready.txt", "w+");
	fprintf(file,"\t\tOAS\tBS\t\t\tSLS\tBLS\n");
	for(int j = 0; j < 4; j++){
			switch(j)
			{
				case 0:{ 
								fprintf(file, "Start: \n");
								break;
							 }
				case 1:{
								 fprintf(file, "Middle: \n");
								 break;
							 }
				case 2:{
								 fprintf(file, "End: \n");
								 break;
							 }
				case 3:{
									fprintf(file, "Nowhere: \n");
									break;
							 }
			}
		for(int n = 10000; n < 200000; n+=9500){
			int array_rand[n];
			generate_random(array_rand, n, 100000);
			int array_sort[n];
			generate_up(array_sort, n, 100000);

			switch(j)
			{
				case 0:{ 
								array_rand[0] = target;
								array_sort[0] = target;
								break;
							 }
				case 1:{
								 array_rand[int(n/2)];
								 array_sort[int(n/2)];
								 break;
							 }
				case 2:{
								 array_rand[int(n-1)];
								 array_sort[int(n-1)];
								 break;
							 }
				case 3:{
									break;
							 }
			}

			std::chrono::__enable_if_is_duration<std::chrono::duration<long int, std::ratio<1, 1000000> > > time_ord[2];
			std::chrono::__enable_if_is_duration<std::chrono::duration<long int, std::ratio<1, 1000000> > > time_rand[2];

			for(int i = 0; i < 2; ++i){
				auto begin = std::chrono::steady_clock::now();
				functions_ord[i](array_sort, n, target);
				auto end = std::chrono::steady_clock::now();
				time_ord[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

				begin = std::chrono::steady_clock::now();
				functions_rand[i](array_rand, n, target);
				end = std::chrono::steady_clock::now();
				time_rand[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
			}
			
			printf("%d\t\t%d\t%d\t\t\t%d\t%d\n",n ,time_ord[0], time_ord[1], time_rand[0], time_rand[1]);
			fprintf(file,"%d\t\t%d\t%d\t\t\t%d\t%d\n",n ,time_ord[0], time_ord[1], time_rand[0], time_rand[1]);
		}
	}
	fclose(file);
}




int BLS(int *array, int size, int target){
	for(int i = 0; i < size; ++i){
		if(array[i] == target){
			return i;
		}
	}
	return -1;
}

int SLS(int *array, int size, int target){
	int* array2 = (int*)malloc((size+1) * sizeof(int));
	std::memcpy(array2, array, size*sizeof(int));
	array2[size] = target;
	int i = 0;
	while(array2[i] != target)
		++i;
	if(i == size+1){
		delete array2;
		return -1;
	}
	delete array2;
	return i;
}

int OAS(int *array, int size, int target){
	for(int i = 0; i < size; ++i){
		if(array[i] == target){
			return i;
		}
	}
	return -1;
}

int BS(int *array, int size, int target){
	int low = 0;
	int high = size-1;
	while(low<=high){
		int mid = low + (high-low)/2;
		if(array[mid] == target)
			return mid;
		else if(array[mid] < target)
			high = mid-1;
		else if(array[mid] > target)
			low = mid+1;
	}
	return -1;
}

void generate_random(int *arr, int arrLength,int mod) {
	for (int i = 0; i < arrLength; ++i)
		arr[i]=rand()%mod;
}
void generate_up(int *arr, int arrLength, int mod) {
	for(int i = 0; i <  arrLength; ++i)
		arr[i] = i*double(mod)/double(arrLength);
}

