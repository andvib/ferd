

class RailPiece {
    public:
        RailPiece(Waypoint *A, Waypoint *B);
    
        virtual PositionOnRailGet(position_t current_position, float distance_travelled, enum rail_direction);

        virtual OrientationOnRailGet(position_t position_on_rail, enum rail_direction);

    private:
        Waypoint A;
        Waypoint B;
        float m_total_length;
};

class StraightRailPiece : public RailPiece {
    public:
        StraightRailPiece(Waypoint *A, Waypoint *B);

    private:

};

class NewWaypoint {
    public:
        NewWaypoint();

        RailPiece* nextRailPieceGet(RailPiece *current_railpiece);
    
    private:
        RailPiece *m_connection_A;
        RailPiece *m_connection_B;
};

class RailWalker {
    public:
        RailWalker();
        position_t nextPositionGet(position_t current_position, float distance_travelled);

    private:
        RailPiece *current_rail;
        enum rail_direction;

};

class Train {
    public:
    private:
        RailWalker *m_walker;
}