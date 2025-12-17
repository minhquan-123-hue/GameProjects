from game import Game

def main():
    game = Game()

    if not game.init():
        return 1
    
    game.run()
    return 0

if __name__ == "__main__":
    main()