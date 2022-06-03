#include <iostream>
#include "hypercomplex.hpp"

int main() {
      complex q1 = {3, 1};
      complex q2 = {5, -3};

      complex q3 = q1 * q2;

      quaternion q4 = {1 , 6, 8, 6};

      std::cout << "(" << q1 << ")*(" << q2 << ") = " << q3 << "\n";
      return 0; 
}