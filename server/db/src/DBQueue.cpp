#include <DBQueue.hpp>

void DBQueue::execute_query(execute_handler_t exec_handler) {
    pqxx::work transaction(connection);
    exec_handler(transaction);
    transaction.commit();
}
