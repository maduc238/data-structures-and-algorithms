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

Edges
-------

G can also be grown by adding one edge at a time,

.. code-block::

    G.add_edge(0, 1, 4.1);      // weight = 4.1
    G.add_edge(1, 2, 8.2);      // weight = 8.2
    G.add_edge(2, 3);           // weight = 0

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

You can get/set the attributes of an edge using subscript notation if the edge already exists.

.. code-block::

    int weight;
    weight = G.edge_weight(1, 2);

To check if 2 nodes are close to each other, using bool funcrion ``is_near``.

.. code-block::

    is_near(1, 2);

Algorithms
-------

Breadth-First Traversal (or Search) for a graph is similar to Breadth-First Traversal of a tree. The 
only catch here is, unlike trees, graphs may contain cycles, so we may come to the same node again. 
To avoid processing a node more than once. For simplicity, it is assumed that all vertices are 
reachable from the starting vertex.

These are ``breath_first_search`` and ``depth_first_search`` functions.

Given a graph and a source vertex in the graph, find the shortest paths from the source to all vertices 
in the given graph. These algorithms function are: ``Dijkstra``, ``Bellman_Ford``, ``Floyd``.

In graph theory, a cycle in a graph is a non-empty trail in which only the first and last vertices are 
equal. A directed cycle in a directed graph is a non-empty directed trail in which only the first and 
last vertices are equal. A graph without cycles is called an acyclic graph. A directed graph without 
directed cycles is called a directed acyclic graph. A connected graph without cycles is called a tree.
To check graph cycle with two neighbors node, use bool function ``Cycle_Detection``.

A Minimum Spanning Tree (MST) or minimum weight spanning tree is a subset of the edges of a connected, 
edge-weighted undirected graph that connects all the vertices together, without any cycles and with the 
minimum possible total edge weight. That is, it is a spanning tree whose sum of edge weights is as 
small as possible. More generally, any edge-weighted undirected graph (not necessarily connected) has 
a minimum spanning forest, which is a union of the minimum spanning trees for its connected components.
Algorithms show in this Graph library is: ``SpanningTree_Kruskal``, ``SpanningTree_Dijkstra``.


License
-------

.. code-block::

    Copyright (C) 2022 maduc238 Developers
    Ma Viet Duc <duc.mv190036@sis.hust.edu.vn>
    Nguyen Duc Canh <canh.nd196038@sis.hust.edu.vn>
    Do Van Ben <ben.dv191695@sis.hust.edu.vn>
    Nguyen Ho Giang Nam <nam.nhg193030@sis.hust.edu.vn>
    Quach Dinh Dung <dung.qd190014@sis.hust.edu.vn>