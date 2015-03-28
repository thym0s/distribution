#include "result.h"

result_t result( unsigned int points ) {
  return result_t( points );
}

relation_t relation( const result_t & r1 , const result_t & r2 ) {
  return float( r1.points_ - r2.points_ );
}

bool operator<( const result_t & r1 , const result_t & r2 ) {
  return 0 > relation( r1 , r2 );
}

bool operator<=( const result_t & r1 , const result_t & r2 ) {
  return !( r2 < r1 );
}

bool operator>( const result_t & r1 , const result_t & r2 ) {
  return r2 < r1;
}

bool operator>=( const result_t & r1 , const result_t & r2 ) {
  return !( r1 < r2 );
}

bool operator==( const result_t & r1 , const result_t & r2 ) {
  return r1.points_ == r2.points_;
}

