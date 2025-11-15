#ifndef HERB_VISITOR_H
#define HERB_VISITOR_H

#include "ast_node.h"
#include "ast_nodes.h"
#include "util/hb_array.h"

void herb_visit_node(AST_NODE_T* node, bool (*visitor)(AST_NODE_T*, void*), void* data);
void herb_visit_child_nodes(AST_NODE_T* node, bool (*visitor)(AST_NODE_T* node, void* data), void* data);

#endif
