#include "resultf/result_func.hpp"

// Marklar headers
// External library headers
#include "../catch.hpp"
// C++ standard library headers
#include <string>

constexpr int forty_and_two{42};
static std::string const error_string{"Bad wolf"};

TEST_CASE("marklar::result_func::to_value should be create a Result")
{
    using namespace marklar::result_func;
    using Result = Result<int, std::string>;

    Result result{to_value(forty_and_two)};
    REQUIRE(is_value(result)); // Should be true because it holds a value
}

TEST_CASE("marklar::result_func::value should be return with value if Result is holds a value")
{
    using namespace marklar::result_func;
    using Result = Result<int, std::string>;

    Result result{to_value(forty_and_two)};
    REQUIRE(forty_and_two == value(result)); // Should be return with setted value
}

TEST_CASE("marklar::result_func::error should be return with error if Result is holds an error")
{
    using namespace marklar::result_func;
    using Result = Result<int, std::string>;

    Result result{to_error(error_string)};
    REQUIRE(error_string == error(result)); // Should be return with setted error
}

TEST_CASE("marklar::result_func::value should be throw exception if Result is not holds a value")
{
    using namespace marklar::result_func;
    using Result = Result<int, std::string>;

    Result result{to_error(error_string)};
    REQUIRE_THROWS(value(result)); // Should be return with setted value
}

TEST_CASE("marklar::result_func::error should be throw exception if Result is holds an error")
{
    using namespace marklar::result_func;
    using Result = Result<int, std::string>;

    Result result{to_value(forty_and_two)};
    REQUIRE_THROWS(error(result)); // Should be return with setted error
}
