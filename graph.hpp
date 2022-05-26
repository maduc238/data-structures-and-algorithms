#include <iostream>
#include "sort.hpp"
using namespace std;

/*****************************************************************************
 * The graph algorithm base to Networkx in python
 * 
 * Task need to do:
 * breath_first_search and deep_first_search
 * Dijkstra, Bellman-Ford algorithm
 * 
 * To run these functions:
 * Initial a new graph:
 * Graph G;
 * 
 * Create a new node:
 * G.add_node(1);
 * G.add_node(0);
 * G.add_node(2);
 * (Or you can run function: add_sequence_node, add_node_from,...)
 * 
 * Create a new edge:
 * G.add_edge(0,1, 0);  // weight = 0
 * 
 * Delete a node:
 * G.delete_node(2);
 * 
 * Delete a edge:
 * G.delete_edge(0,1);
 * 
 * Print all graph data:
 * G.print_graph_data();
 * 
 * And many more functions to do...
*****************************************************************************/

/* The single node use for edges structure */
class Node{
    public:
    int data;
    int weight;
    Node* next;

    Node(){
        data = 0;
        weight = 0;
        next = NULL;
    }
};

/* The double node use for graph node */
class Node2{
    public:
    int data;
    Node2* next;
    Node* edges;

    Node2(){
        data = 0;
        next = NULL;
        edges = NULL;
    }

    void _add_node(int data, int weight){
        // First element
        if (edges == NULL){
            edges = new Node();
            edges->data = data;
            edges->weight = weight;
        }
        // If not the first element
        else{
            Node* a = edges;
            while(a->data < data && a->next != NULL){
                a = a->next;
            }
            if (a->data == data){
                if (this->data != data)
                cout << "Warning: This node already exists in graph\n";
                return;
            }
            Node* temp = new Node();
            temp->data = data;
            temp->weight = weight;
            if (a->next == NULL){
                if (data < a->data){
                    a->next = temp;
                    // Exchange two data of nodes
                    int temp_data = a->data;
                    int temp_weight = a->weight;
                    a->data = a->next->data;
                    a->weight = a->next->weight;
                    a->next->data = temp_data;
                    a->next->weight = temp_weight;
                }
                else {
                    temp->next = NULL;
                    a->next = temp;
                }
            }
            else {
                temp->next = a->next;
                a->next = temp;
                // Exchange two data of nodes
                int temp_data = a->data;
                int temp_weight = a->weight;
                a->data = a->next->data;
                a->weight = a->next->weight;
                a->next->data = temp_data;
                a->next->weight = temp_weight;
            }
        }
    }

    void _delete_node(int node){
            Node* a = edges;
            bool check = false;
            while (a->next != NULL && a->next->data <= node){
                if (a->next->data == node){
                    check = true;
                    break;
                }
                a = a->next;
            }
            // Delete this node
            if (check == true){
                a->next = a->next->next;
            }
            else if (a->data == node) edges = edges->next;
            else
                cout << "Warning: Can't find node " << node << " in this graph\n";
        }
};

namespace hidden_function{
/* A helper function to print all linked list in the data structure */
void print_all_edge(Node* node){
    if (node == NULL)
        return;
    if (node->next == NULL) cout << node->data;
    else cout << node->data << " - ";
    print_all_edge(node->next);
}

/* A hepler function to print all linked list in the data structure */
void print_all_node(Node2* node){
    if (node == NULL)
        return;
    cout << node->data << ": ";
    print_all_edge(node->edges);
    cout << "\n";
    print_all_node(node->next);
}

/* A helper function */
void _exchange(Node2* a){
    // Exchange two data of nodes
    int temp_data = a->data;
    a->data = a->next->data;
    a->next->data = temp_data;
    // Exchange edges...
    a->next->edges = a->edges;
    a->edges = NULL;
}

/* A helper function */
void _del(Node2* b, Node2* &a, int node){
    // Delete edges with this node
    while (b != NULL && b->data <= a->edges->data){
        if (b->data == a->edges->data){
            b->_delete_node(node);
            if (a->edges->next == NULL) break;
            a->edges = a->edges->next;
        }
        b = b->next;
    }
}
}

/* A Graph class. This class represents a undirected graph using adjacency list representation */
class Graph{
    /* The class members declared as private can be accessed only by the functions inside the class.
    They are not allowed to be accessed directly by any object or function outside the class */
    private:
        // The first pointer in linked list node structure
        Node2* root;
        // Number of node in graph
        int count;

    public:
        // Constructor in class Graph
        Graph(){
            this->root = NULL;
            this->count = 0;
        }
        /* A void function, insert a new node to the graph.
        Example: You want to add node 5:
        Graph G;
        G.add_node(5); */
        void add_node(int data){
            //First element
            if (this->root == NULL){
                this->root = new Node2();
                this->root->data = data;
                count++;
            }
            // Else if this node is not the first
            else{
                Node2* a = this->root;
                while(a->data < data && a->next != NULL){
                    a = a->next;
                }
                if (a->data == data){
                    cout << "Warning: Node " << data << " already exists in this graph\n";
                    return;
                }
                Node2* temp = new Node2();
                temp->data = data;
                if (a->next == NULL){
                    temp->next = NULL;
                    a->next = temp;
                    if (data < a->data){
                        hidden_function::_exchange(a);
                    }
                }
                else {
                    temp->next = a->next;
                    a->next = temp;
                    hidden_function::_exchange(a);
                }
                count++;
            }
        }

        /* Check a node in a graph. If the graph have node n, function call
        back true, else if is node available, function return false */
        bool available_node(int n){
            Node2* a = this->root;
            bool Result = false;
            while (a != NULL && a->data < n){
                a = a->next;
            }
            if (a != NULL &&  a->data == n){
                Result = true;
            }
            return Result;
        }

        /* Insert a new edge in this graph without weight. The two edges in these variables must exist in graph.
        If node 2 and 3 are already existed in graph: (The weight will be set 0)
        add_edge(2, 3); */
        void add_edge(int node1, int node2){
            Node2* a = this->root;
            int c = 0;
            int n_max = max(node1,node2);
            bool Result = false;
            // A checking loop, consider available nodes
            while (a != NULL && a->data <= n_max){
                if (a->data == node1 || a->data == node2)
                    c++;
                a = a->next;
            }
            if (c != 2 && node1 != node2){
                cout << "Waring: There is some node(s) that does not exist in this graph\n";
                return;
            }
            a = this->root;
            while (a->data <= node1 || a->data <= node2){
                if (a->data == node1) a->_add_node(node2, 0);
                if (a->data == node2) a->_add_node(node1, 0);
                if (a->next == NULL) break;
                a = a->next;
            }
        }

        /* Insert a new edge in this graph. The two edges in these variables must exist in graph.
        If node 2 and 3 are already existed in graph and weight is 4:
        add_edge(2, 3, 4); */
        void add_edge(int node1, int node2, int weight){
            Node2* a = this->root;
            int c = 0;
            int n_max = max(node1,node2);
            bool Result = false;
            // A checking loop, consider available nodes
            while (a != NULL && a->data <= n_max){
                if (a->data == node1 || a->data == node2)
                    c++;
                a = a->next;
            }
            if (c != 2 && node1 != node2){
                cout << "Waring: There is some node(s) that does not exist in this graph\n";
                return;
            }
            a = this->root;
            while (a->data <= node1 || a->data <= node2){
                if (a->data == node1) a->_add_node(node2, weight);
                if (a->data == node2) a->_add_node(node1, weight);
                if (a->next == NULL) break;
                a = a->next;
            }
        }
        
        /* A helper function, shows the total number of nodes in the graph */
        void print_count(){
            cout << this->count <<"\n";
        }

        /* A void function print all graph's data: nodes and edges in a node struct
        Just a function that supports displaying data, no application to the algorithm.*/
        void print_graph_data(){
            if (this->root == NULL)
                cout << "Warning: There are no nodes in this graph\n";
            hidden_function::print_all_node(this->root);
        }

        /*  A void function print all nodes in graph G. If graph G have nodes 2,3,4,6,7:
        G.print_nodes();
        -> All nodes: 2, 3, 4, 6, 7 */
        void print_nodes(){
            Node2* a = this->root;
            cout << "All nodes: ";
            while (a != NULL){
                cout << a->data;
                if (a->next != NULL) cout << ", ";
                a = a->next;
            }
            cout << "\n";
        }

        /*  A void function print all nodes in graph G. If graph G have egdes (0-1), (1-3), (3,2), (2,1):
        G.print_edges();
        -> All edges: (0 - 1), (1 - 2), (1 - 3), (2 - 3) */
        void print_edges(){
            Node2* a = this->root;
            cout << "All edges: ";
            while (a != NULL){
                while (a->edges != NULL){
                    if (a->data <= a->edges->data)
                        cout <<"("<<a->data<<" - "<<a->edges->data<<")";
                    if (a->edges->next != NULL && a->data <= a->edges->next->data) cout<< ", ";
                    a->edges = a->edges->next;
                }
                a = a->next;
            }
            cout << "\n";
        }

        /* Given a node name n, this function will delete this node from the graph.
        If node 2 is already existed in graph:
        delete_node(2); */
        void delete_node(int n){
            Node2* a = this->root;
            bool check = false;
            while (a->next != NULL && a->next->data <= n){
                if (a->next->data == n){
                    check = true;
                    break;
                }
                a = a->next;
            }
            // Delete this node
            if (check == true){
                if (a->next->edges != NULL){
                    hidden_function::_del(this->root, a->next, n);
                }
                this->count--;
                a->next = a->next->next;
            }
            else if (a->data == n){
                if (this->root->edges != NULL){
                    hidden_function::_del(this->root, this->root, n);
                }
                this->count--;
                this->root = this->root->next;
                }
            else
                cout << "Warning: Can't find node " << n << " in this graph\n";
        }

        /* Delete a edge connected by two nodes */
        void delete_edge(int node1, int node2){
            if (node2 < node1){
               int temp = node1; node1 = node2; node2 = temp;
            }
            Node2* a = this->root;
            while (a->data <= node2 && a != NULL){
                if (a->data == node1){
                    if (a->edges == NULL) break;
                    a->_delete_node(node2);
                }
                else if (a->data == node2){
                    if (a->edges == NULL) break;
                    a->_delete_node(node1);
                    break;
                }
                a = a->next;
            }
        }

        /* The function returns the weight of edge */
        int edge_weight(int node1, int node2){
            Node2* a = this->root;
            int result = -1;
            while(a != NULL && a->data <= node1){
                if(a->data == node1){
                    while(a->edges != NULL && a->edges->data <= node2){
                        if (a->edges->data == node2){
                            result = a->edges->weight;
                            break;
                        }
                        a->edges = a->edges->next;
                    }
                }
                a = a->next;
            }
            if (result == -1){ cout << "Warning: This edge does not exist in graph\n"; }

            return result;
        }

        /* A void function insert a sequence numbers of nodes in graph, starting from 0 by default.
        This graph must be empty, or else it will break and stop the initialization.
        Graph will have node 0,1,...,7 (with 8 nodes):
        add_sequence_node(8); */
        void add_sequence_node(int number_node){
            if (this->root != NULL){
                // This graph did not empty
                cout << "Warning: Some nodes still exist in the graph, this graph must be empty\n";
                return;
            }
            else if (number_node < 1){
                cout << "Warning: number_node must be greater than 1\n";
                return;
            }
            // Else, initial new node
            this->root = new Node2();
            this->root->data = 0;
            Node2* a = this->root;
            for (int i=1; i<number_node; i++){
                a->next = new Node2();
                a->next->data = i;
                a = a->next;
            }
            this->count += number_node;
        }

        /* Returns an iterator over successor nodes of n.
        If graph have node 3 and its neighbors is 1,2,5:
        print_neighbors(3);
        -> 1 - 2 - 5 */
        void print_neighbors(int n){
            Node2* a = this->root;
            bool check = false;
            while (a != NULL && a->data <= n){
                if (a->data == n){
                    check = true;
                    break;
                }
                a = a->next;
            }
            if (check == false){
                cout << "Warning: Can't find node " << n << " in this graph\n";
                return;
            }
            // Start to print neighbors
            hidden_function::print_all_edge(a->edges);
        }

        /* A void function insert node to graph from a int string: nodes[], with n_nodes is
        the sizes of string nodes[]. This graph must be empty, or else it will break and stop the initialization.
        This function will automatically sort nodes[] and eliminate duplicate nodes.
        Example: nodes[] = {5,2,4,1,3,6,1,0};
        G.add_nodes_from(nodes,8); */
        void add_nodes_from(int nodes[], int n_nodes){
            if (this->root != NULL){
                // This graph did not empty
                cout << "Warning: Some nodes still exist in the graph, this graph must be empty\n";
                return;
            }
            else if (n_nodes < 1){
                cout << "Warning: number_node must be greater than 1\n";
                return;
            }
            // Using heap sort to sort the array nodes[] from sort.hpp
            heap_sort(nodes, n_nodes);
            // Else, initial new node
            this->root = new Node2();
            this->root->data = nodes[0];
            this->count++;
            Node2* a = this->root;
            for (int i=1; i<n_nodes; i++){
                if (nodes[i-1] == nodes[i]) continue;
                a->next = new Node2();
                a->next->data = nodes[i];
                a = a->next;
                this->count++;
            }
        }

        /* Kiem tra n1 va n2 xem ca hai co gan nhau khong? */
        bool is_near(int n1, int n2){
            Node2* a = this->root;
            bool check = false;
            while (a != NULL && a->data <= n1){
                if (a->data == n1){
                    check = true;
                    break;
                }
                a = a->next;
            }
            if (check == false){
                return false;
            }
            check = false;
            Node* b = a->edges;
            while (b != NULL && b->data <= n2){
                if (b->data == n2){
                    check = true;
                    return true;
                }
                b = b->next;
            }
            if (check == false){
                return false;
            }
            return false;
        }

        /* BFS traversal of the vertices reachable from node n */
        void breath_first_search(int n);

        /* DFS traversal of the vertices reachable from node n */
        void deep_first_search(int n);

        void Dijkstra(int n){
            int node_idx[this->count]; 
            Node2* a = this->root;
            int i = 0;
            while (a != NULL){
                node_idx[i] = a->data;
                a = a->next;
                i ++;
            }
            // cai dat
            int inf = 999;
            int dist[this->count];
            int prev[this->count];
            dist[0] = 0;
            for (int i=1; i<this->count; i++){
                if (is_near(n, node_idx[i])){
                    dist[i] = edge_weight(n, node_idx[i]);
                    prev[i] = n;
                }
                else dist[i] = inf;
            }

            // thuat toan...
            for (int i=1; i<this->count; i++){
                cout << "processing";
            }
        }
};