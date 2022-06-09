Graph Data Structure And Algorithms
========


This guide can help you start working with Graph algorithm.

- **Facebook:** https://www.facebook.com/maduc238
- **GitHub and Tutorial:** https://github.com/maduc238/data-structures-and-algorithms

Creating a graph
--------------

Create an empty graph with no nodes and no edges.

.. code-block::

    Graph G;

By definition, a Graph is a collection of nodes (vertices) along with identified pairs of nodes (called edges, links, etc).

Nodes
-------

The graph G can be grown in several ways. Graph includes many graph generator functions and 
facilities to read and write graphs in many formats. To get started though we'll look at simple 
manipulations. You can add one node at a time,

.. code-block::

    G.add_node(1);

or add nodes from any iterable container, such as a list,

.. code-block::

    nodes[] = {5,2,4,1,3,6,1,0};
    G.add_nodes_from(nodes,8);      // 8 is number of node

or you can add with a sequence numbers of nodes in graph.

.. code-block::

    add_sequence_node(8);           // Graph will have node 0,1,...,7 (with 8 nodes)

To shows the total number of nodes in the graph::

    G.print_count();

or you can use::

    int c = G.counts();

Edges
-------

G can also be grown by adding one edge at a time,

.. code-block::

    G.add_edge(0, 1, 4.1);      // weight = 4.1
    G.add_edge(1, 2, 8.2);      // weight = 8.2
    G.add_edge(2, 3);           // weight = 0

Example code::

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

The ``print_graph_data`` will show nodes and these neighbor edges::

    0: 1 (4.1) - 7 (8.8)
    1: 0 (4.1) - 2 (8.2) - 7 (11.6)
    2: 1 (8.2) - 3 (7.1) - 5 (4.1) - 8 (2.3)
    3: 2 (7.1) - 4 (9.5) - 5 (14.5)
    4: 3 (9.5) - 5 (10.1)
    5: 2 (4.1) - 3 (14.5) - 4 (10.1) - 6 (2)
    6: 5 (2) - 7 (1.3) - 8 (6.9)
    7: 0 (8.8) - 1 (11.6) - 6 (1.3) - 8 (7.4)
    8: 2 (2.3) - 6 (6.9) - 7 (7.4)

Removing elements from a graph
-------

One can remove nodes and edges from the graph in a similar fashion to adding. Use methods
``delete_node`` and ``delete_edge``, e.g.

With ``delete_node``, this will automatically delete edges near this node.

.. code-block::

    G.delete_node(2);       // delete node 2
    G.delete_edge(1, 3);    // delete edge 1 - 3

Analyzing graphs
-------

The structure of G can be analyzed using various graph-theoretic functions such as: Print graph data 
with all node with these neighbors by ``print_graph_data``, print all nodes ``print_nodes``, print all 
edges ``print_edges``.

.. code-block::

    G.print_graph_data();
    G.print_nodes();
    G.print_edges();

Accessing edges and neighbors
-------

To see all neighbors for a node, you can call a void function ``print_neighbors``.

.. code-block::

    G.print_neighbors(1);

To change weight for a edge, use function ``change_weight``::

    G.change_weight(1, 2, 2.3);

You can get/set the attributes of an edge using subscript notation if the edge already exists.

.. code-block::

    int weight;
    weight = G.edge_weight(1, 2);

To check if 2 nodes are close to each other, using bool function ``is_near``.

.. code-block::

    is_near(1, 2);

Algorithms
-------

Breadth-First Traversal (or Search) for a graph is similar to Breadth-First Traversal of a tree. The 
only catch here is, unlike trees, graphs may contain cycles, so we may come to the same node again. 
To avoid processing a node more than once. For simplicity, it is assumed that all vertices are 
reachable from the starting vertex. These are ``breath_first_search`` and ``depth_first_search`` functions.

Given a graph and a source vertex in the graph, find the shortest paths from the source to all vertices 
in the given graph. These algorithms function are: ``Dijkstra``, ``Bellman_Ford``, ``Floyd``.

.. code-block::

    G.Dijkstra(0);
    // Or you can use Bellman_Ford()

Return::

    From 0 to 1: 1 0
    From 0 to 7: 7 0
    From 0 to 2: 2 1 0
    From 0 to 6: 6 7 0
    From 0 to 8: 8 2 1 0
    From 0 to 3: 3 2 1 0
    From 0 to 5: 5 6 7 0
    From 0 to 4: 4 5 6 7 0

With ``Floyd``, this will show all shortest weights to all nodes::

    G.Floyd();

Return::

            0       1       2       3       4       5       6       7       8

    0       0       4.1     12.3    19.4    28.9    16.4    10.1    8.8     14.3
    1       4.1     0       8.2     15.3    24.8    12.3    12.9    11.6    10.2
    2       12.3    8.2     0       7.1     14.2    4.1     6.1     7.4     2
    3       19.4    15.3    7.1     0       9.5     11.2    13.2    14.5    9.1
    4       28.9    24.8    14.2    9.5     0       10.1    12.1    13.4    16.2
    5       16.4    12.3    4.1     11.2    10.1    0       2       3.3     6.1
    6       10.1    12.9    6.1     13.2    12.1    2       0       1.3     6.9
    7       8.8     11.6    7.4     14.5    13.4    3.3     1.3     0       7.4
    8       14.3    10.2    2       9.1     16.2    6.1     6.9     7.4     0

In graph theory, a cycle in a graph is a non-empty trail in which only the first and last vertices are 
equal. A directed cycle in a directed graph is a non-empty directed trail in which only the first and 
last vertices are equal. A graph without cycles is called an acyclic graph. A directed graph without 
directed cycles is called a directed acyclic graph. A connected graph without cycles is called a tree.
To check graph cycle with two neighbors node, use bool function ``Cycle_Detection``.::

    std::cout << G.Cycle_Detection(1,4);

A Minimum Spanning Tree (MST) or minimum weight spanning tree is a subset of the edges of a connected, 
edge-weighted undirected graph that connects all the vertices together, without any cycles and with the 
minimum possible total edge weight. That is, it is a spanning tree whose sum of edge weights is as 
small as possible. More generally, any edge-weighted undirected graph (not necessarily connected) has 
a minimum spanning forest, which is a union of the minimum spanning trees for its connected components.
Algorithms show in this Graph library are: ``SpanningTree_Kruskal``.

.. code-block::
    
    Graph G_spanning_tree = G.SpanningTree_Kruskal();
    G_spanning_tree.print_graph_data();

Return::

    0: 1
    1: 0 - 2
    2: 1 - 3 - 5 - 8
    3: 2 - 4
    4: 3
    5: 2 - 6
    6: 5 - 7
    7: 6
    8: 2

License
-------

.. code-block::

    Copyright (C) 2022 maduc238 Developers
    Ma Viet Duc <duc.mv190036@sis.hust.edu.vn>
    Nguyen Duc Canh <canh.nd196038@sis.hust.edu.vn>
    Do Van Ben <ben.dv191695@sis.hust.edu.vn>
    Nguyen Ho Giang Nam <nam.nhg193030@sis.hust.edu.vn>
    Quach Dinh Dung <dung.qd190014@sis.hust.edu.vn>