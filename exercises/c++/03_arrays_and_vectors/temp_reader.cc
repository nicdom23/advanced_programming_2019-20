#include <iostream>
#include <vector>
#include <algorithm>

int main(){
std::vector<double> v;
std::string line;
double i;
while(std::cin >> i)
{v.push_back(i);}

std::sort( v.begin(), v.end() );
double sum{0};
for (int i{0};i<v.size();i++)
	sum += v[i];

std::cout<<"mean:  "<<sum/v.size()<<std::endl;
double median{0};
if (v.size()%2 == 0)
	median =(v[v.size()/2]+v[v.size()/2+1])/2;
else median = v[v.size()/2+1];
std::cout<<"median:  "<< median <<std::endl;


return 0;
}
