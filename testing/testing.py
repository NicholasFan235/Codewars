import random

#random.seed(1)
A = [random.randint(-100,100) for i in range(20)]


def find_smallest_int(arr):
    best = arr[0]
    for n in range(1,len(arr)):
        if arr[n] < best:
            best = arr[n]
    return best



print(find_smallest_int(A))