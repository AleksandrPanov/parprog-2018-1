#include "../gtest/gtest/gtest.h"
#include "tbb/tbb.h"
#include "Matrix.h"

void Foo(int &a)
{
    a++;
}
void ParallelApplyFoo(int *a, size_t n) 
{
    tbb::parallel_for(size_t(0), n, size_t(1), [=](size_t i) { Foo(a[i]); });
}
TEST(tbb_test, tbb_work)
{
    std::vector<int> ar(10000);
    ParallelApplyFoo(&ar[0], ar.size());
    int numbers_of_1 = std::count(ar.begin(), ar.end(), 1);
    EXPECT_EQ(numbers_of_1, ar.size());
}