/* This document defines the following types and classes:
  - result_t [class]
  - relation_t [type]
  - ranking_t [type]
  In addition, some interface to these types is provided.

  Explanation of the types:
  - result_t: Collects the outcome for one participant of the tournament
  - relation_t: Can measure the difference between two results, how much better
                a participant has done than another
  - ranking_t: collects all the information about the outcome of a tournament
*/

typedef float relation_t;

class result_t {
  public:
    result_t( unsigned int points ) : points_( points );
    friend result_t result( unsigned int ); //factory constructor
    friend relation_t relation( const result_t & , const result_t & );
  protected:
    unsigned_int points_;
};
 
result_t result( unsigned int );
relation_t relation( const result_t & , const result_t & );

/* The following comparison operators define a total preorder.
  In other words, it is transitive, and you can compare any two results.
  The operator== checks for functional equality, no difference can be
  observed between equal elements.
*/

bool operator<( const result_t & , const_result_t & );
bool operator<=( const result_t & , const_result_t & );
bool operator>( const result_t & , const_result_t & );
bool operator>=( const result_t & , const_result_t & );
bool operator==( const result_t & , const_result_t & );

typedef std::vector<result_t> ranking_t;

