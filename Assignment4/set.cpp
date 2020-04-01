
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

const treenode* find( const treenode* n, int i ){
   treenode* curr = n;
   while(curr!=nullptr){
      if(curr->val == i){
         return curr;
         break;
      }
      else if(curr->val > i)
         curr = curr->left;
      else if(curr->val < i)
         curr = curr->right;      
   }
   return curr;
}

treenode** find( treenode** n, int i ){
   treenode* curr = *n;
   while(curr->left != nullptr & curr->right != nullptr){
      if(curr->val == i){
         return *curr;
         break;
      }
      else if(curr->val > i)
         curr = curr->left;
      else if(curr->val < i)
         curr = curr->right;      
   }
   return *curr;
}

// PROOFREADING IS NEEDED
bool set::insert(int i){
   treenode* curr = find( tr, i );
   bool status = TRUE
   if(curr->val == i)
      status = FALSE;
   else if(curr->val>i){
      curr = curr->left;
      curr->val = i;
   }
   else{
      curr = curr->right;
      curr->val = i;      
   }
   return status;
}

bool set::contains( int i ) const{
   if(find(tr, i)==nullptr)
      return FALSE; 
   return TRUE;
}


bool set::remove( int i ){
   treenode* curr = find(tr, i);
   if (curr->val ==i){
      if(curr->left != nullptr & curr->right != nullptr){
         treenode temp = removerightmost(curr);
         curr->val = temp->val;
         curr = temp;
         delete temp;
      }
      if(curr->left == nullptr & curr->right == nullptr){
         delete curr;
         curr = nullptr;
      }else if(curr->left != nullptr){
         treenode* temp = curr;
         curr = curr ->left;
         delete temp;
      }else if(curr->right != nullptr){
         treenode* temp = curr;
         curr = curr ->right;
         delete temp;
      }
      return TRUE;
   }
   return FALSE;   
}

treenode* removerightmost( treenode** from ){
   treenode temp = from->right;
   while(temp->left!=nullptr){
      temp = temp->left
   }
   return temp;
}