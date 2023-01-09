
Obstruction = [(1, 2), (1, 5), (8, 5), (8, 3), (11, 3), (11, 1), (5, 1), (5, 3), (4, 3), (4, 1), (1, 1), (1, 2)]

# n = 3: Will talk
Reciever = [(2,4),(2,2),(5,4)]
Transmitter = [(4,4),(6,3),(6,2)]

# Will not talk
# Reciever = [(2,4),(2,2),(5,4)]
# Transmitter = [(6,2),(7,4),(6,3)]


def BFS(graph, source, sink, parents):
    found = [False] * len(graph)                        # creates list of nodes visited
    found[source] = True                                # default source node to found
    nodes = []
    nodes.append(source)                                # append source node to the nodes
    parents[source] = -1                                # list keeps track of the parent nodes for each node

    while len(nodes) > 0:                               # while there are nodes to be traversed
        u = nodes.pop(0)
        for v in range(0, len(graph)):                  # for all other nodes in the graph
            if found[v] == False and graph[u][v] > 0:   # if there is a path between u and v and v has not been found and the residual graph is greater than 0
                nodes.append(v)                         # append v to the nodes
                found[v] = True                         # set v node to visited
                parents[v] = u                          # make u the parent of node v

    if found[sink]:  # If the sink was visited return True and look for another traversal
        return True
    else:
        return False


def maxFlowGraph(Obstruction, Reciever, Transmitter):
    numReciever = len(Reciever)
    numTransmitter = len(Transmitter)
    vertices = 1 + numReciever + numTransmitter + 1  # Total length of the graph/adjacency matrix
    adjMatrix = [[]] * vertices  # Creates a list of lists which will be the adjacency matrix

    i = 0
    while i < vertices:  # Populates the adjacency matrix with all 0s
        adjMatrix[i] = list(0 for j in range(0, vertices))
        i += 1

    for i in range(1):  # Setup source edges
        for j in range(1, numReciever + 1):
            adjMatrix[i][j] = 1

    for i in range(numTransmitter + 1, vertices - 1):  # Setup sink edges
        for j in range(1):
            adjMatrix[i][-1] = 1

    for i, antena in enumerate(Reciever):  # Populate the adjacency matrix by checking each antena and reciever combination
        for j, transmit in enumerate(Transmitter):
            if lineOfSight(antena, transmit, Obstruction):
                adjMatrix[i + 1][j + numReciever + 1] = 1


    return adjMatrix


def edmondsKarp(graph, source, sink):
    parents = [0] * len(graph)  # Track the parent of each node
    u, v = 0, 0  # u = current node, v = target node
    residualGraph = graph  # Create the residual graph from the original graph
    maxFlow = 0  # Initialize a variable to store the max flow of the graph

    while BFS(residualGraph, source, sink,
                               parents):  # While there is a path from the source to the sink
        pathFlow = float('inf')  # Initialize path flow to infinite
        v = sink  # Set the destination or end node to the sink

        while not v == source:  # While v is not 0
            u = parents[v]  # u is the parent node for v
            pathFlow = min(pathFlow, residualGraph[u][v])  # Update path flow to be the bottleneck of the current path
            v = parents[v]  # Create backwards edge

        v = sink  # Reset v to the sink

        while not v == source:  # While v is not 0
            u = parents[v]  # u is the parent node for v
            residualGraph[u][v] -= pathFlow  # Subtract flow from the path
            residualGraph[v][u] += pathFlow  # Add flow to backwards edges
            v = parents[v]  # Create backwards edge

        maxFlow += pathFlow  # add path flow to the max flow
    return maxFlow


# Return true if line segments AB and CD intersect
def counter(pt1, pt2, pt3):
    return (pt3[1] - pt1[1]) * (pt2[0] - pt1[0]) > (pt2[1] - pt1[1]) * (pt3[0] - pt1[0])


def intersect(pt1, pt2, pt3, pt4):
    return counter(pt1, pt3, pt4) != counter(pt2, pt3, pt4) and counter(pt1, pt2, pt3) != counter(pt1, pt2, pt4)


def lineOfSight(pt1, pt2, Obstruction):
    x1, y1 = pt1
    x2, y2 = pt2
    for i, hill in enumerate(Obstruction[:-1]):
        x3, y3 = hill
        x4, y4 = Obstruction[i + 1]

        if intersect((x1, y1), (x2, y2), (x3, y3), (x4, y4)):
            return False
    return True


def isPaired(Reciever, Transmitter):
    if len(Reciever) != len(Transmitter):
        print("The number of Reciever and the number of Transmitter must be the same.")
        return False
    else:
        return True


def runSystem(Reciever, Transmitter, Obstruction):

    maxFlow = None
    if isPaired(Reciever, Transmitter):
        graph = maxFlowGraph(Obstruction, Reciever, Transmitter)
        maxFlow = edmondsKarp(graph, 0, len(graph) - 1)
        
    if maxFlow == len(Reciever):
        temp = "All troops are communicating."
    else:
        temp= "Your troops can't communicate!"

    print(temp)
    return temp


if __name__ == '__main__':
    runSystem(Reciever, Transmitter, Obstruction)