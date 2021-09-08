#include<iostream>
#include<string>
#include<chrono>
using namespace std;
class BigInt{
    private:
    string val;
    //This function adds two strings
    int compare(string a,string b)
    {
        if(a.length()>b.length())
            return 1;
        else if(a.length()<b.length())
            return -1;
        else
        {
            if(a[0]>b[0])
                return 1;
            else if(a[0]<b[0])
                return -1;
            else
                return 0;
        }
    }
    static string add(string a,string b)
    {
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
        //remove the zeros incase both no. have lots of same digits in the front
        while(result[0]=='0' && result.length()>1)
            {
                result.erase(0,1);
            }
        return result;
    }
    //a>b
    static string multiply(string a,string b)
    {
        string result(1,'0');
        if(a.compare("0")==0 || b.compare("0")==0)
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
        //remove the zeros incase both no. have lots of same digits in the front
        while(result[0]=='0' && result.length()>1)
            {
                result.erase(0,1);
            }
        return result;
    }
    string divide(string a,string b)
    {
        
    }
    string gcd_runner(string a,string b)
    {
        if(b=="0")
		    return a;
	    string mod=divide(a,b);
	    return gcd_runner(b,mod);	
    }
    string binary_expo(string x,unsigned long long n)
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
    public:
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
    BigInt gcd(BigInt a,BigInt b)
    {
        BigInt temp = BigInt(gcd_runner(this->val,b.val));
        return temp;
    }
    BigInt power(unsigned long long b)
    {
        BigInt temp = BigInt(binary_expo(this->val,b));
        return temp;
    }
    static string factorial(unsigned long long n)
    {
        string result="1";
        for(unsigned long long i=2;i<=n;i++)
        {
            result=multiply(result,to_string(i));
        }
        return result;
    }
};
void test_cases()
{
    string x="121023",y="58098";   
    BigInt a=BigInt(x);
    BigInt b=BigInt(y);
    auto start = chrono::high_resolution_clock::now();
    BigInt c=a+b;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
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
}
int main()
{
    test_cases();
    return 0;
}