﻿# Змейка
Игра "Змейка".
В ходе игры игрок управляет змейкой, состоящей из нескольких клеток. Цель игры - набрать как можно больше очков. Очки даются за то, что
змейка ест еду (т.е. попадает головой в клетку, содержащую их). Еда появляется изначально и каждый раз, когда предыдущая съедена. За каждую
еду игроку начисляется количество очков, равное уровню сложности, и длина змейки увеличивается на 1 клетку. Также каждые 4 съеденные еды на
игровом поле появляется бонус, который существует 40 тактов игры (количество тактов в секунде равно уровню сложности). При съедении бонус
даёт количество очков, равное количеству оставшихся тактов и не увеличивает длину змейки.
## Движение змейки
Голова змейки движется со скоростью 1 клетка в такт игры в заданном направлении. Остальное тело перемещается на клетку, ранее занятую
предыдущим сегментом (т.е. второй сегмент переходит на место головы, третий на место второго и т.д.). При этом, если голова змейки
пересекает границу игрового поля, она оказывается с его противоположной стороны. Игра завершается, если голова змейки всталкивается с
телом.
## Управление
W, A, S, D - задать направление движения вверх, вправо, вниз и влево соответственно.  
+/- - увеличить/уменьшить уровень сложности на 1  
Управление производится через символы (т.е. для нажатия "W" необходима латинская раскладка)
