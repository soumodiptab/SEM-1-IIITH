#include<iostream>
using namespace std;
template <typename T>
class Node
{
    public:
    int row;
    int col;
    T value;
    Node *left;
    Node *right;
    Node(int row,int col,T value)
    {
        this->row=row;
        this->col=col;
        this->value=value;
        left=NULL;
        right=NULL;
    }
    void swap()
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
        rear=NULL;
        size=0;
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
        Node<T>* new_node= new Node<T>(i,j,value);
        insert(new_node);
        size++;
    }
    SparseMatrix<T> add(SparseMatrix b)
    {
        SparseMatrix<T> temp(rows,cols);
        Node<T>* iter_a=front;
        Node<T>* iter_b=b.front;
        while(iter_a!=NULL && iter_b!=NULL)
        {
            if(iter_a->row==iter_b->row && iter_a->col==iter_b->col)
            {
                T val=iter_a->value+iter_b->value;
                if(val!=0)
                {
                    temp.insert(iter_a->row,iter_b->col,val);
                }
                iter_a=iter_a->right;
                iter_b=iter_b->right;
            }
            else if(iter_a->row<iter_b->row || (iter_a->row==iter_b->row && iter_a->col<iter_b->col))
            {
                temp.insert(iter_a->row,iter_a->col,iter_a->value);
                iter_a=iter_a->right;
            }
            else
            {
                temp.insert(iter_b->row,iter_b->col,iter_b->value);
                iter_b=iter_b->right;
            }
        }
        while(iter_a!=NULL)
        {
            temp.insert(iter_a->row,iter_a->col,iter_a->value);
            iter_a=iter_a->right;
        }
        while(iter_b!=NULL)
        {
            temp.insert(iter_b->row,iter_b->col,iter_b->value);
            iter_b=iter_b->right;
        }
        return temp;
    }
    void sort(SparseMatrix x)
    {
        Node<T>*iter1=x.front;
        Node<T>*q=x.front;
        while(iter!=NULL)
        {
            if()
            iter=iter->right;
        }
    }
    SparseMatrix<T>transpose()
    {
        SparseMatrix<T>temp(cols,rows);
        Node<T>*iter=front;
        while(iter!=NULL)
        {
            temp.insert(iter->col,iter->row,iter->value);
            iter=iter->right;
        }
        sort(temp);
        return temp;
    }
    void print()
    {
        Node<T>*temp=front;
        cout<<"--------------------------"<<endl;
        cout<<"dim: "<<rows<<"x"<<cols<<endl;
        cout<<"--------------------------"<<endl;
        cout << "r\tc\tv\n";
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
    /*cout<<"A Transpose :"<<endl;
    SparseMatrix<int>at=a.transpose();
    at.print();*/
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