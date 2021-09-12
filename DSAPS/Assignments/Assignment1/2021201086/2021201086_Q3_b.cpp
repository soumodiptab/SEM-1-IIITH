#include<iostream>
using namespace std;
// Sparse Matrix Represented using row and col arrays
template <typename T>
class SparseMatrix{
    private:
    int capacity=50;
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
        while(temp.capacity<size)
            temp.enlarge();
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
    SparseMatrix<T> add(SparseMatrix<T> b)
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
        int i=0,j=0;// j finds valid row,col,value
        while(j<size)
        {
            while(j<size&&((row[j]==-1&&col[j]==-1)||value[j]==0))
            {
                j++;
            }
            if(j==size)
                break;
            row[i]=row[j];
            col[i]=col[j];
            value[i]=value[j];
            i++;
            j++;
        }
        size=i;
    }
    SparseMatrix<T> multiply(SparseMatrix<T> b)
    {
        SparseMatrix<T> bt=b.transpose();
        SparseMatrix<T> temp(rows,bt.cols);
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
};
template <typename T>
void initializer(SparseMatrix<T> &a,T** matrix,int row,int col)
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            if(matrix[i][j])
                a.insert(i,j,matrix[i][j]);
}
template <typename T>
T** create_matrix(int row,int col)
{
    T temp;
    T** arr=new T*[row];
    for(int i=0;i<row;i++)
    {
        arr[i]=new T[col];
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cin>>temp;
            arr[i][j]=temp;
        }
    }
    return arr;
}
/*
void test()
{
    int mat[][4]={{1,3,0,0},{0,0,2,0},{0,2,0,0},{0,0,0,0}};
    int mat2[][4]={{3,0,0,0},{-1,0,0,9},{0,0,0,0},{0,1,0,0}};
    SparseMatrix<int>a(4,4);
    //initializer(a,mat,4,4);
    SparseMatrix<int>b(4,4);
    //initializer(b,mat2,4,4);
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
    cout<<"A*B :"<<endl;
    SparseMatrix<int>mul=a.multiply(b);
    mul.print();
}
*/


void driver()
{
    int row,col,choice;
    cin>>choice;
    switch(choice)
    {
        case 1://add
        {  
            cin>>row>>col;
            SparseMatrix<int>a(row,col);
            int **arr1=create_matrix<int>(row,col);
            initializer(a,arr1,row,col);
            cin>>row>>col;
            SparseMatrix<int>b(row,col);
            int **arr2=create_matrix<int>(row,col);
            initializer(b,arr2,row,col);
            SparseMatrix<int>c=a.add(b);
            c.print();
        }
            break;
        case 2://multiply
        {
            cin>>row>>col;
            SparseMatrix<int>a(row,col);
            int **arr1=create_matrix<int>(row,col);
            initializer(a,arr1,row,col);
            cin>>row>>col;
            SparseMatrix<int>b(row,col);
            int **arr2=create_matrix<int>(row,col);
            initializer(b,arr2,row,col);
            SparseMatrix<int>c=a.multiply(b);
            c.print();
        }
            break;
        case 3 ://transpose
        {
            cin>>row>>col;
            SparseMatrix<int>a(row,col);
            int **arr=create_matrix<int>(row,col);
            initializer(a,arr,row,col);
            SparseMatrix<int>at=a.transpose();
            at.print();
        }
    }
}
int main()
{
    //test();
    driver();
    return 0;
}