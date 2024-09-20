#pragma once
#include "Edge.h"
#include <set>
#include <type_traits> // Include this for std::is_same
#include <algorithm> // for std::max and std::min
#include <iostream> // For std::cout



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
     * @param weight - the weight of the edge
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
     * @brief return the din(v) of the vertex
     * @param vertex - the vertex we search is deg
     * @return int 
     */
    int degin(const V &vertex)const {
        return Son(vertex).size();
    }

    /**
     * @brief return the din(v) of the vertex
     * @param vertex - the vertex we search is deg
     * @return int 
     */
    int degout(const V &vertex)const {
        return Parent(vertex).size();
    }


    template<class Function>
    /**
     * @brief building a graph that vertex are the vals in the set
     * @param vertexs the set of vertexs we put on the graph
     * @param function - the function that calculate the weight of edge
     * @param defaultval - check if the user want default val on the graph
     * 
     */
    Graph(const set<V> &vertexs,const Function &function,
    const bool defaultin = false){
        for(const auto from : vertexs){
            for(const auto to :vertexs){
                SaveEdge(from,to,function(from,to),defaultin);
            }
        }
    }

    template<class Function>
    /**
     * @brief build a graph that his vertex are
     * v1 - v2
     * @param v1 - vertex 1
     * @param v - vertex 2
     * @param function - function that get the weight
     * of the edges
     */
    Graph(const V &v1 ,const V &v2,const Function function,
    const bool defaultin = false){
        V minvertx = std::min(v1,v2);
        V maxvertx = std::max(v1,v2);
        for(V i = minvertx; i <= maxvertx;i++){
            for(V j = minvertx; j <= maxvertx;j++){
                SaveEdge(i,j,function(i,j),defaultin);
            }
        }
    }
    template<class Function>
    /**
     * @brief build a graph that [V(),maxvertex]
     * @param maxvertex - the max vertex we got
     * @param function - the function calculate the weight
     * @param defaultin - the defualt val we take
     */
    Graph(const V &maxvertex, const Function& function, const bool defaultin = false)
        : Graph(V() + 1, maxvertex, function, defaultin) 
        { // Delegating constructor using initializer list
    }

    //default constractor
    Graph() = default;

    /**
     * @brief return the weight of the edge we take
     * @param from - the vertex we out
     * @param to - the vertex we sign in
     * @return refernce of the weight
     */
    W& operator()(const V& from, const V& to) {
        Edge edge(from,to);
        return graph[edge];
    }

    private:
    unordered_map<Edge<V>,W,EdgeHash<V>> graph;
    /**
     * @brief check if we need to save this edge on the memory
     * @param from - the edge we out from
     * @param to - the edge we sign in
     * @param weight - the weight of the edge
     */
    void SaveEdge(const V &from,const V &to,const W &weight,bool defaultin){
        if(!defaultin){
            W defaultweight = W();
            if(defaultweight == weight){
                return;
            }
        }
        SetEdge(from,to,weight);
    }
};


