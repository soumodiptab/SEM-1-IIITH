#include<iostream>
using namespace std;
template <typename T>
class Node
{
    int row;
    int col;
    T value;
    Node *left;
    Node *right;
    public:
    Node(int row,int col,T value)
    {
        this->row=row;
        this->col=col;
        this->value=value;
        left=NULL;
        right=NULL;
    }
    swap()
    {
        int temp=row;
        row=col;
        col=temp;
    }
};
template <typename T>
class SparseMatrix
{
    int size;
    int rows,cols;
    Node<T>* front;
    Node<T>* rear;
    public:
    SparseMatrix(int rows,int cols)
    {
        this->rows=rows;
        this->cols=cols;
        front=NULL;
        rear=NULL:
    }
    void insert(Node<T>* new_node)
    {//Insert ar rear
        //No node present
        if(front==NULL)
        {
            front=new_node;
            rear=front;
        }
        else
        {
            rear->right=new_node;
            new_node->left=rear;
            rear=new_node;
        }
    }
    void insert(int i, int j ,T value)
    {
        Node<T>* new_node=new Node()
    }
    SparseMatrix<T> add(SparseMatrix b)
    {
        SparseMatrix<T> temp(rows,cols);
    }
    void print()
    {
        Node<T>*temp=front;
        cout<<"--------------------------"<<endl;
        cout<<"dim: "<<rows<<"x"<<cols<<endl;
        cout<<"--------------------------"<<endl;
        cout << "row\tcol\tvalue\n";
        cout<<"--------------------------"<<endl;
        while(temp!=NULL)
        {
            cout<<temp->row<<"\t"<<temp->col<<"\t"<<temp->value<<endl;
            temp=temp->right;
        }
        cout<<"--------------------------"<<endl;
    }
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
    //SparseMatrix<int>at=a.transpose();
    //at.print();
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