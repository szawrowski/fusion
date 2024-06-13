// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef FUSION_TYPE_RESULT_H_
#define FUSION_TYPE_RESULT_H_

#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <variant>

#include "fusion/types/error.h"

namespace fusion {

template <typename T, typename E>
class Result {
public:
  using ValueType = T;
  using ErrorType = E;
  using ResultType = std::variant<ValueType, Error<ErrorType>>;

public:
  constexpr Result(const ValueType& value) : inner_(value) {}

  constexpr Result(ValueType&& value) : inner_(std::move(value)) {}

  constexpr Result(const Error<ErrorType>& error) : inner_(error) {}

  constexpr Result(Error<ErrorType>&& error) : inner_(std::move(error)) {}

  template <typename U>
  constexpr Result(
      U&& value,
      std::enable_if_t<std::is_constructible_v<Error<ErrorType>, U>>* =
          nullptr) {
    using DecayedType = std::decay_t<U>;
    if constexpr (std::is_same_v<DecayedType, ValueType>) {
      inner_ = std::forward<U>(value);
    } else {
      inner_ = Error<ErrorType>{std::forward<U>(value)};
    }
  }

  Result(const Result& other) : inner_{other.inner_} {}

  Result& operator=(const Result& other) {
    if (this != &other) {
      this->inner_ = other.inner_;
    }
    return *this;
  }

  constexpr Result(Result&& other) noexcept(
      std::is_nothrow_move_constructible_v<ValueType> &&
      std::is_nothrow_move_constructible_v<ErrorType>)
      : inner_(std::move(other.inner_)) {}

  Result& operator=(Result&& other) noexcept(
      std::is_nothrow_move_assignable_v<ValueType> &&
      std::is_nothrow_move_assignable_v<ErrorType>) {
    if (this != &other) {
      inner_ = std::move(other.inner_);
    }
    return *this;
  }

public:
  const ResultType& GetInner() const { return inner_; }

public:
  constexpr bool operator==(const Result& other) const {
    return inner_ == other.inner_;
  }

  constexpr bool operator!=(const Result& other) const {
    return !(*this == other);
  }

  explicit operator bool() const noexcept { return HasValue(); }

public:
  [[nodiscard]] constexpr bool HasValue() const noexcept {
    return std::holds_alternative<ValueType>(inner_);
  }

  [[nodiscard]] constexpr bool HasError() const noexcept {
    return std::holds_alternative<Error<ErrorType>>(inner_);
  }

public:
  const ValueType& Get() const {
    if (HasValue()) {
      return std::get<ValueType>(inner_);
    }
    throw std::logic_error("Called Get() on an error result");
  }

  // ValueType& Get() {
  //   if (HasValue()) {
  //     return std::get<ValueType>(inner_);
  //   }
  //   throw std::logic_error("Called Get() on an error result");
  // }

  const ErrorType& GetError() const {
    if (HasError()) {
      return std::get<Error<ErrorType>>(inner_).Get();
    }
    throw std::logic_error("Called Error() on a non-error result");
  }

  // ErrorType& GetError() {
  //   if (HasError()) {
  //     return std::get<Error<ErrorType>>(inner_).Get();
  //   }
  //   throw std::logic_error("Called Error() on a non-error result");
  // }

public:
  template <typename Func>
  auto Map(Func func) const {
    if (HasValue()) {
      return Result<std::invoke_result_t<Func, const ValueType&>, ErrorType>(
          func(std::get<ValueType>(inner_)));
    }
    return *this;
  }

  template <typename Func>
  auto MapError(Func func) const {
    if (HasError()) {
      return Result<ValueType, std::invoke_result_t<Func, const ErrorType&>>(
          func(std::get<Error<ErrorType>>(inner_).Get()));
    }
    return *this;
  }

  template <typename Func>
  auto AndThen(Func func) const {
    if (HasValue()) {
      return func(std::get<ValueType>(inner_));
    }
    return *this;
  }

  template <typename Func>
  auto OrElse(Func func) const {
    if (HasError()) {
      return func(std::get<Error<ErrorType>>(inner_).Get());
    }
    return *this;
  }

  template <typename U>
  ValueType UnwrapOr(const U& value) const {
    if (HasValue()) {
      return std::get<ValueType>(inner_);
    }
    return value;
  }

  template <typename ErrFunc>
  auto UnwrapOrElse(ErrFunc func) const {
    if (HasValue()) {
      return std::get<ValueType>(inner_);
    }
    return func(std::get<Error<ErrorType>>(inner_).Get());
  }

  const ValueType& UnwrapOrDefault() const {
    static ValueType default_value{};
    return UnwrapOr(default_value);
  }

  const ValueType& UnwrapOrDefault(const ValueType& default_value) const {
    return UnwrapOr(default_value);
  }

  const ValueType& Expect(const std::string& message) const {
    if (HasValue()) {
      return std::get<ValueType>(inner_);
    }
    throw std::runtime_error(message);
  }

  template <typename U>
  auto ExpectError(const U& message) const {
    if (HasError()) {
      return std::get<Error<ErrorType>>(inner_).Get();
    }
    throw std::runtime_error(message);
  }

  template <typename Func>
  auto Filter(Func func) const {
    if (HasValue() && func(std::get<ValueType>(inner_))) {
      return *this;
    }
    return Result{Error<ErrorType>{}};
  }

  template <typename U, typename Func>
  auto Fold(U&& init, Func&& f) const {
    if (HasValue()) {
      return std::forward<Func>(f)(std::forward<U>(init),
                                   std::get<ValueType>(inner_));
    }
    return std::forward<U>(init);
  }

  template <typename Func>
  auto Then(Func func) const {
    if (HasValue()) {
      return func(std::get<ValueType>(inner_));
    }
    return *this;
  }

  template <typename Func>
  auto CatchError(Func func) const {
    if (HasError()) {
      return func(std::get<Error<ErrorType>>(inner_).Get());
    }
    return *this;
  }

  template <typename Func>
  auto OnError(Func func) const {
    if (HasError()) {
      func(std::get<Error<ErrorType>>(inner_).Get());
    }
    return *this;
  }

  template <typename Func>
  auto Customize(Func&& func) const {
    return func(*this);
  }

  template <typename TFunc, typename EFunc, typename... Args>
  auto Inspect(TFunc value_func, EFunc error_func, Args&&... args) const {
    if (HasValue()) {
      return std::invoke(std::forward<TFunc>(value_func),
                         std::get<ValueType>(inner_),
                         std::forward<Args>(args)...);
    }
    return std::invoke(std::forward<EFunc>(error_func),
                       std::get<Error<ErrorType>>(inner_).Get(),
                       std::forward<Args>(args)...);
  }

private:
  ResultType inner_;
};

}  // namespace fusion

#endif  // FUSION_TYPE_RESULT_H_