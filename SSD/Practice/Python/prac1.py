import pprint
# message = "Sun rises in the east"
# count={}
# for character in message:
#     count.setdefault(character,0)
#     count[character]=count[character]+1
# #pprint.pprint(count)
# print(count)
batch_size = [
    {
        'name':'college_X',
        'size':[20,50,60,45]
    },
    {
        'name':'college_Y',
        'size':[56,23,34,78,67]
    }
]
print(sum(batch_size[0]['size']))
#nested dictionary ex:
result = {'Ryuzin':{'maths':80,'english':75},'Karuizawa':{'maths':92,'english':85}}
# pprint.pprint(result)
for k,v in result.items():
    for value in v.values():
        print(value)