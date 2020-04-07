
#include "set.h"


void print( std::ostream& out, const treenode* n, size_t indent )
{

   for( size_t i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween( const treenode* n, 
                   const int* lowerbound, const int* upperbound ) 
{
   while(n) 
   {
      if( lowerbound && *lowerbound >= n -> val )
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if( upperbound && n -> val >= *upperbound )
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checkbetween( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
} 


void deallocate( treenode* n )
{
   while(n)
   {
      deallocate( n -> left );
      treenode* bye = n;
      n = n -> right;
      delete bye;
   }
}


void writecopy( treenode** to, treenode* from )
{
   while( from )
   {
      *to = new treenode{ from -> val };

      writecopy( & (*to) -> left, from -> left );
      to = & (*to) -> right;
      from = from -> right;
   }
   *to = nullptr;
}


void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


std::ostream& set::print( size_t indent, std::ostream& out ) const
{
   ::print( out, tr, indent );
   return out;
}


size_t log_base2( size_t s ){
   size_t value = 0;        
   if(s==0)
      return value;
   else{
      while(s!=1){
         s = s/2;
         ++value;
      }
   }
   return value;
}

const treenode* find( treenode* n, int i ){
   if (n == nullptr || n->val == i){
      return n;
   }else if(n->val < i){
      return find(n->right, i);
   }
   return find(n->left, i);
}

treenode** find( treenode** n, int i ){
   if( *n == nullptr || (*n)->val == i ){
      return n;
   }else if((*n)->val < i){
      return find(&(*n)->right, i);
   }
   return find(&(*n)->left, i);
}



bool set::insert(int i){
   treenode** curr = find( &tr, i );
   
   if(*curr == nullptr){
      *curr = new treenode(i);
      return true;
   }
   return false;
}

bool set::contains( int i ) const{
   if(find(tr, i)==nullptr)
      return false; 
   return true;
}


treenode* removerightmost( treenode** from ){
   if((*from)-> right == nullptr){
      treenode* curr = *from;
      *from = (*from)->left;
      return curr;
   }
   return removerightmost(&(*from)->right);
}

bool set::remove( int i){
   treenode** curr = find(&tr, i);

   if(*curr == nullptr)
      return false;
   if((*curr)->right == nullptr && (*curr)->left == nullptr){
      delete *curr;
      *curr = nullptr;
   }else if((*curr)->right == nullptr && (*curr)->left != nullptr){
      treenode* temp = *curr;
      (*curr) = (*curr)->left;
      delete temp;
      temp = nullptr;
   }else{
      treenode* rightmost = removerightmost(curr);
      (*curr) -> val = rightmost->val;
      delete rightmost;
      rightmost = nullptr;
   }
   return true;
}

size_t size( const treenode* n ){
   if (n == nullptr){
      return 0;
   }
   return size(n->left) + size(n->right) + 1;
}  

void clear(treenode *n){
   if (n != nullptr){
      clear(n->left);
      clear(n->right);
      delete n;
   }
}

void set::clear(){
   ::clear(tr);
   tr = nullptr;
}

bool set::isempty(){
   return tr == nullptr;
}
   
size_t height(const treenode *n) {
   if (n == nullptr) {
     return 0;
   }
   return std::max(height(n->left), height(n->right)) + 1;
}

// size_t height(const treenode *n) {
//    return log_base2(size(n) + 1) + 1;
// }