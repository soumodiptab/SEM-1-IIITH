#include<iostream>
using namespace std;


class Employee
{
    public:
    string name;
    string emp_id;
};
template<class T>
class avl
{
    class Node
    {
        public :
        T data;
        int height;
        int count;
        Node *left,*right,*parent;
        Node(T key)
        {
            data=key;
            count=1;
            height=1;
            left=NULL;
            right=NULL;
            parent=NULL;
        }
    };
    Node *root;
    /*----------Utility apis which is used in other functions------------*/
    public:
    Node* find(T key)
    {

    }
    /*--------------------------------------------------------------------*/
    struct Trunk
    {
        Trunk *prev;
        string str;
 
        Trunk(Trunk *prev, string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };
    void showTrunks(Trunk *p)
    {
        if (p == nullptr)
        {
            return;
        }
        showTrunks(p->prev);
        cout << p->str;
    }
    void printTree(Node* root, Trunk *prev, bool isLeft)
    {
    if(root == NULL)
    {
        return;
    }
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    cout << root->data <<","<<root->count<< endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
    }
    void display()
    {
        Node *root=new Node(2);
        Node *l=new Node(1);
        Node *r=new Node(3);
        Node *r2=new Node(4);
        root->left=l;
        root->right=r;
        root->left->right=r2;
        printTree(root, NULL, false);
    }

    /*-------------------------------------------------------------------*/
    int get_height(Node *target)
    {
        if(target!=NULL)
            return target->height;
        return 0;
    }
    int max_height(Node *head)
    {
        Node* left_p=head->left;
        Node* right_p=head->right;
        int l=0,r=0;
        if(left_p)
            l=left_p->height;
        if(right_p)
            r=right_p->height;
        return (l>r)?l:r;
    }
    int balance_factor(Node *head)
    {
        int l=0,r=0;
        if(head->left)
            l=head->left->height;
        if(head->right)
            r=head->right->height;
        return (l-r);
    }
    Node* left_rotation(Node* head)
    {
        Node* pivot=head->right;
        head->right=pivot->left;
        pivot->left=head;
        pivot->height=1+max_height(pivot);
        head->height=1+max_height(head);
        return pivot;
    }
    Node* right_rotation(Node* head)
    {
        Node *pivot=head->left;
        head->left=pivot->right;
        pivot->right=head;
        pivot->height=1+max_height(pivot);
        head->height=1+max_height(head);
        return pivot;   
    }
    Node* insert(Node* head, T key)
    {
        //vacant position
        if(head==NULL)
        {
            Node *new_node=new Node(key);
            return new_node;
        }
        //comparator --<change later>
        if(key < head->data)
        {
            head->left=insert(head->left,key);
        }
        //go to right sub tree  comparator--<change later>
        else if(key > head->data)
        {
            head->right=insert(head->right,key);
        }
        //duplicate key so increase count
        else
        {
            head->count=head->count+1;
            return head;
        }
        //update the height
        head->height=1+max_height(head);
        int bf=balance_factor(head);
        //Now identify the location of the imbalance
        //left side imbalance
        if(bf>1)
        {
            //LL
            if(get_height(head->left->left)>=get_height(head->left->right))
            {
                return right_rotation(head);
            }
            else if(key > head->data)
            {
                Node * temp=left_rotation();
            }
        }
        else if(bf<-1)
        {
            if(get_height(head->right->right)>=get_height(head->right->left))
            {

            }
        }
    }
    /*-------------------------------------------------------------------*/
    void insert_key(T key)
    {

    }
    void delete_key(T key)
    {

    }
    void search_key(T key)
    {

    }
    int count_key(T key)
    {

    }
    T lower_bound(T key)
    {

    }
    T upper_bound(T key)
    {

    }

};
void testcases()
{
    avl<int>tree;
    tree.display();
    /*for(int i=1;i<=10;i++)
    {
        tree.insert_key(i);
        cout<<"-------------------------------------------"<<endl;
        tree.display();
    }*/
}
int main()
{
    testcases();
    return 0;
}