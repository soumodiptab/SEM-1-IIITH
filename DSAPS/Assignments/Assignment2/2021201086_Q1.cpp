#include<iostream>
using namespace std;
const string ERROR="ERROR";

class Employee
{
    public:
    string name;
    long long int emp_id;
    public:
    Employee()
    {
        name="";
        emp_id=0;
    }
    Employee(string name, long long int emp_id)
    {
        this->name=name;
        this->emp_id=emp_id;
    }
    bool operator < (Employee x)
    {
        return this->emp_id < x.emp_id;
    }
    bool operator > (Employee x)
    {
        return this->emp_id > x.emp_id;
    }
    bool operator <= (Employee x)
    {
        return this->emp_id <= x.emp_id;
    }
    bool operator >= (Employee x)
    {
        return this->emp_id >= x.emp_id;
    }
    bool operator == (Employee x)
    {
        return this->emp_id == x.emp_id;
    }
    Employee* operator - (Employee x)
    {
        Employee* z=new Employee();
        z->emp_id=this->emp_id-x.emp_id;
        return z;
    }
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
        int left_count,right_count;
        Node *left,*right;
        Node(T key)
        {
            data=key;
            count=1;
            height=1;
            left_count=0;
            right_count=0;
            left=NULL;
            right=NULL;
        }
    };
    Node *root;
    /*----------Utility apis which is used in other functions------------*/
    public:
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
        trunk->str = "————";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`————";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    cout<<root->data <<","<<root->count<<","<<root->height<< endl;
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
    }
    void display()
    {
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
        head->height=1+max_height(head);
        pivot->height=1+max_height(pivot);
        head->right_count=pivot->left_count;
        pivot->left_count=head->left_count+head->count+head->right_count;
        return pivot;
    }
    Node* right_rotation(Node* head)
    {
        Node *pivot=head->left;
        head->left=pivot->right;
        pivot->right=head;
        head->height=1+max_height(head);
        pivot->height=1+max_height(pivot);
        head->left_count=pivot->right_count;
        pivot->right_count=head->left_count+head->count+head->right_count;
        return pivot;   
    }
    Node* fix_nodes(Node* head,int bf)
    {
        if(bf>1)
        {
            //LL
            if(get_height(head->left->left)>=get_height(head->left->right))
            {
                return right_rotation(head);
            }
            //LR
            else
            {
                Node* temp=left_rotation(head->left);
                return right_rotation(head);
            }
        }
        else
        {
            //RR
            if(get_height(head->right->right)>=get_height(head->right->left))
            {
                return left_rotation(head);
            }
            else
            {
                Node* temp=right_rotation(head->right);
                return left_rotation(head);
            }
        }
    }
    Node* insert(Node* head,T key)
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
            head->left_count++;
        }
        //go to right sub tree  comparator--<change later>
        else if(key > head->data)
        {
            head->right=insert(head->right,key);
            head->right_count++;
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
        if(abs(bf)>1)
        {
            return fix_nodes(head,bf);
        }
        return head;
    }
    Node* search(Node* head,T key)
    {
        if(head==NULL)
            return head;
        else if(head->data==key)
        {
            return head;
        }
        else if(key<head->data)
            return search(head->left,key);
        else
            return search(head->right,key);
    }
    /*-------------------------------------------------------------------*/
    bool has_two_children(Node *head)
    {
        if(head->left && head->right)
            return true;
        else
            return false;
    }
    bool is_leaf(Node *head)
    {
        if(head->left==NULL && head->right==NULL)
            return true;
        else
            return false;
    }
    Node* get_node(Node *head)
    {
        if(head->left)
            return head->left;
        else if(head->right)
            return head->right;
        else
            return NULL;
    }
    //x=y
    void transfer(Node* x,Node *y)
    {
        x->data=y->data;
        x->count=y->count;
    }
    Node* inorder_predecessor(Node *head)
    {
        if(head->right==NULL)
            return head;
        return inorder_predecessor(head->right);
    }
    Node* del(Node* head,T key)
    {
        if(head==NULL)
            return head;
        if(key < head->data)
        {
            head->left=del(head->left,key);
            head->left_count--;
        }
        else if( key > head->data)
        {
            head->right=del(head->right,key);
            head->right_count--;
        }
        else//key found
        {
            if(head->count>1)
            {
                head->count=head->count-1;
                return head;
            }
            if(has_two_children(head))
            {
                Node* new_target=inorder_predecessor(head->left);
                transfer(head,new_target);
                head->left_count=new_target->count;
                head->left=del(head->left,head->data);
            }
            else
            {
                Node* mark_for_deletion=head;
                head=get_node(head);
                delete(mark_for_deletion);
            }
        }
        if(head==NULL)
            return head;
        //update the height
        head->height=1+max_height(head);
        int bf=balance_factor(head);
        //Now identify the location of the imbalance
        //left side imbalance
        if(abs(bf)>1)
        {
            return fix_nodes(head,bf);
        }
        return head;
    }
    /**
     * @brief 
     * 
     * @param head 
     * @param key 
     * @param cache 
     */
    void upper(Node* head, T key,T& cache)
    {
        if(head==NULL)
            return;
        if(key < head->data)
        {
            cache=head->data;
            upper(head->left,key,cache);
        }
        else
        {
            upper(head->right,key,cache);
        }
    }
    /**
     * @brief 
     * 
     * @param head 
     * @param key 
     * @param cache 
     */
    void lower(Node* head, T key,T& cache)
    {
        if(head==NULL)
            return;
        if(key > head->data)
        {
            cache=head->data;
            lower(head->right,key,cache);
        }
        else
        {
            lower(head->left,key,cache);
        }
    }
    T kth(Node *head,int k)
    {
        if(head->right_count >= k)
        {
            return kth(head->right,k);
        }
        else if(head->count + head->right_count >= k)
        {
            return head->data;
        }
        else
        {
            int new_k=k-head->count-head->right_count;
            return kth(head->left,new_k);
        }
    }
    /*-----------------------------------------------------------------------*/
    void insert_key(T key)
    {
        root=insert(root,key);
    }
    void delete_key(T key)
    {
        Node* temp=search(root,key);
        if(temp==NULL)
        {
            return;
        }
        else
        {
            root=del(root,key);
        }
    }


    bool search_key(T key)
    {
        Node* temp=search(root,key);
        return (temp==NULL)?false:true;
    }
    int count_key(T key)
    {
        Node* temp=search(root,key);
        if(temp==NULL)
            return -1;
        else
            return temp->count;
    }
    T lower_bound(T key)
    {
        T lower_bound_value=NULL;
        lower(root,key,lower_bound_value);
        return lower_bound_value;
    }
    T upper_bound(T key)
    {
        T upper_bound_value=NULL;
        upper(root,key,upper_bound_value);
        return upper_bound_value;
    }
    Node* min_value_tree(Node* head)
    {
        if(head->left)
        {
            return min_value_tree(head->left);
        }
        else
        {
            return head;
        }
    }
    Node* max_value_tree(Node* head)
    {
        if(head->right)
        {
            return max_value_tree(head->right);
        }
        else
        {
            return head;
        }
    }

    T closest(T key)
    {
        if(root==NULL)
        {
            return NULL;
        }
        T max=max_value_tree(root)->data;
        T min=min_value_tree(root)->data;
        T upper_val=NULL;
        T lower_val=NULL;
        if(key > max)
        {
            return max;
        }
        else if(key < min)
        {
            return min;
        }
        else // key is tree bounds
        {
            upper(root,key,upper_val);
            lower(root,key,lower_val);
            if(upper_val != NULL && lower_val != NULL)
            {
                if((key - lower_val) <= (upper_val - key))
                {
                    return lower_val;
                }
                else
                    return upper_val;
            }
            else if(upper_val==NULL)
            {
                return lower_val;
            }
            else
            {
                return upper_val;
            }
        }
    }
    T kth_largest(int k)
    {
        return kth(root,k);
    }
    /**
     * @brief Finds the count of nodes greater than a key
     * 
     * @param key 
     * @return int 
     */
    int upper_count(Node *head,T key)
    {
        if(head==NULL)
        {
            return 0;
        }
        if(key < head->data)//go left and add
        {
            return head->count+head->right_count+upper_count(head->left,key);
        }
        else if(key > head->data)//go right without adding
        {
            return upper_count(head->right,key);
        }
        else//key match
        {
            return head->right_count;
        }
    }
    int upper_count_testing(T key)
    {
        return upper_count(root,key);
    }
    /**
     * @brief Finds the count of nodes lesser than a key
     * 
     * @param key 
     * @return int 
     */
    int lower_count(Node *head,T key)
    {
        if(head==NULL)
        {
            return 0;
        }
        if(key < head->data)//go left without adding
        {
            return lower_count(head->left,key);
        }
        else if(key > head->data)//go right and add
        {
            return head->count+head->left_count+lower_count(head->right,key);
        }
        else//key match
        {
            return head->left_count;
        }
    }
    int lower_count_testing(T key)
    {
        return lower_count(root,key);
    }
    int range_count(T low_key,T up_key)
    {
        if(root==NULL)
         return 0;
        T max_node_val=max_value_tree(root)->data;
        T min_node_val=min_value_tree(root)->data;
        //out of range
        if(up_key>max_node_val && low_key>max_node_val)
        {
            return 0;
        }
        else if(low_key<min_node_val && up_key < min_node_val)
        {
            return 0;
        }
        else // within avl bounds partial/full
        {
            T actual_low_key=low_key;
            T actual_up_key=up_key;
            if(!search_key(low_key))
            {
                if(low_key< min_node_val)
                    actual_low_key=min_node_val;
                else
                    actual_low_key=upper_bound(low_key);
            }
            if(!search_key(up_key))
            {
                if(up_key > max_node_val)
                    actual_up_key=max_node_val;
                else
                    actual_up_key=lower_bound(up_key);
            }
            int total_count=root->left_count+root->count+root->right_count;
            int up_out_of_range=upper_count(root,actual_up_key);
            int low_out_of_range=lower_count(root,actual_low_key);
            return total_count-up_out_of_range-low_out_of_range;
        }
    }
    //------------------------------------------------------------------------------
    void node_check()
    {
        Node *root=new Node(2);
        Node *l=new Node(1);
        Node *r=new Node(3);
        Node *r2=new Node(4);
        root->left=l;
        root->right=r;
        root->left->right=r2;
    }
};
void testcases()
{
    avl<int>tree;
    for(int i=1;i<=30;i+=4)
    {
        tree.insert_key(i);
        cout<<"-------------------------------------------"<<endl;
        tree.display();
    }
    for(int i=40;i>=1;i-=3)
    {
        tree.insert_key(i);
        cout<<"-------------------------------------------"<<endl;
        tree.display();
    }
    tree.insert_key(7);
    cout<<"-------------------------------------------"<<endl;
    tree.display();
    tree.insert_key(6);
    cout<<"-------------------------------------------"<<endl;
    tree.display();
    cout<<"-------------------------------------------"<<endl;
    //cout<<tree.search_key(17)<<endl;
    //cout<<tree.search_key(18)<<endl;
    cout<<"-------------------------------------------"<<endl;
    //tree.upper_bound(21);
    //tree.lower_bound(21);
    tree.delete_key(6);
    tree.display();
    cout<<"-------------------------------------------"<<endl;
    tree.delete_key(5);
    tree.delete_key(1);
    tree.delete_key(1);
    tree.display();
    cout<<"-------------------------------------------"<<endl;
    tree.delete_key(29);
    tree.display();
    cout<<"-------------------------------------------"<<endl;
    //cout<<tree.kth_largest(7)<<endl;
    cout<<tree.closest(42)<<endl;
    cout<<tree.closest(35)<<endl;
    cout<<tree.closest(1)<<endl;
    cout<<tree.lower_bound(1)<<endl;
    //cout<<tree.count_key(49)<<endl;
    //tree.range_count(1,42);
    cout<<tree.upper_count_testing(7)<<endl;
    cout<<tree.lower_count_testing(22)<<endl;
    
}
int main()
{
    testcases();
    return 0;
}