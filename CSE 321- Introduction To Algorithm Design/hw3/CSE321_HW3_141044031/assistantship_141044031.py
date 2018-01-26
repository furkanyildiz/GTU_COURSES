import sys
def perms(n,A,b):

    if n == 1:
        b.append(list(A))
    else:
        for i in range(0,n-1):
            perms(n-1,A,b)
            if n%2 == 1: #n is even
                A[0], A[n-1] = A[n-1] , A[0]
            else:
                A[i], A[n-1] = A[n-1] , A[i]
        perms(n-1,A,b)

#list should include at least one element.
#helps to calculate subsets of given list
def subsets(liste):
    if len(liste) == 1:
        return [liste[0]]
    else:
        subs = subsets(liste[1:])

        for i in range(len(subs)):
            subs.append(int(str(liste[0]) + str(subs[i])))

        subs.append(liste[0])
        return subs

#returns all subset of given list.
def find_all_subsets(liste):
    all_subsets = subsets(liste)
    list_of_ints = []
    for subset in all_subsets:
        list_of_ints.append([int(i) for i in str(subset)])
    return list_of_ints

#returns subsets of given list which has n elements
def n_elems_subsets(liste,n):
    n_elems_subset = []
    all_subsets = find_all_subsets(liste)
    for subset in all_subsets:
        if len(subset) == n:
            n_elems_subset.append(subset)
    return n_elems_subset


# the functions creates a n elemensts subsets and returns all permutations of this subsets
def create_perms_for_n_elems_subsets(liste, n):
    all_permutations = []

    n_elems_subset = n_elems_subsets(liste, n)

    for subset in n_elems_subset:
        perms_for_the_subset = []
        perms(n, subset, perms_for_the_subset)
        all_permutations = all_permutations + perms_for_the_subset
    return all_permutations


def calculate_cost(perm, table):
    cost = 0
    index = 0
    for i in perm:
        cost = cost + table[i - 1][index]
        index = index + 1

    return cost

def findOptimalAssistantship(inputTable):
    course_number = len(inputTable[0])
    research_asistant_number = len(inputTable)
    if course_number > research_asistant_number:
        return None,None
    assistant_list = [i for i in range (1,1+research_asistant_number) ]
    #asistanlarin derslere gore dagilim combinasyonlari
    distribution_by_classes_for_ra = create_perms_for_n_elems_subsets(assistant_list ,course_number)

    min_cost_perm = []
    min_cost = sys.maxsize
    for one_distiribution in distribution_by_classes_for_ra:
        cost_of_the_perm = calculate_cost(one_distiribution,inputTable)
        if min_cost > cost_of_the_perm:
            min_cost = cost_of_the_perm
            min_cost_perm = one_distiribution

    #bunu yapmamızın sebebi asistan numarasini yukarida 1 den baslatmamizdir.
    min_cost_perm = [i-1 for i in min_cost_perm]
    asst = []
    for i in range(research_asistant_number):
        if i in min_cost_perm:
            asst.append(min_cost_perm.index(i))
        else:
            asst.append(-1)
            min_cost = min_cost + 6
    return asst,min_cost


inputTable = [
    [5, 8,  7],  # R.A. 0
    [8, 12, 7],  # R.A. 1
    [4, 8,  5]]  # R.A. 3
    
asst, time = findOptimalAssistantship(inputTable)
print(asst)
print(time)
