#DNA table
'''
傳入兩個bit
然後回傳ATCG其中一個
'''
from sympy import appellf1


def dna_table(first,second):
    if first=='0' and second=='0':
        return 'A'
    elif first=='0' and second=='1':
        return 'G'
    elif first=='1' and second=='0':
        return 'C'
    else:
        return 'T'
    
#transform bit to ATCG
'''
傳入一個list
裡面形態是string
但是都是0跟1
回傳一個list
裡面是ATCG
如果傳入的不是偶數長度的就在最後補一個'0'
會同時把結果存到cyphertext.txt
'''
def dna(after_xor_list):
    if len(after_xor_list)%2!=0:
        after_xor_list.append('0')
    return_list=[]
    for i in range(0,len(after_xor_list),2):
        return_list.append(dna_table(after_xor_list[i],after_xor_list[i+1]))
    cyphertext_output=open('cypher.txt','a')
    for i in range(len(return_list)):
        cyphertext_output.write(return_list[i])
    cyphertext_output.write('\n')
    cyphertext_output.close()
    return return_list
        
#test DNA.py
'''
'''
if __name__=='__main__':
    after_xor_list=['1', '1', '1', '0', '1', '1', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '0', '0', '0', '1', '0']
    temp=dna(after_xor_list)
    for i in range(len(temp)):
        print(temp[i],end='')
    print