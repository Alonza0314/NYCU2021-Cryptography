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

//CFB
string cfb(string plaintext, CryptoPP::byte key[], const CryptoPP::byte iv[])
{
	string ciphertext;
	CFB_Mode<AES>::Encryption cbf_e;
	AlgorithmParameters params = MakeParameters(Name::FeedbackSize(), 4)(Name::IV(), ConstByteArrayParameter(iv, 16));
	cbf_e.SetKey(key, AES::DEFAULT_KEYLENGTH, params);

	StringSource en(plaintext, true, new StreamTransformationFilter(cbf_e, new StringSink(ciphertext)));
	return ciphertext;
}
//CBC
string cbc(string plaintext, CryptoPP::byte key[], CryptoPP::byte iv[], string padding)
{
	string ciphertext;
	CBC_Mode<AES>::Encryption cbc_e;
	cbc_e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	
	if (padding == "zero")
	{
		StringSource en(plaintext, true, new StreamTransformationFilter(cbc_e, new StringSink(ciphertext), BlockPaddingSchemeDef::ZEROS_PADDING));
		return ciphertext;
	}
	else
	{
		StringSource en(plaintext, true, new StreamTransformationFilter(cbc_e, new StringSink(ciphertext), BlockPaddingSchemeDef::PKCS_PADDING));
		return ciphertext;
	}
}
//ECB
string ecb(string plaintext, CryptoPP::byte key[])
{
	string ciphertext;
	ECB_Mode<AES>::Encryption ecb_e;
	ecb_e.SetKey(key, AES::DEFAULT_KEYLENGTH);

	StringSource en(plaintext, true, new StreamTransformationFilter(ecb_e, new StringSink(ciphertext), BlockPaddingSchemeDef::PKCS_PADDING));
	return ciphertext;
}
void print_out(string ciphertext)
{
	for (int i = 0; i < ciphertext.size(); i++)
	{
		cout << setfill('0') << setw(2) <<  hex << (0xff & static_cast<CryptoPP::byte>(ciphertext[i]));
	}cout << endl;
}
int main()
{
	CryptoPP::byte key[AES::DEFAULT_KEYLENGTH], iv_0[AES::BLOCKSIZE], iv_9[AES::BLOCKSIZE], key_[AES::DEFAULT_KEYLENGTH];
	memset(key, 0x00, AES::DEFAULT_KEYLENGTH);
	memset(iv_0, 0x00, AES::BLOCKSIZE);
	memset(iv_9, 0x00, AES::BLOCKSIZE);
	for (int i = 0; i < AES::BLOCKSIZE; i++)
	{
		iv_0[i] = '0';
		iv_9[i] = '9';
	}
	string plaintext_text = "AES is the US block cipher standard.";
	string keytext_text = "keyis84932731830";
	string plaintext = "Hello World!";
	string keytext = "1234567890ABCDEF";
	for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++)
	{
		key[i] = keytext[i];
		key_[i] = keytext_text[i];
	}

	cout << "CFB:";
	print_out(cfb(plaintext, key, iv_0));
	cout << "CBC_0:";
	print_out(cbc(plaintext, key, iv_0, "zero"));
	cout << "CBC_9:";
	print_out(cbc(plaintext, key, iv_9, "PKCS"));
	cout << "ECB:";
	print_out(ecb(plaintext, key));
	/*string encoded, cipher = ecb(plaintext, key, "PKCS");
	encoded.clear();
	StringSource(cipher, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); cout << encoded << endl;
	cout << "ECB:";*/
	string cfb_ciphertext = cfb(plaintext_text, key_, iv_0);
	string cbc_0_ciphertext = cbc(plaintext_text, key_, iv_0, "zero");
	string cbc_9_ciphertext = cbc(plaintext_text, key_, iv_9,"PKCS");
	string ecb_ciphertext = ecb(plaintext_text, key_);
	fstream output;
	output.open("aes-out.txt",ios::app);
	for (int i = 0; i < cfb_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<CryptoPP::byte>(cfb_ciphertext[i]));
	}output << endl;
	for (int i = 0; i < cbc_0_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<CryptoPP::byte>(cbc_0_ciphertext[i]));
	}output << endl;
	for (int i = 0; i < cbc_9_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<CryptoPP::byte>(cbc_9_ciphertext[i]));
	}output << endl;
	for (int i = 0; i < ecb_ciphertext.size(); i++)
	{
		output << setfill('0') << setw(2) << hex << (0xff & static_cast<CryptoPP::byte>(ecb_ciphertext[i]));
	}output << endl;
	output.close();
	return 0;
}