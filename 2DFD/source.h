#ifndef SOURCE_H
#define SOURCE_H
using namespace std;

extern int n_src,key_typ_src,key_typ_src_function;

class Source {
public:
      int x,z;
	  float dip,m0,mxx,mzx,mzz;
      float f[20000],fu[20000],fw[20000];
      void vynuluj_time_function(int);
      int sprav_time_function();
};

extern Source src[50];
#endif
