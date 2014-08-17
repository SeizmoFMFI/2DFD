#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
//#include <queue>
#include <string>
//#include <vector>

#include "displacement_update.h"
#include "files.h"
#include "IO.h"
#include "model.h"
#include "nonreflecting.h"
#include "receiver.h"
#include "source.h"
#include "velocity_update.h"
using namespace std;

#define INFO if (true) //messages, which can be turned on / off, usefull for testing and debugging
#define PI 3.14159265359f
//#define DIM 2000
#define BIGDIM 4000
//#define BIGF 9999999.0f
#define SQR(x) ((x) * (x))
#define FORALL for(int i=0;i<mx;i++) for(int l=0;l<mz;l++)
#define FORINH for(int i=0;i<mx;i++) for(int l=0;l<l_hom;l++)
/*
#define SPARSE const int upi = (mx-1)/dm+1-2*attenuate_boundary_n/dm; const int upl = (l_hom-1)/dm+1;
#define FORSPARSE_NODECLARE for(int i=0;i<upi;i++) for(int l=0;l<upl;l++)
#define FORSPARSE SPARSE FORSPARSE_NODECLARE
#define SPARSE_NOBND const int upi = (mx-1)/dm+1; const int upl = (l_hom-1)/dm+1;
#define FORSPARSE_NOBND SPARSE_NOBND FORSPARSE_NODECLARE
*/

extern void CPU_TIME(); 
extern void time_loop(const int iter),velocity_update(const int iter),displacement_update();

extern void auxiliary(),ERR(string),aux_charakteristika();
extern float u[BIGDIM][BIGDIM],w[BIGDIM][BIGDIM],vu[BIGDIM][BIGDIM],vw[BIGDIM][BIGDIM],
             txx_hline[BIGDIM],tzz_mline[BIGDIM][4],tzx_mline[BIGDIM][4];

extern int max_num_iter;

extern float h,dt;
extern float a_FD,b_FD;

extern float **allocate2Dzeros(const int &sizeX,const int &sizeY);
extern void delete2D(float **arr,const int &sizeX);