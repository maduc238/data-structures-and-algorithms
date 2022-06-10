#include <iostream>
#include <string>
#include "sort.hpp"
#include "queue.hpp"
#include "stack.hpp"

/* Configure data type for weight
You can change it as: int, unsigned int, float, double,...
*/
typedef float weight_type;

/* The single node use for edges structure */
class Node{
    public:
    int data;
    weight_type weight;
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
    std::string name;
    Node2* next;
    Node* edges;

    Node2(){
        data = 0;
        next = NULL;
        edges = NULL;
        name = "";
    }

    ~Node2(){
        delete[] edges;
        delete[] next;
        data = 0;
        next = NULL;
        edges = NULL;
        name = "";
    }

    void _add_node(int data, weight_type weight){
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
                std::cout << "Warning: This node already exists in graph\n";
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
                    weight_type temp_weight = a->weight;
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
                weight_type temp_weight = a->weight;
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
            std::cout << "Warning: Can't find node " << node << " in this graph\n";
    }

    void _change_weight(int node, weight_type w){
        Node* a = edges;
        bool check = false;
        while (a != NULL && a->data <= node){
            if (a->data == node){
                check = true;
                break;
            }
            a = a->next;
        }
        if (check == true)
            a->weight = w;
        else
            std::cout << "Warning: Can't find node " << node << " in this graph\n";
    }
};
namespace hidden_function{
/* A helper function to print all linked list in the data structure */
void print_all_edge(Node* node){
    if (node == NULL)
        return;
    if (node->next == NULL) std::cout << node->data << " (" << node->weight << ")";
    else std::cout << node->data << " (" << node->weight << ") - ";
    print_all_edge(node->next);
}

/* A hepler function to print all linked list in the data structure */
void print_all_node(Node2* node){
    if (node == NULL)
        return;
    std::cout << node->data << " (" << node->name << "): ";
    print_all_edge(node->edges);
    std::cout << "\n";
    print_all_node(node->next);
}

/* A helper function */
void _exchange(Node2* a){
    // Exchange two data of nodes
    int temp_data = a->data;
    a->data = a->next->data;
    a->next->data = temp_data;
    std::string temp_name = a->name;
    a->name = a->next->name;
    a->next->name = temp_name;
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

void print_path(int dest, int idx[], int prev[]){
    if (dest == -1 || dest == 0) return;
    //std::cout << idx[dest] << " ";
    std::cout << idx[dest] << " ";
    print_path(prev[dest], idx, prev);
}

void print_path(int dest, int idx[], int prev[], std::string names[]){
    if (dest == -1 || dest == 0) return;
    //std::cout << idx[dest] << " ";
    std::cout << names[dest] << " - ";
    print_path(prev[dest], idx, prev, names);
}

/**
 * Quick Sort
**/
void swap(weight_type* a, weight_type* b){
	weight_type t = *a;
	*a = *b;
	*b = t;
}
void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}
void heapify(weight_type arr[], int a1[], int a2[], int n, int i){
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i){
		swap(&arr[i], &arr[largest]);
        swap(&a1[i], &a1[largest]);
        swap(&a2[i], &a2[largest]);
		heapify(arr, a1, a2, n, largest);
	}
}
void heap_sort(weight_type arr[], int a1[], int a2[], int n){
	for(int i = n/2 - 1; i >= 0; i--)
		heapify(arr, a1, a2, n, i);
	for(int i = n - 1; i > 0; i--){
		swap(&arr[0], &arr[i]);
        swap(&a1[0], &a1[i]);
        swap(&a2[0], &a2[i]);
		heapify(arr, a1, a2, i, 0);
	}
}

int arg_arr(int n, int a[], int len){
    int i;
    for (i=0;i<len;i++){
        if (a[i] == n) break;
    }
    return i;
}
}

weight_type inf = 99999;
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

        ~Graph(){
            delete[] this->root;
            this->count = 0;
        }

        /* A void function, insert a new node to the graph.
        Example: You want to add node 5:
        Graph G;
        G.add_node(5);
        This node's name will be set "None" */
        void add_node(int data){
            //First element
            if (this->root == NULL){
                this->root = new Node2();
                this->root->data = data;
                this->root->name = "None";
                count++;
            }
            // Else if this node is not the first
            else{
                Node2* a = this->root;
                while(a->data < data && a->next != NULL){
                    a = a->next;
                }
                if (a->data == data){
                    std::cout << "Warning: Node " << data << " already exists in this graph\n";
                    return;
                }
                Node2* temp = new Node2();
                temp->data = data;
                temp->name = "None";
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
        /* A void function, insert a new node to the graph.
        Example: You want to add node 5 with name "Home":
        Graph G;
        G.add_node(5, "Home"); */
        void add_node(int data, std::string name){
            //First element
            if (this->root == NULL){
                this->root = new Node2();
                this->root->data = data;
                this->root->name = name;
                count++;
            }
            // Else if this node is not the first
            else{
                Node2* a = this->root;
                while(a->data < data && a->next != NULL){
                    a = a->next;
                }
                if (a->data == data){
                    std::cout << "Warning: Node " << data << " already exists in this graph\n";
                    return;
                }
                Node2* temp = new Node2();
                temp->data = data;
                temp->name = name;
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

        //Acess a node in graph.
        Node2* acess_node(int n){
            Node2* a = this->root;
            while(a!=NULL &&(a->data)<n){
                a=a->next;
            }
            return a;
        }

        /* Insert a new edge in this graph without weight. The two edges in these variables must exist in graph.
        If node 2 and 3 are already existed in graph: (The weight will be set 0.0)
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
                std::cout << "Waring: There is some node(s) that does not exist in this graph\n";
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
        If node 2 and 3 are already existed in graph and weight is 4.5:
        add_edge(2, 3, 4.5); */
        void add_edge(int node1, int node2, weight_type weight){
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
                std::cout << "Waring: There is some node(s) that does not exist in this graph\n";
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

        /* Change weight for edge (node1 - node2) */
        void change_weight(int node1, int node2, weight_type weight){
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
                std::cout << "Waring: There is some node(s) that does not exist in this graph\n";
                return;
            }
            a = this->root;
            while (a->data <= node1 || a->data <= node2){
                if (a->data == node1) a->_change_weight(node2, weight);
                if (a->data == node2) a->_change_weight(node1, weight);
                if (a->next == NULL) break;
                a = a->next;
            }
        }

        /* A helper function, shows the total number of nodes in the graph */
        void print_count(){
            std::cout << this->count <<"\n";
        }
        /* A helper function, return the total number of nodes in the graph */
        int counts(){
            return this->count;
        }

        /* A void function print all graph's data: nodes and edges in a node struct
        Just a function that supports displaying data, no application to the algorithm.*/
        void print_graph_data(){
            if (this->root == NULL)
                std::cout << "Warning: There are no nodes in this graph\n";
            hidden_function::print_all_node(this->root);
        }

        /* A void function help displaying data with a Graph matrix */
        void print_matrix();

        /* A void function print all nodes in graph G. If graph G have nodes 2,3,4,6,7:
        G.print_nodes();
        -> All nodes: 2, 3, 4, 6, 7 */
        void print_nodes(){
            Node2* a = this->root;
            std::cout << "All nodes: ";
            while (a != NULL){
                std::cout << a->data;
                if (a->next != NULL) std::cout << ", ";
                a = a->next;
            }
            std::cout << "\n";
        }

        /*  A void function print all nodes in graph G. If graph G have egdes (0-1), (1-3), (3,2), (2,1):
        G.print_edges();
        -> All edges: (0 - 1), (1 - 2), (1 - 3), (2 - 3) */
        void print_edges(){
            Node2* a = this->root;
            std::cout << "All edges: ";
            while (a != NULL){
                Node* b = a->edges;
                while (b != NULL){
                    if (a->data <= b->data)
                        std::cout <<"("<<a->data<<" - "<<b->data<<")";
                    if (b->next != NULL && a->data <= b->next->data) std::cout<< ", ";
                    b = b->next;
                }
                a = a->next;
            }
            std::cout << "\n";
        }

        int num_edges(){
            Node2* a = this->root;
            int c=0;
            while (a != NULL){
                Node* b = a->edges;
                while (b != NULL){
                    if (a->data <= b->data) c++;
                    b = b->next;
                }
                a = a->next;
            }
            return c;
        }

        /* Return degree of node n
        */
        int node_degree(int n){
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
                return 0;
            }
            Node* b = a->edges;
            int c = 0;
            while (b != NULL){
                c++;
                b = b->next;
            }
            return c;
        }

        /* Given a node name n, this function will delete this node from the graph.
        If node 2 is already existed in graph:
        G.delete_node(2); */
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
                std::cout << "Warning: Can't find node " << n << " in this graph\n";
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
        weight_type edge_weight(int node1, int node2){
            Node2* a = this->root;
            weight_type result = inf;
            while(a != NULL && a->data <= node1){
                if(a->data == node1){
                    Node* b = a->edges;
                    while(b != NULL && b->data <= node2){
                        if (b->data == node2){
                            result = b->weight;
                            break;
                        }
                        b = b->next;
                    }
                }
                a = a->next;
            }
            if (result == inf){ std::cout << "Warning: This edge does not exist in graph\n"; }

            return result;
        }

        /* A void function insert a sequence numbers of nodes in graph, starting from 0 by default.
        This graph must be empty, or else it will break and stop the initialization.
        Graph will have node 0,1,...,7 (with 8 nodes):
        add_sequence_node(8); */
        void add_sequence_node(int number_node){
            if (this->root != NULL){
                // This graph did not empty
                std::cout << "Warning: Some nodes still exist in the graph, this graph must be empty\n";
                return;
            }
            else if (number_node < 1){
                std::cout << "Warning: number_node must be greater than 1\n";
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
                std::cout << "Warning: Can't find node " << n << " in this graph\n";
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
                std::cout << "Warning: Some nodes still exist in the graph, this graph must be empty\n";
                return;
            }
            else if (n_nodes < 1){
                std::cout << "Warning: number_node must be greater than 1\n";
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

        /* Check if node n1 and node n2 are neighbor */
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
        int* breath_first_search(int n){
            struct queue* q = create_queue();
            int arr[this->count]={};
            int result[this->count];
            int j=0;
            add_element_into_queue(q, n);
            arr[n]=1;
            while (!isEmpty(q)){
                int currentVertex = remove_element_from_queue(q);
                result[j]=currentVertex;
                j++;
                Node* temp = (this->acess_node(currentVertex))->edges;
                while (temp!=NULL) {
                    int adjVertex = temp->data ;
                    if(arr[adjVertex]==0){
                        arr[adjVertex]=1;
                        add_element_into_queue(q, adjVertex);
                    }
                    temp = temp->next;
                }
            }
            int* p=result;
            return p;
        }

        void print_breath_first_search(int n){
            int *p;
            int node_idx[this->count];
            p = breath_first_search(n);
            for (int i=0; i<this->count; i++){
                node_idx[i] = *(p+i);
            }
            delete[] p;
            for (int i=0; i<this->count; i++){
                std::cout << node_idx[i] << ", ";
            }
            std::cout << "\n";
        }

        /* DFS traversal of the vertices reachable from node n */
        int* depth_first_search(int n){
            struct stack* s;
            init_st(s);
            int arr2[this->count]={};
            int result2[this->count];
            int j=0;
            push(s, n);
            arr2[n]=1;
            while(!isEmp(s)){
                int currentVertex = pop(s);
                result2[j]=currentVertex;
                j++;
                Node* temp2 = (this->acess_node(currentVertex))->edges;
                while (temp2!=NULL) {
                    int adjVertex = temp2->data ;
                    if(arr2[adjVertex]==0){
                        arr2[adjVertex]=1;
                        push(s, adjVertex);
                    }
                    temp2 = temp2->next;
                }           
            
            }
            int* q=result2;
            return q;
        }

        /* The main function that calculates distances of
        shortest paths and show these paths from src to all vertices
        */
        void Dijkstra(int n){
            int node_idx[this->count];
            std::string names[this->count];
            int F[this->count];
            weight_type dist[this->count];
            int prev[this->count];
            node_idx[0] = n;
            F[0] = 1;   // v0 in F
            dist[0] = 0;
            prev[0] = -1;
            Node2* a = this->root;
            int i = 1;
            while (a != NULL){
                if (a->data == n){
                    names[0] = a->name;
                    a = a->next;
                    continue;
                }
                node_idx[i] = a->data;
                names[i] = a->name;
                F[i] = 0;
                dist[i] = inf;
                prev[i] = -1;
                i++;
                a = a->next;
            }
            a = this->root;
            while (a != NULL){
                if (a->data == n) break;
                a = a->next;
            }
            Node* b = a->edges;
            while (b != NULL){
                int idx = hidden_function::arg_arr(b->data, node_idx, this->count);
                dist[idx] = b->weight;
                prev[idx] = 0;
                b = b->next;
            }
            delete[] b;
            for (int i=1; i<this->count; i++){
                weight_type dist_min = inf;
                int m_min = -1;
                for (int m=1; m<this->count; m++){
                    if ((F[m] == 0) && (dist[m] < dist_min)){
                        dist_min = dist[m];
                        m_min = m;
                    }
                }
                if (m_min == -1) continue;
                F[m_min] = 1;
                a = this->root;
                while (a != NULL){
                    if (a->data == node_idx[m_min]) break;
                    a = a->next;
                }
                b = a->edges;
                while (b != NULL){
                    int k = hidden_function::arg_arr(b->data, node_idx, this->count);
                    if (!F[k]){
                        weight_type distance = dist[m_min] + b->weight;
                        if (dist[k] > distance){
                            dist[k] = distance;
                            prev[k] = m_min;
                        }
                    }
                    b = b->next;
                }
                delete[] b;
            }
            std::cout << "Dijkstra algorithm:\n";
            for (int i=1; i<this->count; i++){
                std::cout<<"From "<< names[i] <<" to "<<names[0]<<": ";
                hidden_function::print_path(i, node_idx, prev, names);
                std::cout << names[0] << "\n";
            }
        }

        /* The main function that finds shortest distances from src to all
        other vertices using Bellman-Ford algorithm.
        */
        void Bellman_Ford(int n){
            int node_idx[this->count];
            std::string names[this->count];
            weight_type dist[this->count];
            int prev[this->count];
            node_idx[0] = n;
            dist[0] = 0;
            prev[0] = -1;
            Node2* a = this->root;
            int i = 1;
            while (a != NULL){
                if (a->data == n){
                    names[0] = a->name;
                    a = a->next;
                    continue;
                }
                prev[i] = -1;
                node_idx[i] = a->data;
                names[i] = a->name;
                dist[i] = inf;
                i++;
                a = a->next;
            }
            bool key = false;
            while (!key){
                key = true;
                for (int u=0; u<this->count; u++){
                    a = this->root;
                    while (a != NULL){
                        if (a->data == node_idx[u]) break;
                        a = a->next;
                    }
                    Node* b = a->edges;
                    while (b != NULL){
                        int v = hidden_function::arg_arr(b->data, node_idx, this->count);
                        weight_type distance = dist[u] + b->weight;
                        if (distance < dist[v]){
                            dist[v] = dist[u] + b->weight;
                            prev[v] = u;
                            key = false;
                        }
                        b = b->next;
                    }
                    delete[] b;
                }
            }
            std::cout << "Bellman-Ford algorithm:\n";
            for (int i=1; i<this->count; i++){
                std::cout<<"From "<< names[i] <<" to "<<names[0]<<": ";
                hidden_function::print_path(i, node_idx, prev, names);
                std::cout << names[0] << "\n";
            }
        }

        /* The Floyd Warshall Algorithm is for solving the All Pairs Shortest Path problem. 
        The problem is to find shortest distances between every pair of vertices in a given edge 
        weighted directed Graph. This function print Shortest distance matrix
        */
        void Floyd(){
            int node_idx[this->count];
            Node2* a = this->root;
            int i = 0;
            while (a != NULL){
                node_idx[i] = a->data;
                a = a->next;
                i ++;
            }
            weight_type D[this->count][this->count];
            int P[this->count][this->count];
            for (int i=0;i<this->count;i++){
                for (int j=i;j<this->count;j++){
                    P[i][j] = -1;
                    P[j][i] = -1;
                    if (i == j){
                        D[i][j] = 0; D[j][i] = 0;
                    }
                    else if (is_near(node_idx[i],node_idx[j])){
                        D[i][j] = edge_weight(node_idx[i],node_idx[j]);
                        D[j][i] = D[i][j];
                    }
                    else{
                        D[i][j] = inf; D[j][i] = inf;
                    }
                }
            }
            for (int i=0;i<this->count;i++){
                for (int j=0;j<this->count;j++){
                    for (int k=0;k<this->count;k++){
                        if (D[i][j] > (D[i][k] + D[k][j])){
                            D[i][j] = D[i][k] + D[k][j];
                            P[i][j] = k;
                        }
                    }
                }
            }
            std::cout << "Floyd algorithm\n\t";
            for (int i=0;i<this->count;i++){
                std::cout << node_idx[i] << "\t";
            }
            std::cout << "\n\n";
            for (int i=0;i<this->count;i++){
                std::cout << node_idx[i] << "\t";
                for (int j=0;j<this->count;j++){
                    std::cout << D[i][j] << "\t";
                }
                std::cout << "\n";
            }
        }

        /* Print shortest path from node n1 to node n2 */
        void Shortest_path_Dijkstra(int n1, int n2){
            int node_idx[this->count];
            int F[this->count];
            weight_type dist[this->count];
            int prev[this->count];
            node_idx[0] = n2;
            F[0] = 1;   // v0 in F
            dist[0] = 0;
            prev[0] = -1;
            Node2* a = this->root;
            int i = 1;
            while (a != NULL){
                if (a->data == n2){
                    a = a->next;
                    continue;
                }
                node_idx[i] = a->data;
                F[i] = 0;
                dist[i] = inf;
                prev[i] = -1;
                i++;
                a = a->next;
            }
            a = this->root;
            while (a != NULL){
                if (a->data == n2) break;
                a = a->next;
            }
            Node* b = a->edges;
            while (b != NULL){
                int idx = hidden_function::arg_arr(b->data, node_idx, this->count);
                dist[idx] = b->weight;
                prev[idx] = 0;
                b = b->next;
            }
            delete[] b;
            for (int i=1; i<this->count; i++){
                weight_type dist_min = inf;
                int m_min = -1;
                for (int m=1; m<this->count; m++){
                    if ((F[m] == 0) && (dist[m] < dist_min)){
                        dist_min = dist[m];
                        m_min = m;
                    }
                }
                if (m_min == -1) continue;
                F[m_min] = 1;
                a = this->root;
                while (a != NULL){
                    if (a->data == node_idx[m_min]) break;
                    a = a->next;
                }
                b = a->edges;
                while (b != NULL){
                    int k = hidden_function::arg_arr(b->data, node_idx, this->count);
                    if (!F[k]){
                        weight_type distance = dist[m_min] + b->weight;
                        if (dist[k] > distance){
                            dist[k] = distance;
                            prev[k] = m_min;
                        }
                    }
                    b = b->next;
                }
                delete[] b;
            }
            std::cout<<"From "<< n1 <<" to "<< n2 <<": ";
            hidden_function::print_path(hidden_function::arg_arr(n1, node_idx, this->count),
                node_idx, prev);
            std::cout << n2 << "\n";
        }

        /* Print shortest path from node n1 to node n2 */
        void Shortest_path_Bellman_Ford(int n1, int n2){
            int node_idx[this->count];
            weight_type dist[this->count];
            int prev[this->count];
            node_idx[0] = n2;
            dist[0] = 0;
            prev[0] = -1;
            Node2* a = this->root;
            int i = 1;
            while (a != NULL){
                if (a->data == n2){
                    a = a->next;
                    continue;
                }
                prev[i] = -1;
                node_idx[i] = a->data;
                dist[i] = inf;
                i++;
                a = a->next;
            }
            bool key = false;
            while (!key){
                key = true;
                for (int u=0; u<this->count; u++){
                    a = this->root;
                    while (a != NULL){
                        if (a->data == node_idx[u]) break;
                        a = a->next;
                    }
                    Node* b = a->edges;
                    while (b != NULL){
                        int v = hidden_function::arg_arr(b->data, node_idx, this->count);
                        weight_type distance = dist[u] + b->weight;
                        if (distance < dist[v]){
                            dist[v] = dist[u] + b->weight;
                            prev[v] = u;
                            key = false;
                        }
                        b = b->next;
                    }
                    delete[] b;
                }
            }
            std::cout<<"From "<< n1 <<" to "<< n2 <<": ";
            hidden_function::print_path(hidden_function::arg_arr(n1, node_idx, this->count),
                node_idx, prev);
            std::cout << n2 << "\n";
        }

        /* Returns true if the graph contains a cycle, else false.
        To initial this function, visited = {}, count = 0
        Example: Cycle_Detec(s, c, {}, 0);
        */
        bool Cycle_Detec(int s, int c, int visited[], int count){
            Node2* a = this->root;
            while (a != NULL && a->data <= c){
                if (a->data == c){
                    break;
                }
                a = a->next;
            }
            Node* b = a->edges;
            int num = node_degree(c);
            if (num == 0) return false;
            else {
                int Ac[num];
                for (int i=0;i<num;i++){
                    Ac[i] = b->data;
                    b = b->next;
                }
                bool check = false;
                for (int i=0;i<num;i++){
                    if (Ac[i] == s){
                        check = true;
                        break;
                    }
                }
                if (check == true) return true;
                else{
                    for (int i=0;i<num;i++){
                        check = true;
                        for (int j=0;j<count;j++){
                            if (visited[j] == Ac[i])
                                check = false;
                        }
                        if (check == true){
                            int vi[count+1];
                            for (int k=0;k<count;k++){
                                vi[k] = visited[k];
                            }
                            vi[count] = Ac[i];
                            if (Cycle_Detec(s, Ac[i], vi, count+1))
                                return true;
                        }
                    }
                    return false;
                }
            }
            return false;
        }

        /* Returns true if the graph contains a cycle with two node s and c,
        else false.
        */
        bool Cycle_Detection(int s, int c){
            return Cycle_Detec(s, c, {}, 0);
        }

        /* What is Minimum Spanning Tree? 
        Given a connected and undirected graph, a spanning tree of that graph is a subgraph that is a tree and connects 
        all the vertices together. A single graph can have many different spanning trees. A minimum spanning tree (MST) 
        or minimum weight spanning tree for a weighted, connected, undirected graph is a spanning tree with a weight less 
        than or equal to the weight of every other spanning tree. The weight of a spanning tree is the sum of weights given 
        to each edge of the spanning tree.
        This function will return a new Graph. Example with Graph G, you want to make a MST for this graph:
            Graph G_new = G.SpanningTree_Kruskal();
        */
        Graph SpanningTree_Kruskal(){
            Graph temp;
            Node2* a = this->root;
            int ne = num_edges();
            int nn = 0;
            int S1[ne], S2[ne];
            weight_type W[ne];
            int i = 0;
            while (a != NULL){
                Node* b = a->edges;
                while (b != NULL){
                    if (a->data <= b->data){
                        S1[i] = a->data;
                        S2[i] = b->data;
                        W[i] = b->weight;
                        i++;
                    }
                    b = b->next;
                }
                delete[] b;
                temp.add_node(a->data);
                nn++;
                a = a->next;
            }
            hidden_function::heap_sort(W, S1, S2, ne);
            i = 0;
            while (i < ne && temp.num_edges() < nn - 1){
                int visited[0];
                if (!temp.Cycle_Detection(S1[i],S2[i])){
                    temp.add_edge(S1[i],S2[i],W[i]);
                }
                i++;
            }
            return temp;
        }
};

/* An example graph - to make fat tree topology in data center network */
Graph fattree_graph(int k){
    int lastCore = k*k/4;
    int lastAggre = lastCore + k*k/2;
    int lastEdge = lastAggre + k*k/2;
    int lastServer = lastEdge + k*k*k/4;
    Graph temp;
    for (int i=0;i<lastServer;i++){
        temp.add_node(i+1);
    }
    for (int pod=0; pod<k; pod++){
        for (int aggre=0; aggre<k/2; aggre++){
            for (int i=0; i<k/2; i++){
                temp.add_edge(lastCore+pod*k/2+aggre+1, 2*lastCore/k*aggre+i+1, 1);
                temp.add_edge(lastCore+pod*k/2+aggre+1, lastAggre+pod*k/2+i+1, 1);
                temp.add_edge(lastAggre+pod*k/2+i+1, lastEdge+pod*k*k/4+k/2*i+aggre+1, 1);
            }
        }
    }
    return temp;
}