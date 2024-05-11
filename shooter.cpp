#include <QPainter>
#include <QTime>
#include "shooter.h"

shooter::shooter(QWidget *parent): QWidget(parent)
{setStyleSheet("background-color:white;");//цвет окна
    resize(field_width,field_height);//размер поля
    loadQImage();
    startGame();
}
void shooter::loadQImage()
{
    tank = QImage(brick_size,brick_size,QImage::Format_ARGB32);//длина, ширина формат блока
    tank.fill(Qt::red);
    target = QImage(brick_size,brick_size,QImage::Format_ARGB32);
    target.fill(Qt::green);
    shot = QImage(brick_size,brick_size,QImage::Format_ARGB32);//длина, ширина формат блока
    shot.fill(Qt::black);
}

void shooter::startGame()
{//создаем танк,задаем координаты верхнего левого угла каждого блока
    //танк начинает движение в нижнем левом углу
    tank_x.push_back(0*brick_size);
    tank_y.push_back(field_height-brick_size);
    tank_x.push_back(2*brick_size);
    tank_y.push_back(field_height-brick_size);
    for(int i = 0;i<3;i++)
    {
        tank_x.push_back(i*brick_size);
        tank_y.push_back(field_height-2*brick_size);
    }
    tank_x.push_back(1*brick_size);
    tank_y.push_back(field_height-3*brick_size);

    locate_target();

    //play=true;//игра началась
    timertank = startTimer(40);//запускаем таймер, отвечает за плавность движения объектов

}

void shooter::locate_target()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    target_x = (r * brick_size);

    r = qrand() % RAND_POS;
    target_y = (r * brick_size);
}
void shooter::paintEvent(QPaintEvent *e)//срабатывает при каждой смене координат и при их начальной установке
{
    Q_UNUSED(e);//переменную е не используем
    painting();
}
void shooter::painting()//перед отрисовкой необходимо, чтобы все координаты уже были обозначены
{
    QPainter qp(this);

    //рисуем цель
    qp.drawImage(target_x, target_y, target);
    //рисуем блоки tank по координатам
    for(int i =0;i<=tank_size;i++)
    {
        qp.drawImage(tank_x[i], tank_y[i], tank);
        qp.setPen(Qt::black);//цвет линии
        qp.drawRect(tank_x[i],tank_y[i],tank.width(),tank.height());
    }
    //рисуем выстрел
    qp.drawImage(shot_x, shot_y, shot);
}


void shooter:: keyPressEvent (QKeyEvent *e) {
    int key = e->key();//извлекаем числовое значение int key из ивента e,здесь в отличии от paintEvent, мы используем переменную e

    switch(key)
    {
    case Qt::Key_Left:
        if(tank_y[5]<tank_y[2] && tank_y[5]<tank_y[4])//танк повернут наверх, нужно повернуть налево
        {tank_x[0]+=2*brick_size;tank_y[1]-=2*brick_size;tank_y[2]+=brick_size;tank_x[2]+=brick_size;
            tank_y[4]-=brick_size;tank_x[4]-=brick_size;tank_y[5]+=brick_size;tank_x[5]-=brick_size;}
        else if(tank_y[5]>tank_y[2] && tank_y[5]>tank_y[4])//танк повернут вниз, нужно повернуть налево
        {tank_y[0]+=2*brick_size;tank_x[1]+=2*brick_size;tank_x[2]-=brick_size;tank_y[2]+=brick_size;
            tank_x[4]+=brick_size;tank_y[4]-=brick_size;tank_x[5]-=brick_size;tank_y[5]-=brick_size;}
        else if(tank_y[5]>tank_y[2] && tank_y[5]<tank_y[4])//танк повернут направо, нужно повернуть налево
        {tank_y[0]+=2*brick_size;tank_x[0]+=2*brick_size;tank_x[1]+=2*brick_size;tank_y[1]-=2*brick_size;
            tank_y[2]+=2*brick_size;tank_y[4]-=2*brick_size; tank_x[5]-=2*brick_size;};

        for(int i =0; i<tank_size;i++)
        {
            tank_x[i]-= brick_size;
        };break;
    case Qt::Key_Right:
        if(tank_y[5]<tank_y[2] && tank_y[5]<tank_y[4])//танк повернут наверх, нужно повернуть направо
        {tank_y[0]-=2*brick_size;tank_x[1]-=2*brick_size;tank_x[2]+=brick_size;tank_y[2]-=brick_size;
            tank_x[4]-=brick_size;tank_y[4]+=brick_size;tank_x[5]+=brick_size;tank_y[5]+=brick_size;}
        else if(tank_y[5]>tank_y[2] && tank_y[5]>tank_y[4])//танк повернут вниз, нужно повернуть направо
        {tank_x[0]-=2*brick_size;tank_y[1]+=2*brick_size;tank_x[2]-=brick_size;tank_y[2]-=brick_size;
            tank_x[4]+=brick_size;tank_y[4]+=brick_size;tank_x[5]+=brick_size;tank_y[5]-=brick_size;}
        else if(tank_y[5]<tank_y[2] && tank_y[5]>tank_y[4])//танк повернут налево, нужно повернуть направо
        {tank_x[0]-=2*brick_size;tank_y[0]-=2*brick_size;tank_y[1]+=2*brick_size;tank_x[1]-=2*brick_size;
            tank_y[2]-=2*brick_size;tank_y[4]+=2*brick_size;tank_x[5]+=2*brick_size;};

        for(int i =0; i<tank_size;i++)
        {
            tank_x[i]+= brick_size;
        };break;
        case Qt::Key_Up:
        if(tank_y[5]>tank_y[2] && tank_y[5]<tank_y[4])//танк повернут направо, нужно повернуть наверх
            {tank_y[0]+=2*brick_size;tank_x[1]+=2*brick_size;tank_x[2]-=brick_size;tank_y[2]+=brick_size;
        tank_x[4]+=brick_size;tank_y[4]-=brick_size;tank_x[5]-=brick_size;tank_y[5]-=brick_size;}
        else if(tank_y[5]<tank_y[2] && tank_y[5]>tank_y[4])//танк повернут налево, нужно повернуть наверх
        {tank_x[0]-=2*brick_size;tank_y[1]+=2*brick_size;tank_x[2]-=brick_size;tank_y[2]-=brick_size;
            tank_x[4]+=brick_size;tank_y[4]+=brick_size;tank_x[5]+=brick_size;tank_y[5]-=brick_size;}
        else if(tank_y[5]>tank_y[2] && tank_y[5]>tank_y[4])//танк повернут вниз, нужно повернуть наверх
        {tank_x[0]-=2*brick_size;tank_y[0]+=2*brick_size;tank_x[1]+=2*brick_size;tank_y[1]+=2*brick_size;tank_x[2]-=2*brick_size;
            tank_x[4]+=2*brick_size;tank_y[5]-=2*brick_size;};
        for(int i =0; i<tank_size;i++)
        {
            tank_y[i]-= brick_size;
        };break;
    case Qt::Key_Down:
            if(tank_y[5]>tank_y[2] && tank_y[5]<tank_y[4])//танк повернут направо, нужно повернуть вниз
            {tank_x[0]+=2*brick_size;tank_y[1]-=2*brick_size;tank_x[2]+=brick_size;tank_y[2]+=brick_size;
                tank_x[4]-=brick_size;tank_y[4]-=brick_size;tank_x[5]-=brick_size;tank_y[5]+=brick_size;}
            else if(tank_y[5]<tank_y[2] && tank_y[5]>tank_y[4])//танк повернут налево, повернуть вниз
            {tank_y[0]-=2*brick_size;tank_x[1]-=2*brick_size;tank_x[2]+=brick_size;tank_y[2]-=brick_size;
                tank_x[4]-=brick_size;tank_y[4]+=brick_size;tank_x[5]+=brick_size;tank_y[5]+=brick_size;}
            else if(tank_y[5]<tank_y[2] && tank_y[5]<tank_y[4])//танк повернут вверх, повернуть вниз
            {tank_x[0]+=2*brick_size;tank_y[0]-=2*brick_size;tank_x[1]-=2*brick_size;tank_y[1]-=2*brick_size;tank_x[2]+=2*brick_size;
                tank_x[4]-=2*brick_size;tank_y[5]+=2*brick_size;};
            for(int i =0; i<tank_size;i++)
            {
                tank_y[i]+= brick_size;
            };break;
    case Qt::Key_Space:

        locate_shot();
        break;
    case Qt::Key_P:
    pauseGame();
      break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
}
    QWidget::keyPressEvent(e);
}

void shooter::pauseGame() {//игра на паузу

    if (pause) {//если кнопка Р была нажата, то отключается

         timertank = startTimer(40);//запускаем таймер, отвечает за плавность движения объектов
        pause = false;
    }

    else {
        //если нет, ставим на паузу, убиваем таймер killTimer(timerId);
        pause = true;
        killTimer(timertank);
    }
}

void shooter::locate_shot()
{   if(tank_y[5]<tank_y[2] && tank_y[5]<tank_y[4])//танк повернут наверх
    {shot_x=tank_x[5];
     shot_y=tank_y[5]-brick_size;
        gunner=1;}
    else if (tank_y[5]>tank_y[2] && tank_y[5]>tank_y[4])//танк повернут вниз
    {shot_x=tank_x[5];
    shot_y=tank_y[5]+brick_size;
    gunner=2;}
    else if(tank_y[5]>tank_y[2] && tank_y[5]<tank_y[4])//танк повернут направо
    {shot_x=tank_x[5]+brick_size;
        shot_y=tank_y[5];
    gunner=3;}
    else if(tank_y[5]<tank_y[2] && tank_y[5]>tank_y[4])//танк повернут налево
    {shot_x=tank_x[5]-brick_size;
        shot_y=tank_y[5];
     gunner=4;};
}
void shooter::move_shot()
{
    if(gunner==1)//танк повернут наверх
    { shot_y-=brick_size;}
    else if (gunner==2)//танк повернут вниз
    {shot_y+=brick_size;}
    else if(gunner==3)//танк повернут направо
    {shot_x+=brick_size;}
    else if(gunner==4)//танк повернут налево
    {shot_x-=brick_size;};
}

void shooter::checkTarget()
{
    if ((shot_x == target_x) && (shot_y == target_y)) {//Если снаряд сталкивается с целью

        locate_target();//создаем новую цель
    }
}
void shooter::timerEvent(QTimerEvent *e)
{  checkTarget();
    move_shot();
    repaint();
}
