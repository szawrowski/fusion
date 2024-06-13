// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef FUSION_TYPE_ERROR_H_
#define FUSION_TYPE_ERROR_H_

#include <utility>

namespace fusion {

template <typename E>
class Error {
public:
  explicit Error(E error) : error_{std::move(error)} {}

  const E& Get() const noexcept { return error_; }

private:
  E error_;
};

template <typename E>
bool operator==(const Error<E>& lhs, const Error<E>& rhs) {
  return lhs.Get() == rhs.Get();
}

template <typename E>
bool operator!=(const Error<E>& lhs, const Error<E>& rhs) {
  return !(lhs == rhs);
}

}  // namespace fusion

#endif  // FUSION_TYPE_ERROR_H_
