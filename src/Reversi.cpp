#include "Reversi.hpp"
#include <iostream>
#include "list"
#include "array"
const int num_columns_and_rows_reversi = 8;

void Reversi::start_reversi_board() {
    this->game_board[3][3] = 'X';
    this->game_board[4][4] = 'X';
    this->game_board[3][4] = 'O';
    this->game_board[4][3] = 'O';
}

Reversi::Reversi() : Game(num_columns_and_rows_reversi, num_columns_and_rows_reversi) {
    this->start_reversi_board();
    this->num_pieces_player_X = 2;
    this->num_pieces_player_O = 2;
};


bool Reversi::is_valid_move() const
{
    return true;
}


bool Reversi::is_space_free(int x, int y) const
{
    if ((this->game_board[x][y] != ' '))
        return false;

    return true;
}

bool Reversi::is_move_inside_board(int x, int y) const
{
    if ((x < 0 || x > this->num_rows - 1) || (y < 0 || y > this->num_columns - 1))
        return false;
            
    return true;
}

bool Reversi::is_there_player_piece_at_the_direction(const char player_piece, const std::array<int, 2>& direction, 
    std::array<int, 2> adjacent_square) const 
{
    std::array<int, 2> current_square = {adjacent_square[0] + direction[0], adjacent_square[1] + direction[1]};

    while (this->is_move_inside_board(current_square[0] + 1, current_square[1] + 1)) 
    {
        if (this->game_board[current_square[0]][current_square[1]] == player_piece) 
            return true;
        else if (this->game_board[current_square[0]][current_square[1]] == ' ')
            return false;
            
        current_square[0] += direction[0];
        current_square[1] += direction[1];
    }
    return false;
}

void Reversi::find_directions_that_make_moves_against_opponent(const std::array<int, 2> &move_coordinates, char player_piece_type, std::list<std::array<int, 2>>& directions_to_capture_opponents) {

    char other_player_piece_type = (player_piece_type == 'X') ? 'O' : 'X';

    std::array<int, 2> adjacent_square = {0, 0};

    for (int i = 1; i > -2; i--){
        for (int j = 1; j > -2; j--){
            if (j != 0 || i != 0) {
                adjacent_square[0] = move_coordinates[0] + i;
                adjacent_square[1] = move_coordinates[1] + j;

                if (this->is_move_inside_board(adjacent_square[0], adjacent_square[1]) && 
                    this->game_board[adjacent_square[0]][adjacent_square[1]] == other_player_piece_type)
                {
                    std::array<int, 2> direction = {adjacent_square[0] - move_coordinates[0], adjacent_square[1] - move_coordinates[1]};

                    if (is_there_player_piece_at_the_direction(player_piece_type, direction, adjacent_square)) {
                        directions_to_capture_opponents.push_back(direction);
                    } 
                }
            }
        }
    }
}

 bool Reversi::is_valid_move(std::array<int, 2>& move_coordinates, char player_piece_type, std::list<std::array<int, 2>>& directions_to_capture_opponents)
{

    if (!this->is_move_inside_board(move_coordinates[0], move_coordinates[1]))
        return false;

    if (!this->is_space_free(move_coordinates[0], move_coordinates[1]))
        return false;

    this->find_directions_that_make_moves_against_opponent(move_coordinates, player_piece_type, directions_to_capture_opponents);
    
    if (directions_to_capture_opponents.empty()) {
        return false;
    }
    
    return true;
}

bool Reversi::process_move(std::array<int, 2> move_coordinates, char player_piece) {
    move_coordinates[0] = move_coordinates[0] - 1;
    move_coordinates[1] = move_coordinates[1] - 1;

    std::list<std::array<int, 2>> directions_to_capture_opponents;

    if(this->is_valid_move(move_coordinates, player_piece, directions_to_capture_opponents)) {
        this->make_move(move_coordinates, player_piece, directions_to_capture_opponents);
        return true;
    }
    return false;

}

void Reversi::flip_pieces(std::array<int, 2> directions, std::array<int, 2> move_coordinates, char player_piece) {
    char opponent_piece = (player_piece == 'X') ? 'O' : 'X';
    int num_pieces_flipped = 0;

    std::array<int, 2> current_square = {directions[0] + move_coordinates[0], directions[1] + move_coordinates[1]};
    
    while(this->game_board[current_square[0]][current_square[1]] == opponent_piece) {
        this->game_board[current_square[0]][current_square[1]] = player_piece;
        current_square[0] += directions[0];
        current_square[1] += directions[1];
        num_pieces_flipped++;
    }

    if(player_piece == 'X') {
        this->num_pieces_player_X += num_pieces_flipped;
        this->num_pieces_player_O -= num_pieces_flipped;
    } else {
        this->num_pieces_player_X -= num_pieces_flipped;
        this->num_pieces_player_O += num_pieces_flipped;
    }
}

void Reversi::make_move()
{
    return;
}

void Reversi::make_move(std::array<int, 2> move_coordinates, char player_piece, std::list<std::array<int, 2>>& directions_to_capture_opponents) 
{
    this->game_board[move_coordinates[0]][move_coordinates[1]] = player_piece;

    for(auto direction : directions_to_capture_opponents) 
        this->flip_pieces(direction, move_coordinates, player_piece);    
}


void Reversi::check_win() const
{
    
}

