#ifndef GITSTORY_BLOB_HPP
#define GITSTORY_BLOB_HPP

#include "unique_ptr.hpp"

extern "C" {
#include <git2/buffer.h>
};

struct git_blob;

namespace gitxx {
class oid;

struct buf {
    buf() noexcept  = default;
    buf(buf const&) = delete;
    buf(buf&& other) noexcept
        : buffer_{other.buffer_} {
        other.buffer_.ptr  = nullptr;
        other.buffer_.size = 0;
    }
    ~buf() { git_buf_dispose(&buffer_); }

    [[nodiscard]] std::string_view sv() const {
        return std::string_view{buffer_.ptr, buffer_.size};
    }

    ::git_buf buffer_;
};

class blob {
public:
    explicit blob(git_blob* blob);
    [[nodiscard]] buf filter(std::string_view path, oid const& id) const;

private:
    internal::unique_ptr<git_blob> blob_;
};
} // namespace gitxx

#endif // GITSTORY_BLOB_HPP
