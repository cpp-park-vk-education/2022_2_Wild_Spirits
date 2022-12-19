#pragma once

namespace LM {

    struct RoomProps {
        size_t id;
    };

    class Room {
    public:
        Room(const RoomProps& props) : m_Props(props) { }
        size_t getId() { return m_Props.id; }

    protected:
        RoomProps m_Props;
    };

}    // namespace LM
