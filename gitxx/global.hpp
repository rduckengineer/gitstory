#ifndef GITSTORY_GLOBAL_HPP
#define GITSTORY_GLOBAL_HPP

namespace gitxx {
struct [[nodiscard]] init_guard {
    init_guard();
    ~init_guard();
};
} // namespace gitxx

#endif // GITSTORY_GLOBAL_HPP
