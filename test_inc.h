
#include <boost/mpl/int.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>


#define SIZE_times_EQUALS(X0,x0) TEST(pack_integer,__LINE__)	\
  {\
    msgpack::capture<BOOST_PP_ENUM_PARAMS(times, X)> captured(BOOST_PP_ENUM_PARAMS(times, x)); \
    int expect = size<BOOST_PP_ENUM_PARAMS(times, X)>(BOOST_PP_ENUM_PARAMS(times, x)); \
  EXPECT_EQ(captured.get_size(), expect);\
  }
