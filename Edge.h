template<class V>
struct Edge{
        V from;
        V to;
        /**
         * @brief - build a Edge object
         * @param from -the vertex the edge out from
         * @param to - the vertex the edge sign in
         */
        Edge(const V &from , const V &To){
            this->from = from;
            this->to = to;
        }

        private:
        /**
         * @brief return true if the edges are equal
         * @param edge1 - the first edge we equal
         * @param edge2 - the second edge we equal
         * @return true if the edges are equal
         */
        friend bool operator==(const Edge &edge1 ,const Edge &edge2) const {
            return edge1.from == edge1.from && edge1.to == edge2.to;
        }
};

template<class V>
struct EdgeHash {
    std::size_t operator()(const Edge& edge) const {
        return std::hash<int>()(edge.from) ^ std::hash<int>()(edge.to << 1);
    }
};