#include <iostream>
#include <array>
#include <utility>
#define CNAME 10
std::array<double,CNAME> give_transpose(std::array<double,CNAME> array, int size_rows, int size_columns);

int main(){
	//const int N = 25;
	int size_rows = 2;
	int size_columns = 5;	
	std::array<double,CNAME> array{1,2,3,4,5,6,7,8,9,10};



for (int i{0};i<size_rows;i++){
	for(int j{0};j<size_columns;j++){
		std::cout<<" "<< array[i*size_columns+j];		
		}	
	std::cout<<std::endl;
	}
std::cout<<std::endl;
std::array<double,CNAME> transp = give_transpose(array, size_rows, size_columns);
for (int i{0};i<size_columns;i++){
	for(int j{0};j<size_rows;j++){
		std::cout<<" "<< transp[i*size_rows+j];		
		}	
	std::cout<<std::endl;
	}
return 0;
}

std::array<double,CNAME> give_transpose(std::array<double,CNAME> array,int size_rows,int size_columns)
{
std::array<double,CNAME> transpose;

for (int i{0};i<size_rows;i++){
	for(int j{0};j<size_columns;j++)
		std::swap(array[size_columns*i+j],transpose[size_rows*j+i]);//transpose[25-(size_columns*i+j)-1]
	
	}

return transpose;
}
