#yardım alındı, http://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/

'''

arr1 'in boyutu 0 oldugunda, arr2'nin k-1. indexindeki eleman en kucuk k. eleman olacaktır. Aynı şey arr2 icinde gecerli.
Bu durumu base case olarak kabul ederek bir recursion algoritma yazıldı. Bu algoritma listenin ortadaki elemanlarını
karsılastırarak listeleri boluyor ta ki listelerden birisi 0 elemana ulasıncaya kadar, bir liste 0 elemana ulastıgında
ise cozumu zaten bılıyoruz. Calısma mantıgı binary searche benzer sekildedir.

Aranan k. eleman listelerin ortalarındaki indexlerin toplamından kucukse listerden birisi sag taraftan kesilmelidir
cunku k sagdakilerle ilgilenemeyecek kadar kucuktur.

Aranan k. eleman listelerin ortalarındaki indexlerin toplamından buyukse listelerden birisi sol taraftan kesilmelidir
cunku k soldakilerle ilgilenmeyecek kadar buyuktur.

Kesilmeler ise arraylerin ortalarındaki elemanları kıyaslayarak yapılmaktadır.

'''

def find_kth_book_1(arr1, arr2, k):
    if k < 1:
        raise IndexError('Index Out Of Range')
    if len(arr1) == 0 :
        return arr2[k-1]
    if len(arr2) == 0 :
        return arr1[k-1]

    mid1 = len(arr1) // 2
    mid2 = len(arr2) // 2

    if mid1 + mid2 < k-1 :

        if arr1[mid1] > arr2[mid2]:
            return find_kth_book_1(arr1,arr2[mid2+1::],k-mid2-1)
        else:
            return find_kth_book_1(arr1[mid1+1::], arr2, k-mid1-1)

    else:
        if arr1[mid1] > arr2[mid2]:
            return find_kth_book_1(arr1[:mid1],arr2,k)
        else:
            return find_kth_book_1(arr1,arr2[:mid2],k)



arr1 = [2, 3, 6, 7, 9, 11, 12];
arr2 = [1, 4, 5, 8, 10];
k = 11;
print(find_kth_book_1(arr1, arr2, k ));

m = ["algotihm", "programminglanguages", "systemsprogramming"]
n = ["computergraphics", "cprogramming","oop"]

arr1 = [1, 5, 6];
arr2 = [2, 3, 4];
book = find_kth_book_1(arr1,arr2,3)
print(book)

book = find_kth_book_1(m,n,4)
print(book)
#Output: oop
book = find_kth_book_1(m,n,6)
print(book)
#Output: systemsprogramming












