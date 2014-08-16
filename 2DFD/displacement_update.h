#ifndef DISP_H
#define DISP_H

extern void displacement_int(int);
extern void store_boundary(int),store_boundary_mz2(),store_boundary_mz3();
extern void inh_displacement_nonreflecting(int),hom_displacement_nonreflecting(int),
	hom_displacement_nonreflecting_mz3(),hom_displacement_nonreflecting_mz2(),hom_displacement_nonreflecting_mz1();
#endif
