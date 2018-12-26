import sys, pygame, random
from pygame.locals import * 

pygame.init()

size = width, height = 640, 480
speed = [2, 2]
black = 0, 0, 0
red = 185, 0, 0
green = 0, 185, 0
blue = 0, 0, 185
gray  = 185, 185, 185

screen = pygame.display.set_mode(size)
pygame.display.set_caption("Tetros")

ball = pygame.image.load("intro_ball.gif")
ballrect = ball.get_rect()

bigfont = pygame.font.Font('freesansbold.ttf', 100)
littlefont = pygame.font.Font('freesansbold.ttf', 20)

def main():
    global FPSCLOCK
    FPSCLOCK = pygame.time.Clock()
    screen.fill(red)
    startScreen('Tetr*s')

    while 1:
        runGame()

def startScreen(text):
    #the 'press a key to continue' screen
    titleSurf, titleRect = makeTextObjs(text, bigfont, gray)
    titleRect.center = (int(width / 2), int(height / 2))
    screen.blit(titleSurf, titleRect)

     #the 'press a key to continue' screen
    titleSurf, titleRect = makeTextObjs(text, bigfont, black)
    titleRect.center = (int(width / 2) - 3, int(height / 2) - 3)
    screen.blit(titleSurf, titleRect)

    titleSurf, titleRect = makeTextObjs('Press the any key to start', littlefont, black)
    titleRect.center = (int(width / 2), int(height / 2) + 100)
    screen.blit(titleSurf, titleRect)
    
    while checkForKeyPress() == None:
        pygame.display.update()
        FPSCLOCK.tick(30)

def runGame():
    #the 'press a key to continue' screen
    checkForQuit()
    randColor = randomColor()
    screen.fill(randColor)
    placeholderSurf, placeholderRect = makeTextObjs("this is where the game goes :)", littlefont, gray)
    placeholderRect.center = (int(width / 2), int(height / 2))
    screen.blit(placeholderSurf, placeholderRect)
    pygame.display.update()
    FPSCLOCK.tick(30)

def randomColor():
    return random.randint(0,255), random.randint(0,255), random.randint(0,255)

def checkForKeyPress():
    checkForQuit()

    for event in pygame.event.get([KEYDOWN,KEYUP]):
        if event.type == KEYDOWN:
            continue
        return event.key
    return None

def checkForQuit():
    for event in pygame.event.get(QUIT):
        pygame.quit()
        sys.exit()
    for event in pygame.event.get(KEYUP):
        if event.key == K_ESCAPE:
            pygame.quit()
            sys.exit()
        pygame.event.post(event)

def makeTextObjs(text, font, color):
    surf = font.render(text, True, color)
    return surf, surf.get_rect()

if __name__ == '__main__':
    main()


