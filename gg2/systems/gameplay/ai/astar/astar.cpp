// function reconstruct_path(came_from, current)
//     total_path := {current}
//     while current in came_from.keys:
//         current := came_from[current]
//         total_path.prepend(current)
//     return total_path

// // A* finds a path from start to goal.
// // h is the heuristic function. h(n) estimates the cost to reach goal from node n.
// function a_star(start, goal, h)
//     // The set of discovered nodes that may need to be (re-)expanded.
//     // Initially, only the start node is known.
//     // This is usually implemented as a min-heap or priority queue rather than a hash-set.
//     open_set := {start}

//     // For node n, came_from[n] is the node immediately preceding it on the cheapest path from the start
//     // to n currently known.
//     came_from := an empty map

//     // For node n, g_score[n] is the currently known cost of the cheapest path from start to n.
//     g_score := map with default value of Infinity
//     g_score[start] := 0

//     // For node n, f_score[n] := g_score[n] + h(n). f_score[n] represents our current best guess as to
//     // how cheap a path could be from start to finish if it goes through n.
//     f_score := map with default value of Infinity
//     f_score[start] := h(start)

//     while open_set is not empty
//         // This operation can occur in O(Log(N)) time if open_set is a min-heap or a priority queue
//         current := the node in open_set having the lowest f_score[] value
//         if current = goal
//             return reconstruct_path(came_from, current)

//         open_set.remove(current)
//         for each neighbor of current
//             // d(current,neighbor) is the weight of the edge from current to neighbor
//             // tentative_g_score is the distance from start to the neighbor through current
//             tentative_g_score := g_score[current] + d(current, neighbor)
//             if tentative_g_score < g_score[neighbor]
//                 // This path to neighbor is better than any previous one. Record it!
//                 came_from[neighbor] := current
//                 g_score[neighbor] := tentative_g_score
//                 f_score[neighbor] := tentative_g_score + h(neighbor)
//                 if neighbor not in open_set
//                     open_set.add(neighbor)

//     // Open set is empty but goal was never reached
//     return failure