#include <iostream>
#include "graph.hpp"

int main(){
    Graph G;
    G.add_sequence_node(9);
    G.add_edge(0,1,4.1);
    G.add_edge(1,2,8.2);
    G.add_edge(2,3,7.1);
    G.add_edge(3,4,9.5);
    G.add_edge(4,5,10.1);
    G.add_edge(5,6,2.0);
    G.add_edge(6,7,1.3);
    G.add_edge(7,8,7.4);
    G.add_edge(0,7,8.8);
    G.add_edge(1,7,11.6);
    G.add_edge(6,8,6.9);
    G.add_edge(2,8,2.3);
    G.add_edge(2,5,4.1);
    G.add_edge(3,5,14.5);

    G.print_graph_data();
    G.Dijkstra(0);
    // G.print_graph_data();
    G.Bellman_Ford(0);
    return 0;
}
