Graph Data Structure And Algorithms
========


This guide can help you start working with Graph algorithm.

- **Facebook (including documentation):** https://www.facebook.com/maduc238
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
manipulations. You can add one node at a time,::

    G.add_node(1);

or add nodes from any iterable container, such as a list,::

    nodes[] = {5,2,4,1,3,6,1,0};
    G.add_nodes_from(nodes,8);      // 8 is number of node

or you can add with a sequence numbers of nodes in graph::

    add_sequence_node(8);
    // Graph will have node 0,1,...,7 (with 8 nodes)

Edges
-------

G can also be grown by adding one edge at a time,::

    G.add_edge(0, 1, 4.1);      // weight = 4.1
    G.add_edge(1, 2, 8.2);      // weight = 8.2

License
-------

   Copyright (C) 2022 maduc238 Developers
   Ma Viet Duc <duc.mv190036@sis.hust.edu.vn>
   Nguyen Duc Canh
   Do Van Ben
   Nguyen Ho Giang Nam
   Quach Dinh Dung
