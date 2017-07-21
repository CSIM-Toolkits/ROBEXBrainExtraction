#include <string>
#define MAX_R 30000

int load_nrnodes();
int load_ntree();
double * load_xbestsplit(std::string DAT_PATH);
double *load_classwt();
double *load_cutoff();
int *load_treemap(std::string DAT_PATH);
int *load_nodestatus(std::string DAT_PATH);
int *load_nodeclass(std::string DAT_PATH);
int *load_bestvar(std::string DAT_PATH);
int *load_ndbigtree(std::string DAT_PATH);
int load_nclass();
int load_predict_all();
