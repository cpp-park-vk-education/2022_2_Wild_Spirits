#pragma once

#include "Utils.hpp"

template <typename... columns>
class Record {
public:
    using id_type = int;
    using types = typename ColumnTypeResolver<columns...>::type;
    using data_tuple_t = typename TupleCreator<types>::type;

private:
    std::vector<std::string> field_names;
    std::string table_name;
    data_tuple_t _data;
    id_type _id;

public:
    constexpr Record(const std::string &table_name, const data_tuple_t &data): table_name(table_name), _data(data), _id(std::get<0>(data)) {
        pushColumnNames<columns...>(field_names);
    }

    template<int id>
    auto get() {
        return std::get<id>(_data);
    }

    id_type id() const {
        return _id;
    }

    const data_tuple_t &data() const {
        return _data;
    }

    void update(pqxx::work &tr, const std::string &key, const std::string &value) {
        std::stringstream ss;

        ss << "UPDATE " << std::quoted(table_name);
        ss << " SET " << tr.esc(key) << " = " << std::quoted(tr.esc(value), '\'');
        ss << " WHERE id = " << id() << ";";

        std::cout << ss.str() << std::endl;

        tr.exec0(ss.str());
    }
};
