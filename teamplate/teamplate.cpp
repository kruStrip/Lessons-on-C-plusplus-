#include <iostream> 
#include <stdexcept>
using namespace std; 
 
template <typename T> 
struct Array { 
private: 
 int8_t* data; 
 size_t size; 

public: 
    Array(size_t size) {
        this->size = 0;
        data = new int8_t[size];
 }
 
 Array() { 
  delete[] data; 
 } 
 
 size_t getSize() const {
     return size;
 }
 T operator[](int i) {
     if(i>=size|| i<0) throw out_of_range("Index out of range");

     return data[i];
 }

 //void add(const T& value) { 
 // if (size == capacity) { 
 //  capacity *= 2; 
 //  T* new_data = new T[capacity]; 
 //  for (int i = 0; i < size; i++) { 
 //   new_data[i] = data[i]; 
 //  } 
 //  delete[] data; 
 //  data = new_data; 
 // } 
 // data[size++] = value; 
 //} 
}; 

template <>
struct Array<bool> {
private:
    int8_t* data;
    size_t size;

public:
    Array(size_t size) {
        this->size = 0;
        data = new int8_t[size / 8];
    }

    Array() {
        delete[] data;
    }

    size_t getSize() const {
        return size;
    }
    bool operator[](int i) {
        if (i >= size || i < 0) throw out_of_range("Index out of range");

        size_t v = i / 8;
        size_t u = i % 8;

        return (data[v]>>(7-u)) &1;
    }

    //void add(const T& value) { 
    // if (size == capacity) { 
    //  capacity *= 2; 
    //  T* new_data = new T[capacity]; 
    //  for (int i = 0; i < size; i++) { 
    //   new_data[i] = data[i]; 
    //  } 
    //  delete[] data; 
    //  data = new_data; 
    // } 
    // data[size++] = value; 
    //} 
};
 
int main() { 
 Array<int> arr; 
 return 0;
}