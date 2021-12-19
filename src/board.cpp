#include "board.hpp"

Board::Board() {
    board_ = std::vector<int> (14, 4);
    board_.at(6) = 0;
    board_.at(13) = 0;
}


