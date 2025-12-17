import pygame 
import sys

class Game:
    def __init__(self):
        self.running = False
        self.window = None
        self.clock = None


    def init(self):
        print("program run...")
        pygame.init()

        try:
            self.window = pygame.display.set_mode((800,400))
            pygame.display.set_caption("pong")
        except Exception as e:
            print("Fail to create window: ", e)
            return False
        

        self.clock = pygame.time.Clock()
        self.running = True

        print("Window object: ", self.window)
        return True
    
    def run(self):
        while self.running:
            self.handle_events()
            self.render()
            self.clock.tick(60) # limit to 60FPS

        self.clean_up()

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print("quit event: ", event.type)
                self.running = False

    def render(self):
        # equivalent to SDL_SetRenderDrawColor + SDL_RenderClear
        self.window.fill((0,0,0))
        pygame.display.flip()

    def clean_up(self):
        pygame.quit()
        sys.exit()
            