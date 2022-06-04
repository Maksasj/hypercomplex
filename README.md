# Hypercomplex
Simmple single-header library written in C++, intended for simple way to interact with hypercomplex numbers;

In mathematics, hypercomplex number is a traditional term for an element of a finite-dimensional unital algebra over the field of real numbers.

### Provides simple way to interact with:
- Matrix type
- Matrix algebra
- Simple way to save & load matrix from files.

### **Complex**
In mathematics, a complex number is an element of a number system that contains the real numbers and a specific element denoted i, called the imaginary unit, and satisfying the equation i^2 = −1. Moreover, every complex number can be expressed in the form a + bi, where a and b are real numbers. Because no real number satisfies the above equation, i was called an imaginary number by René Descartes. For the complex number a + bi, a is called the real part and b is called the imaginary part. The set of complex numbers is denoted by either of the symbols **C** or C. Despite the historical nomenclature "imaginary", complex numbers are regarded in the mathematical sciences as just as "real" as the real numbers and are fundamental in many aspects of the scientific description of the natural world. [Wikipedia](https://en.wikipedia.org/wiki/Complex_number)

```c++
complex z1 = {3, 1};
complex z2 = {5, -3};

complex z3 = z1*z2;

std::cout << z3;

/* Result:
+18e1-4e2
*/
```

### **Quaternion**
In mathematics, the quaternion number system extends the complex numbers. Quaternions were first described by Irish mathematician [William Rowan Hamilton](https://en.wikipedia.org/wiki/William_Rowan_Hamilton) in 1843 and applied to mechanics in three-dimensional space. Hamilton defined a quaternion as the quotient of two directed lines in a three-dimensional space, or equivalently, as the quotient of two vectors. Multiplication of quaternions is [noncommutative](https://en.wikipedia.org/wiki/Noncommutative).

Quaternions are generally represented in the form

**a +bi + cj + dk**

where a, b, c, and d are real numbers; and i, j, and k are the basic quaternions. [Wikipedia](https://en.wikipedia.org/wiki/Quaternion)

```c++
quaternion q1 = {3, 1, 4, 6};
quaternion q2 = {5, -3, -4, 3};

quaternion q3 = q1*q2;

std::cout << q3;

/* Result:
+16e1+32e2-13e3+47e4
*/
```

### **Octonions**
Octonions are not as well known as the quaternions and complex numbers, which are much more widely studied and used. Octonions are related to exceptional structures in mathematics, among them the exceptional Lie groups. Octonions have applications in fields such as string theory, special relativity and quantum logic. Applying the Cayley–Dickson construction to the octonions produces the sedenions. [Wikipedia](https://en.wikipedia.org/wiki/Octonion)

```c++
octonion o1 = {7, 3, 5, -6, 8, 2, 9, 1};
octonion o2 = {1, -6, 4, 3, 8, 8, 9, 9};

octonion o3 = o1*o2;

std::cout << o3;

/* Result:
-147e1-24e2+70e3+175e4+76e5+8e6+167e7-57e8
*/
```