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
    G.add_node(0);
    G.add_node(1);
    G.add_node(2);
    G.add_edge(0,1, 1);
    G.add_edge(0,2, 2);
    G.add_node(4);
    G.add_edge(2,4, 3);
    G.add_node(5);
    G.add_edge(1,5, 4);
    G.add_node(3);
    G.add_edge(1,3, 5);
    G.add_edge(3,5, 6);
    G.add_edge(3,4, 7);
    G.add_node(6);
    G.add_edge(3,6, 8);
    
    // G.print_graph_data();
    // cout << "----------------\n";
    // G.delete_node(2);
    // G.print_graph_data();
    G.Dijkstra(0);
    return 0;
}