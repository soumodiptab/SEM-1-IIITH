#include<iostream>
#include<string>
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
                return 0;//more code here 
        }
    }
    string add(string a,string b)
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
            int tmp=(a[i]-'0')+(b[i]-0)+carry;
            carry=0;
            if(tmp>'9')
            {
                tmp-=10;
                carry++;
            }
            result[i]=tmp;
        }
        if(carry)
        {
            result.insert(0,1,'1');
        }
        return result;
    }
    //Assuming a>b as specified in the question
    string substract(string a,string b)
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
    string multiply(string a,string b)
    {
        if(a.length()<b.length())
            a.swap(b);
        
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
};
void test_cases()
{
    string x="121321",y="83864";   
    BigInt a=BigInt(x);
    BigInt b=BigInt(y);
    BigInt c=a+b;
    BigInt d=a-b;
    cout<<c.value()<<endl;
    cout<<d.value()<<endl;
}
int main()
{
    test_cases();
    return 0;
}