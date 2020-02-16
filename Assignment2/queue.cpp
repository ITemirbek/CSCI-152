
#include "queue.h"

// TODO: Implement everything from the queue class here, along with
// testqueue ... we are only providing checkinvariant
void testqueue(){
	queue q1 = {2, 3, 4, 5};
	std::cout << q1;
	queue q2 = q1;
	std::cout << q2;
	q2.push(7);
	std::cout << q2;
	//q1.clear();
	std::cout << "q1 = " <<q1;
	q1 = q2;
	std::cout << "q1 = " <<q1;	
	q1 = q1;
	std::cout << "q1 = " <<q1;
	q1.checkinvariant();
	std::cout << "q1 last -> " << q1.peek() << "\n";
//	queue q3;
//	std::cout << q3.peek();
	for( unsigned int j = 0; j < 30; ++ j )
	{
		q1. push( j * j );
		q1. checkinvariant( );
		if( j % 5 == 0 )
		{
			while( q1. size( ))
			{
				std::cout << q1. peek( ) << "\n";
				q1. pop( );
				q1. checkinvariant( );
			}
		}
	}

}
bool queue::empty() const{
	return current_size == 0;
}
size_t queue::size() const{
	return current_size;
}
double queue::peek() const{
	if(current_size == 0)
		throw std::runtime_error("peek: queue is empty!");
	else return last->val;
}

const queue& queue::operator = (const queue& q){
	if(current_size != q.current_size)
		clear();
	else{
		qnode* curr = first;
		qnode* qcurr = q.first;
		while(curr == qcurr & curr != nullptr){
			curr = curr->next;
			qcurr = qcurr->next;
		}
		if(curr != nullptr)
			clear();
		else std::cout << "self assignment"<<"\n";
		//else clear();
	}
	if(first == nullptr){
		qnode* curr = q.first;
		while(curr != nullptr){
			push(curr->val);
			curr = curr-> next;
		}
	}
	return *this;
}

void queue::clear(){
	while(first != nullptr)
		pop();
}

void queue::pop(){
	if(current_size==0)
		throw std::runtime_error("pop: queue is empty");
	else if(current_size==1){
		first = nullptr;
		last = nullptr;
	}else {
		first = first->next;
	}
	--current_size;
}

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
    qnode* new_last = new qnode(q); 
    last->next = new_last;
    last = new_last;
  }
    ++current_size;
}

queue::queue():
  first(nullptr),
  last(nullptr),
  current_size(0){

  }

queue::queue(const queue& q):
  current_size(0)
  //first(new qnode(q.first))
{
	qnode *curr = q.first;
	while(curr != nullptr){
		push(curr->val);
		curr = curr->next;
	}
}

queue::queue(std::initializer_list<double> init):
	current_size(0)
{
  for(double val: init){
    push(val);
  }
}

void queue::print(std::ostream& out) const{
	
	qnode *curr = first;
	if(first){
		while (curr != nullptr) {
			out<<curr->val <<" ";
			curr = curr->next;
		}
		out << "\n";
		
	}else 
		out << "Empty list!" << "\n";
}
queue::~queue(){
	clear();
}
