#include "Game.hpp"
#ifndef REVERSI_H
#define REVERSI_H
#include <array>
#include <list>

class Reversi : public Game {
    private:
        int num_pieces_player1;
        int num_pieces_player2;
    public:
        Reversi();
        bool is_valid_move() const override;
        bool is_valid_move(const std::array<int, 2>& move_coordinates, char player_piece_type, std::list<std::array<int, 2>>& squares_to_make_move);
        bool is_space_free(int x, int y) const;
        bool is_there_player_piece_at_the_direction(const char player_piece, const std::array<int, 2>& direction, 
             std::array<int, 2> adjacent_square) const;
        void make_move() override;
        void make_move(int x, int y, char player_piece); 
        virtual void check_win() const override; 
        void find_squares_that_make_moves_against_opponent(const std::array<int, 2>& move_coordinates, char player_piece_type, std::list<std::array<int, 2>>& squares_to_make_move);
        void process_move(const std::array<int, 2>& move_coordinates, char player_piece_type);
};

#endif