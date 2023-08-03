#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;
double vx = 4, vy = -4, vp = 10.0f;
//Function to Draw Bricks
void Draw_Bricks(RenderWindow& window, RectangleShape LongBrick[5][10],
    RectangleShape ShortBrick[4][8], bool LongVisible[5][10],
    bool ShortVisible[4][8]) {
    double x = 0, y = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            LongBrick[i][j].setFillColor(Color::Color(176, 196, 222));
            LongBrick[i][j].setSize(Vector2f(192.0f, 25.0f));
            LongBrick[i][j].setPosition(x, y);
            if (LongVisible[i][j]) {
                window.draw(LongBrick[i][j]);
            }
            x += 193.0;
        }
        x = 0;
        y += 54.0;
    }
    double x2 = 193.0, y2 = 27.0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            ShortBrick[i][j].setFillColor(Color::Color(224, 255, 255));
            ShortBrick[i][j].setSize(Vector2f(192.0f, 25.0f));
            ShortBrick[i][j].setPosition(x2, y2);
            if (ShortVisible[i][j]) {
                window.draw(ShortBrick[i][j]);
            }
            x2 += 193.0;
        }
        x2 = 193.0;
        y2 += 54;
    }
}
//function to initialize boolean array elements as true:
void All_True(bool LongVisible[5][10], bool ShortVisible[4][8]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            LongVisible[i][j] = true;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            ShortVisible[i][j] = true;
        }
    }
}
//Function to make the ball bounce off screen sides:
void BallScreenBounce(Sprite& ball, int& attempts, bool& GameOver) {
    if (ball.getPosition().x > 1880.0f) {
        vx *= -1;
    }
    else if (ball.getPosition().x < 0.0) {
        vx *= -1;
    }
    else if (ball.getPosition().y > 960.0f) {
        ball.setPosition(1000.0f, 700.0f);
        vy = -4;
        attempts--;
        if (attempts == 0) {
            GameOver = true;
        }
    }
    else if (ball.getPosition().y < 0.0f) {
        vy *= -1;
    }
}
int main()
{
    RenderWindow window(VideoMode(1940, 1000), "Brick Breaker", Style::Default);
    window.setFramerateLimit(120);
    RectangleShape LongBrick[5][10], ShortBrick[4][8];
    bool LongVisible[5][10], ShortVisible[4][8];
    int score = 0;
    int attempts = 3;
    bool GameOver = false;

    //Background:
    Texture wall1;
    wall1.loadFromFile("8.JPG");
    Sprite background;
    background.setTexture(wall1);

    //setting font:
    Font font;
    font.loadFromFile("fonto.ttf");

    //Score Text:
    Text Score;
    Score.setFont(font);
    Score.setString("Score: " + to_string(score));
    Score.setPosition(50, 850);
    Score.setCharacterSize(35);

    //Winner Text:
    Text Winner;
    Winner.setFont(font);
    Winner.setString("Winner");
    Winner.setPosition(600, 330);
    Winner.setCharacterSize(200);

    //Game Over Text:
    Text gameover;
    gameover.setFont(font);
    gameover.setString("Game Over");
    gameover.setPosition(370, 330);
    gameover.setCharacterSize(200);

    //Attempts text
    Text Attempts;
    Attempts.setFont(font);
    Attempts.setPosition(50, 900);
    Attempts.setCharacterSize(35);

    //setting sound:
    SoundBuffer buffer;
    buffer.loadFromFile("bounce.wav");
    Sound sound;
    sound.setBuffer(buffer);

    //ball:
    Texture ball_texture;
    ball_texture.loadFromFile("15.png");
    Sprite ball;
    ball.setTexture(ball_texture);
    ball.setPosition(1000.0f, 700.0f);

    //paddle
    RectangleShape paddle(Vector2f(200, 20));
    paddle.setPosition(400, 800);

    //initializing all values of bool arrays as true:
    All_True(LongVisible, ShortVisible);

    //window:
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            }
        }
        //keyboard input :
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && paddle.getPosition().x > 0)
        {
            paddle.move(-vp, 0.0f);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && paddle.getPosition().x < 1720) {
            paddle.move(vp, 0.0f);

        }

        //collision with paddle 
        FloatRect ballbound = ball.getGlobalBounds();
        FloatRect paddlebound = paddle.getGlobalBounds();
        if (ball.getGlobalBounds().intersects(paddlebound))
        {
            vy = -vy;
        }
        window.clear();

        //Ball bouncing off screen sides:
        BallScreenBounce(ball, attempts, GameOver);
        ball.move(vx, vy);

        //if the bricks aren't finished:
        if (score != 820) {

            //Making sure the player didn't use his 3 attempts:
            if (!GameOver)
            {
                //Drawing Bricks & Background:
                window.draw(background);
                Draw_Bricks(window, LongBrick, ShortBrick, LongVisible, ShortVisible);

                //collision:
                FloatRect ballbound = ball.getGlobalBounds();
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 10; j++) {

                        //condition satisfied once so the sound is played once as well:
                        if (ballbound.intersects(LongBrick[i][j].getGlobalBounds()) && LongVisible[i][j]) {
                            if (abs(vy) < 8.5) {
                                vy *= -1.25;

                            }
                            else {
                                vy *= -1;
                            }
                            ball.move(vx, vy);
                            sound.play();
                            LongVisible[i][j] = false;
                            score += 10;
                        }
                    }
                }
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 8; j++) {
                        //Same condition:
                        if (ballbound.intersects(ShortBrick[i][j].getGlobalBounds()) && ShortVisible[i][j]) {
                            if (abs(vy) < 8.5) {
                                vy *= -1.25;

                            }
                            else {
                                vy *= -1;
                            }
                            ball.move(vx, vy);
                            sound.play();
                            ShortVisible[i][j] = false;
                            score += 10;
                        }
                    }
                }
                window.draw(paddle);
                window.draw(ball);
                window.draw(Attempts);
            }
            else
            {
                window.draw(gameover);
                Score.setCharacterSize(100);
                Score.setPosition(640, 550);
                window.draw(Score);
            }
            window.draw(Score);
        }
        else
        {
            window.draw(background);
            Score.setPosition(640, 550);
            window.draw(Score);
            window.draw(Winner);
        }
        Attempts.setString("Attempts: " + to_string(attempts));
        Score.setString("Score: " + to_string(score));
        window.display();
    }
    return 0;
}