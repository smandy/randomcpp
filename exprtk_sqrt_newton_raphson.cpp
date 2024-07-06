#include <cmath>
#include <cstdio>
#include <string>

#include "exprtk.hpp"

// pacaur -Ss exprtk

template <typename T>
void newton_sqrt()
{
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T> expression_t;
    typedef exprtk::parser<T> parser_t;
    typedef exprtk::function_compositor<T> compositor_t;
    typedef typename compositor_t::function function_t;

    T x = T(0);

    symbol_table_t symbol_table;

    symbol_table.add_constants();
    symbol_table.add_variable("x", x);

    compositor_t compositor(symbol_table);

    compositor.add(
        function_t("newton_sqrt")
            .var("x")
            .expression(
                " switch                                                   "
                " {                                                        "
                "    case x < 0  : null;                                   "
                "    case x == 0 : 0;                                      "
                "    case x == 1 : 1;                                      "
                "    default:                                              "
                "    {                                                     "
                "       var z := 100;                                      "
                "       var sqrt_x := x / 2;                               "
                "       repeat                                             "
                "          if (equal(sqrt_x^2, x))                         "
                "             break[sqrt_x];                               "
                "          else                                            "
                "             sqrt_x := (1 / 2) * (sqrt_x + (x / sqrt_x)); "
                "       until ((z -= 1) <= 0);                             "
                "    };                                                    "
                " }                                                        "));

    const std::string expression_str = "newton_sqrt(x)";

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_str, expression);

    for (std::size_t i = 0; i < 100; ++i) {
        x = static_cast<T>(i);

        const T result = expression.value();

        printf("sqrt(%03d) - Result: %15.13f\tReal: %15.13f\n",
               static_cast<unsigned int>(i),
               result,
               std::sqrt(x));
    }
}

int main()
{
    newton_sqrt<double>();
    return 0;
}
