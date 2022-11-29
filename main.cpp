#include "autoptr.hpp"
#include <iostream>

int main(){
   auto_pointer<int>* ptr = new auto_pointer<int>(new int(10));
   auto_pointer<int> other_ptr;
   other_ptr = *ptr;
   std::cout << *other_ptr << std::endl;
   delete ptr;
   std::cout << *other_ptr << std::endl; 
   return 0;
}