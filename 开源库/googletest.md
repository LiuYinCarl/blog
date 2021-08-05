# googletest 

##　说明

googletest 版本：1.11.0



## TestSuite

gtest 中的 TestSuite 的概念表示一个测试组，同一个 TestSuite 下的所有测试都属于这个组，有了 TestSuite 这个概念，可以方便的对测试用例进行分类。

## googletest 简单执行流程分析

```c++
#include "gtest/gtest.h"

int add(int a, int b) {
  return a + b;
}

TEST(addSuite, test0) {
  EXPECT_EQ(add(1, 2), 3);
}

TEST(addSuite, test1) {
  EXPECT_EQ(add(4, 3), 6);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

这个例子中，需要考虑几个问题

1. `TEST` 宏是如何定义的，为什么写了 `TEST` 宏就可以自动执行测试？
2. `addSuite` 这个 TestSuite 是怎么被管理的，`test0` 与 `test1` 这两个测试用例又是如何被 `addSuite` 管理的？

先看一下 `TEST` 宏的定义

``` c++
#if !GTEST_DONT_DEFINE_TEST
#define TEST(test_suite_name, test_name) GTEST_TEST(test_suite_name, test_name)
#endif

#define GTEST_TEST(test_suite_name, test_name)             \
  GTEST_TEST_(test_suite_name, test_name, ::testing::Test, \
              ::testing::internal::GetTestTypeId())

// Helper macro for defining tests.
#define GTEST_TEST_(test_suite_name, test_name, parent_class, parent_id)      \
  static_assert(sizeof(GTEST_STRINGIFY_(test_suite_name)) > 1,                \
                "test_suite_name must not be empty");                         \
  static_assert(sizeof(GTEST_STRINGIFY_(test_name)) > 1,                      \
                "test_name must not be empty");                               \
  class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                    \
      : public parent_class {                                                 \
   public:                                                                    \
    GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() = default;           \
    ~GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)() override = default; \
    GTEST_DISALLOW_COPY_AND_ASSIGN_(GTEST_TEST_CLASS_NAME_(test_suite_name,   \
                                                           test_name));       \
    GTEST_DISALLOW_MOVE_AND_ASSIGN_(GTEST_TEST_CLASS_NAME_(test_suite_name,   \
                                                           test_name));       \
                                                                              \
   private:                                                                   \
    void TestBody() override;                                                 \
    static ::testing::TestInfo* const test_info_ GTEST_ATTRIBUTE_UNUSED_;     \
  };                                                                          \
                                                                              \
  ::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(test_suite_name,          \
                                                    test_name)::test_info_ =  \
      ::testing::internal::MakeAndRegisterTestInfo(                           \
          #test_suite_name, #test_name, nullptr, nullptr,                     \
          ::testing::internal::CodeLocation(__FILE__, __LINE__), (parent_id), \
          ::testing::internal::SuiteApiResolver<                              \
              parent_class>::GetSetUpCaseOrSuite(__FILE__, __LINE__),         \
          ::testing::internal::SuiteApiResolver<                              \
              parent_class>::GetTearDownCaseOrSuite(__FILE__, __LINE__),      \
          new ::testing::internal::TestFactoryImpl<GTEST_TEST_CLASS_NAME_(    \
              test_suite_name, test_name)>);                                  \
  void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::TestBody()

```

从上面这几个宏中可以看出，`TEST` 这个宏其实就是在定义了一个类。这个宏写的太难看了φ(*￣0￣)，还是使用 gcc 的命令展开一下这个宏。

```bash
gcc -E -P test.cpp -o macro_expand.cpp
```

``` c++
// 展开后的相关代码
int add(int a, int b)
{
    return a + b;
}

static_assert(sizeof("addSuite") > 1, "test_suite_name must not be empty");
static_assert(sizeof("test0") > 1, "test_name must not be empty");
class addSuite_test0_Test : public ::testing::Test
{
public:
    addSuite_test0_Test() = default;
    ~addSuite_test0_Test() override = default;
    addSuite_test0_Test(addSuite_test0_Test const &) = delete;
    addSuite_test0_Test &operator=(addSuite_test0_Test const &) = delete;
    addSuite_test0_Test(addSuite_test0_Test &&) noexcept = delete;
    addSuite_test0_Test &operator=(addSuite_test0_Test &&) noexcept = delete;

private:
    void TestBody() override;
    static ::testing::TestInfo *const test_info_ __attribute__((unused));
};
::testing::TestInfo *const addSuite_test0_Test::test_info_ = 
    ::testing::internal::MakeAndRegisterTestInfo("addSuite", "test0", nullptr, nullptr,
                                                ::testing::internal::CodeLocation("mytest.cpp", 7), 
                                                (::testing::internal::GetTestTypeId()), 
                                                ::testing::internal::SuiteApiResolver<::testing::Test>::GetSetUpCaseOrSuite("mytest.cpp", 7), 
                                                ::testing::internal::SuiteApiResolver<::testing::Test>::GetTearDownCaseOrSuite("mytest.cpp", 7), 
                                                new ::testing::internal::TestFactoryImpl<addSuite_test0_Test>);
void addSuite_test0_Test::TestBody()
{
    switch (0)
    case 0:
    default:
        if (const ::testing::AssertionResult gtest_ar = (::testing::internal::EqHelper::Compare("add(1, 2)", "3", add(1, 2), 3)))
            ;
        else
            ::testing::internal::AssertHelper(::testing::TestPartResult::kNonFatalFailure, "mytest.cpp", 8, gtest_ar.failure_message()) = ::testing::Message();
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

可以看到，代码中调用了 `MakeAndRegisterTestInfo` 函数，该函数的功能是创建一个 `TestInfo` 对象并注册。

``` c++
TestInfo* MakeAndRegisterTestInfo(
    const char* test_suite_name, const char* name, const char* type_param,
    const char* value_param, CodeLocation code_location,
    TypeId fixture_class_id, SetUpTestSuiteFunc set_up_tc,
    TearDownTestSuiteFunc tear_down_tc, TestFactoryBase* factory) {
  TestInfo* const test_info =
      new TestInfo(test_suite_name, name, type_param, value_param,
                   code_location, fixture_class_id, factory);
  GetUnitTestImpl()->AddTestInfo(set_up_tc, tear_down_tc, test_info);
  return test_info;
}
```

看一下这个函数将 `TestInfo` 注册到了哪里？

``` c++
void AddTestInfo(internal::SetUpTestSuiteFunc set_up_tc,
                internal::TearDownTestSuiteFunc tear_down_tc,
                TestInfo* test_info) {
#if GTEST_HAS_DEATH_TEST
// In order to support thread-safe death tests, we need to
// remember the original working directory when the test program
// was first invoked.  We cannot do this in RUN_ALL_TESTS(), as
// the user may have changed the current directory before calling
// RUN_ALL_TESTS().  Therefore we capture the current directory in
// AddTestInfo(), which is called to register a TEST or TEST_F
// before main() is reached.
if (original_working_dir_.IsEmpty()) {
    original_working_dir_.Set(FilePath::GetCurrentDir());
    GTEST_CHECK_(!original_working_dir_.IsEmpty())
        << "Failed to get the current working directory.";
}
#endif  // GTEST_HAS_DEATH_TEST
// 这里去获取对应的 TestSuite 对象，然后将 TestCase 注册到 TestSuite
GetTestSuite(test_info->test_suite_name(), test_info->type_param(),
                set_up_tc, tear_down_tc)
    ->AddTestInfo(test_info);
}

// 获取指定了名字的 TestSuite 对象, 如果不存在则创建一个
TestSuite* UnitTestImpl::GetTestSuite(
    const char* test_suite_name, const char* type_param,
    internal::SetUpTestSuiteFunc set_up_tc,
    internal::TearDownTestSuiteFunc tear_down_tc) {
  // Can we find a TestSuite with the given name?
  const auto test_suite =
      std::find_if(test_suites_.rbegin(), test_suites_.rend(),
                   TestSuiteNameIs(test_suite_name));

  if (test_suite != test_suites_.rend()) return *test_suite;

  // No.  Let's create one.
  auto* const new_test_suite =
      new TestSuite(test_suite_name, type_param, set_up_tc, tear_down_tc);

  // Is this a death test suite?
  if (internal::UnitTestOptions::MatchesFilter(test_suite_name,
                                               kDeathTestSuiteFilter)) {
    // Yes.  Inserts the test suite after the last death test suite
    // defined so far.  This only works when the test suites haven't
    // been shuffled.  Otherwise we may end up running a death test
    // after a non-death test.
    ++last_death_test_suite_;
    // 这里说明了 TestSuite 是被 UnitTestImpl::test_suites_ 这个 vector 管理的
    test_suites_.insert(test_suites_.begin() + last_death_test_suite_,
                        new_test_suite);
  } else {
    // No.  Appends to the end of the list.
    test_suites_.push_back(new_test_suite);
  }

  test_suite_indices_.push_back(static_cast<int>(test_suite_indices_.size()));
  return new_test_suite;
}

// Adds a test to this test suite.  Will delete the test upon
// destruction of the TestSuite object.
// 将 TestInfo(TestCase) 插入到 TestSuite
// 这里也可以看出 test0 与 test1 这两个测试用例是如何被 `addSuite` 管理的
void TestSuite::AddTestInfo(TestInfo* test_info) {
  test_info_list_.push_back(test_info);
  test_indices_.push_back(static_cast<int>(test_indices_.size()));
}
```

注册的所有 TestCase 最终都是被 main 函数中的 `RUN_ALL_TESTS` 函数调用的，下面看一下具体的调用路径。

``` c++
inline int RUN_ALL_TESTS() {
  return ::testing::UnitTest::GetInstance()->Run();
}

// Runs all tests in this UnitTest object and prints the result.
// Returns 0 if successful, or 1 otherwise.
//
// We don't protect this under mutex_, as we only support calling it
// from the main thread.
int UnitTest::Run() {
  const bool in_death_test_child_process =
      internal::GTEST_FLAG(internal_run_death_test).length() > 0;

  return internal::HandleExceptionsInMethodIfSupported(
      impl(),
      &internal::UnitTestImpl::RunAllTests,
      "auxiliary test code (environments or event listeners)") ? 0 : 1;
}

// Runs all tests in this UnitTest object, prints the result, and
// returns true if all tests are successful.  If any exception is
// thrown during a test, the test is considered to be failed, but the
// rest of the tests will still be run.
//
// When parameterized tests are enabled, it expands and registers
// parameterized tests first in RegisterParameterizedTests().
// All other functions called from RunAllTests() may safely assume that
// parameterized tests are ready to be counted and run.
bool UnitTestImpl::RunAllTests() {
  for (int i = 0; gtest_repeat_forever || i != repeat; i++) {
    // Runs each test suite if there is at least one test to run.
    if (has_tests_to_run) {
      // Sets up all environments beforehand.
      repeater->OnEnvironmentsSetUpStart(*parent_);
      ForEach(environments_, SetUpEnvironment);
      repeater->OnEnvironmentsSetUpEnd(*parent_);

      // Runs the tests only if there was no fatal failure or skip triggered
      // during global set-up.
      if (Test::IsSkipped()) {
          // ... ...
      } else if (!Test::HasFatalFailure()) {
        for (int test_index = 0; test_index < total_test_suite_count();
             test_index++) {
          // 该处调用运行一个 TestSuite
          GetMutableSuiteCase(test_index)->Run();
          if (GTEST_FLAG(fail_fast) &&
              GetMutableSuiteCase(test_index)->Failed()) {
            for (int j = test_index + 1; j < total_test_suite_count(); j++) {
              GetMutableSuiteCase(j)->Skip();
            }
            break;
          }
        }
      } else if (Test::HasFatalFailure()) {
          // ... ...
      }

      // Tears down all environments in reverse order afterwards.
      repeater->OnEnvironmentsTearDownStart(*parent_);
      std::for_each(environments_.rbegin(), environments_.rend(),
                    TearDownEnvironment);
      repeater->OnEnvironmentsTearDownEnd(*parent_);
    }

    // Tells the unit test event listener that the tests have just finished.
    repeater->OnTestIterationEnd(*parent_, i);
  }
}

// Runs every test in this TestSuite.
void TestSuite::Run() {
  if (!should_run_) return;

  internal::UnitTestImpl* const impl = internal::GetUnitTestImpl();
  impl->set_current_test_suite(this);

  TestEventListener* repeater = UnitTest::GetInstance()->listeners().repeater();

  // Call both legacy and the new API
  repeater->OnTestSuiteStart(*this);
//  Legacy API is deprecated but still available
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
  repeater->OnTestCaseStart(*this);
#endif  //  GTEST_REMOVE_LEGACY_TEST_CASEAPI_

  impl->os_stack_trace_getter()->UponLeavingGTest();
  internal::HandleExceptionsInMethodIfSupported(
      this, &TestSuite::RunSetUpTestSuite, "SetUpTestSuite()");

  start_timestamp_ = internal::GetTimeInMillis();
  internal::Timer timer;
  for (int i = 0; i < total_test_count(); i++) {
    // 执行 TestSuite 中的某个 TestCase
    GetMutableTestInfo(i)->Run();
    if (GTEST_FLAG(fail_fast) && GetMutableTestInfo(i)->result()->Failed()) {
      for (int j = i + 1; j < total_test_count(); j++) {
        GetMutableTestInfo(j)->Skip();
      }
      break;
    }
  }

  // Call both legacy and the new API
  repeater->OnTestSuiteEnd(*this);
//  Legacy API is deprecated but still available
#ifndef GTEST_REMOVE_LEGACY_TEST_CASEAPI_
  repeater->OnTestCaseEnd(*this);
#endif  //  GTEST_REMOVE_LEGACY_TEST_CASEAPI_

  impl->set_current_test_suite(nullptr);
}


// Creates the test object, runs it, records its result, and then
// deletes it.
void TestInfo::Run() {
  if (!should_run_) return;

  // Tells UnitTest where to store test result.
  internal::UnitTestImpl* const impl = internal::GetUnitTestImpl();
  impl->set_current_test_info(this);

  TestEventListener* repeater = UnitTest::GetInstance()->listeners().repeater();

  // Notifies the unit test event listeners that a test is about to start.
  repeater->OnTestStart(*this);

  result_.set_start_timestamp(internal::GetTimeInMillis());
  internal::Timer timer;

  impl->os_stack_trace_getter()->UponLeavingGTest();

  // Creates the test object.
  Test* const test = internal::HandleExceptionsInMethodIfSupported(
      factory_, &internal::TestFactoryBase::CreateTest,
      "the test fixture's constructor");

  // Runs the test if the constructor didn't generate a fatal failure or invoke
  // GTEST_SKIP().
  // Note that the object will not be null
  if (!Test::HasFatalFailure() && !Test::IsSkipped()) {
    // This doesn't throw as all user code that can throw are wrapped into
    // exception handling code.
    // 此处最终执行一个 TestCase
    test->Run();
  }

  if (test != nullptr) {
    // Deletes the test object.
    impl->os_stack_trace_getter()->UponLeavingGTest();
    internal::HandleExceptionsInMethodIfSupported(
        test, &Test::DeleteSelf_, "the test fixture's destructor");
  }

  result_.set_elapsed_time(timer.Elapsed());

  // Notifies the unit test event listener that a test has just finished.
  repeater->OnTestEnd(*this);

  // Tells UnitTest to stop associating assertion results to this
  // test.
  impl->set_current_test_info(nullptr);
}


// Runs the test and updates the test result.
void Test::Run() {
  if (!HasSameFixtureClass()) return;

  internal::UnitTestImpl* const impl = internal::GetUnitTestImpl();
  impl->os_stack_trace_getter()->UponLeavingGTest();
  internal::HandleExceptionsInMethodIfSupported(this, &Test::SetUp, "SetUp()");
  // We will run the test only if SetUp() was successful and didn't call
  // GTEST_SKIP().
  // 这里调用的 &Test::TestBody 就是上面 TEST 宏生成的 addSuite_test0_Test::TestBody 函数
  // 可以使用 gdb 单步调试验证一下
  if (!HasFatalFailure() && !IsSkipped()) {
    impl->os_stack_trace_getter()->UponLeavingGTest();
    internal::HandleExceptionsInMethodIfSupported(
        this, &Test::TestBody, "the test body");
  }

  // However, we want to clean up as much as possible.  Hence we will
  // always call TearDown(), even if SetUp() or the test body has
  // failed.
  impl->os_stack_trace_getter()->UponLeavingGTest();
  internal::HandleExceptionsInMethodIfSupported(
      this, &Test::TearDown, "TearDown()");
}
```

```bash
#  gdb 打印堆栈来验证一下
(gdb) bt
#0  addSuite_test0_Test::TestBody (this=0x809cbe0) at /home/lzh/github/googletest/mytest/mytest.cpp:7
#1  0x00000000080482ec in testing::internal::HandleSehExceptionsInMethodIfSupported<testing::Test, void> (object=0x809cbe0, method=&virtual testing::Test::TestBody(),
    location=0x805f80b "the test body") at /home/lzh/github/googletest/googletest/src/gtest.cc:2607
#2  0x0000000008040001 in testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void> (object=0x809cbe0, method=&virtual testing::Test::TestBody(),
    location=0x805f80b "the test body") at /home/lzh/github/googletest/googletest/src/gtest.cc:2643
#3  0x0000000008014664 in testing::Test::Run (this=0x809cbe0) at /home/lzh/github/googletest/googletest/src/gtest.cc:2682
#4  0x00000000080150a6 in testing::TestInfo::Run (this=0x809bf90) at /home/lzh/github/googletest/googletest/src/gtest.cc:2861
#5  0x00000000080159a3 in testing::TestSuite::Run (this=0x809c430) at /home/lzh/github/googletest/googletest/src/gtest.cc:3015
#6  0x0000000008025335 in testing::internal::UnitTestImpl::RunAllTests (this=0x809c0f0) at /home/lzh/github/googletest/googletest/src/gtest.cc:5855
#7  0x000000000804981a in testing::internal::HandleSehExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool> (object=0x809c0f0,
    method=(bool (testing::internal::UnitTestImpl::*)(testing::internal::UnitTestImpl * const)) 0x8024f16 <testing::internal::UnitTestImpl::RunAllTests()>,
    location=0x80602f8 "auxiliary test code (environments or event listeners)") at /home/lzh/github/googletest/googletest/src/gtest.cc:2607
#8  0x000000000804123f in testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool> (object=0x809c0f0,
    method=(bool (testing::internal::UnitTestImpl::*)(testing::internal::UnitTestImpl * const)) 0x8024f16 <testing::internal::UnitTestImpl::RunAllTests()>,
    location=0x80602f8 "auxiliary test code (environments or event listeners)") at /home/lzh/github/googletest/googletest/src/gtest.cc:2643
#9  0x0000000008023a9a in testing::UnitTest::Run (this=0x8089500 <testing::UnitTest::GetInstance()::instance>) at /home/lzh/github/googletest/googletest/src/gtest.cc:5438
#10 0x000000000800ac33 in RUN_ALL_TESTS () at /home/lzh/github/googletest/mytest/../googletest/include/gtest/gtest.h:2490
#11 main (argc=<optimized out>, argv=<optimized out>) at /home/lzh/github/googletest/mytest/mytest.cpp:17
(gdb) c
```

googletest 的简单的执行流程就是上面这样子啦。

(～￣▽￣)～