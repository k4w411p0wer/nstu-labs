#define TESTCASE int main()

#define ASSERT(expression)                                                     \
  if (!(expression))                                                           \
    return 1;
#define ASSERT_EQ(val1, val2) ASSERT((val1) == (val2))


// #define GTEST_ASSERT_(expression, on_failure)                   \
//   GTEST_AMBIGUOUS_ELSE_BLOCKER_                                 \
//   if (const ::testing::AssertionResult gtest_ar = (expression)) \
//     ;                                                           \
//   else                                                          \
//     on_failure(gtest_ar.failure_message())
