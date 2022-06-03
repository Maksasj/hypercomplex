#ifndef HYPERCOMPLEX_H
#define HYPERCOMPLEX_H

#include <string>
#include <iostream>
#include <cmath>

struct imaginary {
      float a;
      
      float operator+(imaginary const& other) { return a + other.a; }
      float operator-(imaginary const& other) { return a - other.a; }
      float operator/(imaginary const& other) { return a / other.a; }
      float operator*(imaginary const& other) { return (-1.0)*(a*other.a); }

      friend std::ostream& operator<<(std::ostream& os, imaginary other) {
            os << other.a;
            return os;
      }
};

struct complex {
      float a;
      imaginary i;

      complex(float _a, float _i) { a = _a; i.a = _i; };
      complex operator+(complex const& other) { return {a + other.a, i + other.i}; }
      complex operator-(complex const& other) { return {a - other.a, i - other.i}; }
      complex operator*(complex const& other) { return {(a*other.a - i.a*other.i.a), (a*other.i.a + i.a*other.a)}; }

      friend std::ostream& operator<<(std::ostream& os, complex other) {
            os << other.a << (other.i.a > 0 ? '+' : '-') << abs(other.i.a) << "i";
            return os;
      }
};

struct quaternion: complex {
      imaginary j;
      imaginary k;
      quaternion(float _a, float _i, float _j, float _k): complex(_a, _i) { j.a = _j; k.a = _k; };

      quaternion operator+(quaternion const& other) { return {a + other.a, i + other.i, j + other.j, k + other.k}; }
      quaternion operator-(quaternion const& other) { return {a - other.a, i - other.i, j - other.j, k - other.k}; }
      quaternion operator*(quaternion const& other) { 
            return {
                  (a*other.a - i.a*other.i.a - j.a*other.j.a - k.a*other.k.a),
                  (a*other.i.a + i.a*other.a + j.a*other.k.a - k.a*other.j.a),
                  (a*other.j.a - i.a*other.k.a + j.a*other.a + k.a*other.i.a),
                  (a*other.k.a + i.a*other.j.a - j.a*other.i.a + k.a*other.a)
            };
      }

      friend std::ostream& operator<<(std::ostream& os, quaternion other) {
            os    << other.a << (other.i.a > 0 ? '+' : '-') << fabs(other.i.a) << "i" 
                  << (other.j.a > 0 ? '+' : '-') << fabs(other.j.a) << "j" 
                  << (other.k.a > 0 ? '+' : '-') << fabs(other.k.a) << "k";
            return os;
      }
};

#endif