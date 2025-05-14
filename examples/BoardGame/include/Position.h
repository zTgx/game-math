#include <functional>

using Position = std::pair<int, int>; // row, col

// Custom hash function for Position (std::pair<int, int>)
struct PositionHash {
    size_t operator()(const Position& pos) const {
        // Combine hashes of the two integers (simple approach)
        return std::hash<int>()(pos.first) ^ (std::hash<int>()(pos.second) << 1);
    }
};

// Custom equality function (optional, but good practice)
struct PositionEqual {
    bool operator()(const Position& lhs, const Position& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};