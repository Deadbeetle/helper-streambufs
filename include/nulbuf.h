/**
 * Copyright © 2021 Anton Kossler
 */

#pragma once

#include <streambuf>

/**
 * @brief A streambuf that eats everything written to it and returns EOF on read
 * @tparam CharT The underlying character type
 * @tparam Traits Some information about CharT
 */
template <typename CharT, typename Traits = std::char_traits<CharT> >
class basic_nulbuf : public std::basic_streambuf<CharT, Traits> {
    protected:
        /**
         * @brief Insert a character
         * @return Always returns success (i.e. not EOF)
         */
        typename Traits::int_type overflow(typename Traits::int_type) override {
            return !Traits::eof();
        }

        /**
         * @brief Attempt to read a character
         * @return Always returns EOF
         */
        typename Traits::int_type underflow() override {
            return Traits::eof();
        }

        /**
         * @brief Synchronize the stream with the associated character sequence
         * @return Always return 0, because there is nothing to synchronize
         */
        int sync() override {
            return 0;
        }
};

using nulbuf = basic_nulbuf<char>;
using wnulbuf = basic_nulbuf<wchar_t>;
