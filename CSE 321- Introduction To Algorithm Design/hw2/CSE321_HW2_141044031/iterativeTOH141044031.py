def TOH(height):
    liste = [0] * height
    calculate(height,"SRC","DST","AUX",liste)
    for i in range(len(liste)):
        print('Elapsed time for disk ',i+1,": ",liste[i])

def calculate(height,source, destination, auxilary,listem):

    if height >= 1:
        calculate(height-1,source,auxilary,destination,listem)
        print("disc", height, ": ", source, " to ", destination)
        helper(height,source,destination,listem)
        calculate(height-1,auxilary,destination,source,listem)


def helper(height,source,destination,liste):

    distance_map = {'SRC':1, 'AUX': 2 , 'DST': 3}
    distance = abs(distance_map.get(source) - distance_map.get(destination))
    liste[height-1] = liste[height-1] +  height * distance

TOH(3)