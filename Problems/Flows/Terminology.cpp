// https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/
// https://cp-algorithms.web.app/graph/edmonds_karp.html
// https://www.youtube.com/watch?v=K1i-wP82Zdo	(BEST) 


// What does Augment mean in English?
// 		To increase something by adding
// Augmenting Paths:
// A simple path from source to sink (without cycles) in the "residual" graph.
// Residual Capactiy of an edge is: how much flow can still happen through that edge
// Residual graph is the graph of these residual capacities
// It will never be negative as we add / subtract the minimum

// Integer flow theorem:
// If c(e) for all edges e in the graph are integers, then there exists a max flow f for which
// every flow value f(e) is an integer.
// (f is obviously integer then if f(e) all are integers)

// Ford Fulkerson Algorithm:
	// Initialise all edge flows to 0
	// while (there exists an augmented path from source to sink in residual graph):
	// 		Augment the flow along the path with min(residual capacity)	[increase]
// This algorithm will take (V+E)*f time, where f is the max flow
// (because the flow of network will always increase by atleast 1 because:
//		in every augmenting path, we will augment it by the mn value, and mn > 0
//		(if mn was zero, it wouldn't have been inclluded in the augment path)
//		(residual capacity of 0, such edge never included in the residual graph)
// In case of rational capactities, algorithm is not bounded.
// In case of irrational capacities, algorithm may not terminate or converge to max flow


// https://qr.ae/pGjKY4

// Edmond Karp:
// Same as Ford Fulkerson BUT do BFS and find the shortest lenght augment path
// Time complexity will be O((V+E) * VE)
// There can be atmost VE phases of the algorithm. We can understand this by analysing how many
// times does an edge become critical.
// Edge is said to be critical when it gets fully filled after augmenting the augment path (the minimum edge)
// If an edge becomes critical again, it is because next shortest path was found through this edge.
// This means the distance from the source of the edge keeps increasing
// It can atmost be V-1 distance away from the source. So it becomes critical O(V) times
// Therefore all edges will be critical maximal times within EV iterations
// Thats why time complexity is O(VE^2)

// Max Flow Min Cut:
// An s-t cut is: Imagine a partition of graph into 2 connected disjoint sets of vertices (one including s,
//	the other including t). Now the sum of flow on the edges bw A and B is called the value of cut.
// Ofcourse, we cannot send more water than a cut
// So the max cut is bounded by the minimum cut value
// Max flow = min cut
// How to find a min cut ?
// All nodes reachable in residual graph from s will form A, others will form B.
// Why? cause 
// nodes coming out of A will ALL be saturated (i.e. residual capacity = 0)
// The saturation will be maximized because we took as many unsaturated as possible from s.
// Max saturation => Max flow => Min Cut


