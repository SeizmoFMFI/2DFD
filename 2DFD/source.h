#ifndef SOURCE_H
#define SOURCE_H
using namespace std;

extern int n_src, src_type, src_time_function, src_char_time;

class Source {
public:
      int x,z;
	  float dip,m0,mxx,mzx,mzz;
      float f[20000],fu[20000],fw[20000];
      bool make_time_function();
};

extern Source src[50];
#endif
