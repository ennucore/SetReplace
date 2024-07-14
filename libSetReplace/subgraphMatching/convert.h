#pragma once

#include <cstddef>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "graph.h"

namespace STMatch {
    // typedef int graph_node_t;
    // typedef long graph_edge_t;
    // typedef char pattern_node_t;
    // typedef char set_op_t;
    // typedef unsigned int bitarray32;
    // typedef struct {
    //     graph_node_t nnodes = 0;
    //     graph_edge_t nedges = 0;
    //     bitarray32* vertex_label;
    //     graph_edge_t* rowptr;
    //     graph_node_t* colidx;
    // } Graph;

    Graph convert_to_arrays(std::vector<std::pair<int, int>> edges) {
        std::vector<int> vertices;
        vertices.reserve(2 * edges.size());
        for (auto &e : edges) {
            vertices.push_back(e.first);
            vertices.push_back(e.second);
        }
        std::sort(vertices.begin(), vertices.end());
        vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());

        Graph g;
        g.nnodes = (graph_node_t)vertices.size();
        g.nedges = (graph_edge_t)edges.size();
        for (auto &e : edges) {
            e.first = (int)(std::lower_bound(vertices.begin(), vertices.end(), e.first) - vertices.begin());
            e.second = (int)(std::lower_bound(vertices.begin(), vertices.end(), e.second) - vertices.begin());
        }

        bitarray32 *vertex_label = new bitarray32[g.nnodes];
        std::fill_n(vertex_label, g.nnodes, 1);

        g.rowptr = new graph_edge_t[g.nnodes + 1];
        g.colidx = new graph_node_t[g.nedges];
        std::sort(edges.begin(), edges.end());
        std::fill_n(g.rowptr, g.nnodes + 1, g.nedges);
        for (int i = (int)edges.size() - 1; i >= 0; --i) {
            g.rowptr[edges[i].first] = i;
            g.colidx[i] = edges[i].second;
        }
        for (int i = (int)g.nnodes - 1; i >= 0; --i) {
            g.rowptr[i] = std::min(g.rowptr[i], g.rowptr[i + 1]); 
        }
        return g;
    }

}