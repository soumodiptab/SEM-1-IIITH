
import re
import sys

input_string = sys.argv[1]
words = re.findall('[A-Z][^A-Z]*', input_string)
if(len(words) < 1):
    print(input_string)
    exit(0)
x = input_string.split(words[0])[0]
output_list = []
output_list.append(x.lower())
for i in words:
    output_list.append(" "+i.lower())
output_String = "".join(output_list)
print(output_String)
