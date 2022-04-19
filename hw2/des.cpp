#include<iostream>
#include<fstream>
#include<bitset>
#include<cstring>
#include<cmath>
using namespace std;
//initial exchange
int ip[] = { 58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7 };
//last exange
int ip_1[] = { 40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25 };
//key exchange 64->56
int pc_1[] = { 57,49,41,33,25,17,9,
1,58,50,42,34,26,18,
10,2,59,51,43,35,27,
19,11,3,60,52,44,36,
63,55,47,39,31,23,15,
7,62,54,46,38,30,22,
14,6,61,53,45,37,29,
21,13,5,28,20,12,4 };
//press exchange 56->48
int pc_2[] = { 14,17,11,24,1,5,3,28,
15,6,21,10,23,19,12,4,
26,8,16,7,27,20,13,2,
41,52,31,37,47,55,30,40,
51,45,33,48,44,49,39,56,
34,53,46,42,50,36,29,32 };
//left shift
int shiftbits[] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
//extend exchange 32->48
int ext[] = { 32,1,2,3,4,5,
4,5,6,7,8,9,
8,9,10,11,12,13,
12,13,14,15,16,17,
16,17,18,19,20,21,
20,21,22,23,24,25,
24,25,26,27,28,29,
28,29,30,31,32,1 };
//s-box
int s_box[8][4][16] = {
 {
  {4,14,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
  {0,15,7,4,14,2,13,1,10,6,12,11,9,5,8,3},
  {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
  {13,12,8,2,4,9,1,7,5,11,3,14,10,0,6,15}
 },
 {
  {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
  {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
  {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
  {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
 },
 {
  {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
  {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
  {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
  {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
 },
 {
  {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
  {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
  {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
  {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
 },
 {
  {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
  {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
  {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
  {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
 },
 {
  {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
  {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
  {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
  {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
 },
 {
  {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
  {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
  {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
  {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
 },
 {
  {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
  {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
  {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
  {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
 }
};
//p enchange 32->32
int p[] = { 16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25 };

bitset<64> key;
bitset<64> key_2;
bitset<64> plaintext_text;
bitset<48> subkey[16];

//leftshift
bitset<28> leftshift(bitset<28> subkey,int shift_num)
{
    bitset<28> temp=subkey;
    for(int i=27;i>=0;i--)
    {
        if(i-shift_num<0)
        {
            subkey[i]=temp[i-shift_num+28];
        }
        else
        {
            subkey[i]=temp[i-shift_num];
        }
    }
    return subkey;
}
//create 16 encrypt keys
void create_16_keys()
{
    bitset<56> key_56;
    bitset<28> left_key;
    bitset<28> right_key;
    bitset<48> key_48;
    //64->56
    for(int i=0;i<56;i++)
    {
        key_56[55-i]=key[64-pc_1[i]];
    }
    //create subkey
    for(int i=0;i<16;i++)
    {
        //cut to two key
        for(int j=55;j>=28;j--)
        {
            left_key[j-28]=key_56[j];
            right_key[j-28]=key_56[j-28];
        }
        //leftshift
        left_key=leftshift(left_key,shiftbits[i]);
        right_key=leftshift(right_key,shiftbits[i]);
        for(int j=55;j>=28;j--)
        {
            key_56[j]=left_key[j-28];
            key_56[j-28]=right_key[j-28];
        }
        //56->48
        for(int j=0;j<48;j++)
        {
            key_48[47-j]=key_56[56-pc_2[j]];
        }
        subkey[i]=key_48;
    }
}
void create_16_keys_key2()
{
    bitset<56> key_56;
    bitset<28> left_key;
    bitset<28> right_key;
    bitset<48> key_48;
    //64->56
    for(int i=0;i<56;i++)
    {
        key_56[55-i]=key_2[64-pc_1[i]];
    }
    //create subkey
    for(int i=0;i<16;i++)
    {
        //cut to two key
        for(int j=55;j>=28;j--)
        {
            left_key[j-28]=key_56[j];
            right_key[j-28]=key_56[j-28];
        }
        //leftshift
        left_key=leftshift(left_key,shiftbits[i]);
        right_key=leftshift(right_key,shiftbits[i]);
        for(int j=55;j>=28;j--)
        {
            key_56[j]=left_key[j-28];
            key_56[j-28]=right_key[j-28];
        }
        //56->48
        for(int j=0;j<48;j++)
        {
            key_48[47-j]=key_56[56-pc_2[j]];
        }
        subkey[i]=key_48;
    }
}
//function of mima 32+48->32
bitset<32> function(bitset<32> data,bitset<48> subkey)
{
    bitset<48> data_48;
    //32->48
    for(int i=0;i<48;i++)
    {
        data_48[47-i]=data[32-ext[i]];
    }
    //XOR
    data_48=data_48^subkey;
    //s-box
    bitset<32> key_32;
    int count=0;
    for(int i=0;i<48;i=i+6)
    {
        int row=data_48[47-i]*2+data_48[47-i-5];
        int col=data_48[47-i-1]*8+data_48[47-i-2]*4+data_48[47-i-3]*2+data_48[47-i-4]*1;
        int temp=s_box[i/6][row][col];
        bitset<4> binary(temp);
        for(int j=3;j>=0;j--)
        {
            key_32[31-count]=binary[j];
            count++;
        }
    }
    //p exchange 32->32
    bitset<32> final_data_32;
    for(int i=0;i<32;i++)
    {
        final_data_32[31-i]=key_32[32-p[i]];
    }
    return final_data_32;
}
//des encrypt
bitset<64> encrypt(bitset<64>&plaintext)
{
    bitset<64> cipher;
    bitset<64> temp;
    bitset<32> left;
    bitset<32> right;
    //ip exchange
    for(int i=0;i<64;i++)
    {
        temp[63-i]=plaintext[64-ip[i]];
    }
    //divide into left and right
    for(int i=63;i>=32;i--)
    {
        left[i-32]=temp[i];
        right[i-32]=temp[i-32];
    }
    //iterate for 16 round
    for(int i=0;i<16;i++)
    {
        bitset<32> tempp=right;
        right=left^function(right,subkey[i]);
        left=tempp;
    }
    //merge
    for(int i=63;i>=32;i--)
    {
        temp[i]=right[i-32];
        temp[i-32]=left[i-32];
    }
    //exchange ip_1
    for(int i=0;i<64;i++)
    {
        cipher[63-i]=temp[64-ip_1[i]];
    }
    return cipher;
}
//des decrypt
bitset<64> decrypt(bitset<64>&cipher)
{
    bitset<64> plaintext;
    bitset<64> temp;
    bitset<32> left;
    bitset<32> right;
    //ip exchange
    for(int i=0;i<64;i++)
    {
        temp[63-i]=cipher[64-ip[i]];
    }
    //divide into left and right
    for(int i=63;i>=32;i--)
    {
        left[i-32]=temp[i];
        right[i-32]=temp[i-32];
    }
    //iterate for 16 round
    for(int i=0;i<16;i++)
    {
        bitset<32> tempp=right;
        right=left^function(right,subkey[15-i]);
        left=tempp;
    }
    //merge
    for(int i=63;i>=32;i--)
    {
        temp[i]=right[i-32];
        temp[i-32]=left[i-32];
    }
    //exchange ip_1;
    for(int i=0;i<64;i++)
    {
        plaintext[63-i]=temp[64-ip_1[i]];
    }
    return plaintext;
}
void alphabat_to_64(string key_alphabet)
{
    int array[8];
    for(int i=0;i<8;i++)
    {
        array[i]=(int)key_alphabet[i];
    }
    int count=0;
    for(int i=0;i<64;i=i+8)
    {
        bitset<8> binary(array[i/8]);
        for(int j=7;j>=0;j--)
        {
            key[63-count]=binary[j];
            count++;
        }
    }
    /*int count=0;
    for(int i=0;i<key_alphabet.size();i++)
    {
        int number;
        switch(key_alphabet[i])
        {
            case '0':number=0;
            break;
            case '1':number=1;
            break;
            case '2':number=2;
            break;
            case '3':number=3;
            break;
            case '4':number=4;
            break;
            case '5':number=5;
            break;
            case '6':number=6;
            break;
            case '7':number=7;
            break;
            case '8':number=8;
            break;
            case '9':number=9;
            break;
            case 'A':case 'a':number=10;
            break;
            case 'B':case 'b':number=11;
            break;
            case 'C':case 'c':number=12;
            break;
            case 'D':case 'd':number=13;
            break;
            case 'E':case 'e':number=14;
            break;
            case 'F':case 'f':number=15;
            break;
            default:
            break;
        }
        bitset<4> binary(number);
        for(int j=3;j>=0;j--)
        {
            key[63-count]=binary[j];
            count++;
        }
    }
    cout<<key<<endl;*/
}
void alphabat_to_64_key2(string key_alphabet)
{
    int array[8];
    for(int i=0;i<8;i++)
    {
        array[i]=(int)key_alphabet[i];
    }
    int count=0;
    for(int i=0;i<64;i=i+8)
    {
        bitset<8> binary(array[i/8]);
        for(int j=7;j>=0;j--)
        {
            key_2[63-count]=binary[j];
            count++;
        }
    }
}
void plaintext_to_64(string plaint_alphabet)
{
    int array[8];
    for(int i=0;i<8;i++)
    {
        array[i]=(int)plaint_alphabet[i];
    }
    int count=0;
    for(int i=0;i<64;i=i+8)
    {
        bitset<8> binary(array[i/8]);
        for(int j=7;j>=0;j--)
        {
            plaintext_text[63-count]=binary[j];
            count++;
        }
    }
}
bitset<64> hex_to_binary(string ciphertext_hex)
{
    bitset<64> binary;
    int count=0;
    for(int i=0;i<64;i=i+4)
    {
        int number;
        switch(ciphertext_hex[i/4])
        {
            case '0':number=0;
            break;
            case '1':number=1;
            break;
            case '2':number=2;
            break;
            case '3':number=3;
            break;
            case '4':number=4;
            break;
            case '5':number=5;
            break;
            case '6':number=6;
            break;
            case '7':number=7;
            break;
            case '8':number=8;
            break;
            case '9':number=9;
            break;
            case 'A':case 'a':number=10;
            break;
            case 'B':case 'b':number=11;
            break;
            case 'C':case 'c':number=12;
            break;
            case 'D':case 'd':number=13;
            break;
            case 'E':case 'e':number=14;
            break;
            case 'F':case 'f':number=15;
            break;
            default:
            break;
        }
        bitset<4> temp(number);
        for(int j=3;j>=0;j--)
        {
            binary[63-count]=temp[j];
            count++;
        }
    }
    return binary;
}
void to_ascii_and_fout(bitset<64> plaintext_64bit)
{
    fstream output;
    output.open("des-out.txt",ios::app);
    for(int i=63;i>=0;i=i-8)
    {
        int number=0;
        for(int j=i;j>i-8;j--)
        {
            number+=(int)plaintext_64bit[j]*pow(2,(j%8));
        }
        output<<(char)number;
    }output<<endl;
    output.close();
}
void to_ascii_and_out(bitset<64> plaintext_64bit)
{
    for(int i=63;i>=0;i=i-8)
    {
        int number=0;
        for(int j=i;j>i-8;j--)
        {
            number+=(int)plaintext_64bit[j]*pow(2,(j%8));
        }
        cout<<(char)number;
    }cout<<endl;
}
char change_to_hex(int number)
{
    switch(number)
    {
        case 0:
        return '0';
        case 1:
        return '1';
        case 2:
        return '2';
        case 3:
        return '3';
        case 4:
        return '4';
        case 5:
        return '5';
        case 6:
        return '6';
        case 7:
        return '7';
        case 8:
        return '8';
        case 9:
        return '9';
        case 10:
        return 'A';
        case 11:
        return 'B';
        case 12:
        return 'C';
        case 13:
        return 'D';
        case 14:
        return 'E';
        case 15:
        return 'F';
    }
}
void to_hex_and_out(bitset<64> text_64bit)
{
    for(int i=63;i>=0;i=i-4)
    {
        int number=0;
        for(int j=i;j>i-4;j--)
        {
            number+=(int)text_64bit[j]*pow(2,(j%4));
        }
        cout<<change_to_hex(number);
    }cout<<endl;
}

int main()
{
    /*ifstream input;
    input.open("DES-Key-Ciphertext.txt");
    for(int i=0;i<6;i++)
    {
        string key_alphabet;
        string ciphertext_hex;
        input>>key_alphabet>>ciphertext_hex;
        alphabat_to_64(key_alphabet);
        create_16_keys();
        bitset<64> ciphertext=hex_to_binary(ciphertext_hex);
        bitset<64> plaintext_64=decrypt(ciphertext);
        to_ascii_and_fout(plaintext_64);
    }
    input.close();*/
    //encrypt
    system("cls");
    string key_alphabet="37198391";
    string plaintext="security";
    plaintext_to_64(plaintext);
    alphabat_to_64(key_alphabet);
    create_16_keys();
    bitset<64> ciphertext_64=encrypt(plaintext_text);
    to_hex_and_out(ciphertext_64);
    //decrypt
    string key__alphabet="37198391";
    string ciphertext="2badf07add648074";
    alphabat_to_64_key2(key__alphabet);
    create_16_keys_key2();
    bitset<64> ciphertext_binary=hex_to_binary(ciphertext);
    bitset<64> plaintext_64=decrypt(ciphertext_binary);
    to_ascii_and_out(plaintext_64);
    return 0;
}