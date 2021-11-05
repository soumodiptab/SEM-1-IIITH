argumentList = sys.argv
s = argumentList[1]
l = s.split()
l = sorted(l, key=lambda x: int(x))
ans = []
for i in l:
    try:
        ans.append(int(i))
    except:
        ans.append(float(i))
print(ans)
