#include <DBQueue.hpp>

void DBQueue::execute_query(execute_handler_t handler) {
    pqxx::work transaction(connection);
    handler(transaction);
    transaction.commit();
}
