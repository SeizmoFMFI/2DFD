#ifndef SOURCE_H
#define SOURCE_H
using namespace std;

extern int n_src,src_type,src_time_function;

class Source {
public:
      int x,z;
	  int num_active_iter; //how many iterations is source active (source time function is not zero)
	  float dip,m0,mxx,mzx,mzz;
      float f[20000],fu[20000],fw[20000];
      void reset_time_function();
      int make_time_function();
};

extern Source src[50];
#endif
