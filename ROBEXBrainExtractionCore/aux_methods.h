#include <vnl/vnl_matrix.h>
#include <vnl/vnl_vector.h>
#include <cstdlib>

char * generateBogusFilename();

int * randperm(int n_el);

void cross_3d(double *res, vnl_vector<double> a, vnl_vector<double> b);

int load_EDGES(double **pr, int **ir, int **jc, std::string datPath);

double *load_lambda(std::string datPath);

double *load_lambda2(std::string datPath);

double *load_mean_normals(std::string datPath);

double *load_mu(std::string datPath);

double *load_PHI(std::string datPath);

double *load_PHI2(std::string datPath);

double *load_face(std::string datPath);
