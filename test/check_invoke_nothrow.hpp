#ifndef GITSTORY_CHECK_INVOKE_NOTHROW_HPP
#define GITSTORY_CHECK_INVOKE_NOTHROW_HPP

#define CHECK_INVOKE_NOTHROW(EXPR) \
    [&]() {                        \
        try {                      \
            return EXPR;           \
        } catch (...) {            \
            CHECK_NOTHROW(throw);  \
            return EXPR;           \
        }                          \
    }()

#endif // GITSTORY_CHECK_INVOKE_NOTHROW_HPP
