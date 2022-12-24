#pragma once

// #include 

#include "Record.hpp"

template<StringLiteral Name, typename... columns>
struct Table {
    using id_type = int;
    using types = typename ColumnTypeResolver<Column<"id", id_type>, columns...>::type;
    using data_tuple_t = typename TupleCreator<types>::type;

    using record_t = Record<Column<"id", id_type>, columns...>;

    static std::optional<record_t> optional_find_by(pqxx::work &tr, const std::string &key, const std::string &value) {
        std::stringstream ss;

        ss << "SELECT * from " << std::quoted(Name.value);
        ss << " WHERE " << tr.esc(key) << " = " << std::quoted(tr.esc(value), '\'') << ";";

        pqxx::result res = tr.exec(ss.str());

        std::cout << res.affected_rows() << std::endl;

        if (res.affected_rows() == 0) {
            return {};
        }

        return record_t(Name.value, RowGetter<types>::get_tuple(res[0]));
    }

    static record_t find_by(pqxx::work &tr, const std::string &key, const std::string &value) {
        std::stringstream ss;

        ss << "SELECT * from " << std::quoted(Name.value);
        ss << " WHERE " << tr.esc(key) << " = " << std::quoted(tr.esc(value), '\'') << ";";

        return record_t(Name.value, Executor<types>::execute(tr, ss.str()));
    }

    static record_t find_by_id(pqxx::work &tr, int id) {
        return find_by(tr, "id", std::to_string(id));
    }

    static std::optional<record_t> optional_find_by_id(pqxx::work &tr, int id) {
        return optional_find_by(tr, "id", std::to_string(id));
    }

    template <typename... Ts>
    static void create(pqxx::work &tr, Ts... args) {
        std::vector<std::string> field_names;
        pushColumnNames<columns...>(field_names);

        std::string column_names = "";

        for (unsigned int i = 0; i < field_names.size() - 1; ++i) {
            column_names += field_names[i] + ",";
        }
        column_names += field_names[field_names.size() - 1];

        std::string table_name = std::string("\"") + Name.value + "\"";
        pqxx::stream_to::raw_table(tr, {table_name}, column_names).write_values(args...);
    }
};
