#include <iostream>
#include "hypercomplex.hpp"

template<typename T> void printH(T a1, T a2) {
      std::cout << "(" << a1 << ")*(" << a2 << ") = " << a1*a2 << "\n";
}

int main() {
      complex z1 = {3, 1}; 
      complex z2 = {5, -3};
      printH(z1, z2);

      quaternion q1 = {3, 1, 4, 6};
      quaternion q2 = {5, -3, -4, 3};
      printH(q1, q2);
      printH(q2, q1);

      octonion o1 = {7, 3, 5, -6, 8, 2, 9, 1};
      octonion o2 = {1, -6, 4, 3, 8, 8, 9, 9};
      printH(o1, o2);

      return 0; 
}