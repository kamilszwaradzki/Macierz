#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Matrix{
    int** matrix; // Tablica dynamiczna 2-wymiarowa.
    int row;
    int col;
};

int** Array_2D(int,int); // Funkcja przydzielająca pamięć dla tablicy 2-wymiarowej

struct Matrix *Matrix_create(int row, int col) // Stworzenie Macierzy
{
    struct Matrix *mat = malloc(sizeof(struct Matrix));
    assert(mat != NULL); // Funkcja przerwie program gdy wskaźnik będzie NULLem czyli pusty.
    assert(col > 0 && row > 0); // Funkcja przerwie program gdy liczba kolumn i wierszy nie będzie dodatnia.
    mat->col = col;
    mat->row = row;
    mat->matrix = Array_2D(row,col);

    return mat;
}

void Matrix_destroy(struct Matrix *mat) // Usunięcie macierzy
{
    assert(mat != NULL); // Jak wyżej
   
    for (int i = 0; i < mat->row; i++){
       free(mat->matrix[i]);
   }
   
   free(mat->matrix);
   free(mat);
}
void Matrix_fill(struct Matrix *mat) // Wypełnienie macierzy
{

        int buffer = 0; // zmienna służąca za bufor dla błędów ;)
        printf("Wprowadz elementy macierzy[%i]x[%i]\n",mat->row,mat->col);

        for(int i = 0; i < mat->row; ++i)
        { 
           for(int j=0; j < mat->col; ++j)
            {
               printf("wprowadz a[%d][%d]: ", i+1, j+1);
                while(scanf("%i", &mat->matrix[i][j]) != 1)
                {
                   	while((buffer = getchar()) != '\n' && buffer != EOF); // czyści bufor wejścia
                    printf("wprowadz a[%d][%d]: ", i+1, j+1);
                }
            }
        }
}
void Matrix_print(struct Matrix *mat) //Wyświetla zawartość macierzy
{
           for(int i = 0; i < mat->row; ++i)
           {
                 for(int j = 0; j < mat->col; ++j)
                 {
                     printf("%3i",mat->matrix[i][j]);
                 }
                 printf("\n");
           }
}

int determ(int** a,int n) { //a[][] - macierz,n - stopień macierzy
  int det = 0, p, h, k, i, j;
  int** temp;
  temp = Array_2D(n,n);
  if(n==1) { // Wyznacznik macierzy 1x1
    return a[0][0];
  } else if(n==2) { 
    det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]); // Wyznacznik dla macierzy 2x2
    return det;
  } else { // Wyznacznik dla macierzy n > 2, n x n
    for(p=0;p<n;p++) {
      h = 0;
      k = 0;
      for(i=1;i<n;i++) {
        for( j=0;j<n;j++) {
          if(j==p) {
            continue;
          }
          temp[h][k] = a[i][j];
          k++;
          if(k==n-1) {
            h++;
            k = 0;
          }
        }
      }
      det=det+a[0][p]*pow(-1,p)*determ(temp,n-1);
    }
    return det;
  }
}
int main()
{
    int rows, cols;
    int det = 0; 
    printf("Podaj liczbe wierszy: ");
    while(scanf("%i", &rows) != 1)
    {
       while((rows = getchar()) != '\n' && rows != EOF); // czyści bufor wejścia
       printf("Podaj liczbe wierszy: ");
    }

    printf("Podaj liczbe kolumn: ");
    while(scanf("%i", &cols) != 1)
    {
       while((cols = getchar()) != '\n' && cols != EOF); // czyści bufor wejścia
       printf("Podaj liczbe kolumn: ");
    } 

    struct Matrix *mat_1 = Matrix_create(rows,cols);
    Matrix_fill(mat_1); // Wypełnienie nowo utworzonej mat_1.
    Matrix_print(mat_1); // Wyświetlenie zawartości mat_1.
    printf("Wyznacznik jest równy = %d\n",determ(mat_1->matrix,cols));
    Matrix_destroy(mat_1); // Posprzątanie po mat_1.

    getchar();
    return 0;
}

int** Array_2D(int row, int col) 
{
    int** theArray; //Deklaracja tablicy wskaźników,która będzie imitować tablicę 2-wymiarową.
    theArray = (int**) malloc(row*sizeof(int*)); // Allokacja pamięci dla tablicy

    for (int i = 0; i < row; i++)
    {
        theArray[i] = (int*) malloc(col*sizeof(int)); // Alokacja dla tablicy w tablicy
    }
    return theArray; // Zwrócenie tablicy dwu-wymiarowej
}
