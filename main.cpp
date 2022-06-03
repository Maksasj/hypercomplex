#include <iostream>
#include "hypercomplex.hpp"

int main() {
      complex q1 = {3, 1};
      complex q2 = {5, -3};
      
      quaternion q4 = {-1.69 , 6.2, -8.1, 6.42};
      quaternion q5 = {56.0 , -1.3, 69.2, 0.46};

      std::cout << "(" << q1 << ")*(" << q2 << ") = " << q1*q2 << "\n";
      std::cout << "(" << q4 << ")*(" << q5 << ") = " << q4*q5 << "\n";
      return 0; 
}