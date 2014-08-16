#include "global.h"

                            //volane vo velocity_update()
void horizontal_line_0() {
     free_surface_0_stress_int();
     free_surface_0_stress_2nd();
     
     free_surface_0_velocity_int();
     free_surface_0_velocity_2nd();
}

void horizontal_line_1() {
     free_surface_1_stress_int();
     free_surface_1_stress_2nd();
     
     free_surface_1_velocity_int();
     free_surface_1_velocity_2nd();
} 

void horizontal_line_2() {
     free_surface_2_stress_int();
     free_surface_2_stress_2nd();
     
     free_surface_2_velocity_int();
     free_surface_2_velocity_2nd();
}

void horizontal_line_hom(int l) {
     hom_stress_int(l);
     hom_stress_2nd(l);
     
     hom_velocity_int(l);
     hom_velocity_2nd(l);
}

void horizontal_line_inh(int l) {
     inh_stress_int(l);
     inh_stress_2nd(l);
     
     inh_velocity_int(l);
     inh_velocity_2nd(l);
}

void horizontal_line_mz2() {
     bottom_boundary_2_stress_int();
     bottom_boundary_2_stress_2nd();
     bottom_boundary_2_velocity();
} 

void horizontal_line_mz3() {
     bottom_boundary_3_stress_int();
     hom_stress_2nd(mz3);
     
     hom_velocity_int(mz3);
     hom_velocity_2nd(mz3);
} 
