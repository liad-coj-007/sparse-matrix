#pragma once
#include "Edge.h"
#include <set>

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
     * @brief return a set of vertex that goes parent -> other vertex
     * @param parent - the vertex we want to find who the vertex parent
     * @return a set of sons of parent
     */
    set<V> Parent(const V &parent) const {
        set<V> sons;
        for(const auto pair:graph){
            if(pair.first.from == parent){
                sons.insert(pair.first.to);
            }
        }
        return sons;
    }
    
    /**
     * @brief return the parents of the son vertex
     * @param son - the vertex we search his parents
     * @return a set of parents of the son vertex
     */
    set<V> Son(const V &son) const {
        set<V> parents;
        for(const auto pair: graph){
            if(pair.first.to == son){
                parents.insert(pair.first.from);
            }
        }
        return parents;
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