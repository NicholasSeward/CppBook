#include <iostream>
class Meters { public: explicit Meters(double value) : value_{value} {} double value() const { return value_; } explicit operator double() const { return value_; } private: double value_{}; };
int main() { Meters m{1.5}; double d{static_cast<double>(m)}; std::cout << d << '\n'; return 0; }
