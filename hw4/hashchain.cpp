#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>
#include"..\cryptopp860\files.h"
#include"..\cryptopp860\hex.h"
#include"..\cryptopp860\sha.h"
#include"..\cryptopp860\filters.h"
using namespace std;
using namespace CryptoPP;

char to_char[16] = { '0', '1', '2', '3', '4' , '5', '6' ,'7' , '8', '9' , 'A', 'B', 'C', 'D', 'E', 'F' };

int main()
{
	fstream out;

	string message = "109550130";
	string digest, prev;

	SHA256 hash;
	hash.Update((const byte*)message.data(), message.size());
	digest.resize(hash.DigestSize());
	hash.Final((byte*)&digest[0]);

	StringSource(digest, true, new HexEncoder(new StringSink(prev)));
	string temp0, temp1, nonce = "00000000";
	string output, hv0, hv1;

	int flag;
	output = "";
	temp0 = "";
	temp1 = "";
	hv0 = "";
	hv1 = "";

	StringSource(nonce, true, new HexDecoder(new StringSink(temp0)));
	StringSource(prev, true, new HexDecoder(new StringSink(temp1)));
	cout << 0 << "\n" << prev << "\n" << nonce << "\n";
	out.open("out.txt", ios::app);
	//out << 0 << "\n" << prev << "\n" << nonce << "\n";
	out.close();
	prev = "";
	hv0 = temp1 + temp0;

	hash.Update((const byte*)hv0.data(), hv0.size());
	hv1.resize(hash.DigestSize());
	hash.Final((byte*)&hv1[0]);

	StringSource(hv1, true, new HexEncoder(new StringSink(output)));
	cout << output << "\n";
	out.open("out.txt", ios::app);
	//out << output << "\n";
	out.close();
	prev = "000000035D99F5883C2E666C08F0F5CA0D7702B0BFACBB3ACD48632EF11ACD01";

	for (int times = 7; times < 9; times++)
	{
		cout << times << "\n" << prev << "\n";
		out.open("out.txt", ios::app);
		//out << times << "\n" << prev << "\n";
		out.close();
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					for (int l = 0; l < 16; l++)
					{
						for (int m = 0; m < 16; m++)
						{
							for (int n = 0; n < 16; n++)
							{
								for (int o = 0; o < 16; o++)
								{
									for (int p = 0; p < 16; p++)
									{
										flag = 0;
										nonce[0] = to_char[i];
										nonce[1] = to_char[j];
										nonce[2] = to_char[k];
										nonce[3] = to_char[l];
										nonce[4] = to_char[m];
										nonce[5] = to_char[n];
										nonce[6] = to_char[o];
										nonce[7] = to_char[p];
										cout << nonce << endl;
										output = "";
										temp0 = "";
										temp1 = "";
										hv0 = "";
										hv1 = "";
										StringSource(nonce, true, new HexDecoder(new StringSink(temp0)));
										StringSource(prev, true, new HexDecoder(new StringSink(temp1)));

										hv0 = temp1 + temp0;

										hash.Update((const byte*)hv0.data(), hv0.size());
										hv1.resize(hash.DigestSize());
										hash.Final((byte*)&hv1[0]);

										StringSource(hv1, true, new HexEncoder(new StringSink(output)));

										while (output[flag] == '0')
										{
											flag++;
										}
										if (flag == times)
										{
											break;
										}
									}
									if (flag == times)
									{
										break;
									}
								}
								if (flag == times)
								{
									break;
								}
							}
							if (flag == times)
							{
								break;
							}
						}
						if (flag == times)
						{
							break;
						}
					}
					if (flag == times)
					{
						break;
					}
				}
				if (flag == times)
				{
					break;
				}
			}
			if (flag == times)
			{
				break;
			}
		}
		prev = "";
		prev = output;
		cout << nonce << "\n" << output << "\n";
		out.open("out.txt", ios::app);
		//out << nonce << "\n" << output << "\n";
		out.close();
	}
	return 0;
}