#include "global.h"
float e1,e2,e12,lam_il,lam2mu_il;
int ll,ll_ind;//,llm2,llm1,llp1,llp2,ll_ind;

void explosive_source(const int &i,const int &xi,const int &zi,const float &f) {
	float tmp_den=co_density;
	if (zi<l_hom) 
		tmp_den=density_u[xi][zi];
            
				//    Fx
	vu[xi+1][zi] += 1000*dt*f/tmp_den;
    vu[xi][zi]   -= 1000*dt*f/tmp_den;
              
              //    Fz
    vw[xi][zi+1] += 1000*dt*f/tmp_den;
    vw[xi][zi]   -= 1000*dt*f/tmp_den;
}

void double_couple_source(const int &i,const int &xi,const int &zi,const float &f) {
	const float mxx=src[i].mxx;
    const float mzx=src[i].mzx;
    const float mzz=src[i].mzz;

	float tmp_den=co_density;
	if (zi<l_hom) 
		tmp_den=density_u[xi][zi];
	
	float I = dt*f/tmp_den;
              //    Fx
              vu[xi+1][zi]   += mxx*I;
              vu[xi+1][zi+1] += mzx*I;
              vu[xi][zi+1]   += mzx*I;
              
              vu[xi][zi]     -= mxx*I;
              vu[xi+1][zi-1] -= mzx*I;
              vu[xi][zi-1]   -= mzx*I;

              //    Fz
              vw[xi][zi+1]   += mzz*I;
              vw[xi+1][zi+1] += mzx*I;
              vw[xi+1][zi]   += mzx*I;
              
              vw[xi][zi]     -= mzz*I;
              vw[xi-1][zi+1] -= mzx*I;
              vw[xi-1][zi]   -= mzx*I;
}

void velocity_update(const int iter) {
     horizontal_line_0();
     horizontal_line_1();
     horizontal_line_2();
     
	 for (int l=3;l<l_hom;l++) 
         horizontal_line_inh(l);
     for (int l=l_hom;l<mz3;l++)
         horizontal_line_hom(l);

     horizontal_line_mz3();
     horizontal_line_mz2();

     if (iter<source_num_active_iter) {
		 int xi=src[active_source].x;
		 int zi=src[active_source].z;

         if (src_type==1)                  //explosive source
			 explosive_source(active_source,xi,zi,src[active_source].f[iter]); 
         else if (src_type==2)                 //double-couple
			 double_couple_source(active_source,xi,zi,src[active_source].f[iter]);
		 else 
			 ERR("no such source type");
		 cout<<iter<<" "<<u[xi][zi]<<" "<<w[xi][zi]<<" "<<vu[xi][zi]<<" "<<vw[xi][zi]<<" "<<src[active_source].f[iter]<<endl;
     }
}
