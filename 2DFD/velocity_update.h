#ifndef VELO_H
#define VELO_H

extern void horizontal_line_inh(int),horizontal_line_hom(int),horizontal_line_0(),
            horizontal_line_1(),horizontal_line_2(),horizontal_line_mz3(),horizontal_line_mz2();
            
extern void compute_e1_e2_int(int,int),compute_e1_e2_2nd(int,int),compute_e12_int(int,int),compute_e12_2nd(int,int),
			nastav_lambda(int,int),
			vyrataj_xx(int),vyrataj_zz(int,int),vyrataj_zx(int,int,int);
extern void free_surface_0_stress_int(),	free_surface_0_stress_2nd(),
            free_surface_0_velocity_int(),	free_surface_0_velocity_2nd(),
            free_surface_1_stress_int(),	free_surface_1_stress_2nd(),
            free_surface_1_velocity_int(),	free_surface_1_velocity_2nd(),
            free_surface_2_stress_int(),	free_surface_2_stress_2nd(),
            free_surface_2_velocity_int(),	free_surface_2_velocity_2nd();
            
extern void hom_stress_int(int),	hom_stress_2nd(int),
            hom_velocity_int(int),	hom_velocity_2nd(int),
			hom_stress_zz_2nd(int,int),hom_stress_zx_2nd(int,int),
            inh_stress_int(int),	inh_stress_2nd(int),
            inh_velocity_int(int),	inh_velocity_2nd(int);
            
extern void bottom_boundary_2_stress_int(),bottom_boundary_2_stress_2nd(),
            bottom_boundary_2_velocity(),
            bottom_boundary_3_stress_int();
     
extern float e1,e2,e12,lam_il,lam2mu_il;
extern int ll,ll_ind;
#endif
