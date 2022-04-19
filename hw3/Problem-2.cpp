#include<iostream>
using namespace std;
#define n 238589771
#define seed 7477
#define bits 1000000
bool table[bits];
int main()
{
    system("cls");
    unsigned x=seed;
    float zero=0;
    float one=0;
    for(int i=0;i<bits;i++)
    {
        //cout<<x<<endl;
        table[i]=(bool)(x%2);
        if(table[i])
        {
            one++;
        }
        else
        {
            zero++;
        }
        x*=x;
        x=x%n;
        //system("pause");
    }
    cout<<"one="<<one<<endl;
    cout<<"zero="<<zero<<endl;
    float zero_=zero/bits;
    float one_=one/bits;
    cout<<"0="<<zero_<<endl;
    cout<<"1="<<one_<<endl;

    float zz=0;
    float zo=0;
    float oz=0;
    float oo=0;
    float count=0;
    for(int i=0;i<bits-1;i++)
    {
        if(table[i]==0&&table[i+1]==0)
        {
            zz++;
        }
        else if(table[i]==0&&table[i+1]==1)
        {
            zo++;
        }
        else if(table[i]==1&&table[i+1]==0)
        {
            oz++;
        }
        else if(table[i]==1&&table[i]==1)
        {
            oo++;
        }
        count++;
    }
    cout<<"00="<<zz<<endl;
    cout<<"01="<<zo<<endl;
    cout<<"10="<<oz<<endl;
    cout<<"11="<<oo<<endl;
    cout<<"count="<<count<<endl;
    float zz_=zz/count;
    float zo_=zo/count;
    float oz_=oz/count;
    float oo_=oo/count;
    cout<<"00_"<<zz_<<endl;
    cout<<"01_"<<zo_<<endl;
    cout<<"10_"<<oz_<<endl;
    cout<<"11_"<<oo_<<endl;
    return 0;
}