#ifndef HYPERCOMPLEX_H
#define HYPERCOMPLEX_H

#include <string>
#include <iostream>

struct imaginary {
      float a;
      
      float operator*(imaginary const& other) { return -1.0; }
      float operator+(imaginary const& other) { return a + other.a; }

      friend std::ostream& operator<<(std::ostream& os, imaginary other) {
            os << std::to_string(other.a);
            return os;
      }
};

struct complex {
      float a;
      imaginary i;

      complex operator+(complex const& other) { return {a + other.a, i + other.i}; }

      complex(float _a, float _i) { a = _a; i.a = _i; };
};

struct quaternion: complex {
      imaginary j;
      imaginary k;
      quaternion(float _a, float _i, float _j, float _k): complex(_a, _i) { j.a = _j; k.a = _k; };
};

#endif