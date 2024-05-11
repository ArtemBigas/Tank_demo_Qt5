#ifndef SHOOTER_H
#define SHOOTER_H
#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
class shooter:public QWidget
{
public:
    shooter(QWidget *parent =0);

protected:
    void paintEvent(QPaintEvent *e);//причина первого срабатывания QPaintEvent - window.show();
    void keyPressEvent(QKeyEvent *e);// ловит сигналы от клавиатуры
    void timerEvent(QTimerEvent *e);//срабатывает при смене таймера, по сути игровой процесс
private:
    QImage tank;
    QImage target;
    QImage shot;

    static const int brick_size=10;//размер кирпича из которого будет состоять все объекты
    static const int field_height = 300;//длина дороги
    static const int field_width = 300;//ширина дороги
    static const int RAND_POS = 29;//используется для вычисления случайной позиции яблока
    static const int tank_size = 6;//количество блоков в машине
    //текущие координаты машины
    std::vector <int> tank_x;
    std::vector<int>tank_y;
    //текущие координаты цели и снаряда
    int target_x;
    int target_y;
    int shot_x;
    int shot_y;
     void loadQImage();//заполняем кирпичи для моделей
    void startGame();//начинаем игру
     void pauseGame();//пауза
    void gameOver();//конец игры
     void painting();//рисуем модели
    bool pause = false;//игра идет или нет
    int timertank;//счетчик таймера движения танка
    void locate_target();//где находиться цель
    void locate_shot();//где находиться выстрел
    int gunner;//переменная, которая определяет направление выстрела, определяется в момент выстрела,
    //без нее снаряд будет менять направление в зависимости от направления ствола
    void move_shot();//движение выстрела
    void checkTarget();//проверяем столкновение с целью
};

#endif // SHOOTER_H
