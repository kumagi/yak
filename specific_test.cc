#include <list>
#include <map>
#include <string>
#include <assert.h>

#include <stdio.h>
#include <msgpack.hpp>
#include <gtest/gtest.h>

struct data{
  int a_;
  int b_;
  data(int a, int b):a_(a),b_(b){}
  //  data(const data& o):a_(o.a_),b_(o.b_){}
  MSGPACK_DEFINE(a_,b_);
 private:
  data();
};
template<class tuple>
void tuple_dump(const tuple& t){
    msgpack::sbuffer sb;
    msgpack::pack(sb, t);
    const char* ptr = sb.data();
    for(std::size_t i=0; i<sb.size(); ++i){
        printf("%02x",*ptr++ & 255);
    }
}
template<class tuple>
int tuple_size(const tuple& t){
    msgpack::sbuffer sb;
    msgpack::pack(sb, t);
    return sb.size();
}

#define size(t1,length,...) TEST(node_1,__LINE__)	\
  {\
    msgpack::type::tuple<__VA_ARGS__> t(t1);\
    EXPECT_EQ(tuple_size(t), length);\
  }
#define size2(t1,t2,length,...) TEST(node_2,__LINE__)	\
  {\
    msgpack::type::tuple<__VA_ARGS__> t(t1,t2);	\
    EXPECT_EQ(tuple_size(t), length);\
  }

int p(4);
data d(3,2);
size(p,2,int);
size(d,4,data)
size2(p,d,5,int,data);


int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  msgpack::type::tuple<data,int> t(data(2,3),2);
  tuple_dump(t);
    return RUN_ALL_TESTS();
}
