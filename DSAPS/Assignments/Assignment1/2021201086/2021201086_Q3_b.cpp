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
    void delete_node(Node<T>* target)
    {//delete from : <front> <middle> <rear>
        if(target->left == NULL)//i.e. front node
        {
            front=target->right;
        }
        if(target->right == NULL)//i.e. rear node
        {
            rear=target->left;
        }
        //for middle nodes
        if(target->left != NULL)
            target->left->right=target->right;
        if(target->right != NULL)
            target->right->left=target->left;
        delete target;
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
    void swap(Node<T>* a,Node<T>* b)
    {
        T temp_val=a->value;
        int temp_row=a->row;
        int temp_col=a->col;
        a->value=b->value;
        a->row=b->row;
        a->col=b->col;
        b->value=temp_val;
        b->row=temp_row;
        b->col=temp_col;
    }
    void sort()
    {
        Node<T>*iter1=front;
        while(iter1!=NULL)
        {
            Node<T>*iter2=iter1->right;
            while(iter2!=NULL)
            {
                if(iter2->row<iter1->row ||(iter2->row==iter1->row && iter2->col<iter1->col))
                {
                    swap(iter1,iter2);
                }
                iter2=iter2->right;
            }
            iter1=iter1->right;
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
        temp.sort();
        return temp;
    }
    void combine()
    {

        Node<T>*iter1=front;
        while(iter1!=NULL)
        {
            Node<T>*iter2=iter1->right;
            while(iter2!=NULL && (iter1->row==iter2->row && iter1->col==iter2->col))
            {
                Node<T>*del_node=iter2;
                iter1->value=iter1->value+iter2->value;
                iter2=iter2->right;
                delete_node(del_node);
                size--;
            }
            iter1=iter1->right;
        }
        iter1=front;
        while(iter1!=NULL)
        {
            Node<T>*del_node=iter1;
            iter1=iter1->right;
            if(del_node->value==0)
            {
                delete_node(del_node);
                size--;
            }
        }
    }
    SparseMatrix<T>multiply(SparseMatrix b)
    {
        SparseMatrix<T>bt=b.transpose();
        SparseMatrix<T>temp(rows,b.cols);
        Node<T>*itera=front;
        while(itera!=NULL)
        {
            Node<T>*iterb=bt.front;
            while(iterb!=NULL)
            {
                if(itera->col==iterb->col)
                {
                    T val=itera->value*iterb->value;
                    temp.insert(itera->row,iterb->row,val);
                }
                iterb=iterb->right;
            }
            itera=itera->right;
        }
        temp.sort();
        temp.combine();
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
        case 1://Transpose
        {   
            cin>>row>>col;
            SparseMatrix<int>a(row,col);
            int **arr=create_matrix<int>(row,col);
            initializer(a,arr,row,col);
            SparseMatrix<int>at=a.transpose();
            at.print();
        }
            break;
        case 2://Add
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
        case 3 ://Multiply
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
    }
}
int main()
{
    //test();
    driver();
    return 0;
}