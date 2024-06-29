#include <gtest/gtest.h>

#include "add.h"


TEST(Addition, Add) {
    EXPECT_EQ(2, add(1,1));
}
