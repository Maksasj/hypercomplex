#ifndef HYPERCOMPLEX_H
#define HYPERCOMPLEX_H

#include <string>
#include <iostream>
#include <cmath>
#include <utility>

template<typename T> T conj(T x) {
      T xstar = x*(-1.0);
      xstar.a *= -1;
      return xstar;
}

template<class T1, class T2> struct Cpair {
      T1 a1;
      T2 a2;
};

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
      complex(float _a, imaginary _i) { a = _a; i = _i; };

      complex operator+(complex const& other) { return {a + other.a, i + other.i}; }
      complex operator-(complex const& other) { return {a - other.a, i - other.i}; }
      complex operator*(float const& x) { return {(a*x), (i.a*x)}; }
      complex operator*(complex const& other) {
            return {
                  (a*other.a - i.a*other.i.a),
                  (a*other.i.a + i.a*other.a)
            };
      }

      friend std::ostream& operator<<(std::ostream& os, complex other) {
            os << other.a << (other.i.a > 0 ? '+' : '-') << abs(other.i.a) << "i";
            return os;
      }
};

struct quaternion: complex {
      imaginary j;
      imaginary k;

      quaternion(float _a, float _i, float _j, float _k): complex(_a, _i) { j.a = _j; k.a = _k; };

      Cpair<complex, complex> cut(quaternion q) {
            return {{q.a, q.i.a}, {q.j.a, q.k.a}};
      }

      quaternion operator-(quaternion const& other) { return {a - other.a, i - other.i, j - other.j, k - other.k}; }
      quaternion operator+(quaternion const& other) { return {a + other.a, i + other.i, j + other.j, k + other.k}; }
      quaternion operator*(float const& x) { return {(a*x), (i.a*x), (j.a*x), (k.a)*x}; }
      quaternion operator*(quaternion const& other) { 
            auto p1 = cut({a, i.a, j.a, k.a});
            auto p2 = cut(other);

            complex qp1 = {p1.a1*p2.a1 - conj(p2.a2)*p1.a2};
            complex qp2 = {p2.a2*p1.a1 + p1.a2*conj(p2.a1)};

            quaternion q = {qp1.a, qp1.i.a, qp2.a, qp2.i.a};
            return q;
      }

      /*
      quaternion operator*(quaternion const& other) { 
            return {
                  (a*other.a - i.a*other.i.a - j.a*other.j.a - k.a*other.k.a),
                  (a*other.i.a + i.a*other.a + j.a*other.k.a - k.a*other.j.a),
                  (a*other.j.a - i.a*other.k.a + j.a*other.a + k.a*other.i.a),
                  (a*other.k.a + i.a*other.j.a - j.a*other.i.a + k.a*other.a)
            };
      }
      */

      friend std::ostream& operator<<(std::ostream& os, quaternion other) {
            os    << other.a 
                  << (other.i.a > 0 ? '+' : '-') << fabs(other.i.a) << "i" 
                  << (other.j.a > 0 ? '+' : '-') << fabs(other.j.a) << "j" 
                  << (other.k.a > 0 ? '+' : '-') << fabs(other.k.a) << "k";
            return os;
      }
};

struct octonion: quaternion {
      imaginary e5;
      imaginary e6;
      imaginary e7;
      imaginary e8;

      octonion(   float _a, float _i, float _j, float _k,
                  float _e5, float _e6, float _e7, float _e8
      ): quaternion(_a, _i, _j, _k) { 
            e5.a = _e5;
            e6.a = _e6;
            e7.a = _e7;
            e8.a = _e8;
      };

      Cpair<quaternion, quaternion> cut(octonion o) {
            return {{o.a, o.i.a, o.j.a, o.k.a}, {o.e5.a, o.e6.a, o.e7.a, o.e8.a}};
      }

      octonion operator*(octonion const& other) { 
            auto p1 = cut({a, i.a, j.a, k.a, e5.a, e6.a, e7.a, e8.a});
            auto p2 = cut(other);

            quaternion qp1 = {p1.a1*p2.a1 - conj(p2.a2)*p1.a2};
            quaternion qp2 = {p2.a2*p1.a1 + p1.a2*conj(p2.a1)};

            octonion q = {qp1.a, qp1.i.a, qp1.j.a, qp1.k.a, qp2.a, qp2.i.a, qp2.j.a, qp2.k.a};
            return q;
      }

      friend std::ostream& operator<<(std::ostream& os, octonion other) {
            os    << other.a 
                  << (other.i.a > 0 ? '+' : '-') << fabs(other.i.a) << "i" 
                  << (other.j.a > 0 ? '+' : '-') << fabs(other.j.a) << "j" 
                  << (other.k.a > 0 ? '+' : '-') << fabs(other.k.a) << "k"

                  << (other.e5.a > 0 ? '+' : '-') << fabs(other.e5.a) << "e5"
                  << (other.e6.a > 0 ? '+' : '-') << fabs(other.e6.a) << "e6"
                  << (other.e7.a > 0 ? '+' : '-') << fabs(other.e7.a) << "e7"
                  << (other.e8.a > 0 ? '+' : '-') << fabs(other.e8.a) << "e8";
            return os;
      }
};

#endif