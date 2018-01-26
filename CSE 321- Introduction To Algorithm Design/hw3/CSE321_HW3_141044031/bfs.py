def breadthFirstSearch(graph, starting_vertex):

    queue = []
    vertex_num = len(graph)
    parent = vertex_num*[-1]
    visited = vertex_num*[False]

    queue.append(starting_vertex)
    visited[starting_vertex-1] = True
    parent[starting_vertex-1] = 0
    while len(queue) != 0:

        current = queue.pop(0)
        neighbours = graph.get(current, [])

        for a_neighbour in neighbours:

            if visited [a_neighbour - 1] == False:
                visited[a_neighbour - 1] = True
                queue.append(a_neighbour)
                parent[a_neighbour - 1] = current

    return parent
