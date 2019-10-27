#include <iostream>


enum class month_type { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };  

class Date {//here not everything is public but defaut visibility of the symbols is private!!
private: //implied
  unsigned int _day;
  month_type _month;
  unsigned int _year;

 public: //defined a function is inside the class and can access private variables
  
	Date(const unsigned int day,month_type month,const unsigned int year);
	unsigned int day() const{return _day;}
        month_type month() const{return _month;}
	unsigned int year() const{return _year;}
	void add_day();
	void add_n_days(int n,Date date);
	void print(){
	std::cout << _day<<"/"<<static_cast<int>(_month)<<"/"<<_year<<std::endl;}


	  // note no ; at the end
};   // note ; at the end of the declaration
Date::Date(const unsigned int day,month_type month,const unsigned int year)
	:_day{day},_month{month},_year{year}
	{std::cout<<"date built\n";}	

//void Date::print_date(Date date){
//std::cout << date._day<<"/"<<date._month<<"/"<<date._year;
//}

//std::ostream& operator<<(std::ostream& os, const Foo& f) {//operator overloading
  //os << f._i << " " << f._d << " " << f._s << std::endl;
 // return os;
//}


void Date::add_day(){

switch (_month){
	case month_type::jan: 
	if(_day==31) {_month=month_type::feb;
			_day=1;}
	else _day++;
	break;
	case month_type::mar:
	if(_day==31) {_month=month_type::apr;
			_day=1;}
	else _day++;	
	break;
	case month_type::may:
	if(_day==31) {_month=month_type::jun;
			_day=1;}
	else _day++;
	break;
	case month_type::jul:
if(_day==31) {_month=month_type::aug;
			_day=1;}
	else _day++;
	break; 
	case month_type::aug: 
if(_day==31) {_month=month_type::sep;
			_day=1;}
	else _day++;
	break;
	case month_type::oct:
if(_day==31) {_month=month_type::nov;
			_day=1;}
	else _day++;
	break;
 case month_type::dec:

if(_day==31) {_month=month_type::jan;
			_day=1;_year=_year+1;}
	else _day++;
	break;

	case month_type::apr: 
	
if(_day==30) {_month=month_type::may;
			_day=1;}
	else _day++;
	break;
case month_type::jun: 

if(_day==30) {_month=month_type::jul;
			_day=1;}
	else _day++;
	break;
case month_type::sep:

if(_day==30) {_month=month_type::oct;
			_day=1;}
	else _day++;
	break;
	case month_type::nov:

if(_day==30) {_month=month_type::dec;
			_day=1;}
	else _day++;
	break;

	case month_type::feb :
		
if(_day==28) {_month=month_type::mar;
			_day=1;}
	else _day++;
	break;
	default:
		std::cout << "not a month\n";
		break;
	}

//std::cout <<"day_added"<<std::endl;
}
void add_n_days(int n,Date& date){
for(int i =0;i<n;i++) date.add_day();
std::cout<<"added "<<n<<" days"<< std::endl;
}
bool operator==(const Date& lhs, const Date& rhs){
 bool a = lhs.day()==rhs.day();
 bool b = static_cast<int>(lhs.month()) == static_cast<int>(rhs.month());
 bool c = lhs.year()==rhs.year();
return a && b && c;
}
bool operator!=(const Date& lhs, const Date& rhs){
return !(lhs==rhs);
}
std::ostream& operator<<(std::ostream& os, const Date& d){
 os << d.day()<<"/"<<static_cast<int>(d.month())<<"/"<<d.year()<<std::endl;
	return os;
}
bool is_leap(const int y){
return( y%4==0 && y%400!=0)
}
int main(){
Date date{11,month_type::may,1996};
date.print();
date.add_day();
date.print();
add_n_days(20,date);
date.print();
add_n_days(200,date);
date.print();
add_n_days(366,date);
date.print();
Date date1{12,month_type::jun,1996};
Date date2{12,month_type::jun,1996};
bool e = (date1==date2);
std::cout<<"equal?"<<e<<std::endl;
date2.add_day();
e = (date1==date2);
std::cout<<"equal?"<<e<<std::endl;
e = (date1!=date2);
std::cout<<"not_equal?"<<e<<std::endl;
std::cout<< date2;
return 0;
}
