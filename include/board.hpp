#ifndef BOARD_HPP
#define BOARD_HPP

#include "entity.hpp"

#include <iostream>
#include <vector>

enum class Player {kPlayer1, kPlayer2};

class Board {
public:
    // default constructor, sets board_[0] and board_[7] == 0; player_turn_ == kPlayer1
    Board();

    // checks player_turn_ and calls the appropriate method
    // throws exception if idx <= 0 || idx == 7 || idx > 13
    void StartMove(int start_idx);

    // loops through the board to check if the game has ended
    // everything except board_.at(0) and board_.at(7) == 0
    bool CheckForWinner();

    // determine winner after CheckForWinner() returns true
    // compare board_.at(0) and board_.at(7)
    Player DeclareWinner();

    // resets the board for another round of gameplay
    void Restart();

    // output operator for local testing
    friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
    // creates a int vector of length 14 and initializes all values to 4
    std::vector<int> board_;

    // player representation for board class
    Player player_turn_ = Player::kPlayer1;

    // called depending on player_turn_
    // throws exception if invalid idx is passed
    // TODO: how to handle rollovers (5 -> 7, 12 -> 0) and player_turn_ changes
    void MovePlayerOne(int start_idx); // 0 <= idx < 6
    void MovePlayerTwo(int start_idx); // 6 < idx < 13
};

#endif