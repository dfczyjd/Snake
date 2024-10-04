# Snake
#### Scroll down for English version

Игра "Змейка".  
В ходе игры игрок управляет змейкой, состоящей из нескольких клеток. Цель игры - набрать как можно больше очков. Очки даются за то, что
змейка ест еду (т.е. попадает головой в клетку, содержащую их). Еда появляется изначально и каждый раз, когда предыдущая съедена. За каждую
еду игроку начисляется количество очков, равное уровню сложности, и длина змейки увеличивается на 1 клетку. Также каждые 4 съеденные еды на
игровом поле появляется бонус, который существует 40 тактов игры (количество тактов в секунде равно уровню сложности). При съедении бонус
даёт количество очков, равное количеству оставшихся тактов и не увеличивает длину змейки.
## Движение змейки
Голова змейки движется со скоростью 1 клетка в такт игры в заданном направлении. Остальное тело перемещается на клетку, ранее занятую
предыдущим сегментом (т.е. второй сегмент переходит на место головы, третий на место второго и т.д.). При этом, если голова змейки
пересекает границу игрового поля, она оказывается с его противоположной стороны. Игра завершается, если голова змейки сталкивается с
телом.
## Управление
W, A, S, D - задать направление движения вверх, вправо, вниз и влево соответственно.  
+/- - увеличить/уменьшить уровень сложности на 1  
Управление производится через символы (т.е. для нажатия "W" необходима латинская раскладка)

# English
The Snake game
The player controls the snake consisting of several cells. The goal of the game is to score as many points as possible. The points are earned by consuming food by the snake (i. e. directing its head to the cell containing it). One food piece spawns at the beginning and respawns at a random cell every time it is eaten. Every piece of food adds the number of equal to current difficulty level to current score and increases the snake's length by 1. Additionally after each 4 pieces of food a bonus item spawns, which exists for 40 game ticks. The bonus item scores the number of points equal to remaining ticks and does not increase the snake's length.
## Snake movement
The head of the snake moves at the rate of 1 cell per game tick in the current direction. The remaining body segments move to occupy the cell previously taken by the previous segment (i. e. second segment moves to where the head was, the third one moves to the previous position of the second one etc.). If the snake's head crosses the map bound, it moves to the opposite side of the map instead. Game ends if the head collides with any other segment.
## Controls
W, A, S, D - set the movement direction to up, down, left or right respectively
+/- - increase or descrease difficulty level (equals to the number of game ticks in second and the score earned per food piece)
Note: Controls are performed using symbols, not keys (i. e. difficulty can be increased on standard keyboards by pressing the '=/+' key with Shift key down)
