#include "timer.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
//code for getting rid of repetitions, and c++ 
timer<> t;

template <typename I>
void set_timed(const std::size_t n, I first, I last) {//to get rid of repetition is contained in this set  set starts from first element, it creates a balanced tree_ value type = T
  t.start();
  using value_type = typename std::iterator_traits<I>::value_type;//typename serves to identify value_type as
  std::set<value_type> set{first, last};
  t.stop();
}

template <typename I>
void vector_timed(const std::size_t n, I first, I last) {
  t.start();
  using value_type = typename std::iterator_traits<I>::value_type;
  std::vector<value_type> v{first, last};
  std::sort(first, last);
  auto it = std::unique(v.begin(), v.end());//returns an iterator- if yoi have a sequence, it gets rid of duplicates std unique returns the iterator one past the last one


  t.stop();
(void)std::distance(first,it);

}

using namespace std::chrono;
int main() {
  using value_type = int;
  for (std::size_t n = 16; n < (1 << 25); n <<= 1) {//n bit shift, faster than multiplication
    std::vector<value_type> v(n);
    std::iota(v.begin(), v.end(), value_type(-1024));
    std::random_shuffle(v.begin(), v.end());
    for (std::size_t i = 0; i < n; ++i) {
      v[i] = int{v[i]} & 1023;//bit mask number bits higher than this number will be set to zero
//number 1024 the comparison gives zero number 1025 gives 1  n=16 at the end of each iteration i do a left shift of one bit, multiply by two
    }
    std::cout << std::setw(15) << n << "\t";
    // set_timed(n,v.begin(),v.end());
 
//three iterators are passed
   vector_timed(n, v.begin(), v.end());
  }//std_vector is a faster method,modern computers are fast when elements are contiguous in memory-. how many operations we do constructing a set?
}
