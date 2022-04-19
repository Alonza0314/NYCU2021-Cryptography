#pragma GCC optimization("0fast");
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<exception>
#include<cmath>
#include"..\cryptopp860\rsa.h"
#include"..\cryptopp860\sha.h"
#include"..\cryptopp860\filters.h"
#include"..\cryptopp860\files.h"
#include"..\cryptopp860\osrng.h"
#include"..\cryptopp860\SecBlock.h"
#include"..\cryptopp860\cryptlib.h"

using namespace std;
using namespace CryptoPP;

int main()
{
	/*fstream output;

	//Problem 1-128
	Integer n1("0x04823f9fe38141d93f1244be161b20f"), e1("0x11");
	RSA::PublicKey pk1;
	pk1.Initialize(n1, e1);
	string message1 = "Hello World!";
	Integer m1((const byte*)message1.data(), message1.size());
	Integer c1 = pk1.ApplyFunction(m1);
	output.open("out.txt", ios::app);
	output << hex << c1 << "\n";
	output.close();
	//Problem 1-256
	Integer n2("0x9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9"), e2("0x10001");
	RSA::PublicKey pk2;
	pk2.Initialize(n2, e2);
	string message2 = "RSA is public key.";
	Integer m2((const byte*)message2.data(), message2.size());
	Integer c2 = pk2.ApplyFunction(m2);
	output.open("out.txt", ios::app);
	output << hex << c2 << "\n";
	output.close();*/
	//Problem 3
	/*Integer n3("0xc4b361851de35f080d3ca7352cbf372d"), e3("0x1d35"), c3("0xa02d51d0e87efe1defc19f3ee899c31d");
	string decrypt = "0x53a0a95b089cf23adb5cc73f07XXXXX";
	char to_hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	RSA::PrivateKey pv;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				for (int l = 0; l < 16; l++)
				{
					for (int m = 0; m < 16; m++)
					{
						decrypt[decrypt.length() - 1] = to_hex[m];
						decrypt[decrypt.length() - 2] = to_hex[l];
						decrypt[decrypt.length() - 3] = to_hex[k];
						decrypt[decrypt.length() - 4] = to_hex[j];
						decrypt[decrypt.length() - 5] = to_hex[i];
						Integer d3(decrypt.c_str());
						Integer r3 = a_exp_b_mod_c(c3, d3, n3);
						size_t req = r3.MinEncodedSize();
						string plaintext;
						plaintext.resize(req);
						r3.Encode((byte*)plaintext.data(), plaintext.size());
						//cout << i << " " << j << " " << k << " " << l << " " << m << " plaintext:" << plaintext << endl;
						int flag = 1;
						for (int n = 0; n < plaintext.length(); n++)
						{
							if (plaintext[n] < 32 || plaintext[n]>127 || plaintext[n] == 47)
							{
								flag = 0;
								break;
							}
						}
						if (flag)
						{
							output.open("out.txt", ios::app);
							output << to_hex[i] << to_hex[j] << to_hex[k] << to_hex[l] << to_hex[m] << endl;
							output << plaintext << "\n";
							output.close();
							//system("pause");
						}
					}
				}
			}
		}
	}*/
	Integer n("253963006250652707627402859040685100389"), e("65537"), d("42772482296155483517134936268603049473");
	string c = "3163916997447552524836610353353193934X";
	char dec[10] = { '0','1','2','3','4','5','6','7','8','9' };
	RSA::PrivateKey PrivKey;
	for (int i = 0; i < 10; i++) {
		c[c.length() - 1] = dec[i];
		Integer c_int(c.c_str());
		Integer plaintext_int = a_exp_b_mod_c(c_int, d, n);
		size_t req = plaintext_int.MinEncodedSize();
		string plaintext;
		plaintext.resize(req);
		plaintext_int.Encode((byte*)plaintext.data(), plaintext.size());
		int count = 0;
		cout << plaintext << endl;
		cout << plaintext_int << endl;
	}
	return 0;


	
	
	
	
	
	
	
	
	
	/*
	45032603503400789370087526392904881963

824132021141*/
}
