#include "signature.hpp"

extern "C" {
#include <git2/signature.h>
}

namespace gitxx {
auto signature::when() const -> std::chrono::system_clock::time_point {
    using std::chrono::seconds;
    // TODO: deal with timezones
    return system_clock::time_point{seconds{sig_->when.time}};
}
auto signature::name() const -> std::string_view {
    return sig_->name ? sig_->name : "";
}
auto signature::email() const -> std::string_view {
    return sig_->email ? sig_->email : "";
}

} // namespace gitxx
