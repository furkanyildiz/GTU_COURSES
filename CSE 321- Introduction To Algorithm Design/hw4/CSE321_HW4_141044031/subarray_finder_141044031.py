'''

Verilen arrayin önce left ve right en kücük sub arraylerini buluyoruz ancak bu yeterli degil buna ek olarak birde
ortanca elemanları kapsayarak olusturabilecegimiz en kücük sub arrayi arıyoruz bu arrayide bulduktan sonra
buldugumuz toplam 3 arrayi karsılastırdıgımızda bunların en kücügü aradıgımız minimum sub arraydir.
Detaydan kısaca bahsedecek olursak, arrayi kucultmek icin arrayin kopyası ile bölmek yerine, high ve low indexleri
kullanıldı. Left ve right sub arrayleri bulmak icin arrayimizi 2 ye bölüyoruz sol taraftan min left sub arrayi
saü taraftan ise right sub arrayi buluyoruz ardından, ortancaları kontorl ediyoruz yani ornegin,
left sub array = [-13, 9, 23, -1] ise -1' yi iceren tum sub arraylerden en kucuk olanını seciyoruz bu bizim
min_left_sum_arr 'imiz oluyor
right sub array = [-81, 4, -7, 7] ise -81'i iceren tum sub arraylerden en kucuk olanını seciyoruz buda bizim
min_right_sum_arr 'imiz oluyor
daha sonra min_left_sum_arr ve min_right_sum_arr i concat ediyoruz (birlestirme)
olusan bu 3. arrayle diğer iki arrayi (left sub array ve right sub array) i kıyaslıyoruz en kucuk olan bizim çözümümüzdür.

Worst Case Analiz: Listeyi ortadan itibaren soldan ve sagdan ayırarak arrayler elde etmemiz T(n/2) + T(n/2), bu arraylerden en kucuk
toplama sahip arrayi bulmamız ise yine left ve right icin n/2 + n/2 dir.
T(n) = 2T(n/2)+ n  = O(nlogn) dir.


'''


def sums(listes):
    sum = 0
    for liste in listes:
        if type(liste) == list:
            sum = sum  + sums(liste)
        else:
            sum = sum + liste
    return sum

def find_min_arr(listes):
    min = listes[0]
    min_val = sums(min)
    for liste in listes[1::]:
        val = sums(liste)
        if val < min_val:
            min = liste

    return min

def min_subarray_finder_helper(array, low, high):

    # len arr == 1
    if low == high:
        return [array[low]]

    mid = low + (high - low) // 2

    left_min_array = min_subarray_finder_helper(array ,low ,mid)
    right_min_array = min_subarray_finder_helper(array , mid +1 ,high)

    left_sum_arr = []
    A = array[: mid +1]
    for i in range(len(A)):
        left_sum_arr.append(A[len(A) - i -1:])

    min_left_sum_arr = find_min_arr(left_sum_arr)

    right_sum_arr = []

    A = array[mid + 1::]
    for i in range(len(A)):
        right_sum_arr.append(A[:i + 1])

    min_right_sum_arr = find_min_arr(right_sum_arr)


    A = min_left_sum_arr + min_right_sum_arr

    if min(sum(left_min_array), sum(right_min_array)) == sum(left_min_array):
        ans = left_min_array
    else:
        ans = right_min_array

    if min(sum(ans), sum(A)) == sum(ans):
        return ans
    else:
        return A



def min_subarray_finder(array):
    return min_subarray_finder_helper(array, 0, len(array) - 1)


inpArr = [1, -4, -7, 5, -13, 9, 23, -1]  # [-4, -7, 5, -13]
# inpArr = [-1, -4, -7, 5, -13, 9, 23, -1]
# inpArr = [-13, 9, 23, -1,-81, 4, -7, 7] # [ -1, -81, 4 , -7 ]
# inpArr = [-13, 9, 23, -1] #[-13]
# inpArr = [-81, 4, -7, 7] #[-81, 4, -7]

#inpArr = [-7, -1, 3, -10, 8, -40]

msa = min_subarray_finder(inpArr)
print(msa)
# Output: [-4, -7, 5, -13]
print(sum(msa))
# Output: -19