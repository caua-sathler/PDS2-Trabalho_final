#include "Player.hpp"
#include "Reversi.hpp"
#include "Connect4.hpp"
#include <limits>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

//lidar com exceção
Player* find_player_in_list(std::list<Player>& player_list, const std::string& user_name) {
    for (auto& player : player_list) {
        if (player.get_username() == user_name) {
            return &player;
        }
    }
    return nullptr;
}

int main() {
    std::ifstream file_in;
    file_in.open("/home/leonardo/PDS2-Final_Project/teste");
    if (!file_in.is_open()){
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }

    std::list<Player> player_list;
    read_register_file(player_list, file_in);

    file_in.close();

    std::string command;
    std::string name_in, username_in;
    bool error = false;

    while(std::cin >> command){
        if (command == "LJ"){
            char sort_command;
            std::cin >> sort_command;
            if (sort_command == 'A')
                player_list.sort(Player::compare_username);
            else if (sort_command == 'N')
                player_list.sort(Player::compare_name);
            else {
                std::cout << "ERRO: comando inexistente" << std::endl;
                continue;
            }
            std::list<Player>::iterator it;
            for (it = player_list.begin(); it != player_list.end(); it++){
                it->print_player();
            }
            continue;

        } else if (command == "CJ"){
            std::string line_in;
            std::getline(std::cin, line_in);
            std::stringstream stream_in(line_in);
            stream_in >> username_in;
            stream_in.ignore();
            std::getline(stream_in, name_in);
            if (name_in == ""){
                std::cout << "ERRO: dados incorretos" << std::endl;
                continue;
            }
            Player new_player(name_in, username_in);
            if (Player::register_player(new_player, player_list) == true)
                std::cout << "Jogador " << new_player.get_username() << " cadastrado com sucesso" << std::endl;
            else   
                std::cout << "ERRO: jogador repetido" << std::endl;
            continue;
            
        } else if (command == "RJ"){
            std::cin >> username_in;
            if (Player::remove_player(username_in, player_list) == true)
                std::cout << "Jogador " << username_in << " removido com sucesso" << std::endl;
            else 
                std::cout << "ERRO: jogador inexistente" << std::endl;
            continue;

                } else if (command == "EP") {
            char game;
            std::string username_player1, username_player2;
            std::cin >> game >> username_player1 >> username_player2;
            //verificar se os dois jogadores existem

            if (game == 'R') {
                Reversi reversi_game;

                char player_piece = 'X';
                char opponent_piece = 'O';

                while (true) {
                    int x, y;

                    bool is_there_movement_for_player = reversi_game.is_there_valid_move_for_player(player_piece);
                    bool someone_won = reversi_game.check_win(is_there_movement_for_player, player_piece);
                    reversi_game.print_reversi_board();
                    std::cout << "X: " << reversi_game.get_num_pieces_player_X() << " " << "O: " << reversi_game.get_num_pieces_player_O() << std::endl;

                    if (someone_won) {
                        Player *player1, *player2;

                        player1 = find_player_in_list(player_list, username_player1);
                        player2 = find_player_in_list(player_list, username_player2);
                        reversi_game.register_win_and_loss(player1, player2);

                        if (reversi_game.get_num_pieces_player_X() > reversi_game.get_num_pieces_player_O()) {
                            std::cout << username_player1 << " ganhou!" << std::endl;
                        } else if (reversi_game.get_num_pieces_player_X() < reversi_game.get_num_pieces_player_O()) {
                            std::cout << username_player2 << " ganhou!" << std::endl;
                        } else {
                            std::cout << "Houve empate!" << std::endl;
                        }
                        break;
                    }
                    else if (is_there_movement_for_player && !someone_won) {

                        if (player_piece == 'X') {
                            std::cout << username_player1 << " " << "[X]" << ": " << std::ends;
                        } else {
                            std::cout << username_player2 << " " << "[O]" << ": " << std::ends;
                        }

                        if (!(std::cin >> x >> y)) {
                            std::cout << "Invalid input. Please enter two integers for your move.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        if (!reversi_game.process_move({x, y}, player_piece)) {
                            std::cout << "Movimento Inválida, vez passada para o oponente" << std::endl;
                        }

                        player_piece = reversi_game.switch_players(player_piece);
                        opponent_piece = reversi_game.switch_players(opponent_piece);
                    }
                    else if (!is_there_movement_for_player && !someone_won) {
                        player_piece = reversi_game.switch_players(player_piece);
                        opponent_piece = reversi_game.switch_players(opponent_piece);
                        std::cout << "Não há jogadas válida, vez passada para o oponente" << std::endl;
                    }
                }

            } else if (game == 'L') { 
                Connect4 connect4_game;
                bool game_over = false;

                Player* player1 = find_player_in_list(player_list, username_player1);
                Player* player2 = find_player_in_list(player_list, username_player2);

                while (!game_over) {
                    int column;
                    connect4_game.print_game_board();
                    char current_player = 'X';

                    std::cout << "Turno de jogador <" << connect4_game.get_current_player() << ">:" << std::endl;
                    std::cin >> column;

                    if (connect4_game.is_valid_move(column)) {
                        connect4_game.make_move(column);
                        if (connect4_game.check_win()) {
                            connect4_game.print_game_board();
                            if (connect4_game.get_current_player() == 'X') {
                                player1->add_win("Lig4");
                                player2->add_loss("Lig4");
                                std::cout << "Parabéns, " << username_player1 << "! Você venceu!\n";
                            } else {
                                player2->add_win("Lig4");
                                player1->add_loss("Lig4");
                                std::cout << "Parabéns, " << username_player2 << "! Você venceu!\n";
                            }
                            game_over = true;
                        } else if (connect4_game.is_board_full()) {
                            std::cout << "O jogo terminou em empate!\n";
                            game_over = true;
                        }

                        connect4_game.switch_players(current_player);
                    } else {
                        std::cout << "Movimento inválido. Tente novamente.\n";
                    }
                }
            }
        } else if (command == "FS"){
            break;

        } else {
            if (error == false){
                std::cout << "ERRO: comando inexistente" << std::endl;
                error = true;
                continue;
            }
        }
    }

    std::ofstream file_out;
    file_out.open("teste");
    if (!file_out.is_open()){
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }

    write_register_file(player_list, file_out);

    file_out.close();
}