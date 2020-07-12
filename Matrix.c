#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Matrix{
    int** matrix; // 2D Dynamic Array
    int row;
    int col;
}; //struct Matrix

void buffer_clear(int); // Clear input buffer

int** Array_2D(const int *,const int *); // Function assigning memory for a 2-dimensional array

void Matrix_fill(struct Matrix *); // Fill matrix

void setSizeMat(int *, int *); // This function is used to determine the size of the matrix.

struct Matrix *Matrix_create(int row, int col) // Constructor
{
    struct Matrix *mat = malloc(sizeof(struct Matrix));
    
    setSizeMat(&row, &col);
    assert(mat != NULL);
    assert(col > 0 && row > 0); 
    
    mat->col = col;
    mat->row = row;
    mat->matrix = Array_2D(&row, &col);
    Matrix_fill(mat); 
   
    return mat;
} // struct Matrix *Matrix_create(int row, int col)

void Matrix_destroy(struct Matrix *mat) // Destroy matrix
{
    assert(mat != NULL);
   
    for (int i = 0; i < mat->row; i++){
       free(mat->matrix[i]);
   }
   
   free(mat->matrix);
   free(mat);
} // void Matrix_destroy(struct Matrix *mat)

void Matrix_print(struct Matrix *mat) // Print a matrix
{
    printf("\n");
    
    for(int i = 0; i < mat->row; ++i)
    {
         for(int j = 0; j < mat->col; ++j)
         {
             printf("%3i",mat->matrix[i][j]);
         }
         printf("\n");
    }
} // void Matrix_print(struct Matrix *mat)

void gauss(struct Matrix *mat);
void ungauss(struct Matrix *mat);

void Matrix_ops(struct Matrix *mat, struct Matrix *mat_2)
{
    assert(mat != NULL && mat_2 != NULL);
    buffer_clear(0);
    char ops;
    printf("Adding(a)/Subtract(s)/Multiply(m)/Elimination of Gauss(g)\nWhich operation do you want to perform? ");
    scanf("%c",&ops);
    switch(ops)
    {
        case 'a': // Operation of adding matrices
        {  
            if(mat -> col == mat_2 -> col && mat -> row == mat_2 -> row)
            {
               for(int i = 0; i < mat->row; ++i)
               {
                     for(int j = 0; j < mat->col; ++j)
                     {
                        mat->matrix[i][j] += mat_2->matrix[i][j];
                     }
               }
               printf("\nMatrix after adding:");
               Matrix_print(mat);
            }
            else{
                printf("\nError: Cannot add two matrices - they have different dimensions.");
            }
            break;
        } // case 'a':

        case 's': // Operation of substracting matrices
        {
            if(mat -> col == mat_2 -> col && mat -> row == mat_2 -> row)
            {
                for(int i = 0; i < mat->row; ++i)
                {
                     for(int j = 0; j < mat->col; ++j)
                     {
                        mat->matrix[i][j] -= mat_2->matrix[i][j];
                     }
                }
                printf("\nMatrix after subtraction: \n");
                Matrix_print(mat);
            }
            else{
               printf("\nError: Cannot subtract two matrices - they have different dimensions.");
            }
            break;
        } // case 's':

        case 'm': // Operation of multiplying matrices
        {
            int sum = 0, i = 0, j = 0,z = 0;
            int** ptrArr;
            ptrArr = Array_2D(&mat -> row,&mat_2 -> col);
            printf("Matrix after multiplying:");
            if(mat -> col == mat_2 -> row)
            {
                for(i = 0; i < mat -> row; ++i)
                {
                    for(j = 0; j < mat_2 -> col; ++j)
                    {
                        for(int k = 0; k < mat_2 -> row; ++k)
                        {
                            sum += mat -> matrix[i][k] * mat_2 -> matrix[k][j];
                        }
                        ptrArr[i][j] = sum;
                        printf("%3i",ptrArr[i][j]);
                        sum = 0;
                    }
                    printf("\n");
                }
                for(z = 0; z < mat -> row; ++z)
                {
                     free(ptrArr[z]);
                }
                 
                free(ptrArr);
            }
            else{
                printf("\nError: Cannot be multiplied - the length of the columns does not correspond to the length of the rows.");
            }
            break;
        } // case 'm':

        case 'g': // Elimination of Gauss
        {
            char choice; 
            while(!(choice == 'y' || choice == 'Y'))
            {        

                buffer_clear(0);
                printf("Add(a)/Remove(r) the rows with the gauss method? ");
                scanf("%c",&choice);
                if(feof(stdin) != 0){ clearerr(stdin); break;}
                choice == 'a' || choice == 'r' ? (choice == 'a' ? ungauss(mat) : gauss(mat)) : puts("Error! Wrong operation!");
                printf("Do you want to quit the program?(y\\n)");
                buffer_clear(choice);
                scanf("%c",&choice);
            }
            break;
        } // case 'g':

        default:
            break;
    } // switch(&ops)
} // void Matrix_ops(char a, struct Matrix *mat, struct Matrix *mat_2)

void gauss(struct Matrix *mat) // Subtraction of matrix rows 
{
        assert(mat != NULL);
        int i = 0, k = 0;    
        
        printf("Which row do you want to subtract? ");
        scanf("%i",&i);
        if(feof(stdin) != 0){ clearerr(stdin); return; }
       
        printf("Which row is the one to serve this? ");
        scanf("%i",&k);
        if(feof(stdin) != 0){ clearerr(stdin); return; }

        for(int j = 0; j < mat->col; ++j)
        {
           mat->matrix[i-1][j] -= mat->matrix[k-1][j];
        }
        printf("Matrix after subtraction:");
        Matrix_print(mat);
} //  void gauss(struct Matrix *mat)  

void ungauss(struct Matrix *mat) // Adding rows in the matrix
{
        assert(mat != NULL);
        int i = 0, k = 0;    
        
        printf("Which row do you want to add? ");
        scanf("%i",&i);
        if(feof(stdin) != 0){ clearerr(stdin); return; }
        
        printf("Which row is the one to serve this? ");
        scanf("%i",&k);
        if(feof(stdin) != 0){ clearerr(stdin); return; }
        
        for(int j = 0; j < mat->col; ++j)
        {
           mat->matrix[i-1][j] += mat->matrix[k-1][j];
        }
        printf("Matrix after adding:");
        Matrix_print(mat);
} // void ungauss(struct Matrix *mat)

int main()
{
    int rows = 0, cols = 0;

    struct Matrix *mat_1 = Matrix_create(rows,cols);
    struct Matrix *mat_2 = Matrix_create(rows,cols);

    Matrix_print(mat_1); // Print mat_1.
    Matrix_print(mat_2); // Print mat_2.
    Matrix_ops(mat_1,mat_2);

    Matrix_destroy(mat_1); // Destroy mat_1.
    Matrix_destroy(mat_2); // Destroy mat_2.

    getchar();
    return 0;
} // int main()

void setSizeMat(int *rows, int *cols)
{
    printf("Enter the number of rows: ");
    while(scanf("%i", &(*rows)) != 1)
    {
        if(feof(stdin) != 0){ clearerr(stdin); }
        buffer_clear(*rows);
        printf("Enter the number of rows: ");
    }

    printf("Enter the number of columns: ");
    while(scanf("%i", &(*cols)) != 1)
    {

        if(feof(stdin) != 0){ clearerr(stdin); }
        buffer_clear(*cols);
        printf("Enter the number of columns: ");

    } 
} // void setSizeMat(int *rows, int *cols)


int** Array_2D(const int *row,const int *col) 
{
    int** theArray; // Declaration of an pointer to pointer that will imitate a 2-dimensional array.
    theArray = (int**) malloc((*row)*sizeof(int*)); // Allocation memory for the array

    for (int i = 0; i < (*row); i++)
    {
        theArray[i] = (int*) malloc((*col)*sizeof(int)); // Allocation memory for the array in the array
    }
    return theArray; // Return a 2D array
} // int** Array_2D(const int *row,const int *col) 

void Matrix_fill(struct Matrix *mat)
{

        int buffer = 0; // Variable used as buffer for errors ;)
        printf("Enter the elements of the matrix[%i]x[%i]\n",mat->row,mat->col);

        for(int i = 0; i < mat->row; ++i)
        { 
           for(int j=0; j < mat->col; ++j)
            {
               printf("Enter a[%d][%d]: ", i+1, j+1);
                while(scanf("%i", &mat->matrix[i][j]) != 1)
                {

                    if(feof(stdin) != 0){ clearerr(stdin); }
                    buffer_clear(buffer);
                    printf("Enter a[%d][%d]: ", i+1, j+1);
                }
            }
        }
} // void Matrix_fill(struct Matrix *mat)
void buffer_clear(int c)
{
    while ((c = getchar()) != '\n' && c != EOF) {  }
} // buffer_clear(int c)
