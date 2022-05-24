#pragma once
#include "for_each.hpp"

#define FOR_EACH_N_JOIN_0(...)
#define FOR_EACH_N_JOIN_1(N, what, x, ...)\
  what(N, 1, x)                     \
  FOR_EACH_N_JOIN_0(N, what, ##__VA_ARGS__)
#define FOR_EACH_N_JOIN_2(N, what, x, ...)\
  what(N, 2, x), \
  FOR_EACH_N_JOIN_1(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_3(N, what, x, ...)\
  what(N, 3, x), \
  FOR_EACH_N_JOIN_2(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_4(N, what, x, ...)\
  what(N, 4, x), \
  FOR_EACH_N_JOIN_3(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_5(N, what, x, ...)\
  what(N, 5, x), \
 FOR_EACH_N_JOIN_4(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_6(N, what, x, ...)\
  what(N, 6, x), \
  FOR_EACH_N_JOIN_5(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_7(N, what, x, ...)\
  what(N, 7, x), \
  FOR_EACH_N_JOIN_6(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_8(N, what, x, ...)\
  what(N, 8, x), \
  FOR_EACH_N_JOIN_7(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_9(N, what, x, ...)\
  what(N, 9, x), \
  FOR_EACH_N_JOIN_8(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_10(N, what, x, ...)\
  what(N, 10, x), \
  FOR_EACH_N_JOIN_9(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_11(N, what, x, ...)\
  what(N, 11, x), \
  FOR_EACH_N_JOIN_10(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_12(N, what, x, ...)\
  what(N, 12, x), \
  FOR_EACH_N_JOIN_11(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_13(N, what, x, ...)\
  what(N, 13, x), \
  FOR_EACH_N_JOIN_12(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_14(N, what, x, ...)\
  what(N, 14, x), \
  FOR_EACH_N_JOIN_13(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_15(N, what, x, ...)\
  what(N, 15, x), \
  FOR_EACH_N_JOIN_14(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_16(N, what, x, ...)\
  what(N, 16, x), \
  FOR_EACH_N_JOIN_15(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_17(N, what, x, ...)\
  what(N, 17, x), \
  FOR_EACH_N_JOIN_16(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_18(N, what, x, ...)\
  what(N, 18, x), \
  FOR_EACH_N_JOIN_17(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_19(N, what, x, ...)\
  what(N, 19, x), \
  FOR_EACH_N_JOIN_18(N, what, __VA_ARGS__)
#define FOR_EACH_N_JOIN_20(N, what, x, ...)\
  what(N, 20, x), \
  FOR_EACH_N_JOIN_19(N, what, __VA_ARGS__)

#define FOR_EACH_N_JOIN_(N, what, ...) CONCATENATE(FOR_EACH_N_JOIN_, N)(N, what, ##__VA_ARGS__)
#define FOR_EACH_N_JOIN(what, ...) FOR_EACH_N_JOIN_(FOR_EACH_NARG(__VA_ARGS__), what, ##__VA_ARGS__)
