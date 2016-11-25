#include "stdio.h"
#include "stdlib.h"
#include "loadModel.h"
#include "swaps.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


int load_nrnodes(){
    int a= 40001;
    return a;
}

int load_ntree(){ 
    int a=200;
    return a;
}


double * load_xbestsplit(){
#ifdef _WIN32
#define DAT_DIR "\\ROBEX-data\\dat\\"
    char* HOME_DIR=getenv("HOMEPATH");
#else
#define DAT_DIR "/ROBEX-data/dat/"
    char* HOME_DIR=getenv("HOME");
#endif

    double * p = (double *) malloc((MAX_R*load_ntree())*sizeof(double));
    if(p==NULL){
        fprintf(stderr,"Insufficient memory available\n");
        exit(1);
    }
    FILE *fp;
    stringstream all_DAT_DIR;
    all_DAT_DIR<<HOME_DIR<<DAT_DIR;
    char filename[2000]; sprintf(filename,"%sxbestsplit.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {
        fprintf(stdout,"Cannot open a necessary .dat file\n");
        exit( 1 );
    }

    size_t result = fread (p,sizeof(double),(MAX_R*load_ntree()),fp);
    if (result != (MAX_R*load_ntree())) {fprintf(stdout,"Reading error\n"); exit (1);}

    sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
    int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
    if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
    if(twoFiftySix!=256){
        for(int i=0; i<MAX_R*load_ntree(); i++)
            fix_double(p+i);
    }

    fclose(fp);

    return p;
}

double *load_classwt(){ 
    double * p = (double *) malloc(2*sizeof(double));
    if(p==NULL){
        fprintf(stderr,"\n Ran out of memory, exiting... \n");
        exit(1);
    }
    *p=1.0;
    *(p+1)=1.0;
    return p;
}


double *load_cutoff(){ 
    double * p = (double *) malloc(2*sizeof(double));
    if(p==NULL){
        fprintf(stderr,"\n Ran out of memory, exiting... \n");
        exit(1);
    }
    *p=0.5;
    *(p+1)=0.5;
    return p;

}


int *load_treemap(){ 
#ifdef _WIN32
#define DAT_DIR "\\ROBEX-data\\dat\\"
    char* HOME_DIR=getenv("HOMEPATH");
#else
#define DAT_DIR "/ROBEX-data/dat/"
    char* HOME_DIR=getenv("HOME");
#endif
    int *  p = NULL;
    if(2*MAX_R<load_nrnodes()){
        p = (int *) malloc((4*MAX_R*load_ntree())*sizeof(int));
        if(p==NULL){
            fprintf(stderr,"Insufficient memory available\n");
            exit(1);
        }
        FILE *fp;
        stringstream all_DAT_DIR;
        all_DAT_DIR<<HOME_DIR<<DAT_DIR;
        char filename[2000]; sprintf(filename,"%streemap.dat",all_DAT_DIR.str().c_str());
        if( ( fp = fopen( filename, "rb")) == NULL) {
            fprintf(stdout,"Cannot open a necessary .dat file\n");
            exit( 1 );
        }

        size_t result = fread (p,sizeof(int),(4*MAX_R*load_ntree()),fp);
        if (result != (4*MAX_R*load_ntree())) {fprintf(stdout,"Reading error\n"); exit (1);}

        sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
        if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
        int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
        if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
        if(twoFiftySix!=256){
            for(int i=0; i<4*MAX_R*load_ntree(); i++)
                fix_int(p+i);
        }

        fclose(fp);
    }
    else{
        p = (int *) malloc((load_nrnodes()*2*load_ntree())*sizeof(int));
        if(p==NULL){
            fprintf(stderr,"Insufficient memory available\n");
            exit(1);
        }
        FILE *fp;
        stringstream all_DAT_DIR;
        all_DAT_DIR<<HOME_DIR<<DAT_DIR;
        char filename[2000]; sprintf(filename,"%streemap.dat",all_DAT_DIR.str().c_str());
        if( ( fp = fopen( filename, "rb")) == NULL) {
            fprintf(stdout,"Cannot open a necessary .dat file\n");
            exit( 1 );
        }

        size_t result = fread (p,sizeof(int),(load_nrnodes()*2*load_ntree()),fp);
        if (result != (load_nrnodes()*2*load_ntree())) {fprintf(stdout,"Reading error\n"); exit (1);}

        sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
        if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
        int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
        if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
        if(twoFiftySix!=256){
            for(int i=0; i<load_nrnodes()*2*load_ntree(); i++)
                fix_int(p+i);
        }

        fclose(fp);
    }
    return p;
}


int *load_nodestatus(){ 
#ifdef _WIN32
#define DAT_DIR "\\ROBEX-data\\dat\\"
    char* HOME_DIR=getenv("HOMEPATH");
#else
#define DAT_DIR "/ROBEX-data/dat/"
    char* HOME_DIR=getenv("HOME");
#endif
    int * p = (int *) malloc((MAX_R*load_ntree())*sizeof(int));
    if(p==NULL){
        fprintf(stderr,"Insufficient memory available\n");
        exit(1);
    }
    FILE *fp;
    stringstream all_DAT_DIR;
    all_DAT_DIR<<HOME_DIR<<DAT_DIR;
    char filename[2000]; sprintf(filename,"%snodestatus.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {
        fprintf(stdout,"Cannot open a necessary .dat file\n");
        exit( 1 );
    }

    size_t result = fread (p,sizeof(int),(MAX_R*load_ntree()),fp);
    if (result != (MAX_R*load_ntree())) {fprintf(stdout,"Reading error\n"); exit (1);}

    sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
    int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
    if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
    if(twoFiftySix!=256){
        for(int i=0; i<MAX_R*load_ntree(); i++)
            fix_int(p+i);
    }

    fclose(fp);

    return p;
}


int *load_nodeclass(){ 
#ifdef _WIN32
#define DAT_DIR "\\ROBEX-data\\dat\\"
    char* HOME_DIR=getenv("HOMEPATH");
#else
#define DAT_DIR "/ROBEX-data/dat/"
    char* HOME_DIR=getenv("HOME");
#endif
    int * p = (int *) malloc((MAX_R*load_ntree())*sizeof(int));
    if(p==NULL){
        fprintf(stderr,"Insufficient memory available\n");
        exit(1);
    }
    FILE *fp;
    stringstream all_DAT_DIR;
    all_DAT_DIR<<HOME_DIR<<DAT_DIR;
    char filename[2000]; sprintf(filename,"%snodeclass.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen(filename, "rb")) == NULL) {
        fprintf(stdout,"Cannot open a necessary .dat file\n");
        exit( 1 );
    }

    size_t result = fread (p,sizeof(int),(MAX_R*load_ntree()),fp);
    if (result != (MAX_R*load_ntree())) {fprintf(stdout,"Reading error\n"); exit (1);}

    sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
    int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
    if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
    if(twoFiftySix!=256){
        for(int i=0; i<MAX_R*load_ntree(); i++)
            fix_int(p+i);
    }

    fclose(fp);

    return p;
}


int *load_bestvar(){ 
#ifdef _WIN32
#define DAT_DIR "\\ROBEX-data\\dat\\"
    char* HOME_DIR=getenv("HOMEPATH");
#else
#define DAT_DIR "/ROBEX-data/dat/"
    char* HOME_DIR=getenv("HOME");
#endif
    int * p = (int *) malloc((MAX_R*load_ntree())*sizeof(int));
    if(p==NULL){
        fprintf(stderr,"Insufficient memory available\n");
        exit(1);
    }
    FILE *fp;
    stringstream all_DAT_DIR;
    all_DAT_DIR<<HOME_DIR<<DAT_DIR;
    char filename[2000]; sprintf(filename,"%sbestvar.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {
        fprintf(stdout,"Cannot open a necessary .dat file\n");
        exit( 1 );
    }

    size_t result = fread (p,sizeof(int),(MAX_R*load_ntree()),fp);
    if (result != (MAX_R*load_ntree())) {fprintf(stdout,"Reading error\n"); exit (1);}

    sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
    int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
    if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
    if(twoFiftySix!=256){
        for(int i=0; i<MAX_R*load_ntree(); i++)
            fix_int(p+i);
    }

    fclose(fp);

    return p;
}


int *load_ndbigtree(){ 
#ifdef _WIN32
#define DAT_DIR "\\ROBEX-data\\dat\\"
    char* HOME_DIR=getenv("HOMEPATH");
#else
#define DAT_DIR "/ROBEX-data/dat/"
    char* HOME_DIR=getenv("HOME");
#endif
    int * p = (int *) malloc(load_ntree()*sizeof(int));
    if(p==NULL){
        fprintf(stderr,"Insufficient memory available\n");
        exit(1);
    }
    FILE *fp;
    stringstream all_DAT_DIR;
    all_DAT_DIR<<HOME_DIR<<DAT_DIR;
    char filename[2000]; sprintf(filename,"%sndbigtree.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {
        fprintf(stdout,"Cannot open a necessary .dat file\n");
        exit( 1 );
    }

    size_t result = fread (p,sizeof(int),load_ntree(),fp);
    if (result != load_ntree()) {fprintf(stdout,"Reading error\n"); exit (1);}

    sprintf(filename,"%s256.dat",all_DAT_DIR.str().c_str());
    if( ( fp = fopen( filename, "rb")) == NULL) {fprintf(stdout,"Cannot open a necessary .dat file\n"); exit( 1 );}
    int twoFiftySix=0;	result = fread (&twoFiftySix,sizeof(int),1,fp);
    if (result != 1) {fprintf(stdout,"Reading error\n"); exit (1);}
    if(twoFiftySix!=256){
        for(int i=0; i<load_ntree(); i++)
            fix_int(p+i);
    }

    fclose(fp);

    return p;
}


int load_nclass(){ 
    int a=2;
    return a;
}

int load_predict_all(){ 
    int a=0;
    return a;
}
