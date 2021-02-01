// put functions 3-7

int add(int a, int b)
{
    return (a + b); 
}

int sub (int a, int b)
{
    int sum = (a - b); 
    if (sum > (b - a))
        return sum; 
    return (b - a); 
}