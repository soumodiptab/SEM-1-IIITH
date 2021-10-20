path = 'weighted_score.csv'
file = open(path,'r')
#data = file.read()
# print(data)
#each line is opened as a string
for line in file:
    line=line.strip()#skips all the line spaces
    line=line.split(',')#converts the string into a list of records
    print(line)
file.close()
# #incase you forget to close the file
# with open(path,'r') as filename:
#     data = filename.read()
# print(data)