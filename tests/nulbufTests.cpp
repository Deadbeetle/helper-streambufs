
#include "gtest/gtest.h"

#include <ostream>

#include "nulbuf.h"

TEST(nulbufTests, SimpleWriteTest) {
    nulbuf buf;
    std::ostream out(&buf);

    out << "foobar" << 3.14159;

    wnulbuf buf2;
    std::wostream out2(&buf2);

    out2 << 12345 << L"lorem ipsum dolar amet" << std::endl;
}

