#include<iostream>
#include<string>
#include<chrono>
using namespace std;
template <typename T>
class stack
{
    int top;
    int capacity=10;
    T *arr;
    public:
    stack()
    {
        arr=new T[capacity];
        top=-1;
    }
    void enlarge()
    {
        capacity*=2;
        T *new_arr=new T[capacity];
        for(int i=top;i>=0;i--)
            new_arr[i]=arr[i];
        delete [] arr;
        arr=new_arr;
    }
    void push(T c)
    {
        if(top<capacity)
            enlarge();
        arr[++top]=c;
    }
    void pop()
    {
        if(top==-1)
            return;
        top--;
    }
    T peek()
    {
        return arr[top];
    }
    bool isEmpty()
    {
        return (top==-1)?true:false;
    }
};
class BigInt{
    private:
    string val;
    public:
    static void remove_trailing_zeros(string &x)
    {
         while(x[0]=='0' && x.length()>1)
            {
                x.erase(0,1);
            }
    }
    static string add(string a,string b)
    {
        remove_trailing_zeros(a);
        remove_trailing_zeros(b);
        int res_length=(a.length()>b.length())?a.length():b.length();
        string result(res_length,'0');
        int diff=std::abs((int)(a.length()-b.length()));
        if(a.length()>b.length())
            b.insert(0,diff,'0');
        else
            a.insert(0,diff,'0');
        int carry=0;
        for(int i=res_length-1;i>=0;i--)
        {
            int tmp=(a[i]-'0')+(b[i]-0)+carry-'0';
            carry=0;
            if(tmp>9)
            {
                tmp-=10;
                carry++;
            }
            result[i]=tmp+'0';
        }
        if(carry)
        {
            result.insert(0,1,'1');
        }
        return result;
    }
    //Assuming a>b as specified in the question
    static string substract(string a,string b)
    {
        remove_trailing_zeros(a);
        remove_trailing_zeros(b);
        int res_length=a.length();
        string result(res_length,'0');
        int diff=std::abs((int)(a.length()-b.length()));
        if(a.length()>b.length())
            b.insert(0,diff,'0');
        //start from back to the front 
        for(int i=result.length()-1;i>=0;i--)
        {
            if(a[i]<b[i])
            {
                a[i]+=10;
                a[i-1]-=1;
            }
            result[i]=(a[i]-'0')-(b[i]-'0')+'0';
        }
        int i=0;
        remove_trailing_zeros(result);
        return result;
    }
    //a>b
    static string multiply(string a,string b)
    {
        remove_trailing_zeros(a);
        remove_trailing_zeros(b);
        string result="0";
        if(compare(a,"0")==0 || compare(b,"0")==0)
            return result;
        for(int i=b.length()-1;i>=0;i--)
        {
            string prod=a;
            int digit=b[i]-'0';
            int carry=0;
            for(int j=prod.length()-1;j>=0;j--)
            {
                int val=((prod[j]-'0')*digit)+carry;
                if(val>9)
                {
                    carry=(val/10);
                    val=val-(carry*10);
                }
                else
                {
                    carry=0;
                }
                prod[j]='0'+val;
            }
            if(carry > 0)
                prod.insert(0,1,('0'+carry));
            prod.append((b.length()-i-1),'0');
            result=add(result,prod);
        }
        remove_trailing_zeros(result);
        return result;
    }
    //a>b :1 a=b :0 a<b :-1
    static int compare(string a,string b)
    {
        if(a.length()>b.length())
            return 1;
        else if(a.length()<b.length())
            return -1;
        else
        {
            for(int i=0;i<a.length();i++)
            {
                if(a[i]>b[i])
                    return 1;
                else if(a[i]<b[i])
                    return -1;
            }
        }
        return 0;
    }
    //-----------------------------------------------------
    static string mod(string dividend,string divisor)
    {
        remove_trailing_zeros(dividend);
        remove_trailing_zeros(divisor);
        if(compare(dividend,divisor)==-1)
            return dividend;
        if(compare(dividend,divisor)==0)
            return "0";
        int i,j;
        j=divisor.length();
        string temp,remaining,res;
        res=dividend;
        while(compare(res,divisor)>=0)
        {
            i=0;
            temp=res.substr(0,j+i);
            if(compare(temp,divisor)==-1)
                i=1;
            temp=res.substr(0,j+i);
            remaining=res.substr(j+i,res.length()-j-i);
            while(compare(temp,divisor)>=0)
            {
                temp=substract(temp,divisor);
            }
            //int rem_length=j-i;
            res=remaining.insert(0,temp);
            remove_trailing_zeros(res);
            if(substract(res,"0")=="0")
                return "0";
            if(compare(res,divisor)==0)
                return "0";
        }
        return res;
    }
    static string gcd_runner(string a,string b)
    {
        if(a=="0")
		    return b;
	    string m=mod(b,a);
	    return gcd_runner(m,a);	
    }
    static string gcd(string a,string b)
    {
        remove_trailing_zeros(a);
        remove_trailing_zeros(b);
        string temp=gcd_runner(a,b);
        return temp;
    }
    //--------------------------------------------------
    BigInt(string x)
    {
        this->val=x;
    }
    string value()
    {
        return this->val;
    }
    BigInt operator +(BigInt x)
    {
        BigInt temp = BigInt(add(this->val,x.val));
        return temp;
    }
    BigInt operator -(BigInt x)
    {
        BigInt temp = BigInt(substract(this->val,x.val));
        return temp;
    }
    BigInt operator *(BigInt x)
    {
        BigInt temp = BigInt(multiply(this->val,x.val));
        return temp;
    }
    //---------------------------------------------------------
    static string binary_expo(string x,unsigned long long int n)
    {
        string result="1";
        while(n>0)
        {
            if(n&1)
                result=multiply(x,result);
            x=multiply(x,x);
            n>>=1;
        }
        return result;
    }
    BigInt power(unsigned long long b)
    {
        BigInt temp = BigInt(binary_expo(this->val,b));
        return temp;
    }
    //------------------------------------------------------------
    static string factorial(unsigned long long int n)
    {
        string result="1";
        for(unsigned long long int i=2;i<=n;i++)
        {
            result=multiply(result,to_string(i));
        }
        return result;
    }
    //-------------------------------------------------------------
    static int identify(char c)
    {//0-unknown 1-number 2-operator
        if(c>='0'&&c<='9')
            return 1;
        if(c=='+'||c=='-'||c=='x')
            return 2;
        return 0;
    }
    static int priority(char c)
    {
        if(c=='+'||c=='-')
            return 1;
        if(c=='x')
            return 2;
        return 0;
    }
    string static apply(string &a,string &b,char op)
    {
        switch(op)
        {
            case '+':
            return add(a,b);
            case '-':
            return substract(a,b);
            case 'x':
            return multiply(a,b);
        }
    }
    static void error_message()
    {
        cout<<"[INFO]:[ERROR Incorrect Expression]"<<endl;
    }
    static string expr_evaluator(string exp)
    {
        stack<char> operators;
        stack<string> operands;
        for(int i=0;i<exp.length();i++)
        {
            int ch=identify(exp[i]);
            if(ch==0)//incorrect character
            {
                error_message();
                return NULL;
            }
            else if(ch==1)//operand
            {
                int j=i;
                while(j<exp.length()&&identify(exp[j])==1)
                {
                    j++;
                }
                if(j<exp.length()&& identify(exp[j])==0)
                {
                    error_message();
                    return NULL;
                }
                string temp=exp.substr(i,j-i);
                i=j-1;
                operands.push(temp);
            }
            else//operator
            {
                while(!operators.isEmpty() && priority(operators.peek())>=priority(exp[i]))
                {
                    string second=operands.peek();
                    operands.pop();
                    string first=operands.peek();
                    operands.pop();
                    char op=operators.peek();
                    operators.pop();
                    remove_trailing_zeros(second);
                    remove_trailing_zeros(first);
                    string result=apply(first,second,op);
                    operands.push(result);
                }
                operators.push(exp[i]);
            }
        }
        while(!operators.isEmpty())
        {
            string second=operands.peek();
            operands.pop();
            string first=operands.peek();
            operands.pop();
            char op=operators.peek();
            operators.pop();
            remove_trailing_zeros(second);
            remove_trailing_zeros(first);
            string result=apply(first,second,op);
            operands.push(result);
        }
        return operands.peek();
    }
};
void test_cases()
{ 
    BigInt a=BigInt("121023");
    BigInt b=BigInt("58098");
    auto start = chrono::high_resolution_clock::now();
    //BigInt c=a+b;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    /*
    cout<<"Add: "<<c.value()<<endl;
    cout << duration.count() <<"ms"<< endl;
    //-----------------------------------------------------------------------------
    BigInt d=a-b;
    BigInt e=a*b;
    cout<<"Substract: "<<d.value()<<endl;
    cout<<"Multiply: "<<e.value()<<endl;
    //-----------------------------------------------------------------------------
    start = chrono::high_resolution_clock::now();
    BigInt f=a.power(999);
    cout<<"Power: "<<f.value()<<endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() <<"ms"<< endl;
    //-----------------------------------------------------------------------------
    start = chrono::high_resolution_clock::now();
    cout<<"Factorial: "<<BigInt::factorial(1000)<<endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() <<"ms"<< endl;
    //-----------------------------------------------------------------------------
    start = chrono::high_resolution_clock::now();
    cout<<BigInt::expr_evaluator("2908+3x28+98-25x12")<<endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() <<"ms"<< endl;
    //-----------------------------------------------------------------------------
    */
    start = chrono::high_resolution_clock::now();
    cout<<BigInt::gcd("42000000000000000000000000000000000000000000000035000000","700700")<<endl;
    //cout<<BigInt::substract("0000","0")<<endl;
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() <<"ms"<< endl;
}
int main()
{
    test_cases();
    return 0;
}