#pragma once

#include <pqxx/pqxx>

#include <string>
#include <functional>

#include <Table.hpp>

class ImagesTable: public Table<"images", Column<"path", std::string>> {};

class CharactersTable: public Table<"Characters",
                               Column<"name", std::string>,
                               Column<"max_hp", int>,
                               Column<"image_id", int>,
                               Column<"meta_information", std::string>> {};

class CharacterInstancesTable: public Table<"characterinstances", 
                                            Column<"character_id", int>,
                                            Column<"hp", int>,
                                            Column<"location_id", int>,
                                            Column<"pos_x", int>,
                                            Column<"pos_y", int>> {};

class CampaginsTable: public Table<"campaigns",
                                   Column<"name", std::string>,
                                   Column<"description", std::optional<std::string>>> {};


class RoomsTable: public Table<"rooms",
                                Column<"DM_id", int>,
                                Column<"capaign_id", int>> {};

class UserRoomMapTable: public Table<"userroommap",
                                Column<"user_id", int>,
                                Column<"room_id", int>> {};

class LocationsTable: public Table<"locations",
                                    Column<"campaign_id", int>,
                                    Column<"name", std::string>,
                                    Column<"background_image_id", int>,
                                    Column<"size_x", int>,
                                    Column<"size_y", int>> {};

class PlayersTable: public Table<"players",
                                Column<"character_instance_id", int>,
                                Column<"campaign_id", int>,
                                Column<"race", std::string>,
                                Column<"class", std::string>> {};

class ItemsTable: public Table<"items",
                                Column<"name", std::string>,
                                Column<"type", std::string>,
                                Column<"effect", std::string>> {};

class ItemStatesTable: public Table<"itemstates", Column<"json", std::string>> {};

class InventoriesTable: public Table<"inventories",
                                    Column<"character_instance_id", int>,
                                    Column<"item_id", int>> {};

class UsersTable: public Table<"users",
                                Column<"nickname", std::string>,
                                Column<"password_hash", std::string>> {};

class DBQueue {
private:
    using execute_handler_t = std::function<void(pqxx::work &)>;
    pqxx::connection connection;

public:
    explicit DBQueue(const std::string &connection_params_str): connection(connection_params_str) {}

    void execute_query(execute_handler_t handler);
};
