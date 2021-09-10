#include<iostream>
#define MAX 1000
using namespace std;
// Sparse Matrix Represented using row and col arrays
template <typename T>
class SparseMatrix{
    private:
    int capacity=100;
    int size; 
    int rows,cols;
    int *row;
    int *col;
    T *value;
    void enlarge()
    {
        capacity*=2;
        int *new_row=new int[capacity];
        int *new_col=new int[capacity];
        T *new_value=new T[capacity];
        for (int i=0;i<size;i++)
        {
            new_row[i]=row[i];
            new_col[i]=col[i];
            new_value[i]=value[i];
        }
        delete [] row;
        delete [] col;
        delete [] value;
        row=new_row;
        col=new_col;
        value=new_value;
    }
    public:
    //inserts a new triple into the matrix(auto operation)
    int insert(int i,int j,T val)
    {
        if(size==capacity)
            enlarge();
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
    SparseMatrix(int rows,int cols)
    {
        this->rows=rows;
        this->cols=cols;
        row=new int[capacity];
        col=new int[capacity];
        value=new T[capacity];
        size=0;
    }
    //returns the transposed Sparse Matrix
    SparseMatrix<T> transpose()
    {
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
    SparseMatrix<T> add(SparseMatrix b)
    {
        SparseMatrix<T> temp(rows,cols);
        int iter_a=0,iter_b=0;
        while(iter_a<size && iter_b<b.size)
        {
            if(row[iter_a]==b.row[iter_b] && col[iter_a]==b.col[iter_b])//same row,col value
            {
                T val=value[iter_a]+b.value[iter_b];
                if(val != 0)//if absolute value zero no need to reinsert
                    temp.insert(row[iter_a],col[iter_a],val);
                    iter_a++;
                    iter_b++;
            }
            else if(row[iter_a]<b.row[iter_b]||(row[iter_a]==b.row[iter_b]&&col[iter_a]<b.col[iter_b]))//Sparse A has lower row,col value
            {
                temp.insert(row[iter_a],col[iter_a],value[iter_a]);
                iter_a++;
            }
            else//Sparse B has lower row,col value
            {
                temp.insert(b.row[iter_b],b.col[iter_b],b.value[iter_b]);
                iter_b++;
            }
        }
        //Inserting the remaining elements
        while(iter_a<size)
        {
            temp.insert(row[iter_a],col[iter_a],value[iter_a]);
            iter_a++;
        }
        while(iter_b<b.size)
        {
            temp.insert(b.row[iter_b],b.col[iter_b],b.value[iter_b]);
            iter_b++;
        }
        return temp;
    }
    void swap(int i,int j)
    {
        T temp_val=value[i];
        int temp_row=row[i];
        int temp_col=col[i];
        value[i]=value[j];
        row[i]=row[j];
        col[i]=col[j];
        value[j]=temp_val;
        row[j]=temp_row;
        col[j]=temp_col;
    }
    void sort()
    {
        for(int i=0;i<size-1;i++)
        {
            for(int j=i+1;j<size;j++)
            {
                if(row[j]<row[i]||(row[i]==row[j]&&col[j]<col[i]))
                {
                    swap(i,j);
                }
            }
        }
    }
    void combine()
    {
        //mark for deletion
        int temp_size=size;
        for(int i=0;i<size-1;i++)
        {
            for(int j=i+1;j<size;j++)
            {
                if(row[i]==row[j]&&col[i]==col[j])
                {
                    row[j]=-1;
                    col[j]=-1;
                    value[i]=value[i]+value[j];
                }
            }
        }
        int i=0;
        while(i<size)
        {
            int j=i;
            while(j<size&&((row[j]==-1&&col[j]==-1)||value[j]==0))
            {
                temp_size--;
                j++;
            }
            if(j==size)
                break;
            row[i]=row[j];
            col[i]=col[j];
            value[i]=value[j];
            i=j+1;
        }
        size=temp_size;
    }
    SparseMatrix<T> multiply(SparseMatrix b)
    {
        SparseMatrix bt=b.transpose();
        SparseMatrix temp(rows,bt.cols);
        for(int itera=0;itera<size;itera++)
        {
            for(int iterb=0;iterb<bt.size;iterb++)
            {
                if(col[itera]==bt.col[iterb])
                {
                    T val=value[itera]*bt.value[iterb];
                    temp.insert(row[itera],bt.row[iterb],val);
                }
            }
        }
        temp.print();
        temp.sort();
        temp.combine();
        return temp;
    }
    void print()
    {
        cout<<"--------------------------"<<endl;
        cout<<"dim: "<<rows<<"x"<<cols<<endl;
        cout<<"--------------------------"<<endl;
        cout << "r\tc\tv\n";
        cout<<"--------------------------"<<endl;
        for (int i = 0; i < size; i++)
        {
            cout<<row[i]<<"\t"<< col[i]<<"\t"<<value[i]<<endl;
        }
        cout<<"--------------------------"<<endl;
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
    int mat[][4]={{0,10,4,2},{0,0,0,0},{0,0,3,0},{4,2,0,0}};
    int mat2[][4]={{0,3,1,0},{0,0,0,2},{0,3,0,0},{0,0,5,0}};
    SparseMatrix<int>a(4,4);
    initializer(a,mat,4,4);
    SparseMatrix<int>b(4,4);
    initializer(b,mat2,4,4);
    /*
    cout<<"A :"<<endl;
    a.print();
    cout<<"A Transpose :"<<endl;
    SparseMatrix<int>at=a.transpose();
    at.print();
    cout<<"B :"<<endl;
    b.print();
    cout<<"A+B :"<<endl;
    SparseMatrix<int>sum=a.add(b);
    sum.print();
    */
    cout<<"A*B :"<<endl;
    SparseMatrix<int>mul=a.multiply(b);
    mul.print();
}
int main()
{
    driver();
    return 0;
}