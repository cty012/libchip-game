#pragma once

#include <chip_game/map.h>

typedef struct {
    Vector neighbors;  // [Vector<char*>] Stores vertex names (owned by HashMap)
    void* val;  // [void] Stores vertex value (owned by user)
} Vertex;

/**
 * Simple undirected unweighted graph class.
 */
typedef struct {
    HashMap vertices;  // Key: vertex name (owned by HashMap); Val: pointer to a Vertex struct (owned by HashMap)
} Graph;

/**
 * Constructor of Vertex.
 * @param vertex The vertex to initialize.
 * @param val The value of the vertex.
 */
void vertex_init(Vertex* vertex, void* val);

/**
 * Destructor of Vertex.
 * @param vertex The vertex to destroy.
 * @param free_val Whether to free the values stored in the vertex.
 */
void vertex_free(Vertex* vertex, bool free_val);

/**
 * Constructor of Graph.
 * @param graph The graph to initialize.
 */
void graph_init(Graph* graph);

/**
 * Destructor of Graph.
 * @param graph The graph to destroy.
 * @param free_val Whether to free the values stored in the vertex.
 */
void graph_free(Graph* graph, bool free_val);

/**
 * Returns the pointer to the Vertex struct associated with the given vertex. If the vertex doesn't exist will return
 * NULL.
 * @param graph The target graph.
 * @param label The label of the vertex to find.
 * @return The pointer to the Vertex struct, or NULL if it doesn't exist.
 */
Vertex* graph_get_vertex(Graph* graph, const char* label);

/**
 * Fill the vector with labels of all vertices.
 * @param graph The target graph.
 * @param vector [Vector<char*>] The vector to fill. Assumed to be initialized.
 * @return Error code. 0: Success; 1: Invalid argument;
 */
int graph_get_vertices(Graph* graph, Vector* vector);

/**
 * Insert a new vertex into the graph. If a vertex with the given label already exists, overwrite the value.
 * @param graph The target graph.
 * @param label The label of the new vertex.
 * @param val The value of the new vertex.
 * @param free_val If need to overwrite, whether to free the values stored in the vertex.
 * @return Error code. 0: Vertex doesn't exist; 1: Vertex exist and overwritten;
 */
int graph_insert_vertex(Graph* graph, char* label, void* val);

/**
 * Removes an existing vertex from the graph. Also removes all edges associated to it.
 * @param graph The target graph.
 * @param free_val Whether to free the values stored in the vertex.
 * @return Number of vertices removed.
 */
size_t graph_remove_vertex(Graph* graph, const char* label, bool free_val);

/**
 * Check whether the specified edge is in the graph.
 * @param graph The target graph.
 * @param label1 The label of the first endpoint.
 * @param label2 The label of the second endpoint.
 * @return Whether the edge exists.
 */
bool graph_has_edge(Graph* graph, const char* label1, const char* label2);

/**
 * Insert a new edge into the graph. If an edge with the given endpoints already exists, do nothing.
 * @param graph The target graph.
 * @param label1 The label of the first endpoint.
 * @param label2 The label of the second endpoint.
 * @return Error code. 0: Edge doesn't exist; 1: Edge exist;
 */
int graph_insert_edge(Graph* graph, const char* label1, const char* label2);

/**
 * Removes an existing edge from the graph.
 * @param graph The target graph.
 * @param label1 The label of the first endpoint.
 * @param label2 The label of the second endpoint.
 * @return Number of edges removed.
 */
size_t graph_remove_edge(Graph* graph, char* label, bool free_val);

/**
 * Clears the graph of vertices and edges.
 * @param graph The target graph.
 * @param free_val Whether to free the values stored in the vertex.
 * @return Number of vertices removed.
 */
size_t graph_clear(Graph* graph, bool free_val);
