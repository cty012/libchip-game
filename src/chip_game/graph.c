#include <chip_game/graph.h>

void vertex_init(Vertex* vertex, void* val) {
    vector_init(&vertex->neighbors, sizeof(char*));
    vertex->val = val;
}

void vertex_free(Vertex* vertex, bool free_val) {
    vector_free(&vertex->neighbors);
    if (free_val) free(vertex->val);
}

void graph_init(Graph* graph) {
    hashmap_init(&graph->vertices);
}

void graph_free(Graph* graph, bool free_val) {
    // Free all vertices
    Vector key_val_pairs;
    vector_init(&key_val_pairs, sizeof(KeyValPair*));
    size_t vsize = vector_size(&key_val_pairs);
    for (size_t i = 0; i < vsize; i++) {
        KeyValPair* pair = *(KeyValPair**)vector_at(&key_val_pairs, i);
        vertex_free(pair->val, free_val);
    }
    vector_free(&key_val_pairs);
    // Free the hash map
    hashmap_free(&graph->vertices, true);
}

Vertex* graph_get_vertex(Graph* graph, const char* label) {
    return hashmap_at(&graph->vertices, label);
}

int graph_get_vertices(Graph* graph, Vector* vector) {
    return hashmap_keys(&graph->vertices, vector);
}

int graph_insert_vertex(Graph* graph, char* label, void* val) {
    Vertex* vertex = graph_get_vertex(graph, label);
    if (vertex) {
        vertex->val = val;
        return 1;
    }
    vertex = malloc(sizeof(Vertex));
    vertex_init(vertex, val);
    hashmap_insert(&graph->vertices, label, vertex, false);
    return 0;
}

// @todo
size_t graph_remove_vertex(Graph* graph, const char* label, bool free_val) {
    (void)graph; (void)label; (void)free_val; return 0;
}

// @todo
bool graph_has_edge(Graph* graph, const char* label1, const char* label2) {
    (void)graph; (void)label1; (void)label2; return false;
}

// @todo
int graph_insert_edge(Graph* graph, const char* label1, const char* label2) {
    (void)graph; (void)label1; (void)label2; return 0;
}

// @todo
size_t graph_remove_edge(Graph* graph, char* label, bool free_val) {
    (void)graph; (void)label; (void)free_val; return 0;
}

// @todo
size_t graph_clear(Graph* graph, bool free_val) {
    (void)graph; (void)free_val; return 0;
}


