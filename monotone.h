#include <algorithm>
#include <functional>

template < class BidirectionalIterator1 ,
           class BidirectionalIterator2 ,
           class T >
  T accumulate_weight( BidirectionalIterator1 first ,
                       BidirectionalIterator1 last ,
                       BidirectionalIterator2 first_weight ,
                       T init ) {
    for( ; first != last ; ++first , ++first_weight ) {
      init += *first * *first_weight;
    }
    return init;
  } 

template < class BidirectionalIterator1 , class BidirectionalIterator2 >
  bool dist_monotone( BidirectionalIterator1 first ,
                      BidirectionalIterator1 last ,
                      BidirectionalIterator2 first_weight ,
                      unsigned int amount ,
                      unsigned int limit ) {
    if( first == last ) {
      return false;
    } else {
      *first = limit = std::min( amount / *first_weight , limit );
      return dist_monotone( ++first , last , ++first_weight , amount - *first , limit );
    }
  }

template < class BidirectionalIterator1 , class BidirectionalIterator2 >
  bool next_monotone( BidirectionalIterator1 first ,
                      BidirectionalIterator1 last ,
                      BidirectionalIterator2 first_weight ) {
    std::reverse_iterator< BidirectionalIterator1 > pr =
      std::find_if( std::reverse_iterator< BidirectionalIterator1 >( last ) ,
                    std::reverse_iterator< BidirectionalIterator1 >( first ) ,
                    std::bind1st( std::greater< unsigned int >() , 1 ) );
    BidirectionalIterator1 p = pr.base();
    BidirectionalIterator2 q = first_weight + ( p - first );
    for( ; p != first ; --first ) {
      unsigned int limit = --*( p - 1 );
      if( dist_monotone( p , last , q ,
                        accumulate_weight( p , last , q , 0 ) ,
                        limit ) ) {
        return true;
      }
    }
    return false;
  }

