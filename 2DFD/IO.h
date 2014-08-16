#ifndef IO_H
#define IO_H

extern void loadModel(),loadData(),loadSource(),load_adjoint_source(),load_grid(),loadReceivers();
extern void record_sparse(int),record_at_receivers(int),record_at_source(int),record_java(const int iter);
extern int record_every_nth_step;
extern void main_vstup();
#endif
