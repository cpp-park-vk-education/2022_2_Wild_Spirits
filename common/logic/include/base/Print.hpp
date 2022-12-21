#pragma once

#include <ostream>
#include <iterator>
#include <functional>

template <typename T, typename Printer = std::function<void(typename T::value_type, std::ostream&)>>
inline std::ostream& printIterable(T begin, T end, std::ostream& out, Printer print =
                                    [] (typename T::value_type obj, std::ostream& out) { out << obj; }) {
    out << "[ ";
    for (auto it = begin; it != end; ++it) {
        print(*it, out);
        if (std::next(it) != end) {
            out << ", ";
        }
    }
    out << " ]";
    return out;                       
}
