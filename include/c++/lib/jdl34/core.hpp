#ifndef JDL34_CPP_CORE_HPP
#define JDL34_CPP_CORE_HPP

#include <cstdio>
#include <cstddef>
#include <cstdlib>

#define JDL34_CPP_LIB_VERSION 1

#define JDL34_CPP_STRINGIFY_IMPL(x) #x
#define JDL34_CPP_STRINGIFY(x) JDL34_CPP_STRINGIFY_IMPL(x)
#define JDL34_CPP_CONCAT_IMPL(a, b) a##b
#define JDL34_CPP_CONCAT(a, b) JDL34_CPP_CONCAT_IMPL(a, b)

#define JDL34_CPP_NARG_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#define JDL34_CPP_NARG1(...) JDL34_CPP_NARG_IMPL(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1,0)
#define JDL34_CPP_NARG(...) (JDL34_CPP_NARG1(__VA_ARGS__))

#define JDL34_CPP_FOREACH_1(m, x)     m(x)
#define JDL34_CPP_FOREACH_2(m, x, ...) m(x) JDL34_CPP_FOREACH_1(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_3(m, x, ...) m(x) JDL34_CPP_FOREACH_2(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_4(m, x, ...) m(x) JDL34_CPP_FOREACH_3(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_5(m, x, ...) m(x) JDL34_CPP_FOREACH_4(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_6(m, x, ...) m(x) JDL34_CPP_FOREACH_5(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_7(m, x, ...) m(x) JDL34_CPP_FOREACH_6(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_8(m, x, ...) m(x) JDL34_CPP_FOREACH_7(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_9(m, x, ...) m(x) JDL34_CPP_FOREACH_8(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_10(m, x, ...) m(x) JDL34_CPP_FOREACH_9(m, __VA_ARGS__)
#define JDL34_CPP_FOREACH_NARG_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#define JDL34_CPP_FOREACH_NARG(...) JDL34_CPP_FOREACH_NARG_IMPL(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1,0)
#define JDL34_CPP_FOR_EACH(m, ...) \
    JDL34_CPP_CONCAT(JDL34_CPP_FOREACH_, JDL34_CPP_FOREACH_NARG(__VA_ARGS__))(m, __VA_ARGS__)

namespace jdl34 {

inline constexpr int version_major = 0;
inline constexpr int version_minor = 1;
inline constexpr int version_patch = 0;

template <typename T, size_t N>
constexpr size_t array_len(const T (&)[N]) { return N; }

template <typename T>
constexpr T clamp(const T& v, const T& lo, const T& hi) {
  return v < lo ? lo : (hi < v ? hi : v);
}

template <typename T>
constexpr const T& min(const T& a, const T& b) { return b < a ? b : a; }

template <typename T>
constexpr const T& max(const T& a, const T& b) { return a < b ? b : a; }

template <typename... Args>
inline int logf(int level, const char* fmt, Args... args) {
  const char* tag = "I";
  switch (level) {
    case 0: tag = "D"; break;
    case 1: tag = "I"; break;
    case 2: tag = "W"; break;
    case 3: tag = "E"; break;
    default: break;
  }
  std::fprintf(stderr, "[jdl34:%s] ", tag);
  int n = std::fprintf(stderr, fmt, args...);
  std::fprintf(stderr, "\n");
  return n;
}

}

#endif