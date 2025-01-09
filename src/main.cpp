#include "Game.hpp"
#include "Player.hpp"
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

int main() {
    std::ifstream file_in;
    file_in.open("teste");
    if (!file_in.is_open()){
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }

    std::list<Player> player_list;
    read_register_file(player_list, file_in);

    file_in.close();

    std::string command;
    std::string name_in, username_in, line_in;
    char extra_space, sort_command;
    bool error = false;

    while(std::cin >> command){
        if (command == "LJ"){
            std::cin >> sort_command;
            if (sort_command == 'A')
                player_list.sort(Player::compare_username);
            else if (sort_command == 'N')
                player_list.sort(Player::compare_name);
            else {
                std::cout << "Erro: comando inexistente" << std::endl;
                continue;
            }
            std::list<Player>::iterator it;
            for (it = player_list.begin(); it != player_list.end(); it++){
                it->print_player();
            }
            continue;

        } else if (command == "CJ"){
            std::getline(std::cin, line_in);
            std::stringstream stream_in(line_in);
            stream_in >> username_in;
            extra_space = stream_in.get();
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

    std::list<Player>::iterator it;
    for (it = player_list.begin(); it != player_list.end(); it++){
        file_out << it->get_username() << std::endl;
        file_out << it->get_name() << std::endl;
        file_out << "Reversi" << " " << it->get_num_win().find("Reversi")->second << " " << it->get_num_loss().find("Reversi")->second << std::endl;
        file_out << "Lig4" << " " << it->get_num_win().find("Lig4")->second << " " << it->get_num_loss().find("Lig4")->second << std::endl;
        file_out << "Velha" << " " << it->get_num_win().find("Velha")->second << " " << it->get_num_loss().find("Velha")->second << std::endl;
    }

    file_out.close();
}