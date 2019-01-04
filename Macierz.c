#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Matrix{
    int** matrix; // Tablica dynamiczna 2-wymiarowa.
    int row;
    int col;
}; //struct Matrix

int** Array_2D(const int *,const int *); // Funkcja przydzielająca pamięć dla tablicy 2-wymiarowej

void Matrix_fill(struct Matrix *); // Wypełnienie macierzy

void setSizeMat(int *, int *); // Funkcja służąca do wyznaczenia rozmiaru macierzy.

struct Matrix *Matrix_create(int row, int col) // konstruktor
{
    struct Matrix *mat = malloc(sizeof(struct Matrix));
    
    setSizeMat(&row, &col);
    assert(mat != NULL); // Funkcja przerwie program gdy wskaźnik będzie NULLem czyli pusty.
    assert(col > 0 && row > 0); // przerwie program gdy liczba kolumn i wierszy nie będzie dodatnia.
    
    mat->col = col;
    mat->row = row;
    mat->matrix = Array_2D(&row, &col);
    Matrix_fill(mat); 
   
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

void Matrix_add(struct Matrix *mat, struct Matrix *mat_2) // Dodawanie macierzy 
{
           assert(mat != NULL && mat_2 != NULL);
    
           if(mat -> col == mat_2 -> col && mat -> row == mat_2 -> row)
           {
               for(int i = 0; i < mat->row; ++i)
               {
                     for(int j = 0; j < mat->col; ++j)
                     {
                        mat->matrix[i][j] += mat_2->matrix[i][j];
                     }
               }
                printf("\nMacierz po dodaniu: \n");
                Matrix_print(mat);
           }
           else{
               printf("Blad: Nie mozna dodac dwoch macierzy: sa innego rozmiaru.");
           }
} // void Matrix_add(struct Matrix *mat, struct Matrix *mat_2)


int main()
{
    int rows = 0, cols = 0;

    struct Matrix *mat_1 = Matrix_create(rows,cols);
    Matrix_print(mat_1); // Wyświetlenie zawartości mat_1.
    
    struct Matrix *mat_2 = Matrix_create(rows,cols);
    Matrix_print(mat_2); // Wyświetlenie zawartości mat_2.

    Matrix_add(mat_1,mat_2); // Dodanie dwóch macierzy.
    
    Matrix_destroy(mat_1); // Posprzątanie po mat_1.
    Matrix_destroy(mat_2); // Posprzątanie po mat_2.

    getchar();
    return 0;
} // int main()

void setSizeMat(int *rows, int *cols)
{
    printf("Podaj liczbe wierszy: ");
    while(scanf("%i", &(*rows)) != 1)
    {
        if(feof(stdin) != 0){ clearerr(stdin); }
        while(((*rows) = getchar()) != '\n' && (*rows) != EOF){} // czyści bufor wejścia
        printf("Podaj liczbe wierszy: ");
    }

    printf("Podaj liczbe kolumn: ");
    while(scanf("%i", &(*cols)) != 1)
    {

        if(feof(stdin) != 0){ clearerr(stdin); }
        while(((*cols) = getchar()) != '\n' && (*cols) != EOF){} // czyści bufor wejścia
        printf("Podaj liczbe kolumn: ");

    } 
} // void setSizeMat(int *rows, int *cols)


int** Array_2D(const int *row,const int *col) 
{
    int** theArray; //Deklaracja tablicy wskaźników,która będzie imitować tablicę 2-wymiarową.
    theArray = (int**) malloc((*row)*sizeof(int*)); // Allokacja pamięci dla tablicy

    for (int i = 0; i < (*row); i++)
    {
        theArray[i] = (int*) malloc((*col)*sizeof(int)); // Alokacja dla tablicy w tablicy
    }
    return theArray; // Zwrócenie tablicy dwu-wymiarowej
} // int** Array_2D(const int *row,const int *col) 

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

                    if(feof(stdin) != 0){ clearerr(stdin); }
                   	while((buffer = getchar()) != '\n' && buffer != EOF){} // czyści bufor wejścia
                    printf("wprowadz a[%d][%d]: ", i+1, j+1);
                }
            }
        }
} // void Matrix_fill(struct Matrix *mat)
