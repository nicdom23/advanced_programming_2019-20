#include <iostream>
#include <string>

int main() {
  std::cout << "Insert measure:\n";
  std::string unit;
  unsigned int measure;
  std::cin >> measure >> unit;

if(unit == "inches" || unit =="inch")
	std::cout << "Measure " << measure << " " << unit << " equals " << measure*0.0254 << " meters";
else if(unit == "yards" || unit =="yard")
	std::cout << "Measure " << measure << " " << unit << " equals " << measure*0.9144 << " meters";
else if(unit == "feets" || unit =="foot")
	std::cout << "Measure " << measure << " " << unit << " equals " << measure*0.3048 << " meters";
else if(unit == "pound" || unit =="pounds")
	std::cout << "Measure " << measure << " " << unit << " equals " << measure*0.453592 << " kilograms";
else 
	std::cout << "Conversion unavailable!";
 std::cout << std::endl;
  return 0;
}
