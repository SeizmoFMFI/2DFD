#include "global.h"

bool Source::make_time_function() {
	assert(max_num_iter < 20000 && "arrays in source too small");

     float aa,bb;
	 int ts = 0;
	 if (src_time_function==1) {//_____________________________ KUPPER ___
		 for (int i=0;i<max_num_iter;i++) {
			aa=i*2.0f*PI/max_num_iter;
			bb=2*aa;
            f[i]=sin(aa)-0.5f*sin(bb);
         }
	 }	/*
         else if (key_typ_src_function==2) {//_____________________________ RICKER ___
            aa=i;
			aa=6*SQR(aa/source_max_num_iter);
            
			f[i]=m0*(aa-0.5f)*exp(-aa);
         }*/
     else if (src_time_function==3) {//______________________________ GABOR ___
		 
		float gamma = 0.3f; //smaller gamma - more delta-like
		float fp = 0.45f/200;
		ts = 0; //0.15*gamma/fp;
		float phi1,phi2;
		
		for (int i=0;i<max_num_iter;i++) {
			 aa   = (float)(i-ts);
			 phi1 = 2.0f*PI*fp*aa/gamma;
			 phi2 = 2.0f*PI*fp*aa + PI/2;
			 f[i]=exp(-SQR(phi1))*cos(phi2)*aa;
		}
     }/*
         else if (key_typ_src_function==4) {//____________________________ BERLAGE ___
            cout<<"ERR: TODO: doprogramuj power to"<<endl;
            cin.get();cin.get();
            //fs[i]=(T**A3(isrc))*EXP(-A2(isrc)*T)*SIN(A1(isrc)*T);
         */
	 else if (src_time_function == 5) { //____________________________ GAUSS ___
		 ts = (int)(max_num_iter/3);
		 int tt = 2*ts;
		 for (int i=0;i<max_num_iter;i++) {
			 f[i] = expf(-(4.f*SQR(i-ts))/SQR(ts/1.5f)) - expf(-(4.f*SQR(i-tt))/SQR(ts/1.5f));
		 }
	 }
	 else if (src_time_function == 6) { //____________________________ GAUSS/2 ___
		 ts = (int)(max_num_iter/3);
		 for (int i=0;i<max_num_iter;i++) {
			 f[i] = expf(-(4.f*SQR(i-ts))/SQR(ts/1.5f));
		 }
	 }
	 else {
		 cerr<<src_time_function<<endl;
		 ERR("No such time function");
		 return false;
	 }

	 return true;
} 
