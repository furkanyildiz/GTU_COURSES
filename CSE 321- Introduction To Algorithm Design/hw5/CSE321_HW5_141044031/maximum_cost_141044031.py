'''
Bir sayı dizisindeki farklar toplamı hesaplanırken, sayılardan herbirinin solundaki ve sağındaki sayı ile ilişkisi
önemli olduğundan 3'erli dolaşacağız sayı dizimizde. Yalnız bu şekilde gezdiğimizde son sayıyı ancak 2 önceki sayıyla
kıyaslamış olacağız bu yüzden son sayıya özel olarak, onu kendinden bir önceki sayıyla kıyaslayacağız. Yaptığımız
kıyaslamalar ise şu şekilde olacak, normal order: listedeki elemanların sırasının en güncel hali, i_to_one: i. index
deki elemanın 1 ile değiştirilmesi (1 ile değiştiriyoruz çünkü Xi <= Yi eşitsizliğini de dikkate aldığımızda 2 sayı
arasındaki fark, ya kendisiyle yada 1 ile maksimum olur. Son durum ise i_plus_1_to_one: i. değiştirdiğimizde, kendinden
bir önceki sayıyla maksimum farkı elde etmiş olabiliriz ama i+1 i kontrol ettiğimizde belki onların aralarındaki farkı
0 a dahi indirmiş olabilirz buda toplamımızı negatif etkiler, bu yüzden i+1. indexdeki elemanıda 1 ile değiştirerek
farkı ölçüyoruz ve maksimumu alıyoruz.

Worst Case Analizi:

Her durumda O(n) sürede çalışır.

'''


def find_maximum_cost(Y):

    if len(Y) <= 1:
        return sum(Y)

    X = Y.copy()

    for i in range(0,len(X)-1):
        #len(X)-3 e kadar 3 lü karşılaştırma yapılabilir
        if i > len(X) - 3:
            normal_order = abs(X[i] - X[i + 1])
            i_to_one = abs(1 - X[i + 1])
            i_plus_1_to_one = abs(X[i] - 1)

        else:
            normal_order = abs(X[i] - X[i + 1]) + abs(X[i + 1] - X[i + 2])
            i_to_one = abs(1 - X[i + 1]) + abs(X[i + 1] - X[i + 2])
            i_plus_1_to_one = abs(X[i] - 1) + abs(1 - X[i + 2])



        if normal_order  < i_to_one and i_to_one > i_plus_1_to_one:
            X[i] = 1
        if normal_order  < i_plus_1_to_one and i_plus_1_to_one >= i_to_one :
            X[i + 1] = 1


    i=len(X) - 3
    if abs(X[i+1] - X[i+2]) < abs(X[i+1] - 1) :
        X[i + 2] = 1

    #print(X)

    max_cost = 0
    for i in range(0,len(X)-1):
        max_cost = max_cost + abs(X[i] - X[i+1])
    return max_cost

Y = [80,22]
cost = find_maximum_cost(Y)
print(cost) #79
Y = [22,80]
cost = find_maximum_cost(Y)
print(cost) #79

Y = [80,22,45,11,67,67,74,91,4,35,34,65,80,21,95,1,52,25,31,2,53]
cost = find_maximum_cost(Y)
print(cost) #1107

Y = [79,6,40,68,68,16,40,63,93,49,91]
cost = find_maximum_cost(Y)
print(cost) #642

Y = [14,1,14,1,14]
cost = find_maximum_cost(Y)
print(cost)
#Output: 52
Y = [1,9,11,7,3]
cost = find_maximum_cost(Y)
print(cost)
#Output: 28
Y = [50,28,1,1,13,7]
cost = find_maximum_cost(Y)
print(cost)
#Output: 78

Y =  [1, 9, 111, 7, 3]
cost = find_maximum_cost(Y)
print(cost)
#Output: 222