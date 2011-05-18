////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_A173DAC1_868C_4CD5_B4F0_CEAF63640D16)
#define SHEOL_A173DAC1_868C_4CD5_B4F0_CEAF63640D16

#include <sheol/config.hpp>

#include <sstream>
#include <iostream>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/current_function.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>

namespace sheol {

enum counter_type {
  counter_sanity,
  counter_test
};

struct fixture {
 public:
  typedef boost::detail::spinlock mutex_type;

 private:
  std::ostream& stream_;
  std::size_t sanity_failures_;
  std::size_t test_failures_;
  mutex_type mutex_;

 public:
  fixture(std::ostream& stream):
    stream_(stream), sanity_failures_(0), test_failures_(0)
  { 
    mutex_type l = BOOST_DETAIL_SPINLOCK_INIT;
    mutex_ = l;
  }

  void increment(counter_type c) {
    switch (c) {
      case counter_sanity:
        ++sanity_failures_; return;
      case counter_test:
        ++test_failures_; return;
      default:
        { BOOST_ASSERT(false); return; }
    }
  }

  std::size_t get(counter_type c) const {
    switch (c) {
      case counter_sanity:
        return sanity_failures_;
      case counter_test:
        return test_failures_;
      default:
        { BOOST_ASSERT(false); return 0; }
    }
  }

  template <typename T>
  bool check(char const* file, int line, char const* function,
             counter_type c, T const& t, char const* msg)
  {
    if (!t) { 
      mutex_type::scoped_lock l(mutex_);
      stream_ 
        << file << "(" << line << "): "
        << msg << " failed in function '"
        << function << "'" << std::endl;
      increment(c);
      return false;
    }
    return true;
  }

  template <typename T, typename U>
  bool check_str_equal(char const* file, int line, char const* function,
                       counter_type c, T const& t, U const& u, char const* msg)
  {
    std::ostringstream oss;

    oss.str("");
    oss << t;
    std::string t_str = oss.str();

    oss.str("");
    oss << u;
    std::string u_str = oss.str();

    if (!(t_str == u_str)) {
      mutex_type::scoped_lock l(mutex_);
      stream_ 
        << file << "(" << line << "): " << msg  
        << " failed in function '" << function << "': "
        << "'" << t_str << "' != '" << u_str << "'" << std::endl;
      increment(c);
      return false;
    }
    return true;
  }

  template <typename T, typename U>
  bool check_equal(char const* file, int line, char const* function,
                counter_type c, T const& t, U const& u, char const* msg)
  {
    if (!(t == u)) {
      mutex_type::scoped_lock l(mutex_);
      stream_ 
        << file << "(" << line << "): " << msg  
        << " failed in function '" << function << "': "
        << "'" << t << "' != '" << u << "'" << std::endl;
      increment(c);
      return false;
    }
    return true;
  }
  
  template <typename T, typename U>
  bool check_not_equal(char const* file, int line, char const* function,
                       counter_type c, T const& t, U const& u,
                       char const* msg)
  {
    if (!(t != u)) {
      mutex_type::scoped_lock l(mutex_);
      stream_ 
        << file << "(" << line << "): " << msg  
        << " failed in function '" << function << "': "
        << "'" << t << "' != '" << u << "'" << std::endl;
      increment(c);
      return false;
    }
    return true;
  }

  template <typename T, typename U>
  bool check_less(char const* file, int line, char const* function,
                  counter_type c, T const& t, U const& u, char const* msg)
  {
    if (!(t < u)) {
      mutex_type::scoped_lock l(mutex_);
      stream_ 
        << file << "(" << line << "): " << msg  
        << " failed in function '" << function << "': "
        << "'" << t << "' >= '" << u << "'" << std::endl;
      increment(c);
      return false;
    }
    return true;
  }
  
  template <typename T, typename U>
  bool check_less_equal(char const* file, int line, char const* function,
                        counter_type c, T const& t, U const& u,
                        char const* msg)
  {
    if (!(t <= u)) {
      mutex_type::scoped_lock l(mutex_);
      stream_ 
        << file << "(" << line << "): " << msg  
        << " failed in function '" << function << "': "
        << "'" << t << "' > '" << u << "'" << std::endl;
      increment(c);
      return false;
    }
    return true;
  }
};

// FIXME: This needs to be protected with boost::call_once or something similar
fixture global_fixture = fixture(std::cerr);

inline int report_errors() {
  std::size_t sanity = global_fixture.get(counter_sanity),
              test   = global_fixture.get(counter_test); 
  if (sanity == 0 && test == 0)
    return 0;

  else {
    std::cerr << sanity << " sanity check"
              << ((sanity == 1) ? " and " : "s and ")
              << test << " test"
              << ((test == 1) ? " failed." : "s failed.")
              << std::endl;
    return 1;
  }
}

} // sheol

#define SHEOL_TEST(expr)                                                \
  ::sheol::global_fixture.check                                         \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr, "test '" BOOST_PP_STRINGIZE(expr) "'")                       \
  /***/

#define SHEOL_TEST_MSG(expr, msg)                                       \
  ::sheol::global_fixture.check                                         \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr, msg)                                                         \
  /***/

#define SHEOL_TEST_STREQ(expr1, expr2)                                  \
  ::sheol::global_fixture.check_str_equal                               \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr1, expr2, "test '" BOOST_PP_STRINGIZE(expr1) " str== "         \
                            BOOST_PP_STRINGIZE(expr2) "'")              \
  /***/

#define SHEOL_TEST_EQ(expr1, expr2)                                     \
  ::sheol::global_fixture.check_equal                                   \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr1, expr2, "test '" BOOST_PP_STRINGIZE(expr1) " == "            \
                            BOOST_PP_STRINGIZE(expr2) "'")              \
  /***/

#define SHEOL_TEST_NEQ(expr1, expr2)                                    \
  ::sheol::global_fixture.check_not_equal                               \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr1, expr2, "test '" BOOST_PP_STRINGIZE(expr1) " != "            \
                            BOOST_PP_STRINGIZE(expr2) "'")              \
  /***/

#define SHEOL_TEST_LT(expr1, expr2)                                     \
  ::sheol::global_fixture.check_less                                    \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr1, expr2, "test '" BOOST_PP_STRINGIZE(expr1) " < "             \
                            BOOST_PP_STRINGIZE(expr2) "'")              \
  /***/

#define SHEOL_TEST_LTE(expr1, expr2)                                    \
  ::sheol::global_fixture.check_less_equal                              \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr1, expr2, "test '" BOOST_PP_STRINGIZE(expr1) " <= "            \
                            BOOST_PP_STRINGIZE(expr2) "'")              \
  /***/

#define SHEOL_TEST_EQ_MSG(expr1, expr2, msg)                            \
  ::sheol::global_fixture.check_equal                                   \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_test,                                             \
     expr1, expr2, msg)                                                 \
  /***/

#define SHEOL_SANITY(expr)                                              \
  ::sheol::global_fixture.check                                         \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr, "sanity check '" BOOST_PP_STRINGIZE(expr) "'")               \
  /***/

#define SHEOL_SANITY_MSG(expr, msg)                                     \
  ::sheol::global_fixture.check                                         \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr, msg)                                                         \
  /***/

#define SHEOL_SANITY_STREQ(expr1, expr2)                                \
  ::sheol::global_fixture.check_str_equal                               \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr1, expr2, "sanity check '" BOOST_PP_STRINGIZE(expr1) " str== " \
                                    BOOST_PP_STRINGIZE(expr2) "'")      \
  /***/

#define SHEOL_SANITY_EQ(expr1, expr2)                                   \
  ::sheol::global_fixture.check_equal                                   \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr1, expr2, "sanity check '" BOOST_PP_STRINGIZE(expr1) " == "    \
                                    BOOST_PP_STRINGIZE(expr2) "'")      \
    /***/

#define SHEOL_SANITY_NEQ(expr1, expr2)                                  \
  ::sheol::global_fixture.check_not_equal                               \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr1, expr2, "sanity check '" BOOST_PP_STRINGIZE(expr1) " != "    \
                                    BOOST_PP_STRINGIZE(expr2) "'")      \
  /***/

#define SHEOL_SANITY_LT(expr1, expr2)                                   \
  ::sheol::global_fixture.check_less                                    \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr1, expr2, "sanity check '" BOOST_PP_STRINGIZE(expr1) " < "     \
                                    BOOST_PP_STRINGIZE(expr2) "'")      \
  /***/

#define SHEOL_SANITY_LTE(expr1, expr2)                                  \
  ::sheol::global_fixture.check_less_equal                              \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr1, expr2, "sanity check '" BOOST_PP_STRINGIZE(expr1) " <= "    \
                                    BOOST_PP_STRINGIZE(expr2) "'")      \
  /***/

#define SHEOL_SANITY_EQ_MSG(expr1, expr2, msg)                          \
  ::sheol::global_fixture.check_equal                                   \
    (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION,                        \
     ::sheol::counter_sanity,                                           \
     expr1, expr2)                                                      \
  /***/

#endif // SHEOL_A173DAC1_868C_4CD5_B4F0_CEAF63640D16

