#http://www.geeksforgeeks.org/longest-common-prefix-set-3-divide-and-conquer/

'''

Oncelikle iki stringin commonlarını veren bir fonksiyon yazdım, bu fonksiyonda once gelen stringlerin boylarını,
kucuk olana gore esitliyorum ardından, iki stringi postfix karsilastiracagimizdan, stringleri ters cevirip,
zipliyorum boylece iki stringin elemanlarını sondan basa dogru bir for dongüsüyle karşılaştırabilme
yetenegine sahip oluyorum ve bu yetenegi kullanarak stringlerin letterleri esit oldukca baska bir stringe atıyorum,
esitligin bozuldugu an donduden cıkıyorum ve sondan baktıgım ıcın common stringini ters cevirip yolluyorum.

longest_common_postfix fonksiyonunda ise, recursion yapabilmek icin wrapper fonksiyon kullandım. Bu fonksiyon
merge sorta çok benziyor,  gelen string arrayini ikiye bölüyor ta ki 1 elemanlı arraya ulaşıncaya kadar, 1 elemanlı
array oluştuğunda bu stringin kendisi common dur zaten, ardından bu şekilde sağ ve sol taraf icin common bulundugunda,
bu commonları karşılastırdıgımız zaman ortaya çıkan sonucta bize result common u verecektir.

Worst Case Analiz: compare_two_strings, stringin tum elemanlarını gezecek(kotu durumda 2 stringinde boyları esittir,
farklı olsalar az olana gore gezicekti), longest_common_postfix fonksiyonu ise bu fonksiyonu tüm stringler icin
cagiracagindan W(n) = O(n.m) olur.
n: String sayısı.
m: En uzun stringin karakter sayısı.

'''

def compare_two_strings (str1,str2):
    if len(str1) > len(str2):
        str1 = str1[len(str1) - len(str2)::]
    elif len(str1) < len(str2):
        str2 = str2[len(str2) - len(str1)::]

    compres_strings = zip(reversed(str1), reversed(str2))

    longest_common = ""
    for i, j in compres_strings:
        if i == j:
            longest_common = longest_common + i
        else:
            break
    return longest_common[::-1]


def longest_common_postfix(String_array):
    return wrapper(String_array,0,len(String_array) -1)

def wrapper (String_array,low,high):
    if low == high:
        return String_array[low]

    if high > low:
        mid = low + (high - low )//2

        commons1 = wrapper(String_array,low,mid)
        commons2 = wrapper(String_array,mid+1,high)

        return compare_two_strings(commons1,commons2)

inpStrings = ["absorptivity", "circularity","electricity", "importunity", "humanity"]
lcp = longest_common_postfix(inpStrings)
print(lcp)
#Output: ity