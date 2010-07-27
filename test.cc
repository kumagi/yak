
#include <boost/mpl/int.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#include <list>
#include <map>
#include <string>
#include <assert.h>

#include <stdio.h>
#include <msgpack.hpp>
#include "yak_msgpack.hpp"
#include "test_defines.h"

#include <gtest/gtest.h>

struct data{
  int a_;
  int b_;
  data(int a, int b):a_(a),b_(b){}
  //  data(const data& o):a_(o.a_),b_(o.b_){}
  MSGPACK_DEFINE(a_,b_);
  YAK_MSGPACK_DEFINE(a_,b_);
 private:
  data();
};

template<class tuple>
int tuple_size(const tuple& t){
  msgpack::sbuffer sb;
  msgpack::pack(sb, t);
  return sb.size();
}
template<typename any>
int size(const any& t){
  msgpack::type::tuple<any> d(t);
  msgpack::sbuffer sb;
  msgpack::pack(sb, d);
  return sb.size();
}
template<typename a0,typename a1>
int size(const a0& t0,const a1& t1){
  msgpack::type::tuple<a0,a1> d(t0,t1);
  msgpack::sbuffer sb;
  msgpack::pack(sb, d);
  return sb.size();
}

template<typename a0>
std::vector<char> get_buff(const a0& t0){
  msgpack::type::tuple<a0> d(t0);
  msgpack::sbuffer sb;
  msgpack::pack(sb, d);
  std::vector<char> buff(sb.size());
  memcpy(&buff[0],sb.data(),sb.size());
  return buff;
}

data d1(21,2);
data d2(23232,2);
data d3(23232,543000534);

SIZE_1_EQUALS(int,0);
SIZE_1_EQUALS(int,1);
SIZE_1_EQUALS(int,-1);
SIZE_1_EQUALS(int,-31);
SIZE_1_EQUALS(int,-32);
SIZE_1_EQUALS(int,-33);
SIZE_1_EQUALS(int,-34);
SIZE_1_EQUALS(int,127);
SIZE_1_EQUALS(int,128);
SIZE_1_EQUALS(int,129);
SIZE_1_EQUALS(int,-127);
SIZE_1_EQUALS(int,-128);
SIZE_1_EQUALS(int,-129);
SIZE_1_EQUALS(int,255);
SIZE_1_EQUALS(int,256);
SIZE_1_EQUALS(int,257);


SIZE_1_EQUALS(data,d1);
SIZE_1_EQUALS(data,d2);
SIZE_1_EQUALS(data,d3);
SIZE_2_EQUALS(int,int,123,4);
SIZE_2_EQUALS(data,int,d1,3);
SIZE_2_EQUALS(data,data,d1,d1);
SIZE_2_EQUALS(data,data,d2,d2);
SIZE_2_EQUALS(data,data,d1,d3);
SIZE_2_EQUALS(data,data,d3,d3);


BUFF_1_EQUALS(int,0);
BUFF_1_EQUALS(int,1);
BUFF_1_EQUALS(int,-1);
BUFF_1_EQUALS(char,0xe0);
BUFF_1_EQUALS(char,0xe1);
BUFF_1_EQUALS(int,CHAR_MAX - 1);
BUFF_1_EQUALS(int,CHAR_MAX);
BUFF_1_EQUALS(int,CHAR_MAX + 1);
BUFF_1_EQUALS(int,CHAR_MIN - 1);
BUFF_1_EQUALS(int,CHAR_MIN);
BUFF_1_EQUALS(int,CHAR_MIN + 1);
BUFF_1_EQUALS(int,UCHAR_MAX - 1);
BUFF_1_EQUALS(int,UCHAR_MAX);
BUFF_1_EQUALS(int,UCHAR_MAX + 1);

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
