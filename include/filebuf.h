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
        basic_filebuf(FILE *file) {
            m_file = file;
        }

    protected:
        /**
         * @brief Insert a character
         * @return Traits::eof() if the file can't be written to; c otherwise
         * @param c The character to insert
         */
        Traits::int_type overflow(Traits::int_type c) override {
            return fputc(c, file);
        }

        /**
         * @brief Attempt to read a character
         * @return Traits::eof() if the file can't be read from; the next
         *         character otherwise
         */
        Traits::int_type underflow() override {
            return fgetc(file);
        }

        /**
         * @brief Synchronize the buffer with the filesystem
         * @return EOF and sets the error indicator in the FILE* on failure; 0
         *         on success
         */
        int sync() override {
            return fflush(file);
        }

    private:
        /// @brief The FILE* to wrap around
        FILE *m_file;
};