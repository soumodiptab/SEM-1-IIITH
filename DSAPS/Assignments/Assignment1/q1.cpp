#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class BigInteger{
    private:
    string value;
    string add(string a,string b)
    {
        int res_size=(a.size()>b.size())?a.size():b.size();
        string result(res_size,'0');
        int diff=abs((int)(a.size()-b.size()));
        return result;
    }
    public:
    BigInteger(string x)
    {
        this->value=x;
    }
    BigInteger operator +(BigInteger x)
    {
        BigInteger temp = BigInteger(add(this->value,x.value));
        return temp;
    }

};
void test_cases()
{
    string x="121321",y="43564";   
    BigInteger a=BigInteger(x);
    BigInteger b=BigInteger(y);
    a+b;
}
int main()
{
    test_cases();
    return 0;
}