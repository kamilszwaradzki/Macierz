#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Matrix{
    int** matrix; // Tablica dynamiczna 2-wymiarowa.
    int row;
    int col;
}; //struct Matrix

int** Array_2D(int,int); // Funkcja przydzielająca pamięć dla tablicy 2-wymiarowej

struct Matrix *Matrix_create(int row, int col) // konstruktor
{
    struct Matrix *mat = malloc(sizeof(struct Matrix));
    assert(mat != NULL); // Funkcja przerwie program gdy wskaźnik będzie NULLem czyli pusty.
    assert(col > 0 && row > 0); // przerwie program gdy liczba kolumn i wierszy nie będzie dodatnia.
    mat->col = col;
    mat->row = row;
    mat->matrix = Array_2D(row,col);

    return mat;
} // struct Matrix *Matrix_create(int row, int col)

void Matrix_destroy(struct Matrix *mat) // Usunięcie macierzy
{
    assert(mat != NULL); // Jak wyżej
   
    for (int i = 0; i < mat->row; i++){
       free(mat->matrix[i]);
   }
   
   free(mat->matrix);
   free(mat);
} // void Matrix_destroy(struct Matrix *mat)

void Matrix_fill(struct Matrix *mat, short *err_no) // Wypełnienie macierzy
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

                    if(feof(stdin) != 0){ (*err_no) = 0; break;}
                   	while((buffer = getchar()) != '\n' && buffer != EOF); // czyści bufor wejścia
                    printf("wprowadz a[%d][%d]: ", i+1, j+1);
                }
               if((*err_no) == 0) {return;}
            }
        }
} // void Matrix_fill(struct Matrix *mat)

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
} // void Matrix_print(struct Matrix *mat)

void setSizeMat(int *, int *, short *); // Funkcja służąca do wyznaczenia rozmiaru macierzy.

int main()
{
    int rows, cols;
    short err_no = 1;

    setSizeMat(&rows,&cols,&err_no);
    if(!err_no){ return 1;}

    struct Matrix *mat_1 = Matrix_create(rows,cols);
    Matrix_fill(mat_1, &err_no); // Wypełnienie nowo utworzonej mat_1.
    if(!err_no){ return 1;}
    Matrix_print(mat_1); // Wyświetlenie zawartości mat_1.
    Matrix_destroy(mat_1); // Posprzątanie po mat_1.

    getchar();
    return 0;
} // int main()

void setSizeMat(int *rows, int *cols,short *err_no)
{
    printf("Podaj liczbe wierszy: ");
    while(scanf("%i", &(*rows)) != 1)
    {
        if(feof(stdin) != 0){ (*err_no) = 0; break;}
        while(((*rows) = getchar()) != '\n' && (*rows) != EOF); // czyści bufor wejścia
        printf("Podaj liczbe wierszy: ");
    }
    if((*err_no) == 0){ return;}

    printf("Podaj liczbe kolumn: ");
    while(scanf("%i", &(*cols)) != 1)
    {

        if(feof(stdin) != 0){ (*err_no) = 0; break;}
        while(((*cols) = getchar()) != '\n' && (*cols) != EOF); // czyści bufor wejścia
        printf("Podaj liczbe kolumn: ");

    } 
} // void setSizeMat(int *rows,int *cols)

int** Array_2D(int row, int col) 
{
    int** theArray; //Deklaracja tablicy wskaźników,która będzie imitować tablicę 2-wymiarową.
    theArray = (int**) malloc(row*sizeof(int*)); // Allokacja pamięci dla tablicy

    for (int i = 0; i < row; i++)
    {
        theArray[i] = (int*) malloc(col*sizeof(int)); // Alokacja dla tablicy w tablicy
    }
    return theArray; // Zwrócenie tablicy dwu-wymiarowej
} // int** Array_2D(int row, int col) 
