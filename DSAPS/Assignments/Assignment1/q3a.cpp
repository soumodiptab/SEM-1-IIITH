#include<iostream>
#include<string>
using namespace std;
// Sparse Matrix Represented using row and col arrays
template <typename T>
class SparseMatrix{
    private:
    int size,capacity; 
    int rows,cols;
    int *row;
    int *col;
    T *value;
    public:
    int insert(int i,int j,T val)
    {
        if(size==capacity)
            return 0;
        row[size]=i;
        col[size]=j;
        value[size]=val;
        size++;
        return 1;
    }
    void insertAt(int pos,int i,int j, T val)
    {
        row[pos]=i;
        col[pos]=j;
        value[pos]=val;
    }
    SparseMatrix(int capacity,int rows,int cols){
        this->capacity=capacity;
        this->rows=rows;
        this->cols=cols;
        row=new int[capacity];
        col=new int[capacity];
        value=new T[capacity];
        size=0;
    }
    //returns the transposed Sparse Matrix
    SparseMatrix<T> transpose(){
        //applying the concept of fast-transpose using total and index arrays
        SparseMatrix<T>temp(capacity,cols,rows);
        temp.size=size;
        int *total=new int[cols];
        int *index=new int[cols+1];
        for(int i=0;i<cols;i++)
            total[i]=0;
        for(int i=0;i<cols;i++)
            total[col[i]]++;
        index[0]=0;
        for(int i=1;i<=cols;i++)
            index[i]=index[i-1]+total[i-1];
        for(int i=0;i<size;i++)
        {
            int pos=index[col[i]]++;
            temp.insertAt(pos,col[i],row[i],value[i]);
        }
        return temp;
    }
    SparseMatrix<T> multiply(SparseMatrix b);
    SparseMatrix<T> add(SparseMatrix b);
    //Change this later a little bit
    void print()
    {
        cout << "\nDimension: " << rows << "x" << cols;
        cout << "\nSparse Matrix: \nRow\tColumn\tValue\n";
        for (int i = 0; i < size; i++)
        {
            cout << row[i] << "\t " << col[i] << "\t " << value[i] << endl;
        }
    }
    /*void print_full(){
        int i=0,j=0;
        for(int k=0;i<size;)
        {
            if(i==row[k]&&j==col[k]&&val[k]!=0)
            {

            }
            else
            {
                cout<<"0 ";
            }
            if(j==size)
        }
    }*/
};
template <typename T>
void initializer(SparseMatrix<T> &a,T matrix[][4],int row,int col)
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            if(matrix[i][j])
                a.insert(i,j,matrix[i][j]);
}
void driver()
{
    int mat[][4]={{0,5,0,6},{2,0,4,0},{0,0,7,0}};
    SparseMatrix<int>a(10,3,4);
    initializer(a,mat,3,4);
    a.print();
    SparseMatrix<int>b=a.transpose();
    b.print();
}
int main()
{
    driver();
    return 0;
}