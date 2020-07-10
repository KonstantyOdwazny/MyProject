#ifndef STEROWANIEWINDOW_H
#define STEROWANIEWINDOW_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "abstractwindow.h"


class SterowanieWindow : public AbstractWindow
{
private:
    //functions
    void InitTexture() override;
    void InitMusic() override;
    void InitText() override{};
public:
    SterowanieWindow();
    ~SterowanieWindow();
    void PollEvents() override;
    bool Running() override;
    void Drawing() override;
    void PlayMusic() override;
    void Update() override{};
};

#endif // STEROWANIEWINDOW_H
