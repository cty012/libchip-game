import chip_game


if __name__ == "__main__":
    game_s = chip_game.GameState(4, 3, [[-1, 7, 4], [3, 4, 3], [6, 3, -1], [-1, -1, 0]])

    print("Before sorting:")
    print(game_s)

    game_s.sort()

    print("After sorting:")
    print(game_s)
