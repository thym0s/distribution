#include <vector>
#include <utility>
#include <iostream>
#include "monotone.h"

int main( int argc , char ** argv ) {
  std::vector< unsigned int > a = { 6 , 0 , 0 };
  std::vector< unsigned int > b = { 1 , 2 , 1 };
  for ( auto i : a ) {
    std::cout << i << ' ';
  }
  dist_monotone( a.begin() , a.end() , b.begin() , 6 , 3 );
  for ( auto i : a ) {
    std::cout << i << ' ';
  }
  next_monotone( a.begin() , a.end() , b.begin() );
  for ( auto i : a ) {
    std::cout << i << ' ';
  }
  return 0;
}

