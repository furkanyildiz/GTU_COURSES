'''
n number of 3, m number of 5 kabul edersek, girilen N degeri sayinin maksimum olabilmesi icin m e esit olmalidir.
fakat her zaman N, m ye esit oldugunda m%3=0 koşulu sağlanmaz, bu durumda ise m yi bir azaldır, n yi bir arttırır,
m%3 = 0 ve n%5=0 durumunu kontrol ederiz, bu durum sağlanana kadar m bir azaltılır, n bir arttırılır, sağlandığında
ise en büyük sayıyı ifade etmek icin doğru m n degerleri bulunmuş olur, döngü sonlandıgı ve bulunmadığı durumda ise
-1 return edilir.
'''

def find_n_m(N):
    for i in range(N,-1,-1):
        m = i
        n = N - m
        if n % 5 == 0 and m % 3 == 0:
            return n,m
    return -1, -1


def decentNumber (N):
    # n number of 3
    # m number of 5
    n,m = find_n_m(N)
    if n == -1:
        return -1
    else:
        return m * '5' + n* '3'


dn = decentNumber(1)
print(dn)
#Output: -1
dn = decentNumber(3)
print(dn)
#Output: 555
dn = decentNumber(5)
print(dn)
#Output: 33333
dn = decentNumber(11)
print(dn)
#Output: 55555533333