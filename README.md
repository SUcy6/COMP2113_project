### COMP2113_project_text_based_game
## Project Name: 
:large_orange_diamond::large_blue_diamond:**Tetris Tornado**:large_orange_diamond::large_blue_diamond:
## Team members:
Group 90

Su Changyue 3035534854

Liu Jin 3035639123
## Game description:
`Tetris Tornado` is a transformation of `Tetris`, a video game designed by Russian software engineer Alexey Pajitnov in 1984.
In `Tetris Tornado`, various shaped pieces *(called tetrominoes in this game)* fall onto the playing field from one of the 4 boundaries. There is a active tetris piece *(which is a 1-by-1 little square)* on the middle of the playing field at the beginning of each game. Players need to move or rotate the middle active tetris piece so that the middle piece can collide with the falling piece and form a new shape. If the player successfully complete a 3-by-3 square, the complete square will vanish and grant the player 1 point. If the middle active piece touches a boundary, game over. 
> In contrast, the original Tetris only has tetrominoes descending from the top to the bottom. Also, in the original game, players control the falling piece rather than the accumulational piece.  
## Game rules:
- Before the start of each game, choose `Sign in` or `Sign up`. If you are a new player, choose `Sign up` to enter a new username *(which can’t be already exist names)*, then a text file will be made to store game records: username and best score. If you are a skilled player, choose `Sign in` and enter your username, then your game record will be called out. Game starts.
- A tile:blue_square: will be formed in the middle. Tetrominoes:green_square::green_square::green_square::green_square: will fall onto the playing field from top to bottom, from left to right, from right to left or from bottom to top. Only one teris piece drops in from one of the 4 directions each time.
- Players control the middle active piece so that the tile will collide falling teris and combine into a new teris. Press `'w'`, `'a'`, `'s'`, `'d'` to move the active piece `up`:arrow_up:, `left`:arrow_left:, `down`:arrow_down:, `right`:arrow_right:. Press `'j'`, `'k'` to rotate the teris `anti-clockwise`:arrow_right_hook: or `clockwise`:leftwards_arrow_with_hook:. Press `'q'` to quit the game and output a file of game status: username, best score and score of the last game.
- There is a scoreboard:clipboard: showing username, best score and current score. The best score will change if you break your record. 

Game cases:joystick::

1. The middle tetris piece does not collide the falling teris piece. Falling tetris will disappear when it touches the end-point of its falling direction.
> E.g. the falling teris piece from left to right will vanish when it touches the right boundary.
2. The middle teris piece collides with the falling teris piece. Two pieces combine together to form new middle teris. Accumulatively, the middle active becomes larger and larger.
3. If the middle teris successfully complete a 3x3 matrix square, this square will disappear and the player gets one point. The remaining parts of middle piece will stay in their location. Even though the remains may be separated, we still look them as one piece.
```
E.g. ####         #***       #
      ###    =>    ***  =>       press 'k'=>   # #   # 
     ####         #***       #                 #
     # #          # #        # #
```
4. If the middle teris piece touches one of the 4 boundaries, game over. The game interface may be 60 x 60.
5. Special cases: the falling piece collides the middle piece but at the same time one of them touches a boundary. In this case, if after the collision they complete a 3x3 square and after the elimination of the 3x3 square the new formed piece does not touches boundaries, game goes on. If after the collision, nothing disappear or after the elimination the new formed piece still touches a boundary, game over. Overall speaking, the priority of `collision`, `elimination` and `boundary test` is: check collision -> check elimination -> check whether the piece touches boundaries. 
> If someone does not care about the game score, he/she can play it as dodgeball. Just move the central piece to avoid catching falling pieces. No ending but no scores.:joy::sunglasses::joy: 
## List of features:
1. Information of tetrominoes in the whole interface is stored in a 60x60 2D `array` with element 0 or 1. Element in the x-th row and y-th column represents a point in game interface with coordinates (x, y), with 0 meaning no tiles and 1 meaning a unit of tile.
2. `Data structure` such as `struct` will be used to create types that describe properteis of tetrominoes, including shape and orientation.
3. `Dynamic memory` is used to store the tetromino information in the middle tetris as well as the surrounding area. Memory will be released once the user quits the game.
4. Newly-generated tetrominoes random in position are achieved by random numbers that represent x, y coordinates of the tiles. Random shapes and orientations of tiles are also generated through `random` numbers, each representing one type of tetromino.
5. `File input and output` are used to save the game record for old users to continue the game.
6. `Multiple files` are used for codes regarding different aspects, such as creating the grid, reading the input, random tetrominoes generator, score calculator, etc.
7. The steady falling of tetrominoes are achieved by `Qtimer`.
## List of non-standard libraries:
NCURSES
## Compilation and execution instructions:
- If you are a freshman to this game, please first type `./freshman.sh` in your terminal to install the ncurses library.(It will take a few minutes :D)
- Main Steps:
