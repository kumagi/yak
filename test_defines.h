
#define SIZE_1_EQUALS(X1,x1) TEST(size_equal_in_1_tuples,__LINE__)	\
  {\
  msgpack::capture<X1> captured(x1);\
  int expect = size<X1>(x1);\
  EXPECT_EQ(captured.get_size(), expect);\
  }
#define SIZE_2_EQUALS(X0,X1,x0,x1) TEST(size_equal_in_2_tuples,__LINE__)\
  {\
    msgpack::capture<X0,X1> captured(x0,x1);\
    int expect = size<X0,X1> (x0,x1);\
    EXPECT_EQ(captured.get_size(), expect);\
  }

#define SIZE_3_EQUALS(X0,X1,X2,x0,x1,x2) TEST(size_equal_in_3_tuples,__LINE__)	\
  {\
    msgpack::capture<BOOST_PP_ENUM_PARAMS(3,X)>\
      captured(BOOST_PP_ENUM_PARAMS(3,x));\
    int expect = size<BOOST_PP_ENUM_PARAMS(3,X)>\
      (BOOST_PP_ENUM_PARAMS(3,x));\
    EXPECT_EQ(captured.get_size(), expect);\
  }
#define SIZE_4_EQUALS(X0,X1,X2,X3,x0,x1,x2,x3) TEST(size_equal_in_4_tuples,__LINE__) \
  {\
    msgpack::capture<BOOST_PP_ENUM_PARAMS(4,X)>	\
      captured(BOOST_PP_ENUM_PARAMS(4,x));\
    int expect = size<BOOST_PP_ENUM_PARAMS(4,X)>\
      (BOOST_PP_ENUM_PARAMS(4,x));\
    EXPECT_EQ(captured.get_size(), expect);\
  }
#define SIZE_5_EQUALS(X0,X1,X2,X3,X4,x0,x1,x2,x3,x4) TEST(size_equal_in_5_tuples,__LINE__) \
  {\
    msgpack::capture<BOOST_PP_ENUM_PARAMS(5,X)>	\
      captured(BOOST_PP_ENUM_PARAMS(5,x));		\
    int expect = size<BOOST_PP_ENUM_PARAMS(5,X)>\
      (BOOST_PP_ENUM_PARAMS(5,x));\
    EXPECT_EQ(captured.get_size(), expect);\
  }

#define BUFF_1_EQUALS(X1,x1) TEST(buff_equal_in_1_tuple,__LINE__)	\
  {\
  msgpack::capture<X1> captured(x1);\
  std::vector<char> target(captured.get_size());\
  int len = captured.serialize(target.data());\
  std::vector<char> origin= get_buff<int>(x1);\
  EXPECT_EQ(len, target.size());\
  EXPECT_EQ(origin.size(),target.size());\
  for(size_t i=0;i < target.size(); i++){\
    EXPECT_EQ(origin[i] & 255,target[i] & 255);	 \
  }\
}
