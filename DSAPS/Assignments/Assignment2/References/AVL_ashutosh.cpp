#include<iostream>
#include<bits/stdc++.h>
using namespace std;
template <class T> struct Less {
    bool operator()(const T &lhs, const T &rhs)
    {
        return lhs < rhs;
    }
};
class stud {
    public:
    int marks;
    string name;
    
};
struct cmpare{
    bool operator()(stud a,stud b)
    {
        return a.name<b.name;
    }
};
template <typename T , class Comparator = Less<T>> class AVL
{
    public:
        class node{
            public:
                T key;
                int height;
                int count;
                node * left;
                node * right;
                node(T k){
                    height = 1; count = 1;
                    key = k;
                    left = NULL;
                    right = NULL;
                }
        };
        node * root = NULL;
        int n = 0;
        vector<T> arr;
        T inorderpreval;
        bool first = false;
        void insert(T x){
            root=insertUtil(root, x);
        } // closing of insert
        void remove(T x){
            root=removeUtil(root, x);
        } //closing of remove
        bool search(T x){
            node*pq =  searchUtil(root,x);
            if(pq == NULL)
             return false;
             return true;

        } //closing of search
        void lowerboundelement(T x)
        {
             lb = NULL;
            lowerboundutil(root,x);
            if(lb == NULL)
             cout<<"-1"<<endl;
            else 
            cout<<lb->key.name<<endl; 

        }// closing of lowerboundelement
        void upperboundelement(T x)
        {
             ub = NULL;
            upperboundutil(root,x);
            if(ub == NULL)
             cout<<"-1"<<endl;
             else
             {
                 cout<<ub->key.name<<endl;
             }
             
        } //closing of upperboundelement

        void closestelement(T x)
        {   node *pq = searchUtil(root,x);
           if( pq != NULL)
              {
                  cout<<x<<endl;
                  return;
              }
         
          
              /*lb = NULL;
              lowerboundutil(root,x);
              inorderpre(root,x);
              if( first!= false)
              cout<< inorderpreval<<endl;
              if(first == false && lb!= NULL)
              cout<<lb->key<<endl;
              if(lb == NULL && first == false)
              cout<<-1<<endl;*/
          
            lb = NULL;
            lowerboundutil(root,x);
            inorderpre(root,x);
           if(first == false)
             {
                 cout <<lb->key<<endl;
                 return;
            }
            T val = inorderpreval;
           T cal = lb->key;
            if(abs(val-x)>abs(cal-x))
              {cout<< cal.name<<endl;
                return;
              }
            cout<< val.name<<endl; 
            
       } // closing of closestelement
       void kthlargest( int k)
       {   arr.clear();
           inorderUtil(root);
           if(arr.size()==0 || k < 1 || k > arr.size())
           {
               cout<<-1<<endl;
           }
           else
           {
               long long int i = arr.size();
               i = i - k;
               cout<<arr[i].name<<endl;
           }
           return;
          
       } // closing of kth largest
       int counting(T x)
       {
           node *pq = searchUtil(root,x);
           if(pq != NULL)
           {
               return pq->count;
           }
           return 0;
       } // closing of counting
       void print()
       {
           arr.clear();
           node* head = root;
           inorderUtil(head);
           for(int i = 0;i<arr.size();i++)
           {
               cout<<arr[i].name<<" ";
           }
           cout<<endl;
       } // closing of print
         int rangecount(T x, T y)
         {   arr.clear();
             inorderUtil(root);
             long long int i = 0;
             int tot = 0;
             while(i<arr.size())
             {
                 if(cmp(arr[i],x) == false && cmp(y,arr[i])==false)
                  tot++;
                  i++;
             }
             return tot;
         } // closing of rangecount
         void inorderpre(node* head,T x )
         {
             if(head == NULL)
             {
                 return;
             }
             if(!cmp(head->key, x) && !cmp(x,head->key))
             {
                 inorderpreval = x;
                 return;
             }
             else if(cmp(head->key , x))
             {
                 if(first)
                 inorderpreval = max(head->key,inorderpreval);
                 
                 else if(!first)
                 {
                     inorderpreval = head->key;
                     first = true;
                 }
             }
             else
             {
                 inorderpre(head->left,x);
             }
         }// closing of inorderpre function
    private:
     node *ub;
     node *lb;
     Comparator cmp;
        int height(node * head){
            if(head==NULL) return 0;
            return head->height;
        } // closing of height
        node * rightRotation(node * head){
            node * tq = head->left;
            head->left = tq->right;
            tq->right = head;
            head->height = 1+max(height(head->left), height(head->right));
            tq->height = 1+max(height(tq->left), height(tq->right));
            return tq;
        } // closing of right rotation

        node * leftRotation(node * head){
            node * tq = head->right;
            head->right = tq->left;
            tq->left = head;
            head->height = 1+max(height(head->left), height(head->right));
            tq->height = 1+max(height(tq->left), height(tq->right));
             return tq;
        } // closing of left rotation

        void inorderUtil(node * head){
            if(head==NULL) return ;
            inorderUtil(head->left);
            int stot = head->count;
            while(stot>0)
            {
                arr.push_back(head->key);
                stot--;
            }
            inorderUtil(head->right);
        } // closing of inorder util

        node * insertUtil(node * head, T x){
            if(head==NULL){
                n+=1;
                node * temp = new node(x);
                return temp;
            }   n++;
             node *pq = searchUtil(root, x);
             if(pq != NULL)
             {
                 pq->count = pq->count+1;
                 return head;

             }
            if(cmp(x ,head->key)) head->left = insertUtil(head->left, x);
            else if(cmp( head->key,x)) head->right = insertUtil(head->right, x);
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(cmp(x, head->left->key)){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal<-1){
                if(cmp( head->right->key,x)){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        } // closing of insert util
        node * removeUtil(node * head, T x){
            if(head==NULL) return NULL;
            n--;
            node*pq = searchUtil(head,x);
            if(pq != NULL)
            {
                pq->count = pq->count-1;
                return head;
            }
            if(cmp(x, head->key)){
                head->left = removeUtil(head->left, x);
            }else if(cmp( head->key,x)){
                head->right = removeUtil(head->right, x);
            }else{
                node * r = head->right;
                if(head->right==NULL){
                    node * l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = removeUtil(head->right, r->key);
                }
            }
            if(head==NULL) return head;
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(cmp(x , head->left->key)){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal <-1){
                if(cmp(x , head->right->key)){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        } // closing of removeutil
        node * searchUtil(node * head, T x){
            if(head == NULL) return NULL;
            T k = head->key;
            if(!cmp(k,x) && !cmp(x,k)) return head;
            if(cmp( x,k)) return searchUtil(head->left, x);
            if(cmp(k , x)) return searchUtil(head->right, x);
        } // closing of searchUtil
       
       
         void lowerboundutil(node* head,T x)
        {
            if(head == NULL)
            return;
            if(cmp( x,head->key))
            {
               lb = head;
               lowerboundutil(head->left,x);
            }
            else
            {
                lowerboundutil(head->right,x);
            }
            
        } // closing of lowerboundutil
        void upperboundutil(node* head,T x)
        {
            if(head == NULL)
            return;
            if(cmp(x,head->key))
            {
                ub = head;
                upperboundutil(head->left,x);
            }
            else
            {
                upperboundutil(head->right,x);
            }
            
        } //closing of upperboundutil
        
};// closing of class AVL
int main(){
    AVL<T,V>t;
    int n;
    cin>>n;
    while(n--)
    {
        int ch;
        cin>>ch;
        if(ch == 1)
        {   T val1;
            cin>>val1;
            t.insert(val1);
            t.print();
        }
        else if(ch == 2)
        {
            T val2;
            cin>>val2;
            t.delete(val2);
            t.print();

        }
        else if(ch == 3)
        {
            T val2;
            cin>>val2;
            t.search(val2);
            t.print();
        }
        else if(ch == 4)
        {
            T val2;
            cin>>val2;
            cout<<t.counting(val2)<<endl;

        }
        else if(ch == 5)
        {
            T val2;
            cin>>val2;
            t.lowerboundelement(val2);
        }
        else if(ch == 6)
        {
            T val2;
            cin>>val2;
            t.upperboundelement(val2);
        }
        else if(ch == 7)
        {
            T k;
            cin>>k;
            t.closestelement(k);
        }
        else if(ch == 8)
        {
             int k;
             cin>>k;
             t.kthlargest(k);
        }
        else if(ch == 9)
        {
            T val1;
            T val2;
            t.rangecount(val1,val2);
        }

    }
   return 0;
   
}