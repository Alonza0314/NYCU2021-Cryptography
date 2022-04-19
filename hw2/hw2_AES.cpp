#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include "..\cryptopp860\osrng.h"
#include "..\cryptopp860\cryptlib.h"
#include "..\cryptopp860\hex.h"
#include "..\cryptopp860\filters.h"
#include "..\cryptopp860\des.h"
#include "..\cryptopp860\modes.h"
#include "..\cryptopp860\secblock.h"
#include "..\cryptopp860\aes.h"

using namespace std;
using namespace CryptoPP;

//CFB en
string cfb(string plaintext, byte key[], const byte iv[])
{
	string ciphertext;
	CFB_Mode<AES>::Encryption cfb_e;
	AlgorithmParameters params = MakeParameters(Name::FeedbackSize(), 4)(Name::IV(), ConstByteArrayParameter(iv, 16));
	cfb_e.SetKey(key, AES::DEFAULT_KEYLENGTH, params);

	StringSource en(plaintext, true, new StreamTransformationFilter(cfb_e, new StringSink(ciphertext)));
	string cipher_hex;
	StringSource(ciphertext, true,new HexEncoder(new StringSink(cipher_hex)));
	cout << cipher_hex << endl;
	return ciphertext;
}
//CFB de
void cfb_de(string ciphertext, byte key[], const byte iv[])
{
	string plaintext;
	CFB_Mode<AES>::Decryption cfb_d;
	AlgorithmParameters params = MakeParameters(Name::FeedbackSize(), 2)(Name::IV(), ConstByteArrayParameter(iv, 16));
	cfb_d.SetKey(key, AES::DEFAULT_KEYLENGTH, params);
	StringSource de(ciphertext, true, new StreamTransformationFilter(cfb_d, new StringSink(plaintext),BlockPaddingSchemeDef::ZEROS_PADDING));
	std::cout << plaintext << endl;
}
//CBC en
string cbc(string plaintext, byte key[], byte iv[], string padding)
{
	string ciphertext;
	CBC_Mode<AES>::Encryption cbc_e;
	cbc_e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	
	if (padding == "zero")
	{
		StringSource en(plaintext, true, new StreamTransformationFilter(cbc_e, new StringSink(ciphertext), BlockPaddingSchemeDef::ZEROS_PADDING));
	}
	else
	{
		StringSource en(plaintext, true, new StreamTransformationFilter(cbc_e, new StringSink(ciphertext), BlockPaddingSchemeDef::PKCS_PADDING));
	}
	string cipher_hex;
	StringSource(ciphertext, true, new HexEncoder(new StringSink(cipher_hex)));
	cout << cipher_hex << endl;
	return ciphertext;
}
//CBC de
void cbc_de(string ciphertext, byte key[], byte iv[], string padding)
{
	string plaintext;
	CBC_Mode<AES>::Decryption cbc_d;
	cbc_d.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	if (padding == "zero")
	{
		StringSource de(ciphertext, true, new StreamTransformationFilter(cbc_d, new StringSink(plaintext), BlockPaddingSchemeDef::ZEROS_PADDING));
	}
	else
	{
		StringSource de(ciphertext, true, new StreamTransformationFilter(cbc_d, new StringSink(plaintext), BlockPaddingSchemeDef::PKCS_PADDING));
	}
	cout << plaintext << endl;
}
//ECB en
string ecb(string plaintext, byte key[])
{
	string ciphertext;
	ECB_Mode<AES>::Encryption ecb_e;
	ecb_e.SetKey(key, AES::DEFAULT_KEYLENGTH);

	StringSource en(plaintext, true, new StreamTransformationFilter(ecb_e, new StringSink(ciphertext), BlockPaddingSchemeDef::PKCS_PADDING));
	string cipher_hex;
	StringSource(ciphertext, true, new HexEncoder(new StringSink(cipher_hex)));
	cout << cipher_hex << endl;
	return ciphertext;
}
//ECB de
void ecb_de(string ciphertext, byte key[])
{
	string plaintext;
	ECB_Mode<AES>::Decryption ecb_d;
	ecb_d.SetKey(key, AES::DEFAULT_KEYLENGTH);
	StringSource s(ciphertext, true,new StreamTransformationFilter(ecb_d,new StringSink(plaintext)));
	cout << plaintext << endl;
}
string hex_to_char(string cipher)
{
	string output;
	for (int i = 0; i < cipher.size(); i+=2)
	{
		int cal = 0;
		int number;
		switch (cipher[i])
		{
		case '0':number = 0;
				break;
		case '1':number = 1;
				break;
		case '2':number = 2;
				break;
		case '3':number = 3;
				break;
		case '4':number = 4;
				break;
		case '5':number = 5;
				break;
		case '6':number = 6;
				break;
		case '7':number = 7;
				break;
		case '8':number = 8;
				break;
		case '9':number = 9;
				break;
		case 'A':case 'a':number = 10;
				break;
		case 'B':case 'b':number = 11;
				break;
		case 'C':case 'c':number = 12;
				break;
		case 'D':case 'd':number = 13;
				break;
		case 'E':case 'e':number = 14;
				break;
		case 'F':case 'f':number = 15;
				break;
		default:
				break;
		}
		cal += number*16;
		switch (cipher[i+1])
		{
		case '0':number = 0;
			break;
		case '1':number = 1;
			break;
		case '2':number = 2;
			break;
		case '3':number = 3;
			break;
		case '4':number = 4;
			break;
		case '5':number = 5;
			break;
		case '6':number = 6;
			break;
		case '7':number = 7;
			break;
		case '8':number = 8;
			break;
		case '9':number = 9;
			break;
		case 'A':case 'a':number = 10;
			break;
		case 'B':case 'b':number = 11;
			break;
		case 'C':case 'c':number = 12;
			break;
		case 'D':case 'd':number = 13;
			break;
		case 'E':case 'e':number = 14;
			break;
		case 'F':case 'f':number = 15;
			break;
		default:
			break;
		}
		cal += number;
		/*switch (number)
		{
		case 0:
			output += "0000";
			break;
		case 1:
			output += "0001";
			break;
		case 2:
			output += "0010";
			break;
		case 3:
			output += "0011";
			break;
		case 4:
			output += "0100";
			break;
		case 5:
			output += "0101";
			break;
		case 6:
			output += "0110";
			break;
		case 7:
			output += "0111";
			break;
		case 8:
			output += "1000";
			break;
		case 9:
			output += "1001";
			break;
		case 10:
			output += "1010";
			break;
		case 11:
			output += "1011";
			break;
		case 12:
			output += "1100";
			break;
		case 13:
			output += "1101";
			break;
		case 14:
			output += "1110";
			break;
		case 15:
			output += "1111";
			break;
		default:
			break;
		}*/
		output += (char)cal;
	}
	return output;
}
int main()
{
	byte key[AES::DEFAULT_KEYLENGTH], iv_0[AES::BLOCKSIZE], iv_9[AES::BLOCKSIZE], key_[AES::DEFAULT_KEYLENGTH];
	memset(key, 0x00, AES::DEFAULT_KEYLENGTH);
	memset(iv_0, 0x00, AES::BLOCKSIZE);
	memset(iv_9, 0x00, AES::BLOCKSIZE);
	for (int i = 0; i < AES::BLOCKSIZE; i++)
	{
		iv_0[i] = '0';
		iv_9[i] = '9';
	}
	for (int i = 0; i < 10; i++)
	{
		char x;
		switch (i)
		{
		case 0:x =  '0';
			break;
		case 1:x = '1';
			break;
		case 2:x = '2';
			break;
		case 3:x = '3';
			break;
		case 4:x = '4';
			break;
		case 5:x = '5';
			break;
		case 6:x = '6';
			break;
		case 7:x = '7';
			break;
		case 8:x = '8';
			break;
		case 9:x = '9';
			break;
		default:
			break;
		}
		for (int j = 0; j < 10; j++)
		{
			char y;
			switch (j)
			{
			case 0:y = '0';
				break;
			case 1:y = '1';
				break;
			case 2:y = '2';
				break;
			case 3:y = '3';
				break;
			case 4:y = '4';
				break;
			case 5:y = '5';
				break;
			case 6:y = '6';
				break;
			case 7:y = '7';
				break;
			case 8:y = '8';
				break;
			case 9:y = '9';
				break;
			default:
				break;
			}
			string keytext = "00000000000000";
			keytext += x;
			keytext += y;
			string ci_text_cfb = "3342292597c67a1bcdb115ad51239dd636fe";
			for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++)
			{
				key[i] = keytext[i];
			}
			std::cout << "CFB_"<<i<<j<<":";
			cfb_de(hex_to_char(ci_text_cfb), key, iv_0);
		}
	}
	//string plaintext = "Hello World!";
	//string keytext = "0000000000000053";
	//string ci_text_cfb = "3342292597c67a1bcdb115ad51239dd636fe";
	//string ci_text_cbc_0 = "4C855D6317608F8DD39461E5BCC940B8";
	//string ci_text_cbc_9 = "06A8B91F6190636D72CA6590360BFB26";
	//string ci_text_ecb = "D523326C27EE0F2165C7696B36F2688E";
	/*for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++)
	{
		key[i] = keytext[i];
	}
	/*cout << "Encrypt:" << endl;
	cout << "CFB:";
	string cipher_cfb = cfb(plaintext, key, iv_0);
	cout << "CBC_0:";
	string cipher_cbc_0 = cbc(plaintext, key, iv_0, "zero");
	cout << "CBC_9:";
	string cipher_cbc_9 = cbc(plaintext, key, iv_9, "PKCS");
	cout << "ECB:";
	string cipher_ecb = ecb(plaintext, key);
	cout << endl;*/
	//std::cout << "Decrypt:" << endl;
	/*std::cout << "CFB:";
	cfb_de(hex_to_char(ci_text_cfb), key, iv_0);
	/*cout << "CBC_0:";
	cbc_de(hex_to_char(ci_text_cbc_0), key, iv_0, "zero");
	cout << "CBC_9:";
	cbc_de(hex_to_char(ci_text_cbc_9), key, iv_9, "PKCS");
	cout << "ECB:";
	ecb_de(hex_to_char(ci_text_ecb), key);*/
	//homework
	/*
	string plaintext_text = "AES is the US block cipher standard.";
	string keytext_text = "keyis84932731830";
	for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++)
	{
		key_[i] = keytext_text[i];
	}
	string cfb_ciphertext = cfb(plaintext_text, key_, iv_0);
	string cbc_0_ciphertext = cbc(plaintext_text, key_, iv_0, "zero");
	string cbc_9_ciphertext = cbc(plaintext_text, key_, iv_9,"PKCS");
	string ecb_ciphertext = ecb(plaintext_text, key_);
	fstream output;
	output.open("aes-out.txt",ios::app);
	for (int i = 0; i < cfb_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<byte>(cfb_ciphertext[i]));
	}output << endl;
	for (int i = 0; i < cbc_0_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<byte>(cbc_0_ciphertext[i]));
	}output << endl;
	for (int i = 0; i < cbc_9_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<byte>(cbc_9_ciphertext[i]));
	}output << endl;
	for (int i = 0; i < ecb_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<byte>(ecb_ciphertext[i]));
	}output << endl;
	output.close();*/
	return 0;
}