import sys
import os
import reduce_function

target_file= sys.argv[1]
input_file= sys.argv[2]
#p= float(sys.argv[3])
#sigma= float(sys.argv[4])
#answer= sys.argv[5]

inputFile_object= open(input_file, "r")
tempFile_object= open("temp", "w")

tempFile_object.writelines(inputFile_object.readlines())

tempFile_object.close()
inputFile_object.close()

n = 2
file_size = os.path.getsize('temp')

while file_size > 1 && file_size * 2 != n :
    if n > file_size:
        n = file_size
    
    len_list = reduce_function.split(file_size, n, sigma)
    

    if(reduce_function.substring(target_file, 'temp', n, len_list) == 'temp'):
        n = 2
        continue

    if(reduce_function.complement(target_file, 'temp', n, len_list) == 'temp'):
        n = 2
    
    file_size = os.path.getsize('temp')


