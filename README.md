# fusion
Exception-free error handling library.

## Example
```c++
#include <iostream>
#include <fusion/fusion.h>

enum class MathError {
  kDivideByZero
};

auto Divide(const double lhs, const double rhs)
    -> fusion::Result<double, MathError> {
  if (lhs == 0 || rhs == 0) {
    return fusion::Error{MathError::kDivideByZero};
  }
  return lhs / rhs;
}

int main() {
  auto result = Divide(64, 4);
  if (result.HasValue()) {
    std::cout << "64 / 4 = " << result.Get() << std::endl;
  } else {
    if (result.GetError() == MathError::kDivideByZero) {
      std::cerr << "Error: divide by zero" << std::endl;
    }
  }
  return 0;
}
```
