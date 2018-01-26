'''

Hırsız, paraları toplamaya ilk columndan herhangibir rowu seçerek başlayacak,ilk columnda herhangibir yeri
seçmesiyle, elde edeceği para aynı. Bu sebeple cost matrix i oluşturulurken, ana matriximizin ilk columunu aynen
yerleştiriyoruz. (Bunu yaparken daha kolay yapabilmek için transpoze aldım) Daha sonra hırsızın maksimum parayla
ayrılabilmesi için diğer columnların değerlerinden maksimum olanı seçmesi lazım, bu yüzden sırasıyla diğer columnları
oluştururken, columun ilgili rowuna nereden gelebileceğine bakılır ve buraya en yüksek ne kadar para ile gelebiliyorsa
ilgili column ve ilgili rowdaki değer o maksimum değer olur. Bu şekilde tüm columlar doldurulduktan sonra, en son column
hırsızın oradaki değer olan para miktarı ile çıkış yapabileceği noktalardır, bunlardan maksimumunu return ettiğimizde
hırsızın en çok ne kadar para ile çıkabileceğini göstermiş oluruz.

Worst Case Analizi:
Algoritma her durumda O(n*m) karmaşıklıkta çalışır.
n:column sayısı
m:row sayısı

'''

def theft(matrix):
    row_len = len(matrix)
    col_len = len(matrix[0])

    matrisT = list(map(list, zip(*matrix))) #traspoze of matrix

    cost_matris = row_len * [ col_len  * [-1] ]


    for i in range(row_len):
        cost_matris[0][i] =  matrisT[0][i]

    cost_matris = list(map(list, zip(*cost_matris))) #traspoze of cost_matris


    for col in range(1,col_len):
        for row in range(0,row_len):
            if row == 0:
                cost_matris[row][col] = max(cost_matris[row][ col-1],cost_matris[row+1][ col-1]) + matrix[row][col]
            elif row == row_len -1 :
                cost_matris[row][ col] = max(cost_matris[row][ col-1],cost_matris[row-1][ col-1]) + matrix[row][col]
            else:
                cost_matris[row][ col] = max(cost_matris[row-1][ col-1],cost_matris[row][ col-1],cost_matris[row+1][ col-1]) + matrix[row][col]

    #print(cost_matris)
    return max([row[col_len-1] for row in cost_matris])

amountOfMoneyInLand= [[1,3,1,5], [2,2,4,1], [5,0,2,3], [0,6,1,2]]
res = theft(amountOfMoneyInLand)
print(res)
#Output: 16
amountOfMoneyInLand= [[10,33,13,15], [22,21,4,1], [5,0,2,3], [0,6,14,2]]
res = theft(amountOfMoneyInLand)
print(res)
#Output: 83