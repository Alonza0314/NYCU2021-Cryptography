#map
'''
傳入都是1個bit(string)
回傳1個bit(string)
'''
def compute(key,plaintext):
    if (key=='0' and plaintext=='0') or (key=='1' and plaintext=='1'):
        return '0'
    else:
        return '1'
    
#xor computation
'''
key:list[string,string,sting,...] 僅有0跟1
plaintext:list[string,string,string,...] 僅有0跟1
return一個list(已經xor之後的東西,裡面是string的形態)
''' 
def xor(key,plaintext):
    return_list=[]
    for i in range(len(key)):
        return_list.append(compute(key[i],plaintext[i]))
    return return_list
    
#test xor_computation.py
'''
結果只會在終端機裡面喲~
plaintext是'GouDongXi'
key是lfsr隨機出來的~
'''
if __name__=='__main__':
    plaintext=['1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '0', '0', '1', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '1', '1', '0', '1', '1', '0', '0', '0', '1', '1', '0', '1', '0', '0', '1']
    key=['0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '1', '1', '1', '0', '1', '0', '1', '0', '0', '1', '0', '1', '0', '1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '0', '1', '1']
    temp=xor(key,plaintext)
    for i in range(len(temp)):
        print(temp[i],end='')
    print()