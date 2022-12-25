#pragma once

#include "Record.hpp"

template<StringLiteral Name, typename... columns>
struct Table {
    using id_type = int;
    using types = ColumnTypeResolver<Column<"id", id_type>, columns...>::type;
    using data_tuple_t = TupleCreator<types>::type;

    using record_t = Record<Column<"id", id_type>, columns...>;

    static std::optional<record_t> optional_find_by(pqxx::work &tr, const std::string &key, const std::string &value) {
        std::stringstream ss;

        ss << "SELECT * from " << std::quoted(Name.value);
        ss << " WHERE " << tr.esc(key) << " = " << std::quoted(tr.esc(value), '\'') << ";";

        pqxx::result res = tr.exec(ss.str());

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
    static record_t create(pqxx::work &tr, Ts... args) {
        std::vector<std::string> field_names;
        pushColumnNames<columns...>(field_names);

        std::string column_names = "";

        for (int i = 0; i < field_names.size() - 1; ++i) {
            column_names += field_names[i] + ",";
        }
        column_names += field_names[field_names.size() - 1];

        std::string table_name = std::string("\"") + Name.value + "\"";

        std::stringstream ss;

        ss << "INSERT INTO " << table_name;
        ss << " (" << column_names << ") VALUES ('";

        std::vector<std::string> values = to_strings(args...);

        for (int i = 0; i < values.size() - 1; ++i) {
            ss << tr.esc(values[i]) << "','";
        }
        ss << tr.esc(values.back()) << "') returning id";

        int id = std::get<int>(tr.exec1(ss.str()).as<int>());

        return record_t (Name.value, std::tuple(id, args...));
    }
};
