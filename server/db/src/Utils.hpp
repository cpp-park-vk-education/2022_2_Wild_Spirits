#pragma once

#include <iostream>
#include <optional>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> const& opt)
{
    return opt ? os << opt.value() : os << "null";
}

template<typename Type, unsigned N, unsigned Last>
struct tuple_printer {

    static void print(std::ostream& out, const Type& value) {
        out << std::get<N>(value) << ", ";
        tuple_printer<Type, N + 1, Last>::print(out, value);
    }
};

template<typename Type, unsigned N>
struct tuple_printer<Type, N, N> {

    static void print(std::ostream& out, const Type& value) {
        out << std::get<N>(value);
    }

};

template<typename... Types>
std::ostream& operator<<(std::ostream& out, const std::tuple<Types...>& value) {
    out << "(";
    tuple_printer<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(out, value);
    out << ")";
    return out;
}

template <typename... Ts>
struct TypeHolder {};

template <typename... Ts>
struct RowGetter{};

template <typename... Ts>
struct RowGetter<TypeHolder<Ts...>> {
    static std::tuple<Ts...> get_tuple(const pqxx::row &row) {
        return row.as<Ts...>();
    }
};

template <typename... Ts>
struct Executor{};

template <typename... Ts>
struct Executor<TypeHolder<Ts...>> {
    static std::tuple<Ts...> execute(pqxx::work &tr, const std::string &query) {
        return tr.exec1(query).as<Ts...>();
    }
};

template <typename... Ts>
struct TupleCreator{};

template <typename... Ts>
struct TupleCreator<TypeHolder<Ts...>> {
    using type = std::tuple<Ts...>;
};

template<size_t N>
struct StringLiteral {
    // cppcheck-suppress noExplicitConstructor
    constexpr StringLiteral (const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    constexpr char operator[] (unsigned int n) const {
        return value[n];
    }

    constexpr int size() const {
        return sizeof(value);
    }
    
    char value[N];
    int length = N;
};

template <StringLiteral Name, typename Type>
struct Column {
    using type = Type;
    char name[Name.length];

    constexpr Column() {
        for (int i = 0; i < Name.size(); ++i) {
            name[i] = Name[i];
        }
    }
};

template <typename T1, typename T2>
struct TypeAdder {
    using type = TypeHolder<T1, T2>;
};

template <typename T, typename... Ts>
struct TypeAdder<T, TypeHolder<Ts...>> {
    using type = TypeHolder<T, Ts...>;
};

template <typename col, typename... cols>
struct ColumnTypeResolver {
    using type = typename TypeAdder<typename col::type, typename ColumnTypeResolver<cols...>::type>::type;
};

template <typename col>
struct ColumnTypeResolver<col> {
    using type = typename col::type;
};

template <typename col>
void pushColumnNames(std::vector<std::string> &res) {
    res.push_back(col().name);
}

template <typename col_1, typename col_2, typename... cols>
void pushColumnNames(std::vector<std::string> &res) {
    res.push_back(col_1().name);
    pushColumnNames<col_2, cols...>(res);
}

template< typename ... Args >
std::vector<std::string> to_strings(Args const& ... args )
{
    std::vector<std::string> res;
    res.reserve(sizeof...(args));
    using List= int[];
    (void)List{0, ( (void)(res.push_back(args)), 0 ) ... };

    return res;
}
