#pragma once

enum class Rank {
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,

    MAX_RANK
};

enum class Suit {
    SPADES,
    DIAMONDS,
    CLUBS,
    HEARTS,

    MAX_SUIT
};

enum class Members {
    Player,
    Dealer
};