#include <iostream>
#include <utility> // For std::pair
#include <functional> // For std::hash

template <typename V>
struct Edge {
    V from; // Source vertex
    V to;   // Destination vertex
    /**
     * @brief constractor new edge
     * @param from - the vertex we out from
     * @param to - the vertex we sign in to
     */
    Edge(const V &from, const V &to) : from(from), to(to) {}


    /**
     * @brief return true if the two edges equal
     * @param other - the other edge we equal
     */
    bool operator==(const Edge<V> &other) const {
        return from == other.from && to == other.to;
    }

   
};

// Custom hash function for Edge
template <typename V>
struct EdgeHash {
    /**
     * @brief hashed edge
     */
    std::size_t operator()(const Edge<V> &edge) const {
        auto hash1 = std::hash<V>()(edge.from);
        auto hash2 = std::hash<V>()(edge.to);
        return hash1 ^ (hash2 << 1); // Combine the two hash values
    }
};