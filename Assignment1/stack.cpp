#include "stack.h"

// Use this method for all your reallocations:

void stack::ensure_capacity( size_t c ) 
{
   if( current_capacity < c )
   {
      // New capacity will be the greater of c and
      // 2 * current_capacity. 

      if( c < 2 * current_capacity )
         c = 2 * current_capacity;

      double* newdata = new double[ c ];
      for( size_t i = 0; i < current_size; ++ i )
         newdata[i] = data[i];

      current_capacity = c;
      delete[] data;
      data = newdata;
   }
}

stack::stack():
	data(new double[5]),
	current_size(0),
	current_capacity(5)
{
//	std::cout << "def 0" << "\n"<< std::endl;
}

stack::stack(const stack& s):
	current_size(s.current_size),
	current_capacity(s.current_capacity),
	data(new double[s.current_capacity])
{
//	std::cout<< "copy constr" << "\n"<< std::endl;
	for(size_t i=0; i < s.current_size; ++i){
		data[i] = s.data[i];
	}
}

stack::~stack() {
//	std::cout << "destructor" << std::endl;
	delete [] data;
}

const stack& stack::operator = ( const stack& s){
//	std::cout << "assignment" << "\n"<<std::endl;
	ensure_capacity(s.current_size);
 	if(current_size != s.current_size){
		current_size = s.current_size;
	}

	for(size_t i=0; i<s.current_size; ++i){
		data[i] = s.data[i];
	}
	return *this;
}

stack::stack(std::initializer_list<double> d):
	current_size(d.size()),
	current_capacity(d.size()),
	data(new double[d.size()])

{	// can be written with push!
//	std::cout << "init" << "\n" <<std::endl;
	size_t i=0;
	for(double val:d){
		data[i] = val;
		++i;
	}
}

void stack::push(double d){
//	std::cout << "push" << "\n" << std::endl;
	ensure_capacity(current_size + 1);
	data[current_size] = d;
	++current_size;
}

void stack::pop(){
//	std::cout << "pop " <<"\n" <<std::endl;
	current_size--;
}

void stack::clear(){
//	std::cout << "clear " << "\n" << std::endl;
	current_size = 0;
}

void stack::reset(size_t s){
//	std::cout << "reset " <<"\n" << std::endl;
	if(current_size > s)
		current_size = s;
}

double stack::peek() const{
//	std::cout << "peek " << "\n" << std::endl;
	return data[current_size-1];
}

size_t stack::size() const{
//	std::cout << "size "  << std::endl;
	return current_size;
}

bool stack::empty() const{
//	std::cout << "empty" << "\n" << std::endl;
	if( current_size == 0)
	{	
//		std::cout<<"TRUEEEEE";
		return true;
	}
	else {
//		std::cout<<"FAAAAALSE";
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, const stack& s){
	
	for(size_t i = 0; i < s.current_size; ++i){
		out << s.data[i];
		out<<" ";
	}
	return out;
}
