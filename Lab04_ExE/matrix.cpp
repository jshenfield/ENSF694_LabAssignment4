//   matrix.cpp


#include "matrix.h"

Matrix::Matrix(int r, int c):rowsM(r), colsM(c)
{
    matrixM = new double* [rowsM];
    assert(matrixM != NULL);
    
    for(int i=0; i < rowsM; i++){
        matrixM[i] = new double[colsM];
        assert(matrixM[i] != NULL);
    }
    sum_rowsM = new double[rowsM];
    assert(sum_rowsM != NULL);
    
    sum_colsM = new double[colsM];
    assert(sum_colsM != NULL);
}


Matrix::~Matrix()
{
    destroy();
}

Matrix::Matrix(const Matrix& source)
{
    copy(source);
}

Matrix& Matrix::operator= (const Matrix& rhs)
{
    if(&rhs != this){
        destroy();
        copy(rhs);
    }
   
    return *this;
}

double Matrix::get_sum_col(int i) const
{
    assert(i >= 0 && i < colsM);
    return sum_colsM[i];
}

double Matrix::get_sum_row(int i) const
{
    assert(i >= 0 && i < rowsM);
    return sum_rowsM[i];
}


void Matrix::sum_of_rows()const
{
   
    for(int i = 0; i < rowsM; i++){
        sum_rowsM[i] = 0; // initialize sum at 0
        for(int j = 0; j < colsM; j++)
            sum_rowsM[i] += matrixM[i][j]; // sum each data point in the row
    }
    // COMMENT OUT THE FOLLOWING LINE AND COMPLETE THE DEFINITION OF THIS FUNCTION
    //cout << "\nSorry I don't know how to calculate sum of rowsM in a matrix. ";

}

void Matrix::sum_of_cols()const
{
    // same logic as above, but swap rows/cols
    for(int i = 0; i < colsM; i++){
        sum_colsM[i] = 0; // initialize sum at 0
        for(int j = 0; j < rowsM; j++)
            sum_colsM[i] += matrixM[j][i]; // sum each data point in the row
    }
    // COMMENT OUT THE FOLLOWING LINE AND COMPLETE THE DEFINITION OF THIS FUNCTION
    //cout << "\nSorry I don't know how to calculate sum of columns in a matrix. ";
    
}

void Matrix::copy(const Matrix& source)
{
    // THIS FUNCITON IS DEFECTIVE AND DOSEN'T PROPERLY MAKE THE COPY OF SROUCE
    if(source.matrixM == NULL){
        matrixM = NULL;
        sum_rowsM = NULL;
        sum_colsM = NULL;
        rowsM = 0;
        colsM = 0;
        return;
    }
    
    rowsM = source.rowsM;
    colsM = source.colsM;
    
    sum_rowsM = new double[rowsM];
    assert(sum_rowsM != NULL);
    
    for (int i = 0; i < rowsM; ++i) { // initialize proper row sums
        sum_rowsM[i] = source.sum_rowsM[i];
    }

    sum_colsM = new double[colsM];
    assert(sum_colsM != NULL);

    for (int j = 0; j < colsM; ++j) { // initialize proper column sums
        sum_colsM[j] = source.sum_colsM[j];
    }
    
    matrixM = new double*[rowsM];
    assert(matrixM !=NULL);
    for(int i =0; i < rowsM; i++){
        matrixM[i] = new double[colsM];
        assert(matrixM[i] != NULL);

        for(int j = 0; j < colsM; j++){
            matrixM[i][j] = source.matrixM[i][j];
        }
    }
    // STUDENTS MUST COMMENT OUT THE FOLLOWING LINE AND FIX THE FUNCTION'S PROBLEM
    //cout << "\nSorry copy fucntion is defective. ";
}

    

void Matrix::destroy()
{
    // destroy each row
    for(int i = 0; i < rowsM; i++){
        delete [] matrixM[i];
    }

    // delete leftover array
    delete [] matrixM;

    // reset member variables
    matrixM = nullptr;
    rowsM = 0; 
    colsM = 0;

    // COMMENT OUT THE FOLLOWING LINE AND COMPLETE THE DEFINITION OF THIS FUNCTION
    //cout << "\nProgram ended without destroying matrices.\n";
}
