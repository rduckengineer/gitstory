#ifndef GITSTORY_UNIQUE_PTR_HPP
#define GITSTORY_UNIQUE_PTR_HPP

#include <memory>

namespace gitxx::internal {
template <typename T>
using unique_ptr = std::unique_ptr<T, void (*)(T*)>;
}

#endif // GITSTORY_UNIQUE_PTR_HPP
