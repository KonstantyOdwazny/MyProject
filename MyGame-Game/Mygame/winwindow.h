#ifndef WINWINDOW_H
#define WINWINDOW_H
#include "abstractwindow.h"

class WinWindow:public AbstractWindow
{
private:
    void InitText() override;
    void InitMusic() override;
    void InitTexture() override;
    sf::Text text;
public:
    WinWindow();
    ~WinWindow();
    void Update() override;
    void Drawing() override;
    void PlayMusic() override{};
    void PollEvents() override;
    bool Running() override;
    bool run;

};

#endif // WINWINDOW_H
