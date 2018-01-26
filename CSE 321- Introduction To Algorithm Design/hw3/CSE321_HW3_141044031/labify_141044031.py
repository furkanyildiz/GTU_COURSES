import bfs

#the function repairs a lab and it's roads which is connectted to it.
def calculate_cost(graph,starting_point,visited,road_cost,lab_cost):

    if visited == len(graph)*[True]:
        return 0

    parent = bfs.breadthFirstSearch(graph, starting_point)
    road_count = -1
    for i in range(len(parent)):
        if parent[i] != -1:
            visited[i] = True
            road_count = road_count +1

        if parent[i] == -1 and visited[i] == False:
            starting_point = i + 1
            break

    return road_cost*road_count + lab_cost + calculate_cost(graph,starting_point,visited,road_cost,lab_cost)



def findMinimumCostToLabifyGTU(lab_cost,road_cost,graph):
    #connected olmayan graphlar icin tuttugum array, bu array ile islem yapilmayan vertexleri belirleyecegiz
    visited = len(graph) * [False]

    #bir labın ve o laba bagli yollarin tamir edilmesiyle olusan cost
    cost_option_1 = calculate_cost(graph,1,visited,road_cost,lab_cost)

    #tum lablarin tamiri ile olusan cost
    cost_option_2 = len(graph) * lab_cost

    return cost_option_1 if cost_option_1<cost_option_2 else cost_option_2


mapOfGTU = {
    1 : set([2,3]),
    2 : set([1,3,4]),
    3 : set([1,2,4]),
    4 : set([3,2]),
    5 : set([6]),
    6 : set([5])
}

mapOfGTU2 = {
1 : set([2,3]),
2 : set([1,3]),
3 : set([1,2])
} # graph is initialized as dictionary

minCost = findMinimumCostToLabifyGTU(5,2,mapOfGTU)
print(minCost)
