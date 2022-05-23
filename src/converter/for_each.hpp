#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x)\
  FOR_EACH_1(what,  __VA_ARGS__)
#define FOR_EACH_3(what, x, ...)\
  what(x)\
  FOR_EACH_2(what, __VA_ARGS__)
#define FOR_EACH_4(what, x, ...)\
  what(x)\
  FOR_EACH_3(what,  __VA_ARGS__)
#define FOR_EACH_5(what, x, ...)\
  what(x)\
 FOR_EACH_4(what,  __VA_ARGS__)
#define FOR_EACH_6(what, x, ...)\
  what(x)\
  FOR_EACH_5(what,  __VA_ARGS__)
#define FOR_EACH_7(what, x, ...)\
  what(x)\
  FOR_EACH_6(what,  __VA_ARGS__)
#define FOR_EACH_8(what, x, ...)\
  what(x)\
  FOR_EACH_7(what,  __VA_ARGS__)
#define FOR_EACH_9(what, x, ...)\
  what(x)\
  FOR_EACH_8(what,  __VA_ARGS__)
#define FOR_EACH_10(what, x, ...)\
  what(x)\
  FOR_EACH_9(what,  __VA_ARGS__)
#define FOR_EACH_11(what, x, ...)\
  what(x)\
  FOR_EACH_10(what,  __VA_ARGS__)
#define FOR_EACH_12(what, x, ...)\
  what(x)\
  FOR_EACH_11(what,  __VA_ARGS__)
#define FOR_EACH_13(what, x, ...)\
  what(x)\
  FOR_EACH_12(what,  __VA_ARGS__)
#define FOR_EACH_14(what, x, ...)\
  what(x)\
  FOR_EACH_13(what,  __VA_ARGS__)
#define FOR_EACH_15(what, x, ...)\
  what(x)\
  FOR_EACH_14(what,  __VA_ARGS__)
#define FOR_EACH_16(what, x, ...)\
  what(x)\
  FOR_EACH_15(what,  __VA_ARGS__)
#define FOR_EACH_17(what, x, ...)\
  what(x)\
  FOR_EACH_16(what,  __VA_ARGS__)
#define FOR_EACH_18(what, x, ...)\
  what(x)\
  FOR_EACH_17(what,  __VA_ARGS__)
#define FOR_EACH_19(what, x, ...)\
  what(x)\
  FOR_EACH_18(what,  __VA_ARGS__)
#define FOR_EACH_20(what, x, ...)\
  what(x)\
  FOR_EACH_19(what,  __VA_ARGS__)

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, N, ...) N
#define FOR_EACH_RSEQ_N() 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)
