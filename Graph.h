#pragma once
#include "Edge.h"
template<class V,class W>
class Graph{
    public:
    /**
     * @brief return true if we have this edge
     * and otherwise false
     * @param from - the edge we out from
     * @param to - the edge we sign in
     * @return true/false
     */
    bool ContainEdge(const V &from ,const V &to)const{
        Edge<V> searchedge(from,to);
        auto it = graph.find(searchedge);
        return it != graph.end();
    }
    
    /**
     * @brief set a new edge to the graph
     * @param from - the edge we out from
     * @param to - the edge we sign in
     */
    void SetEdge(const V &from ,const V &to,const W& weight){
        Edge<V> edge(from,to);
        graph[edge] = weight;
    }


    /**
     * @brief return the weight of the edge we take
     * @param from - the vertex we out
     * @param to - the vertex we sign in
     */
    W& operator()(const V& from, const V& to) {
        Edge edge(from,to);
        return graph[edge];
    }

    private:
    unordered_map<Edge<V>,W,EdgeHash<V>> graph;
};