typedef struct 
{
  double *data_; 	// raw data - access via "entry[a][b]"

  int n;
  double **entry; 
}
Matrix; 

Matrix alloc_matrix(int);
void free_matrix(Matrix);
//   ============================================================
#include <stdlib.h>

Matrix alloc_matrix(int n)
{
  Matrix m; 
  m.n=n;
  m.data_=malloc(sizeof(double) * n * n); 

  m.entry=malloc(sizeof(double*) * n); 
  for (int i=0;i<n;i++)
    m.entry[i]=m.data_+n*i;

  return m;
}
//   ------------------------------------------------------------
void free_matrix(Matrix m)
{
  free(m.entry);
  free(m.data_);
}

//   ============================================================
#include <stdio.h>
#include <omp.h>

int main()
{
  int n=2000; 
  Matrix a=alloc_matrix(n);
  Matrix b=alloc_matrix(n);
  Matrix c=alloc_matrix(n);

// Fill matrices b and c with random numbers 
  srand(123456789UL);
  for (int i=0;i<n;i++)
    for (int j=0;j<n;j++)
    {
      b.entry[i][j] = ((double)rand() / RAND_MAX) - 0.5; 
      c.entry[i][j] = ((double)rand() / RAND_MAX) - 0.5;
    }

  printf("Running with %d threads...\n", omp_get_max_threads());

  double start_time = omp_get_wtime();
  #pragma omp parallel default(none) shared(a, b, c, n)
  {
    #pragma omp for collapse(2) schedule(static)
    for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) {
        
        double sum = 0.0; 
        for (int k=0;k<n;k++) {
          sum += b.entry[i][k] * c.entry[k][j]; 
        }
        a.entry[i][j] = sum; 
        
      }
    }
  }
  double end_time = omp_get_wtime();

  //Local sum because compiler was optimising away most of the calculation
  double check_sum = 0.0;
  for(int i=0; i<n; i++) {
      check_sum += a.entry[i][i];
  }

  printf("a(10,10) = %lf\n", a.entry[10][10]);
  printf("Verification sum: %lf\n", check_sum);
  
  //Print time taken
  printf("Time taken: %f seconds\n", end_time - start_time);

  free_matrix(a);
  free_matrix(b);
  free_matrix(c);
  return 0;
}
