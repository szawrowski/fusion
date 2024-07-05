# Fusion
Exception-free error handling library.

## Example
```c++
#include <iostream>
#include <fusion/fusion.h>

enum class math_error {
  divide_by_zero
};

cait::result_t<double, math_error> divide(const double lhs, const double rhs) {
  if (lhs == 0 || rhs == 0) {
    return cait::error_t{math_error::divide_by_zero};
  }
  return lhs / rhs;
}

int main() {
  auto result = divide(64, 4);
  
  if (result.has_value()) {
    std::cout << "64 / 4 = " << result.get() << std::endl;
  } else {
    if (result.get_error() == math_error::divide_by_zero) {
      std::cerr << "Error: divide by zero" << std::endl;
    }
  }
  return 0;
}
```
