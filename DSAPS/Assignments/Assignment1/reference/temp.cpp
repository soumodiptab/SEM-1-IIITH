static string factorial(unsigned long long n)
    {
        string result="1";
        for(unsigned long long i=2;i<=n;i++)
        {
            result=multiply(result,to_string(i));
        }
        return result;
    }