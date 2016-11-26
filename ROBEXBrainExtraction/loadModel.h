#define MAX_R 30000
//#ifdef _WIN32
//#define DAT_DIR "\\dat\\"
//char* HOME_DIR=getenv("HOMEPATH");
//#else
//#define DAT_DIR "/dat/"
//char* HOME_DIR=getenv("HOME");
//#endif

int load_nrnodes();
int load_ntree();
double * load_xbestsplit();
double *load_classwt();
double *load_cutoff();
int *load_treemap();
int *load_nodestatus();
int *load_nodeclass();
int *load_bestvar();
int *load_ndbigtree();
int load_nclass();
int load_predict_all();
