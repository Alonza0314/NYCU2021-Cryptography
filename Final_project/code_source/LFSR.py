import random

#generate seed for lfsr avoid 00000
'''
產生lfsr的seed
5個bit 可修改
如果是00000就重新產生
'''
def generate_seed():
    seed=[]
    while True:
        for i in range(5):
            seed.append(random.randint(0,1))
        if seed!=[0,0,0,0,0]:
            break
    return seed

#lfsr
'''
調用lfsr()需要傳入一個n
n是你需要幾個bit
會回傳一個含有n個bit的list 包含0或是1
(每一個都是0和1都是string狀態)
這個list就是key會存在key.txt裡面
多次使用key會一行一行存下來
其中lfsr的更新為每10個bit產生後就會更新一次
'''
def lfsr(n):
    seed=generate_seed() 
    record_output=open('key.txt','a')
    return_key=[]
    for round in range(n):
        if round!=0 and n>10 and round%10==0:
            seed=generate_seed()
        new_bit=seed[4]^(seed[2]&seed[0])
        return_key.append(str(new_bit))
        if round==n-1:
            break
        for shift in range(4,-1,-1):
            if shift==0:
                seed[0]=new_bit
            else:
                seed[shift]=seed[shift-1]
    for i in range(n):
        record_output.write(return_key[i])
    record_output.write('\n')
    record_output.close()
    return return_key
    

#test LFSR.py
'''
結果會在key.txt裡面嘿~
'''
if __name__=='__main__':
    for i in range(1,54,2):
        if(i<27):
            temp=lfsr(i)
        else:
            temp=lfsr(54-i)