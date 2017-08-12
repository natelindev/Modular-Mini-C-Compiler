int main(){
    int a;
    a = 1;
    a = a * 2 + 3;
    a = foo(a, 2+3);
    return a;
}
int foo(int a,int b)
{
    return a + b;
}
