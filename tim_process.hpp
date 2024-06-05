#include <type_traits>

#include <utility>

template <typename... Ts> struct Process : public Ts... {
  template <typename source, typename H, typename... T>
  auto process(source &&s) {
    H *h_ptr = static_cast<H *>(this);
    if constexpr (sizeof...(T) == 0) {
      return h_ptr->call(std::forward<source>(s));
    } else {
      return process<decltype(std::declval<H>().call(source{})), T...>(
          h_ptr->call(std::forward<source>(s)));
    }
  };

  template <typename source> auto call(source &&s) {
    return process<source, Ts...>(std::forward<source>(s));
  };
};
