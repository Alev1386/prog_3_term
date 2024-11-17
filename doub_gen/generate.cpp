#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>


void generate_saw(double *a, int size, double mod, double range);
void generate_sin(double *a, int size, double mod, double range);
void generate_lad(double *a, int size, double mod, double range);

void generate_up(double *arr, int arrLength, double mod,double range);
void generate_down(double *arr, int arrLength, double mod, double range);
void generate_random(double *arr, int arrlength, double mod, double range);

void write_at_file(double *array, int size, std::string filename);

typedef void(*FUNC)(double*, int, double, double);
FUNC functions[6] = {&generate_saw, &generate_sin, &generate_lad, generate_up, &generate_down, &generate_random};


int main(){
	int modu = 10;
	int ran = 10;
	int data[10] = {5,10,15,20,25,30,35,40,45,50};
	for(int i = 0; i < 10; ++i){
		data[i] *= 100000;
	}
	std::string **files = new std::string*[6];
	for(int i = 0; i < 6; i++)
	  files[i] = new std::string[10];
	files[0][0] = "saw_generated1.txt";
	files[0][1] = "saw_generated2.txt";
	files[0][2] = "saw_generated3.txt";
	files[0][3] = "saw_generated4.txt";
	files[0][4] = "saw_generated5.txt";
	files[0][5] = "saw_generated6.txt";
	files[0][6] = "saw_generated7.txt";
	files[0][7] = "saw_generated8.txt";
	files[0][8] = "saw_generated9.txt";
	files[0][9] = "saw_generated10.txt";
	
	files[1][0] = "sin_generated1.txt";
	files[1][1] = "sin_generated2.txt";
	files[1][2] = "sin_generated3.txt";
	files[1][3] = "sin_generated4.txt";
	files[1][4] = "sin_generated5.txt";
	files[1][5] = "sin_generated6.txt";
	files[1][6] = "sin_generated7.txt";
	files[1][7] = "sin_generated8.txt";
	files[1][8] = "sin_generated9.txt";
	files[1][9] = "sin_generated10.txt";
	
	files[2][0] = "lad_generated1.txt";
	files[2][1] = "lad_generated2.txt";
	files[2][2] = "lad_generated3.txt";
	files[2][3] = "lad_generated4.txt";
	files[2][4] = "lad_generated5.txt";
	files[2][5] = "lad_generated6.txt";
	files[2][6] = "lad_generated7.txt";
	files[2][7] = "lad_generated8.txt";
	files[2][8] = "lad_generated9.txt";
	files[2][9] = "lad_generated10.txt";
	
	files[3][0] = "up_generated1.txt";
	files[3][1] = "up_generated2.txt";
	files[3][2] = "up_generated3.txt";
	files[3][3] = "up_generated4.txt";
	files[3][4] = "up_generated5.txt";
        files[3][5] = "up_generated6.txt";
        files[3][6] = "up_generated7.txt";
        files[3][7] = "up_generated8.txt";
        files[3][8] = "up_generated9.txt";
        files[3][9] = "up_generated10.txt";
	
	files[4][0] = "down_generated1.txt";
	files[4][1] = "down_generated2.txt";
	files[4][2] = "down_generated3.txt";
	files[4][3] = "down_generated4.txt";
	files[4][4] = "down_generated5.txt";
	files[4][5] = "down_generated6.txt";
	files[4][6] = "down_generated7.txt";
	files[4][7] = "down_generated8.txt";
	files[4][8] = "down_generated9.txt";
	files[4][9] = "down_generated10.txt";
	
	files[5][0] = "random_generated1.txt";
	files[5][1] = "random_generated2.txt";
	files[5][2] = "random_generated3.txt";
	files[5][3] = "random_generated4.txt";
	files[5][4] = "random_generated5.txt";
	files[5][5] = "random_generated6.txt";
	files[5][6] = "random_generated7.txt";
	files[5][7] = "random_generated8.txt";
	files[5][8] = "random_generated9.txt";
	files[5][9] = "random_generated10.txt";
	
	const char* data_files[] = {"data_files1.txt","data_files2.txt","data_files3.txt","data_files4.txt","data_files5.txt","data_files6.txt", "data_files7.txt", "data_files8.txt", "data_files9.txt", "data_files10.txt"};
	
	
	for(int i = 0; i < 10; ++i){
	  int size = data[i];
	  double *array = new double[size];
	  std::chrono::__enable_if_is_duration<std::chrono::duration<long int, std::ratio<1, 1000000> > > time[6];
	  for(int j = 0; j < 6; j++){
	    auto begin = std::chrono::steady_clock::now();
	    functions[j](array, size, modu, ran);
	    auto end = std::chrono::steady_clock::now();
	    time[j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	    write_at_file(array, size, files[j][i]);
          }
	  FILE *file;
	  const char* df = data_files[i];
	  file = fopen(df, "w+");
	  fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d", time[0], time[1], time[2], time[3], time[4], time[5]);
	  fclose(file);
	}
	return 0;
}



void generate_up(double *arr, int arrLength, double mod, double range) {
	for(int i = 0; i <  arrLength; ++i)
		arr[i] = i*double(mod)/double(arrLength);
}

void generate_down(double *arr, int arrLength, double mod, double range) {
	for(int i = 0; i < arrLength; ++i)
		arr[i] = (arrLength - i)*double(mod)/double(arrLength);
}

void generate_random(double *arr, int arrLength,double mod, double range) {
	for (int i = 0; i < arrLength; ++i)
		arr[i] = (double)rand() / RAND_MAX * (mod);
}

void generate_saw(double *a, int size, double mod, double range){//saw
	int c = 0;
	while(c < size){
		int cur = 0;
		while(cur < range && c < size){
			a[c] = int(cur*mod/range);
			c++;
			cur++;
		}
	}
}
void generate_sin(double *a, int size, double mod, double range){//sinus
	for(int i = 0; i < size; ++i)
		a[i] = sin(2*i*3.14*range)*mod;
}
void generate_lad(double *a,int size, double mod, double range){
	int c = 0;
	int line = 0;

	while(c < size){
		int cur = 0;
		while(c < size && cur < range){
			a[c] = line + ((double)rand() / RAND_MAX *(mod/20));
			cur++;
			c++;
		}
		line+=mod;
	}
}


void write_at_file(double *array, int size, std::string filename){
	std::ofstream f;
	f.open(filename);
	for(int i = 0; i < size; ++i)
		f<<i<<'\t'<<array[i]<<'\n';
	f.close();
}
