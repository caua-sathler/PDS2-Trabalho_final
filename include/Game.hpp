#ifndef GAME_H
#define GAME_H

class Game{
    private:
        int num_rows;
        int num_columns;
        char** game_board = nullptr;
    public:
        Game(int num_rows_received, int num_columns_received);
        void create_game_board();
        void print_game_board() const;
        virtual bool verify_valid_move() = 0;
        virtual void make_move() = 0;
        virtual void check_win() = 0;
        char** get_game_board() {
            return game_board;
        }
        ~Game();
};

#endif