import sys
file_name = sys.argv[1]+"result_wc"
f = open(file_name,'r')

minimum=sys.maxsize
maximum=0
count=0
total=0

min_list=[]
max_list=[]

while True :
    line = f.readline()
    word = line.split()
    num = int(word[0])
    if word[1] == "total" :
        total = num
        break

    if (num < minimum):
        minimum = num
        min_list.clear()
        min_list.append(word[1])

    if (num == minimum):
        min_list.append(word[1])

    if (num > maximum):
        maximum = num
        max_list.clear()
        max_list.append(word[1])

    if (num == maximum):
        max_list.append(word[1])

    total=total+num
    count=count+1

print("minimum : ", minimum)
print("minimum file : ", min_list[0])
print("average : ", total / count)
print("maximum : ", maximum)
print("maximum file : ", max_list[0])
f.close()
