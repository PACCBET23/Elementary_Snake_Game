#include "game.h"

#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QMessageBox>


Game::Game(){

    this->resize(DOT_HIGHT * FIELD_HIGHT, DOT_WIDHT * FIELD_WIDHT);

    this->setWindowTitle("Snake game");

    InitGame();

}

void Game::timerEvent(QTimerEvent *event){

    //qDebug() << 1;
    Q_UNUSED(event);

    if(m_in_game){
        CheckApple();
        Move();
        CheckField();
    }
    this->repaint ();

}

void Game::keyPressEvent(QKeyEvent *event){

    int key = event->key();

    if(key == Qt::Key_Left  && m_dir != Directions::right) {m_dir = Directions::left; }
    if(key == Qt::Key_Right && m_dir != Directions::left)  {m_dir = Directions::right;}
    if(key == Qt::Key_Up    && m_dir != Directions::down)  {m_dir = Directions::up;   }
    if(key == Qt::Key_Down  && m_dir != Directions::up)    {m_dir = Directions::down; }



}

void Game::paintEvent(QPaintEvent *event){

    Q_UNUSED(event);

    doDrawing();
}

void Game::doDrawing(){

    QPainter qp(this);

    if(m_in_game){

        qp.setBrush (Qt::red);
        qp.drawEllipse (m_apple.x()*DOT_WIDHT,m_apple.y ()*DOT_HIGHT,DOT_HIGHT,DOT_WIDHT);

        for(int i = 0; i < m_dots.size ();++i){
            if(i==0){
                qp.setBrush (Qt::darkGreen);
                qp.drawEllipse (m_dots[i].x() * DOT_WIDHT,m_dots[i].y() * DOT_HIGHT, DOT_HIGHT, DOT_WIDHT);

            }else{
                qp.setBrush (Qt::green);
                qp.drawEllipse (m_dots[i].x() * DOT_WIDHT,m_dots[i].y() * DOT_HIGHT, DOT_HIGHT, DOT_WIDHT);

            }
        }

    }else{
        GameOver();
    }
}

void Game::LocalApple(){

    // Инициализация генератора случайных чисел
    std::random_device rd;  // Используется для получения случайного начального значения
    std::mt19937 gen(rd()); // Инициализация генератора Mersenne Twister

    std::uniform_int_distribution<> distrib_w(0, DOT_WIDHT - 1); // Диапазон от 0 до DOT_WEIGHT - 1
    std::uniform_int_distribution<> distrib_h(0, DOT_HIGHT - 1); // Диапазон от 0 до DOT_HIGHT - 1

    m_apple.rx() = distrib_w(gen);
    m_apple.ry() = distrib_h(gen);
}

void Game::Move(){

    for(int i = m_dots.size()-1; i > 0; --i){
        m_dots[i] = m_dots[i-1];
    }

    switch(m_dir){
        case left:  {m_dots[0].rx() -= 1; break;}
        case right: {m_dots[0].rx() += 1; break;}
        case up:    {m_dots[0].ry() -= 1; break;}
        case down:  {m_dots[0].ry() += 1; break;}
    }
}

void Game::CheckField(){
    if(m_dots.size() > 4){
        for(int i = 1; i < m_dots.size(); ++i){
            if(m_dots[0] == m_dots[i]) {
                m_in_game = false;
            }
        }
    }

    if(m_dots[0].x() >= FIELD_WIDHT) {m_in_game = false;}
    if(m_dots[0].x() < 0)            {m_in_game = false;}
    if(m_dots[0].y() >= FIELD_HIGHT) {m_in_game = false;}
    if(m_dots[0].y() < 0)            {m_in_game = false;}

    if(!m_in_game) {
        killTimer(m_timer_id);
    }
}

void Game::GameOver(){

    QMessageBox msgb;
    msgb.setText("Game Over");
    msgb.exec();

    InitGame();
}

void Game::CheckApple(){

    if(m_apple == m_dots[0]) {
        m_dots.push_back(QPoint(0, 0));
        LocalApple();
    }
}

void Game::InitGame(){

    m_in_game = true;
    m_dir = right;

    m_dots.resize(3);

    for(int i = 0; i < m_dots.size(); ++i)
    {
        m_dots[i].rx() = m_dots.size() - i - 1;
        m_dots[i].ry() = 0;
    }

    LocalApple();

    m_timer_id = startTimer(DELAY);
}
