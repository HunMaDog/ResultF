/*
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */
#ifndef MARKLAR_RESULT_RESULT_FUNC_HPP
#define MARKLAR_RESULT_RESULT_FUNC_HPP

// Marklar headers
// External library headers
// C++ standard library headers
#include <type_traits>
#include <variant>

namespace marklar::result_func::tag
{
struct Value
{
};
struct Error
{
};

} // namespace marklar::result_func::tag

namespace marklar::result_func
{
template<typename StoredType, typename Tag>
class Storage {
public:
    Storage() = delete;

    explicit constexpr Storage(StoredType const & value)
        : value_{value}
    {
    }

    template<typename Type = StoredType, typename = std::enable_if_t<!std::is_reference<Type>::value>>
    explicit constexpr Storage(Type && value)
        : value_{std::forward<Type>(value)}
    {
    }

    constexpr StoredType & get()
    {
        return value_;
    }

    constexpr std::remove_reference_t<StoredType> const & get() const
    {
        return value_;
    }

    using ref = Storage<StoredType &, Tag>;
    operator ref()
    {
        return ref(value_);
    }

private:
    StoredType value_;
};

template<typename Type>
using ValueStorage = Storage<Type, tag::Value>;

template<typename Type>
using ErrorStorage = Storage<Type, tag::Error>;

template<typename ValueType, typename ErrorType>
using Result = std::variant<std::monostate, ValueStorage<ValueType>, ErrorStorage<ErrorType>>;

template<typename Type>
inline constexpr ValueStorage<Type>
to_value(Type const & value)
{
    return ValueStorage<Type>{value};
}

template<typename Type, typename = std::enable_if_t<!std::is_reference_v<Type>>>
constexpr ValueStorage<Type>
to_value(Type && value)
{
    return ValueStorage<Type>{std::forward<Type>(value)};
}

template<typename Type>
constexpr ErrorStorage<Type>
to_error(Type const & value)
{
    return ErrorStorage<Type>{value};
}

template<typename Type, typename = std::enable_if_t<!std::is_reference_v<Type>>>
constexpr ErrorStorage<Type>
to_error(Type && value)
{
    return ErrorStorage<Type>{std::forward<Type>(value)};
}

constexpr size_t ValuePosition{1};
constexpr size_t ErrorPosition{2};

template<typename Type>
constexpr bool
is_value(Type const & result) noexcept
{
    return result.index() == ValuePosition;
}

template<typename Type>
constexpr bool
is_error(Type const & result) noexcept
{
    return result.index() == ErrorPosition;
}

// Access functions
template<typename ResultType>
constexpr auto const &
value(ResultType const & result)
{
    return std::get<ValuePosition>(result).get();
}

template<typename ResultType>
constexpr auto const &
error(ResultType const & result)
{
    return std::get<ErrorPosition>(result).get();
}

template<typename ResultType>
auto &
modify_value(ResultType const & result)
{
    return std::get<ValuePosition>(result).get();
}

template<typename ResultType>
auto &
modify_error(ResultType const & result)
{
    return std::get<ErrorPosition>(result).get();
}

} // namespace marklar::result_func

#endif // MARKLAR_RESULT_RESULT_FUNC_HPP
