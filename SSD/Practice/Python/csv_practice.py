import csv
path='missing.csv'
file = open(path,'r')
row=csv.reader(file)
header = next(file)
for line in row:
    try:
        part1=line[2].strip("'")
        part2=line[3].strip("'")
        partM=int(part1)*float(part2)
        print(partM)
    except (ValueError,AttributeError) as err:#exception handling just like java
        print("Bad data:",err)
        continue;
file.close()