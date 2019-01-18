#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ggmo.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

int FunctionToMock(int i);

int FunctionUnderTest(int i)
{
    return FunctionToMock(i);
}

MOCK_GLOBAL_OBJ1(int, FunctionToMock, int)
{
    ON_CALL(*this, FunctionToMock(_)).WillByDefault(Return(1));
}

class ggmoTest : public ::testing::Test
{
    public:
        DECL_NICE_GLOBAL_FUNC_MOCK(FunctionToMock);
};

TEST_F(ggmoTest, Sanity)
{
    GMO_EXPECT_CALL(FunctionToMock,(1)).WillOnce(Return(2));
    EXPECT_THAT(FunctionUnderTest(1), Eq(2));
}

