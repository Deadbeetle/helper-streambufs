/**
 * Copyright © 2021 Anton Kossler
 */

#pragma once

#include <streambuf>
#include <cstdio>
#include <iostream>
/**
 * @brief A wrapper around a C-style file handle
 * @tparam CharT The underlying character type of the stream buffers
 * @tparam Traits Some information about CharT
 */
template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_filebuf : public std::basic_streambuf<CharT, Traits> {
    private:
        using int_type = typename Traits::int_type;
        using pos_type = typename Traits::pos_type;
        using off_type = typename Traits::off_type;
        using seekdir = typename std::ios_base::seekdir;
        using openmode = typename std::ios_base::openmode;
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
        int_type overflow(int_type c) override {
            return std::fputc(c, m_file);
        }

        /**
         * @brief Attempt to read a character
         * @return Traits::eof() if the file can't be read from; the next
         *         character otherwise
         */
        int_type underflow() override {
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

        /**
         * @brief Seek to a relative position in the file
         * @return The absolute position of the indicator after seeking
         * @param off The offset to seek to
         * @param dir Where to start seeking
         */
        pos_type seekoff(off_type off, seekdir dir, openmode) override {
            int whence;
            switch (dir) {
                case std::ios_base::beg:
                    whence = SEEK_SET;
                    break;
                case std::ios_base::cur:
                    whence = SEEK_CUR;
                    break;
                case std::ios_base::end:
                    whence = SEEK_END;
                    break;
                default:
                    whence = SEEK_SET;
                    break;
            }
            std::fseek(m_file, off, whence);
            return std::ftell(m_file);
        }

        /**
         * @brief Seek to an absolute position in the file
         * @return The absolute position of the indicator after seeking
         * @param pos The position to seek to
         */
        pos_type seekpos(pos_type pos, openmode) override {
            std::fseek(m_file, pos, SEEK_SET);
            return std::ftell(m_file);
        }

    private:
        /// @brief The FILE* to wrap around
        std::FILE *m_file;
};

using filebuf = basic_filebuf<char>;
using wfilebuf = basic_filebuf<wchar_t>;