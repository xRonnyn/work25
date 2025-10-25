#include <iostream>
#include <limits>

bool safeMultiply(unsigned a, unsigned b, unsigned& result);
bool safePlus(unsigned a, unsigned b, unsigned& result);
bool isPyth(unsigned a, unsigned b, unsigned c, int& error);

int main(){
  using u_t = unsigned;
  u_t a = 0, b = 0, c = 0;
  std::cin >> b >> c;
  size_t count = 0;
  int error_code = 0;

  while (std::cin >> a){
    bool result = isPyth(a, b, c, error_code);
    if (error_code == 2) {
      std::cerr << "переполнение\n";
      return 2;
    }
    count += result ? 1 : 0;
    c = b;
    b = a;
  }

  if (std::cin.eof()){
    std::cout << count << "\n";
  }
  else if(std::cin.fail()){
    std::cerr << "Input err\n";
    return 1;
  }

  return 0;
}

bool safeMultiply(unsigned a, unsigned b, unsigned& result) {
  if (a == 0 || b == 0) {
    result = 0;
    return true;
  }
  if (a > std::numeric_limits<unsigned>::max() / b) {
    return false;
  }
  result = a * b;
  return true;
}

bool safePlus(unsigned a, unsigned b, unsigned& result) {
  if (a > std::numeric_limits<unsigned>::max() - b) {
    return false;
  }
  result = a + b;
  return true;
}

bool isPyth(unsigned a, unsigned b, unsigned c, int& error) {
  unsigned a2, b2, c2;

  if (!safeMultiply(a, a, a2) || !safeMultiply(b, b, b2) || !safeMultiply(c, c, c2)) {
    error = 2;
    return false;
  }

  unsigned sum1, sum2, sum3;
  if (!safePlus(b2, c2, sum1) || !safePlus(a2, c2, sum2) || !safePlus(a2, b2, sum3)) {
    error = 2;
    return false;
  }

  error = 0;
  bool p = (a2 == sum1);
  p = p || (b2 == sum2);
  p = p || (c2 == sum3);
  return p;
}