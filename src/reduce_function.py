from numpy import random


def split (file_size, n, sigma):
    mean = file_size - n / n
    allot = random.normal(loc = mean, scale = sigma, size = n)
    sum_allot = 0
    len_list = list()
    for i = 0 in n - 1 :
        if allot[i] < 0 :
            allot[i] = 0
        else
            if round(allot[i], 0) + sum_allot > file_size - n :
                allot[i] = file_size - n - sum

        len_list.append(int(round(allot[i]),0))
        sum_allot = sum_allot +int(round(allot[i], 0))

    return len_list


def substring (target_file, input_file, n, len_list):
    f = open(input_file, 'r')
    data = f.read()
    f.close()
    
    data_list = list()
    for i in range(len(data)):
        data_list.append(i)
    
    used = set()
    for i in len_list:
        selection = random.sample(data_list, i)
        for j in range(i):
            while selection[j] in used:
                selection[j] = random.sample(data_list,1)
            
        selection.sort()
        substring = ""
        for j in range(i):
            index = selection[j]
            substring = substring + data[index]
        
        # execute target file with substring
        # if test() == fail
        #   return "substring"
        
    # return "temp"



    
def complement (target_file, input_file, n, len_list):
