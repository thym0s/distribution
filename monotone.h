#include <algorithm>
#include <functional>
#include <iostream>

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

template < class BidirectionalIterator1 ,
           class BidirectionalIterator2 ,
           class T >
  T dist_monotone( BidirectionalIterator1 first ,
                      BidirectionalIterator1 last ,
                      BidirectionalIterator2 first_weight ,
                      T amount ,
                      T limit ) {
    typedef typename std::iterator_traits< BidirectionalIterator1 >::value_type value_type;
    if( first == last ) {
      return amount;
    } else {
      *first = limit = std::min< value_type >( amount / *first_weight , limit );
      value_type remainder = amount - *first * *first_weight;
      return dist_monotone< BidirectionalIterator1 ,
                            BidirectionalIterator2 ,
                            T > ( ++first , last , ++first_weight , remainder , limit );
    }
  }

template < class BidirectionalIterator1 ,
           class BidirectionalIterator2 >
  bool next_monotone( BidirectionalIterator1 first ,
                      BidirectionalIterator1 last ,
                      BidirectionalIterator2 first_weight ) {
    typedef typename std::reverse_iterator< BidirectionalIterator1 > rit_type;
    typedef typename std::iterator_traits< BidirectionalIterator1 >::value_type value_type;
    rit_type pr = std::find_if( rit_type( last ) ,
                    rit_type( first ) ,
                    std::bind1st( std::less< value_type >() , value_type(1) ) );
    BidirectionalIterator1 p = pr.base();
    BidirectionalIterator2 q = first_weight + ( p - first );
    value_type remainder = value_type( 0 );
    for( ; p != first ; --p , --q ) {
      for( ; value_type( 0 ) < --*( p - 1) ; ) {
        std::cout << 'A' << *(q - 1) << '\n';
        std::cout << 'B' << accumulate_weight( p , last , q , value_type( *( q - 1) ) ) << '\n';
        remainder += accumulate_weight( p , last , q , value_type( *( q - 1) ) ) ,
        std::cout << 'C' << remainder << '\n';
        remainder = dist_monotone( p , last , q , remainder , *( p - 1) );
        if( remainder == value_type( 0 ) ) {
          return true;
        }
        std::cout << 'D' << remainder << '\n';
      }
    }
    remainder += accumulate_weight( p , last , q , value_type(0) );
    dist_monotone( p , last ,  q , remainder , remainder );
    return false;
  }

