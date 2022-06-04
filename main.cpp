#include <iostream>
#include <vector>
#include "hypercomplex.hpp"

template<typename T> void printH(T a1, T a2) {
      std::cout << "(" << a1 << ")*(" << a2 << ") = " << a1*a2 << "\n";
}

int main() {
      complex q1 = {3, 1};
      complex q2 = {5, -3};
      
      quaternion q4 = {1 , 6, -4, 1};
      quaternion q5 = {-2 , 5, 7, -3};

      octonion o1 = {7, 3, 5, -6, 8, 2, 9, 1};
      octonion o2 = {1, -6, 4, 3, 8, 8, 9, 9};
      
      printH(q1, q2);
      printH(q4, q5);
      printH(o1, o2);
      return 0; 
}