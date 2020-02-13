
#include "queue.h"

// TODO: Implement everything from the queue class here, along with
// testqueue ... we are only providing checkinvariant

bool queue::checkinvariant( ) const
{
   if( current_size == 0 )
   {
      if( first ) 
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size == 0, but first != nullptr\n";
         return false;
      }

      if( last )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size == 0, but last != nullptr\n";
         return false;
      }

      return true;
   }
 
   size_t s = 0;
   const qnode* l = nullptr; // This will remember the last node.

   for( const qnode* p = first; p; p = p -> next ) 
   {
      if( s == current_size )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size is less than real size: ";
         std::cout << current_size << "\n\n"; 
         // I don't want to count further because list may be corrupt. 
         return false;
      }
      ++ s;  
      l = p; 
   }

   if( s != current_size )
   {
      std::cout << "INVARIANT ";
      std::cout << "current_size is not equal to real size\n";
      std::cout << "current_size = " << current_size << "\n";
      std::cout << "real size    = " << s << "\n";

      return false;
   }

   if( l != last )
   {
      std::cout << "INVARIANT: last is not correct, ";
      std::cout << "it is " << last << " but must be " << l << "\n";
      return false;
   }

   return true; 
}

void queue::push(double q){
  if (current_size==0){
    first = new qnode(q);
    last = first;
  }else{
    last->next = new qnode(q);
    last = new qnode(d);
  }
    ++current_size;
}

queue::queue():
  first(nullptr),
  current_size(0){

  }

queue::queue(const queue& q):
  current_size(q.current_size),
  first(new qnode(q.first)),
  last(new qnode(q.last))
  {
    for( const qnode* p = first; p; p = p -> next ){
      p->next =
  }
}