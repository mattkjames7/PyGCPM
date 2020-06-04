#ifndef __LIBGCPM_H__
#define __LIBGCPM_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#endif



/* Variable which stores the path of the data files */
char *libgcpm_path = NULL;
void setLibPath(const char *libpath);
void getlibpath_(char *libpath, int *lp, long int n);

/* This is the function we call in FORTRAN*/
extern void gcpm_v24_(int *itime, float *r, float *amlt, float *alatr, float *akp, float *outn);

/* The wrapper to be called by Python */
void GCPM(float *x, float *y, float *z, int *year, int *doy, float *ut, 
	float *kp, int n, float *ne, float *nH, float *nHe, float *nO,
	int Verbose);
