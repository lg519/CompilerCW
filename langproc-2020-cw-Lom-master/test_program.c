int global = 9;

int dom()
{
    int x = 2;
    do
    {
        global +=1;
        x+=1;
    } while (x < 5);
    return global;
}

int main()
{
      
    return dom();
    
}

