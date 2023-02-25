#include "graph.h"

extern graph_t *build_first_topo();


int main(int argc, char **argv) {
    graph_t *topo = build_first_topo();
    dump_graph_topo(topo);
    return 0;
}