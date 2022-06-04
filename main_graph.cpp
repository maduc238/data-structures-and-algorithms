#include <iostream>
#include "graph.hpp"

int main(){
    /* Create a graph given in the above diagram
            1 --- 5
          /   \  /
        0      3 --- 6
          \     \
            2 -- 4
    */
    Graph G;
    G.add_sequence_node(9);
    G.add_edge(0,1,4);
    G.add_edge(1,2,8);
    G.add_edge(2,3,7);
    G.add_edge(3,4,9);
    G.add_edge(4,5,10);
    G.add_edge(5,6,2);
    G.add_edge(6,7,1);
    G.add_edge(7,8,7);
    G.add_edge(0,7,8);
    G.add_edge(1,7,11);
    G.add_edge(6,8,6);
    G.add_edge(2,8,2);
    G.add_edge(2,5,4);
    G.add_edge(3,5,14);

    G.print_graph_data();
    G.Dijkstra(0);

    return 0;
}
