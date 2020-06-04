#include "libgcpm.h"

void setLibPath(const char *libpath) {
	//printf("Setting path %s\n",libpath);
	int l = strlen(libpath);
	if (libgcpm_path == NULL) {
		libgcpm_path = (char*) malloc(sizeof(char)*l);
	}
	strcpy(libgcpm_path,libpath);
	//printf("Done: %s\n",libgcpm_path);
}

void getlibpath_(char *libpath, int *lp, long int l) {
	//printf("%ld\n",l);
	lp[0] = strlen(libgcpm_path);
	strncpy(libpath,libgcpm_path,lp[0]);
	int i;
	for (i=lp[0];i<l;i++) {
		libpath[i] = ' ';
	}
}

void _ConvertPos(float *x, float *y, float *z, int n, float *r, float *amlt, float *alatr) {
	
	int i;
	float rho2;
	
	for (i=0;i<n;i++) {
		rho2 = x[i]*x[i] + y[i]*y[i];
		r[i] = sqrtf(rho2 + z[i]*z[i]);
		amlt[i] = atan2f(-y[i],-x[i])*12.0/M_PI;
		if (amlt[i] < 0) {
			amlt[i] += 24.0;
		}
		alatr[i] = asinf(z[i]/sqrtf(rho2));
	}
	
}


void _ConvertTime(int *year, int *doy, float *ut, int n, int *itime0, int *itime1) {
	
	int i;
	
	for (i=0;i<n;i++) {
		itime0[i] = year[i]*1000 + doy[i];
		itime1[i] = (int) (ut[i]*3600000.0); 
	}
	
}


void GCPM(float *x, float *y, float *z, int *year, int *doy, float *ut, 
	float *kp, int n, float *ne, float *nH, float *nHe, float *nO,
	int Verbose) {
		
	/* Convert positions */
	float *r = (float*) malloc(sizeof(float)*n);
	float *amlt = (float*) malloc(sizeof(float)*n);
	float *alatr = (float*) malloc(sizeof(float)*n);
	
	_ConvertPos(x,y,z,n,r,amlt,alatr);
	
	/* Convert time */
	int *itime0 = (int*) malloc(sizeof(int)*n);
	int *itime1 = (int*) malloc(sizeof(int)*n);

	_ConvertTime(year,doy,ut,n,itime0,itime1);
	
	/* Loop through each position */
	float tmp[4];
	int itime[2];
	int i;
	for (i=0;i<n;i++) {
		if (Verbose) {
			printf("Calculating %6.2f%%\n",((float) 100 * (i+1))/n);
		}
		itime[0] = itime0[i];
		itime[1] = itime1[i];
		gcpm_v24_(itime,&r[i],&amlt[i],&alatr[i],&kp[i],tmp);
		
		ne[i] = tmp[0];
		nH[i] = tmp[1];
		nHe[i] = tmp[2];
		nO[i] = tmp[3];
	}
	if (Verbose) {
		printf("Calculating %6.2f%%\n",100.0);
	}
}
