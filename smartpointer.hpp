#pragma once
#include <algorithm>
#include <map>

template<typename T>
class auto_pointer{
public:
   auto_pointer() : auto_pointer(nullptr){}
   auto_pointer(T* ptr);
   auto_pointer(const auto_pointer &other) : auto_pointer(other.raw_ptr){}
   ~auto_pointer();

   T& operator*() const;
   auto_pointer<T>& operator=(const auto_pointer &other){
      if(this == &other)
         return *this;
      if(this->raw_ptr == other.raw_ptr)
         return *this;
      this->~auto_pointer();
      allocate(other.raw_ptr);
      return *this;
   }
private:
   void allocate(T* raw_ptr);
   static std::map<T*,int> alloc_map;
   T* raw_ptr;
};

template <typename T>
auto_pointer<T>::auto_pointer(T* ptr){
   allocate(ptr);
}

template <typename T>
auto_pointer<T>::~auto_pointer(){
   if(!raw_ptr)
      return;
   typename std::map<T*,int>::iterator iter = alloc_map.find(raw_ptr);
   iter->second--;
   int i = iter->second;
   if(!iter->second){
      alloc_map.erase(iter);
      delete raw_ptr;
   }
}

template <typename T>
void auto_pointer<T>::allocate(T* raw_ptr){
   this->raw_ptr = raw_ptr;
   if(!raw_ptr)
      return;
   typename std::map<T*,int>::iterator iter = alloc_map.find(raw_ptr);
   if(iter == alloc_map.end())
      alloc_map.insert(std::pair<T*,int>(raw_ptr,1));
   else
      iter->second++;
}

template <typename T>
T& auto_pointer<T>::operator*() const{
   return *raw_ptr;
}

template <typename T>
std::map<T*,int> auto_pointer<T>::alloc_map = std::map<T*,int>();