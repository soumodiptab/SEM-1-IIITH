path = 'weighted_score.csv'
file = open(path,'r')
header = next(file)
print(header)
for line in file:
    line=line.strip()#skips all the line spaces
    line=line.split(',')#converts the string into a list of records
    part1=line[2].strip("'")#removes the ' only from the begining and end
    part2=line[3].strip("'")
    print('First part: ',part1, 'Second part :',part2)
    partM=int(part1)*float(part2)
    print(line)
file.close()