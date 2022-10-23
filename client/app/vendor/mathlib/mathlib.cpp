#include <algorithm>

namespace LM {
    int Max(int V1, int V2, int V3) {
        return std::max(std::max(V1, V2), V3);
    }

    int Min(int V1, int V2, int V3) {
        return std::min(std::min(V1, V2), V3);
    }
}  // namespace LM
