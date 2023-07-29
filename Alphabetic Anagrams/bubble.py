
def bubble(word):
    word = [c for c in word]
    n = len(word)
    swaps = 0
    swapped = True
    while swapped:
        swapped = False
        for i in range(1,n):
            if word[i-1] > word[i]:
                tmp = word[i]
                word[i] = word[i-1]
                word[i-1] = tmp
                swaps+=1
                swapped = True
    return swaps + 1

def sorted(word):
    word = [c for c in word]
    word.sort()
    return ''.join(word)

def brute(word):
    n = len(word)
    w = [c for c in word]
    ws = [c for c in sorted(w)]
    ctr = 0
    for i in reversed(range(n-1)):
        tw = [c for c in ws]
        for j in range(i,n-1):
            print("i:{}, j:{}".format(i,j))
            tmp = tw[j]
            tw[j] = tw[j+1]
            tw[j+1] = tmp
            print(tw)
            ctr+=1
            if tw == w:
                return ctr



#print(brute("ABAB"))
#print(brute("BAAA"))
print(brute("QUESTION"))
#print(brute("BOOKKEEPER"))
