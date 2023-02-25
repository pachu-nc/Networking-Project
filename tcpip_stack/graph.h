#ifndef __GRAPH__
#define __GRAPH__
 
#include "gluethread/glthread.h"
#include<string.h>


#define MAX_INTF_PER_NODE   10
#define NODE_NAME_SIZE      16
#define IF_NAME_SIZE        16


typedef struct node_ node_t;
typedef struct link_ link_t;

typedef struct interface_
{
    char if_name[IF_NAME_SIZE];
    struct node_ *att_node; /*A node to which this interface is connected to*/
    struct link_ *link;     /*Interface is a part of a link*/
} interface_t;


/*Link is a pair of interfaces*/
struct link_ { 
    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
};

/*A node is nothing but a set of interface slots. like a router can be considered a node */
/*So, a node would have a name and a pointer to an array of interface slots */
typedef struct node_ {
    char node_name[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE]; /*Empty slot of the node*/
    glthread_t graph_glue;
}node_t;
GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, graph_glue);

typedef struct graph_ {
    char topology_name[32];
    glthread_t node_list;
}graph_t;

static inline node_t *get_nbr_node(interface_t *interface){
    link_t *link = interface->link;

    if(&link->intf1 == interface) {
        return link->intf2.att_node;
    }
    else {
        return link->intf1.att_node;
    }
}

static inline int get_node_intf_available_slot(node_t *node) {
    int node_no;
    for (node_no = 0; node_no < MAX_INTF_PER_NODE; node_no++)
    {
        if (node->intf[node_no])
            continue;
        return node_no;
    }
}

static inline interface_t *
get_node_if_by_name(node_t *node, char *if_name) {
    int i;
    for(i=0; i < MAX_INTF_PER_NODE; i++) {
        if(strcmp((node->intf[i]->if_name), if_name) == 0)
            return node->intf[i]->att_node;
    }
}

static inline node_t *
get_node_by_node_name(graph_t *topo, char *node_name) {
    
}



void dump_graph_topo(graph_t *graph);
void dump_node(node_t *node);
void dump_interface(interface_t *interface);

#endif /*End of __GRAPH__*/
