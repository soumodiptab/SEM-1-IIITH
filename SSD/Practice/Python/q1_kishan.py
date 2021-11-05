import sys
import re

sentence = sys.argv[1]

if sentence[0].islower():
    while sentence[0].islower():
        print({sentence[0]}, end="")
        sentence = sentence[1:]
        if len(sentence) == 0:
           exit(0)

word_list = re.findall('[A-Z][^A-Z]*', sentence)

for word in word_list:
    word = word.lower()
    print({word},end="")