

#define ARITY 2
#define SIZE_EQUALS(z, n, unused)\
  SIZE_EQUAL(X BOOST_PP_ENUM_TRAILING_PARAMS(n, T)		\
	     x BOOST_PP_ENUM_TRAILING_PARAMS(n, t))		\
    msgpack::capture<X BOOST_PP_ENUM_TRAILING_PARAMS(n, T)>	\
      captured(x BOOST_PP_ENUM_TRAILING_PARAMS(n, t));		\
    int expect = size<X BOOST_PP_ENUM_TRAILING_PARAMS(n, T)>(x BOOST_PP_ENUM_TRAILING_PARAMS(n, t));\
    EXPECT_EQ(captured.get_size(), expect);\
    }

//BOOST_PP_REPEAT(ARITY, COMPARETOR,~);
TEST(hoge,fuga){
}

//SIZE_1_EQUALS(int,5);
//SIZE_2_EQUALS(int,int,3,2);

#define SIZE_1_EQUALS(X1,x1) TEST(pack_integer,__LINE__)	\
  {\
  msgpack::capture<X1> captured(x1);\
  int expect = size<X1>(x1);\
  EXPECT_EQ(captured.get_size(), expect);\
  }
#define SIZE_2_EQUALS(X0,X1,x0,x1) TEST(pack_integer,__LINE__)\
  {\
    msgpack::capture<X0,X1> captured(x0,x1);\
    int expect = size<X0,X1>(x0,x1);\
    EXPECT_EQ(captured.get_size(), expect);\
  }

	
#define PARAMS(z, n, unused)\
  const BOOST_PP_CAT(a, n)& BOOST_PP_CAT(t, n) 

#define SIZE_DEFINES(z,n,unuse)\
  template<BOOST_PP_ENUM_PARAMS(n,typename a)>\
  int size(BOOST_PP_REPEAT(n, PARAMS, ~)){		\
    msgpack::type::tuple<BOOST_PP_ENUM_PARAMS(n,a)>\
      d(BOOST_PP_ENUM_PARAMS(n,t));\
  msgpack::sbuffer sb;\
  msgpack::pack(sb, d);\
  return sb.size();\
}
SIZE_DEFINES(z,2,p)