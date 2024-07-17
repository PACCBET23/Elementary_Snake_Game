#ifndef GAME_H
#define GAME_H

#include <random>

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>


class Game : public QWidget{

public:
    Game();


protected:
    void timerEvent (QTimerEvent *event) override;
    void keyPressEvent (QKeyEvent *event) override;
    void paintEvent (QPaintEvent *event) override;

private:
    static const int DOT_WIDHT   = 20;
    static const int DOT_HIGHT    = 20;
    static const int FIELD_WIDHT = 20;
    static const int FIELD_HIGHT  = 20;
    static const int DELAY  = 150;

    void doDrawing();
    void LocalApple();
    void Move();
    void CheckField();
    void GameOver();
    void CheckApple();


    int m_timer_id;

    QPoint m_apple;

    enum Directions
    {
        left,
        right,
        up,
        down
    };

    Directions m_dir;

    bool m_in_game;
    QVector<QPoint> m_dots;


    void InitGame();

};


#endif // GAME_H
