#include <algorithm>
#include <stdint.h>
#include <limits.h>

#define YAK_MSGPACK_DEFINE(...)\
  size_t get_size() const{\
    return msgpack::type::get_size(__VA_ARGS__);\
  }

namespace msgpack{
namespace type{

template<class T>
size_t get_size(const T& t){
  return t.get_size();
}


template <typename integer>
integer change_endian(const integer& org){
  const unsigned char* p = reinterpret_cast<const unsigned char*>(&org);
  integer ans = 0;
  for(int i=sizeof(integer); i>0;i--){
    ans |= *p & 0xff;
    if(i==1)break;
    ans <<=8;
    p++;
  }
  return ans;
}

inline size_t get_size(const bool&){return 1;}
inline size_t get_size(const float& t){return 5;}
inline size_t get_size(const double& t){return 9;}
inline size_t get_size(const char& t){
  if(t < 0){
    return -33 < t ? 1 : 2;
  }else{
    return 1;
  }
}
inline size_t get_size(const int& t){
  if(0 <= t && t < 128) return 1;
  if(-33< t && t < 0) return 1;
  if(0 <= t && t <= UCHAR_MAX) return 2;
  if(CHAR_MIN <= t && t <= CHAR_MAX) return 2;
  if(SHRT_MIN <= t && t <= SHRT_MAX) return 3;
  return 5;
}

template<class T1, class T2>
size_t get_size(const T1& t1, const T2& t2){
  return 1 + get_size(t1) + get_size(t2);
}
template<class T1, class T2, class T3>
size_t get_size(const T1& t1, const T2& t2, const T3& t3){
  return 1 + get_size(t1) + get_size(t2) + get_size(t3);
}

size_t serialize(const int& t,void* dst){
  char* const p = static_cast<char*>(dst);
  if(0 <= t && t < 128) {
    *p = static_cast<char>(t);
    return 1;
  }
  if(-33 < t && t < 0){
    *p = static_cast<char>(t);
    return 1;
  }
  if(0 < t && t <= UCHAR_MAX){
    *p = 0xcc;
    p[1] = static_cast<unsigned char>(t);
    return 2;
  }
  
  if(CHAR_MIN <= t && t <= CHAR_MAX){
    *p = 0xd0;
    p[1] = static_cast<char>(t);
    return 2;
  }
  if(0 < t && t < USHRT_MAX){
    *p = 0xcd;
    unsigned short* const sp = reinterpret_cast<unsigned short*>(p+1);
    *sp = change_endian(static_cast<unsigned short>(t));
    return 3;
  }
  if(SHRT_MIN < t && t < SHRT_MAX) {
    *p = 0xd1;
    short* const sp = reinterpret_cast<short*>(p+1);
    *sp = change_endian(static_cast<short>(t));
    return 3;
  }
  return 5;
}

size_t serialize(const char& t,void* dst){
  char* const p = static_cast<char*>(dst);
  if(0 <= t && t < 128) {
    *p = static_cast<char>(t);
    return 1;
  }
}








}//type
struct capture_base
{
  virtual std::size_t get_size()const = 0;

  template<class buffer>
  std::size_t serialize(buffer* target)const;
};

template <typename D1 = void, typename D2 = void, typename D3 = void>
struct capture;

template<typename D1>
struct capture<D1>: public capture_base{
  const D1& t1;
  capture(const D1& d1):t1(d1){}
  std::size_t get_size()const{
    using namespace type;
    size_t size = 1;
    size += type::get_size(t1);
    return size;
  }
  
  std::size_t serialize(void* b)const{
    int index = 0;
    char* p = static_cast<char*>(b);
    *p = 0x91;
    index++;
    index += type::serialize(t1,&p[index]);
    return index;
  }
};

template<typename D1,typename D2>
struct capture<D1,D2>: public capture_base{
  capture(const D1& d1,const D2& d2):t1(d1),t2(d2){}
  std::size_t get_size()const{
    using namespace type;
    size_t size = 1; // array2
    size += type::get_size(t1);
    size += type::get_size(t2);
    return size;
  }
  const D1& t1;
  const D2& t2;
};

template<typename D1,typename D2,typename D3>
struct capture: public capture_base{
  capture(const D1& d1,const D2& d2,const D3& d3):t1(d1),t2(d2),t3(d3){}
  std::size_t get_size()const{
    using namespace type;
    size_t size = 1; // array3
    size += type::get_size(t1);
    size += type::get_size(t2);
    size += type::get_size(t3);
    return size;
  }
  const D1& t1;
  const D2& t2;
  const D3& t3;
};

}// msgpack
