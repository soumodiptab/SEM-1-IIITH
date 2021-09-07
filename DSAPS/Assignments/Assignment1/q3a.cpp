#include<iostream>
using namespace std;
// Sparse Matrix Represented using row and col arrays
template <typename T>
class SparseMatrix{
    private:
    const int capacity=100;
    int size; 
    int rows,cols;
    int *row;
    int *col;
    T *value;
    public:
    //inserts a new triple into the matrix(auto operation)
    int insert(int i,int j,T val)
    {
        if(size==capacity)
            return 0;//incase it hits the capacity
        row[size]=i;
        col[size]=j;
        value[size]=val;
        size++;
        return 1;
    }
    //Inserts the triple at a particular index based on pos(manual operation)
    void insertAt(int pos,int i,int j, T val)
    {
        row[pos]=i;
        col[pos]=j;
        value[pos]=val;
    }
    //Constructor for creating a Sparse Matrix of generic type
    SparseMatrix(int rows,int cols){
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
        SparseMatrix<T>temp(cols,rows);
        temp.size=size;
        int *total=new int[cols];
        int *index=new int[cols+1];
        for(int i=0;i<cols;i++)
            total[i]=0;
        for(int i=0;i<size;i++)
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
    SparseMatrix<T> add(SparseMatrix b){
        if(rows != b.rows || cols != b.cols)
            return NULL;
        SparseMatrix<T> temp(rows,cols);
        int apos=0,bpos=0;
        while(apos<size && bpos<b.size)
        {
            if(row[apos]==b.row[bpos] && col[apos]==b.col[bpos])//same row,col value
            {
                T val=value[apos]+b.value[bpos];
                if(val != 0)//if absolute value zero no need to reinsert
                    temp.insert(row[apos],col[apos],val);
                    apos++;
                    bpos++;
            }
            else if(row[apos]<b.row[bpos]||(row[apos]==b.row[bpos]&&col[apos]<b.col[bpos]))//Sparse A has lower row,col value
            {
                temp.insert(row[apos],col[apos],value[apos]);
                apos++;
            }
            else//Sparse B has lower row,col value
            {
                temp.insert(b.row[bpos],b.col[bpos],b.value[bpos]);
                bpos++;
            }
        }
        //Inserting the remaining elements
        while(apos<size)
            temp.insert(row[apos],col[apos],value[apos]);
        while(bpos<b.size)
            temp.insert(b.row[bpos],b.col[bpos],b.value[bpos]);
        return temp;
    }
    SparseMatrix<T> multiply(SparseMatrix b){

    }
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
    //Prints entire matrix along with zeros--not implemented
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
    SparseMatrix<int>a(3,4);
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