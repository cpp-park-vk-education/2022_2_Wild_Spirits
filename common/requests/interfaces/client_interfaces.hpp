#pragma once




namespace Client{
    class Action{};
    class GameState;
    enum Header{
        action,
        img_request,
        room_changes,
        dm_changes,
        apply_request
        };
}