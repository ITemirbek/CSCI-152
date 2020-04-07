
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "queue.h"
#include <deque>


int tests_run = 0;
int tests_correct = 0;

void checkBool( const std::string &s, const bool&  given, const bool& correct )
{
   tests_run++;	
   if( given != correct )
   {
      std::cout << "~INCORRECT -- BOOL" << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
   } else {
      std::cout << "~CORRECT " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
      tests_correct++;
   }
}

void checkSizet( const std::string &s, const size_t&  given, const size_t& correct )
{
   tests_run++;	
   if( given != correct )
   {
      std::cout << "~INCORRECT -- SIZE " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
   } else {
      std::cout << "~CORRECT " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
      tests_correct++;
   }
}

void checkDouble( const std::string &s, const double&  given, const double& correct )
{
   tests_run++;	
   if( abs(given - correct) > 0.1 )
   {
      std::cout << "~INCORRECT -- DOUBLE " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
   } else {
      std::cout << "~CORRECT " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
      tests_correct++;
   }
}

void checkString( const std::string s, const std::string&  given, const std::string& correct )
{
   tests_run++;	
   if( given != correct )
   {
      std::cout << "~INCORRECT " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
   } else {
      std::cout << "~CORRECT " << s << " : " << given <<
                   " SHOULD HAVE BEEN " << correct << "\n";
      tests_correct++;
   }
}

void checkInv(const queue& q) {
   tests_run++;
   if(q.checkinvariant()) {
      std::cout << "~CORRECT INVARIANT CHECK\n";
      tests_correct++;
   } else {
      std::cout << "~INCORRECT INVARIANT CHECK\n";
   }
}

int main( int argc, char* argv [ ] )
{
   //testqueue( );
   //return 0;

#if 0
   {
      // For final exam:

      queue q1; q1. push(2); q1. push(3); q1. push(4);   
      queue& q2 = q1;
      int i = q2. peek( );
      q2. pop( ); q1. push(6); 
      const queue& q3 = q2; 
      i += q1. peek( ); 
      q2. push(i); q2. push(i); q2. pop( ); 
      i += q3. peek( ); i += q3. peek( ); 
      std::cout << "i = " << i << "\n";
      while( q1. size( ))
      {
         std::cout << q1. peek( ) << " "; q1. pop( );
      }
      std::cout << "\n";
      while( q2. size( ))
      {
         std::cout << q2. peek( ) << " "; q2. pop( );
      }
      std::cout << "\n";
      return 0; 
   }
#endif 

   std::string message = "DEFAULT";
   queue q;
   std::deque<double> d;

   checkInv(q);
   checkSizet(message, q.size(), d.size());
	checkBool(message, q.empty(), 1);

   q. push(1); checkInv(q); 
   q. push(2); checkInv(q);
   q. push(3); checkInv(q);
   
   d.push_back(1);
   d.push_back(2);
   d.push_back(3); 

   q. push(2); q. push(3);
   q. push(4); q. push(5); q. push(6);
   q. push(7); q. push(8);
   
   d.push_back(2);
   d.push_back(3);
   d.push_back(4);
   d.push_back(5);
   d.push_back(6);
   d.push_back(7);
   d.push_back(8);

   checkSizet(message, q.size(), d.size());
	checkBool(message, q.empty(), 0);

   std::cout << q << "\n";
   checkInv(q); 

   while( q. size( ) > 5 )
   {
      // double d = q. peek( );
      checkDouble(message, q.peek(), d.front());
      //std::cout << d << "\n";
      q. pop( );
      d.pop_front();
      //std::cout << q << "\n";
      checkInv(q); 
   }

   std::cout << q << "\n";

    q. push(100);
    d.push_back(100);
    std::cout << q << "\n";
    checkInv(q);

    queue q2 = q;
    std::deque<double> d2 = d;
    std::cout << q << "\n";
    std::cout << q2 << "\n";
    q. clear( );
    q2. clear( );
    d.clear();
    d2.clear();
   
    for( size_t i = 0; i < 0; ++ i ) {
       q. push(i);
       d.push_back(i);
    }

    for( size_t i = 0; i < 4; ++ i ) {
       q2. push(100+i);
       d2.push_back(100+i);
    }

    checkInv(q); 
    checkInv(q2); 
    std::cout << q << "\n";
    std::cout << q2 << "\n";

    message = "OPERATOR =";
    q = q2; 
    d = d2;
    q2 = q2;
    d2 = d2;
    std::cout << "now q is " << q << "\n";
    checkInv(q);
    checkInv(q2);
    checkSizet(message, q.size(), d.size());
 	checkBool(message, q.empty(), 0);
    checkSizet(message, q2.size(), d2.size());
 	checkBool(message, q2.empty(), 0);

    while( q. size( ) > 3 )
    {
       //double d = q. peek( );
       //std::cout << d << "\n";
       checkDouble(message, q.peek(), d.front());
       q. pop( );
       d.pop_front();
       checkInv(q); 
    }

    q = q2;
    d = d2;
    std::cout << q << "\n";
    std::cout << q2 << "\n";

    q2. push( 100000 );
    d2.push_back(100000);
    q. push( 20000 ); 
    d.push_back(20000);

    std::cout << q << "\n";
    std::cout << q2 << "\n";

    std::cout << q. size( ) << "\n";
    std::cout << q2. size( ) << "\n";

    checkInv(q);
    q2. checkinvariant( );

    checkSizet(message, q.size(), d.size());
 	checkBool(message, q.empty(), 0);
    checkSizet(message, q2.size(), d2.size());
 	checkBool(message, q2.empty(), 0);

    message = "INIT_LIST";
    queue q3 = { 1,2,3,4,5,6 };
    std::deque<double> d3 = {1,2,3,4,5,6};
    std::cout << q3 << "\n";
    while( q3. size( )) 
    {
       //std::cout << q3. peek( ) << "\n";
       checkDouble(message, q3.peek(), d3.front());
       q3. pop( );
       d3.pop_front();
       checkInv(q3);
    }

    for( unsigned int i = 0; i < 42; ++ i )
    {
       q3. push(i); 
       d3.push_back(i);
       double db = q3. peek( ); 
       checkDouble(message, db, d3.front());
       q3. pop( ); 
       d3.pop_front();
       checkInv(q3); 
       q3. push(db); 
       d3.push_back(db);
       checkInv(q3); 
    }

    message = "SOME MORE";
    q = {1,2,3,4,5};
    d = {1,2,3,4,5};
    q2 = q;
    d2 = d;
    std::cout << q << "\n";
    std::cout << q2 << "\n"; 

    checkSizet(message, q.size(), d.size());
 	checkBool(message, q.empty(), 0);
    checkSizet(message, q2.size(), d2.size());
 	checkBool(message, q2.empty(), 0);

   std::cout << "\nTESTS RUN: " << tests_run << std::endl;
	std::cout << "\nTESTS CORRECT: " << tests_correct << std::endl;	
   return 0;
}
