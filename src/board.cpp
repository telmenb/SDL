#include "board.hpp"

Board::Board() {
    board_ = std::vector<int> (14, 4);
    board_.at(6) = 0;
    board_.at(13) = 0;
}

// void Board::StartMove(int start_idx) {
//     if (start_idx < 0 || start_idx == 6 || start_idx > 12)
//         throw std::runtime_error("Invaid index");

//     if (player_turn_ == Player::kPlayer1) {
//         MovePlayerOne(start_idx);
//     } else {
//         MovePlayerTwo(start_idx);
//     }
// }

int Board::AtIDX(int idx) {
    return board_.at(idx);
}

bool Board::CheckForWinner() {
    bool p1 = true;
    bool p2 = true;
    for (size_t i = 0; i < 13; i++) {
        if (i == 6 || i == 13) continue;
        if (i < 6 && board_.at(i) != 0) p1 = false;
        if (i > 6 && board_.at(i) != 0) p2 = false;
    }
    return p1 || p2;
}

Player Board::DeclareWinner() {
    if (board_.at(6) > board_.at(13)) return Player::kPlayer1;
    if (board_.at(6) < board_.at(13)) return Player::kPlayer2;
    return Player::kTie;
}

void Board::Reset() {
    board_ = std::vector<int> (14, 4);
    board_.at(6) = 0;
    board_.at(13) = 0;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    std::cout << "--------------------\n";
    std::cout << "       Player2" << std::endl;
    os << "  " << "12" << " " << "11" << " " << "10" << " "  << "09" << " "  << "08" << " "  << "07" << " "  << "  " << std::endl;
    // std::cout << std::endl;
    os << "  " << board.board_.at(12) << "  " << board.board_.at(11) << "  " << board.board_.at(10) << "  "  << board.board_.at(9) << "  "  << board.board_.at(8) << "  "  << board.board_.at(7) << "  "  << "  " << std::endl;
    os << board.board_.at(13) << "                  " << board.board_.at(6) << std::endl;
    os << "  " << board.board_.at(0) << "  "  << board.board_.at(1) << "  "  << board.board_.at(2) << "  "  << board.board_.at(3) << "  "  << board.board_.at(4) << "  "  << board.board_.at(5) << "  "  << "  " << std::endl;
    // std::cout << std::endl;
    os << "  " << "00" << " " << "01" << " " << "02" << " "  << "03" << " "  << "04" << " "  << "05" << " "  << "  " << std::endl;
    std::cout << "       Player1" << std::endl;
    std::cout << "--------------------\n";
    return os;
}