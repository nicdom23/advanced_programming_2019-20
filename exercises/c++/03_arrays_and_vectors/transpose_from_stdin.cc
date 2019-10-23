#include <iostream>
#include <vector>
#include <utility>
#include <sstream>

std::vector<double> give_transpose(std::vector<double> vector, int size_rows, int size_columns);

int main(int argc,char ** argv){
	

std::vector<double> vector;
int size_rows;

{
  std::istringstream is{argv[1]};
  is >> size_rows;
}
int size_columns;
{
  std::istringstream is{argv[2]};
  is >> size_columns;
}
	
	for(int i{1};i<size_rows*size_columns+1;i++){
		vector.push_back(i);
		}


for (int i{0};i<size_rows;i++){
	for(int j{0};j<size_columns;j++){
		std::cout<<" "<< vector[i*size_columns+j];		
		}	
	std::cout<<std::endl;
	}
std::cout<<std::endl;
std::vector <double> transp = give_transpose(vector, size_rows, size_columns);


for (int i{0};i<size_columns;i++){
	for(int j{0};j<size_rows;j++){
		std::cout<<" "<< transp[i*size_rows+j];		
		}	
	std::cout<<std::endl;
	}
return 0;
}

std::vector <double> give_transpose(std::vector<double> vector,int size_rows,int size_columns)
{
std::vector<double> transpose (vector);

for (int i{0};i<size_rows;i++){
	for(int j{0};j<size_columns;j++){
 //std::cout<< "swappy";
	
//transpose.push_back(vector[size_columns*i+j]);
	std::swap(vector[size_columns*i+j],transpose[size_rows*j+i]);//transpose[25-(size_columns*i+j)-1]
					}
	      }

return transpose;
}
