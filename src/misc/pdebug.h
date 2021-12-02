#ifndef pdebug
#ifndef NDEBUG
#define pdebug(S)                                                   \
  std::cout << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ \
            << "(): " << S << std::endl;
#define pdebug_val(X)                                               \
  std::cout << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ \
            << "(): " << #X << "=" << X << std::endl;
#else
#define pdebug(S)
#define pdebug_val(X)
#endif
#endif