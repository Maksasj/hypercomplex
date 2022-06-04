#include "../../hypercomplex.hpp"
#include <fstream>

int main() {
      quaternion q1 = {3, 1, 4, 6};
      quaternion q2 = {5, -3, -4, 3};

      std::ofstream out("output.txt");
      out << q1 * q2;
      out.close();

      return 0;
}