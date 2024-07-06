#include <iostream>
#include <tuple>

// http://stackoverflow.com/questions/6245735/pretty-print-stdtuple

/// Looks like this stuff can be replaced with std::index_sequence and
/// std::make_index_sequence from the standard
// namespace aux{
//  template<std::size_t...> struct seq{};
//  template<std::size_t N, std::size_t... Is>
//  struct gen_seq : gen_seq<N-1, N-1, Is...>{};
//  template<std::size_t... Is>
//  struct gen_seq<0, Is...> : seq<Is...>{};

template <class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_ostream<Ch, Tr>& os, Tuple const& t,
                 std::index_sequence<Is...>)
{
    using swallow = int[];
    // TODO - replace this with a fold expression when c++11 comes out
    // Okay. Present andy to future andy. What's going on here maybe not obvious.
    // This is the ( init op ... op pack) variety of the fold expression
    // http://en.cppreference.com/w/cpp/language/fold

    // The init is zero. And op is also a comma expression that has a
    // side-effect on the left ( os <<  .. ) and an output term for the
    // expression (again 0), presumably to keep the compiler happy
    swallow{0, ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...};
}

template <class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                          std::tuple<Args...> const& t)
{
    os << "(";
    print_tuple(os, t, std::make_index_sequence<sizeof...(Args)>());
    return os << ")";
}

// http://stackoverflow.com/questions/6245735/pretty-print-stdtuple
template <typename Tuple, size_t... Idx>
inline auto cherry_pick_tuple(std::index_sequence<Idx...>, Tuple&& tuple)
{
    return std::make_tuple(std::get<Idx>(std::forward<Tuple>(tuple))...);
}

int main(int argc, char* argv[])
{
    auto myTup = std::make_tuple(2, 3, "foo", 2.0f, true);
    std::cout << myTup << std::endl;
    std::cout << cherry_pick_tuple(std::index_sequence<0, 4>{}, myTup)
              << std::endl;
    std::cout << cherry_pick_tuple(std::index_sequence<0, 1>{}, myTup)
              << std::endl;
    std::cout << cherry_pick_tuple(std::index_sequence<2, 3>{}, myTup)
              << std::endl;
}
