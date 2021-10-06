
#include "gtest/gtest.h"

#include <cstdio>

#include <ostream>
#include <string>

#include "filebuf.h"

const std::string TEST_DATA = "abcdefghijklmnopqrstuvwxyz0123456789";

template<typename T, size_t N>
void fillArrayWithData(std::array<T, N>& array) {
    for(auto i = 0; i < N - 1; ++i) {
        array[i] = TEST_DATA[i % TEST_DATA.size()];
    }

    // Set the last byte to being a nul-terminator
    array[N - 1] = 0;
}

TEST(filebufTests, SimpleWriteTest) {
    constexpr size_t BUF_SIZE = 256;

    std::array<char, BUF_SIZE> data_buf;
    fillArrayWithData(data_buf);

    // Create a temporary file for writing
    std::FILE* file = std::tmpfile();

    {
        filebuf buf(file);
        std::ostream out(&buf);

        // Write the data into the file
        out.write(data_buf.data(), data_buf.size());
    }

    // Rewind the FILE* so we can read from it
    std::rewind(file);

    // Verify that the data is all correct
    {
        std::array<char, BUF_SIZE> data_buf2;

        // Make sure that we have read the entire file, and that there is no
        //  extra data
        // Note that there is one extra character in the file (the nul-terminator)
        std::fgets(data_buf2.data(), BUF_SIZE, file);

        // Verify that the data matches what we wrote
        ASSERT_EQ(data_buf, data_buf2);
    }
}

