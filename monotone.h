#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

/* Distributes amount greedily in [ first , last ),
   each share not exceeding limit.
   Returns the unused amount.
*/
template < class BidirectionalIterator1 ,
           class BidirectionalIterator2 ,
           class T >
T dist_monotone( BidirectionalIterator1 first ,
                 BidirectionalIterator1 last ,
                 BidirectionalIterator2 first_weight ,
                 T                      amount ,
                 T                      limit ) {
  if( first == last ) {
    return amount;
  } else {
    *first = limit = std::min< T >( amount / *first_weight , limit );
    amount = amount - *first * *first_weight;
    return dist_monotone< BidirectionalIterator1 ,
                          BidirectionalIterator2 ,
                          T > ( ++first ,
                                last ,
                                ++first_weight ,
                                amount ,
                                limit );
  }
}

/* Calculates the next monotone decreasing partition (in the lexicographic order)
   in [ first , last ), with additional amount.
   The variable amount is changed to the amount remaining after the distribution.
   Returns false iff the partition was the last one in the order, and changes it to
   the first one.
*/
template < class BidirectionalIterator1 ,
           class BidirectionalIterator2 ,
           class T >
bool next_monotone_r( BidirectionalIterator1 first ,
                      BidirectionalIterator1 last ,
                      BidirectionalIterator2 first_weight ,
                      T & amount ) {
  typedef
    typename std::reverse_iterator< BidirectionalIterator1 >
    rit_type;
  typedef
    typename std::iterator_traits< BidirectionalIterator1 >::value_type
    value_type;
  bool ret = false;
  T limit( 0 );
  auto pr = std::find_if( rit_type( last ) ,
                          rit_type( first ) ,
                          std::bind( std::less< value_type >() ,
                                     value_type(1) ,
                                     std::placeholders::_1 ) );
  auto p = pr.base();
  auto q = first_weight + ( p - first );
  limit = amount = std::inner_product( p , last , q , amount );
  if( p != first ) {
    limit = *( p - 1 ) = *( p - 1 ) - 1;
    amount = amount + value_type( 1 ) * *( q - 1 );
    ret = true;
  }
  amount = dist_monotone( p , last ,  q , amount , limit );
  return ret;
}

/* Calculates the next monotone decreasing partition (in the lexicographic order)
   in [ first , last ).
   Returns false iff the partition was the last one in the order, and changes it to
   the first one.
*/
template < class BidirectionalIterator1 ,
           class BidirectionalIterator2 >
bool next_monotone( BidirectionalIterator1 first ,
                    BidirectionalIterator1 last ,
                    BidirectionalIterator2 first_weight ) {
  typedef 
    typename std::iterator_traits< BidirectionalIterator1 >::value_type
    value_type;
  bool ret = true;
  value_type remainder( 0 );
  do {
    ret &= next_monotone_r( first ,
                            last ,
                            first_weight,
                            remainder );
  } while( remainder != 0 );
  return ret;
}

