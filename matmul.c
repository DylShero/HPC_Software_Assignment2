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

int main()
{
  int n=2000; 
  Matrix a=alloc_matrix(n);
  Matrix b=alloc_matrix(n);
  Matrix c=alloc_matrix(n);

// Fill matrices b and c with random numbers 
  srand48(123456789UL);
  for (int i=0;i<n;i++)
    for (int j=0;j<n;j++)
    {
      b.entry[i][j] = drand48() - 0.5; 
      c.entry[i][j] = drand48() - 0.5; 
    }
  
  for (int i=0;i<n;i++)
    for (int j=0;j<n;j++)
    {
      a.entry[i][j] = 0;
      for (int k=0;k<n;k++)
        a.entry[i][j] += b.entry[i][k] * c.entry[k][j]; 
    }

  printf("a(10,10) = %lf\n",a.entry[10][10]);

  free_matrix(a);
  free_matrix(b);
  free_matrix(c);
  return 0;
}
