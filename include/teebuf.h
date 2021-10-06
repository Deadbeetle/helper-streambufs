/**
 * Copyright © 2021 Anton Kossler
 */

#pragma once

#include <streambuf>

/**
 * @brief A wrapper around two stream buffers that allows a single call to write
 *        to both
 * @tparam CharT The underlying character type of the stream buffers
 * @tparam Traits Some information about CharT
 */
template <typename CharT, typename Traits = std::char_traits<CharT> >
class basic_teebuf : public std::basic_streambuf<CharT, Traits> {
    private:
        /// @brief Shorten the name of the base type to improve readability
        using streambuf = std::basic_streambuf<CharT, Traits>;
        using int_type = typename Traits::int_type;

    public:
        /**
         * @brief Construct a basic_teebuf object
         * @param a This streambuf is written to first
         * @param b This streambuf is not written to if a->sputc() returns EOF
         */
        basic_teebuf(streambuf *a, streambuf *b)
            : m_a(a), m_b(b) {}

    protected:
        /**
         * @brief Insert a character
         * @return Traits::eof() if one of the streams can't be written to; c
         *         otherwise
         * @param c The character to insert
         */
        int_type overflow(int_type c) override {
            int_type a = m_a->sputc(c), b = m_b->sputc(c);
            if (a == Traits::eof() || b == Traits::eof())
                return Traits::eof();
            return c;
        }

        /**
         * @brief Synchronize the buffers with the associated character sequence
         * @return 0 on success, -1 on failure
         */
        int_type sync() override {
            if (m_a->pubsync() || m_b->pubsync())
                return -1;
            return 0;
        }

    private:
        /// @brief The first stream to write to
        streambuf *m_a;
        /// @brief The second stream to write to
        streambuf *m_b;
};

using teebuf = basic_teebuf<char>;
using wteebuf = basic_teebuf<wchar_t>;
