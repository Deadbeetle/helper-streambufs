/**
 * Copyright © 2021 Anton Kossler
 */

#pragma once

#include <streambuf>
#include <cstdio>

/**
 * @brief A wrapper around a C-style file handle
 * @tparam CharT The underlying character type of the stream buffers
 * @tparam Traits Some information about CharT
 */
template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_filebuf : public std::basic_streambuf<CharT, Traits> {
    public:
        /**
         * @brief Construct a basic_filebuf object
         * @param file The FILE* to wrap around
         */
        basic_filebuf(std::FILE *file) {
            m_file = file;
        }

    protected:
        /**
         * @brief Insert a character
         * @return Traits::eof() if the file can't be written to; c otherwise
         * @param c The character to insert
         */
        typename Traits::int_type overflow(typename Traits::int_type c) override {
            return std::fputc(c, m_file);
        }

        /**
         * @brief Attempt to read a character
         * @return Traits::eof() if the file can't be read from; the next
         *         character otherwise
         */
        typename Traits::int_type underflow() override {
            return std::fgetc(m_file);
        }

        /**
         * @brief Synchronize the buffer with the filesystem
         * @return EOF and sets the error indicator in the FILE* on failure; 0
         *         on success
         */
        int sync() override {
            return std::fflush(m_file);
        }

    private:
        /// @brief The FILE* to wrap around
        std::FILE *m_file;
};

using filebuf = basic_filebuf<char>;
using wfilebuf = basic_filebuf<wchar_t>;