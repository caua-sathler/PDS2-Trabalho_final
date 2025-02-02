#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.hpp"
#include "Tic_tac_toe.hpp"

const int num_rows_received = 3;
const int num_columns_received = 3;

/**
 * @brief Aloca um tabuleiro com situações de teste no Tic Tac Toe sem a necessidade de uma
 * partida real.
 * @param game_board_situation Tabuleiro que simula situações de jogo
 * @param reversi_game Instância da classe Tic_tac_toe
 */

void create_game_board_situation(char game_board_situation[num_rows_received][num_columns_received], Tic_tac_toe &tic_tac_toe_game) {
    for (int i = 0; i < num_rows_received; ++i) {
        for (int j = 0; j < num_columns_received; ++j) {
            tic_tac_toe_game.get_game_board().set_space(i, j, game_board_situation[i][j]);
        }
    }
}

TEST_CASE("Function is_valid_move test") 
{
    Tic_tac_toe jogo;

    char game_board_situation[num_rows_received][num_columns_received] = {
        {'X', ' ', ' '},
        {' ', 'O', ' '},
        {' ', ' ', ' '}
    };

    create_game_board_situation(game_board_situation, jogo);

    SUBCASE("Move inside board and position free") {
        int x = 3, y = 3;
        CHECK_NOTHROW(jogo.is_valid_move(x, y));
    }

    SUBCASE("Move out of the board") {
        int x = 4, y = 4; 
        CHECK_THROWS_AS(jogo.is_valid_move(x, y), std::runtime_error);

        x = INT_MAX, y = INT_MAX; 
        CHECK_THROWS_AS(jogo.is_valid_move(x, y), std::runtime_error);

        x = INT_MIN, y = INT_MIN;
        CHECK_THROWS_AS(jogo.is_valid_move(x, y), std::runtime_error);
    }

    SUBCASE("Move on a ocuppied position") {
        jogo.make_move(1, 1);
        int x = 1, y = 1;
        CHECK_THROWS_AS(jogo.is_valid_move(x, y), std::runtime_error);
    }
}

TEST_CASE("Function make_move test") 
{
    Tic_tac_toe jogo;

    char game_board_situation[num_rows_received][num_columns_received] = {
        {'X', ' ', ' '},
        {' ', 'O', ' '},
        {' ', ' ', ' '}
    };

    create_game_board_situation(game_board_situation, jogo);

    SUBCASE("Valid move switches the player and update the board") 
    {
        int x = 2, y = 2;
        jogo.make_move(x, y);
        CHECK(jogo.get_game_board().get_space(x - 1, y - 1) == 'O');
        CHECK(jogo.get_current_player() == 'O');
        x = 2, y = 1;
        jogo.make_move(x, y);
        CHECK(jogo.get_game_board().get_space(x - 1, y - 1) == 'O');
        CHECK(jogo.get_current_player() == 'X');
    }

    SUBCASE("Invalid move switch the player and does not update the board") 
    {
        int x = 1, y = 1; 
        jogo.make_move(x, y);
        CHECK(jogo.get_game_board().get_space(x, y) == 'O');
        CHECK(jogo.get_current_player() == 'O');
    }
}

TEST_CASE("Function check_tie test") 
{
    Tic_tac_toe jogo;

    SUBCASE("Game is a tie (board full, no winner)") 
    {
        char tie_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'O', 'X'},
            {'X', 'X', 'O'},
            {'O', 'X', 'O'}
        };

        create_game_board_situation(tie_board, jogo);
        CHECK(jogo.check_tie() == true);
    }

    SUBCASE("Game is not a tie (there is a winner)") 
    {
        char winner_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'X', 'X'},
            {'O', 'O', ' '},
            {' ', ' ', ' '}
        };

        create_game_board_situation(winner_board, jogo);
        CHECK(jogo.check_tie() == false);
    }
}

TEST_CASE("Function check_tic_tac_toe_win test") 
{
    Tic_tac_toe jogo;

    SUBCASE("Win by row") 
    {
        char row_win_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'X', 'X'},
            {'O', 'O', ' '},
            {' ', ' ', ' '}
        };

        create_game_board_situation(row_win_board, jogo);
        CHECK(jogo.check_tic_tac_toe_win() == 'X');
    }

    SUBCASE("Win by column") 
    {
        char column_win_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'O', ' '},
            {'X', 'O', ' '},
            {'X', ' ', ' '}
        };

        create_game_board_situation(column_win_board, jogo);
        CHECK(jogo.check_tic_tac_toe_win() == 'X');
    }

    SUBCASE("Win by main diagonal") 
    {
        char main_diag_win_board[num_rows_received][num_columns_received] = 
        {
            {'O', 'X', 'X'},
            {'X', 'O', ' '},
            {' ', ' ', 'O'}
        };

        create_game_board_situation(main_diag_win_board, jogo);
        CHECK(jogo.check_tic_tac_toe_win() == 'O');
    }

    SUBCASE("Win by secondary diagonal") 
    {
        char sec_diag_win_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'O', 'O'},
            {' ', 'O', ' '},
            {'O', ' ', 'X'}
        };

        create_game_board_situation(sec_diag_win_board, jogo);
        CHECK(jogo.check_tic_tac_toe_win() == 'O');
    }

    SUBCASE("No winner (game in progress)") 
    {
        char no_winner_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'O', ' '},
            {'X', 'O', ' '},
            {'O', ' ', ' '}
        };

        create_game_board_situation(no_winner_board, jogo);
        CHECK(jogo.check_tic_tac_toe_win() == 'F');
    }

    SUBCASE("No winner (tie)") 
    {
        char tie_board[num_rows_received][num_columns_received] = 
        {
            {'X', 'O', 'X'},
            {'X', 'X', 'O'},
            {'O', 'X', 'O'}
        };

        create_game_board_situation(tie_board, jogo);
        CHECK(jogo.check_tic_tac_toe_win() == 'F');
    }
}
