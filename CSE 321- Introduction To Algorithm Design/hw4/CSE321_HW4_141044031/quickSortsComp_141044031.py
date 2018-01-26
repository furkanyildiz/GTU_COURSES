#ref: http://www.wikizero.org/index.php?q=aHR0cHM6Ly9lbi53aWtpcGVkaWEub3JnL3dpa2kvUXVpY2tzb3J0
'''

Hoare partition, Lomuto Partitiona göre tüm elemanları eşit olan listelerde daha iyidir.
Hoare partition, Lomuto Partitiona göre daha verimlidir cunku ortalama olarak 3 kat daha az swap islemini gerceklestirir.
İki partitionda stable sort üretmez.
İki partitionda Quicksortu O(n'2) ye dusurtebilir.

'''


def LomutoPartition(array, low, high):
    pivot = array[high]
    i = low

    for j in range(low,high):
        if array[j] <= pivot:
            array[i], array[j] = array[j], array[i]
            i = i + 1
    array[i], array[high] = array[high], array[i]
    return i



def HoarePartition(array, low, high):
    pivot = array[low]
    #Bu partitionda arrayin en uc noktalarından baslanır
    i = low - 1
    j = high + 1
    while True:
        while True:
            i = i +1
            if(array[i] >= pivot):
                break

        while True:
            j = j - 1
            if(array[j] <= pivot):
                break

        if i>= j:
            return j

        array[i], array[j] = array[j], array[i]



def quickSortHoare(array):
    quickSortH(array,0,len(array)-1)
    return array


def quickSortH(array,low,high) :

    if low < high :
        index_of_pivot = HoarePartition(array,low,high)

        quickSortH(array,low,index_of_pivot)
        quickSortH(array,index_of_pivot +1 ,high)

def quickSortLomuto(array):
    quickSortL(array,0,len(array)-1)
    return array

def quickSortL(array,low,high) :

    if low < high :
        index_of_pivot = LomutoPartition(array,low,high)

        quickSortH(array,low,index_of_pivot)
        quickSortH(array,index_of_pivot +1 ,high)


arr = [15,4,68,24,75,16,42]

qsh = quickSortHoare(arr)
print(qsh)
#Output: [4, 15, 16, 24, 42, 68, 75]
qsl = quickSortLomuto(arr)
print(qsl)
#Output: [4, 15, 16, 24, 42, 68, 75]