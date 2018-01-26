#yardım alındı, http://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/

'''
Bu fonksiyon buyuk olan her zaman arr2 gibi islem yapacagından oncelıkle arr1'ın boyutu daha kucuk ıse, arr1 ile
arr2 yi swap etmek icin fonksiyonu tersten cagırır. Ardından arr1 in eleman sayısının 0 olması durumunda cozumunuz
direk arr2'nin k-1. indexindeki elemandır. (Ilk swapı yapmamız sayesinde, arr2'nin boyutunun sıfır olmasını kontrol
etmemize gerek kalmadı.) Aradığımız k. en kücük elemanın 1. en kücük eleman olma durumunda ise yine çözümümüz basit,
sadece arr1 ve arr2 'nin 0. indexlerinden kücük olanı return etmektir. Diğer durumlarda ise olay biraz daha komplex
hale geliyor, k. en kücügü bulmamız icin listemizi kucultmemız gerekiyor, bunu yapmak icin ise oncelikle 1. ve 2.
arrayin boyutlarını k/2 ile karsılastırıyor ve kucuk olanları alıyoruz. Daha sonra bu aldıgımız degeri arraylerde
karsılastırma indexi olarak kullanacagız. Bu indexlerdeki degerleri karsılastırdıgımızda arr1 deki daha buyukse,
arr1'i komple arr2'yi ise o indexden itibaren alıyoruz ve fonksiyonumuzu tekrar çağırıyoruz ancak bu çağırmayı yaparken
k. eleman için degilde k-(o index) olarak yapıyoruz ki bölünmüş arrayler üzerinden doğru bir şekilde devam edebilelim.
arr2 deki daha büyükse ise tam tersini yapıyoruz, arr1'i o indexten itibaren alıyor ve arr2yi tamamen alıyoruz ve
fonksiyonumuzu tekrar cağırıyoruz ta ki k == 1 olana kadar, bu durumdada zaten 2 arrayin 0. indexlerini karsılastırmamız
yeterli olacaktı.

'''
def find_kth_book_2(arr1, arr2, k):

    if k > len(arr1) + len(arr2) or k < 1:
        raise IndexError('Index Out Of Range')
    if len(arr1) > len(arr2):
        return find_kth_book_2(arr2, arr1,k)
    if len(arr1) == 0:
        return arr2[k-1]
    if k == 1:
        return min(arr1[0], arr2[0])

    i = min(len(arr1),k//2)
    j = min(len(arr2), k//2)

    if arr1[i-1] > arr2[j-1]:
        return find_kth_book_2(arr1,arr2[j::],k-j)
    else:
        return find_kth_book_2(arr1[i::],arr2,k-i)




m = ["algotihm", "programminglanguages", "systemsprogramming"]
n = ["computergraphics", "cprogramming","oop"]

arr1 = [1, 5, 6, 7 , 8, 9, 13,15];
arr2 = [2, 3, 4, 10, 11,12,14,16,17];
k = 17
book = find_kth_book_2(arr1,arr2,k)
print(book)

book = find_kth_book_2(m,n,4)
print(book)
#Output: programminglanguages
book = find_kth_book_2(m,n,6)
print(book)
#Output: systemsprogramming