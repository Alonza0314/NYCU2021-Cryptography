#transform the alphabet to binary
'''
傳入string-plaintext
回傳一個list
同時把plaintext存在plaintext.txt裡面
'''
def trans_plaintext(plaintext):
    plaintext_output=open('plaintext.txt','a')
    plaintext_output.write(plaintext)
    plaintext_output.write('\n')
    plaintext_output.close()
    cyphertext_list=list(plaintext)
    return_list=[]
    for alphabet in cyphertext_list:
        temp_list=list(str(format(ord(alphabet),'b')))
        for element in temp_list:
            return_list.append(element)
    return return_list
    
    
#test transform_plaintext.py
'''
結果會在終端機裡面嘿~
plaintext.txt裡面也會有plaintext
記得去看~
'''
if __name__=='__main__':
    temp_list=trans_plaintext('GouDongXi')
    for i in range(len(temp_list)):
        print(temp_list[i],end='')
    print()