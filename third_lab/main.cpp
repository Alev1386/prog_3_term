#include <iostream>
#include <stdlib.h>
// shaker, fast
void shaker(int *arr, int size, int base);
void quick(int *arr, int low, int high);
void gen_rand(int* arr,int size);




int main(){
	int size[4] = {500, 1000, 10000, 50000}
	for(int i = 0; i < 4; ++i){
		int array[4][size[i]];
		gen_rand(array[0], size[i]);
		for(int i = 1; i < 4; ++i){
			std::memcpy(array[i], array[0], size[i]);
		}



	}
}

void quick(int* arr, int low, int high){
	
	


}


void shaker(int *arr, int size, int base){
	bool flag = true;
	for(int i = 0; i < size; ++i){
		if(flag == true){
			for(int j = i+1; j < size; ++j){
				if(arr[j]<arr[j-1])
					std::swap(arr[j],arr[j-1]);
			}
			flag = false;
		}



		else{
			for(int j = size-i+1; j > i; --j){
				if(arr[j]<arr[j-1])
					std::swap(arr[j],arr[j-1]);
			}
			flag = true;	
		}
	}
}

void gen_rand(int* arr, int size){
	for(int i = 0; i < size; ++i){
		arr[i] = rand();
	}
}
