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
            temp.insert(row[iter_a],col[iter_a],value[iter_a]);
        while(iter_b<b.size)
            temp.insert(b.row[iter_b],b.col[iter_b],b.value[iter_b]);
        return temp;
    }
    SparseMatrix<T> multiply(SparseMatrix b)
    {
        SparseMatrix temp(row,b.col);
        SparseMatrix bt=b.transpose();
        int iter_a=0;
        while(iter_a<size)//row pos in original mat
        {
            int iter_b=0;
            while(iter_b<bt.size)//col pos in original mat
            {
                int i=iter_a,j=iter_b;
                T sum=0;
                while((i<size&&j<bt.size)&&(row[i]==row[iter_a]&&bt.row[j]==bt.row[iter_b]))
                {
                    if(col[i]==bt.col[j])
                    {
                        sum+=value[i]*bt.value[j];
                    }
                }
                if(sum!=0)
                {
                    temp.insert(iter_a,iter_b,sum);
                }
                while(iter_b<b.size)
                {

                }
            }
        }
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
    int mat[][4]={{0,5,0,6},{2,0,4,0},{0,0,7,0}};
    int mat2[][4]={{2,3,0,1},{0,0,0,5},{0,1,-7,0}};
    SparseMatrix<int>a(3,4);
    cout<<"A :"<<endl;
    initializer(a,mat,3,4);
    a.print();
    cout<<"A Transpose :"<<endl;
    SparseMatrix<int>at=a.transpose();
    at.print();
    cout<<"B :"<<endl;
    SparseMatrix<int>b(3,4);
    initializer(b,mat2,3,4);
    b.print();
    cout<<"A+B :"<<endl;
    SparseMatrix<int>sum=a.add(b);
    sum.print();

}
int main()
{
    driver();
    return 0;
}