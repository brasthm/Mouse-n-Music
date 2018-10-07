#ifndef CONSTANTES_H
#define CONSTANTES_H

static constexpr float PI = 3.14159265f;

static constexpr size_t WINDOW_W = 1024;
static constexpr size_t WINDOW_H = 768;


static constexpr float REFERENCE_X = WINDOW_W/2.f;
static constexpr float REFERENCE_Y = 698.f;

static constexpr float REFERENCE_MARGIN = 150.f;

static constexpr size_t NOTE_NB_POINTS = 16;
static constexpr float NOTE_START_DISTANCE = 1000.f;

static constexpr float POP_UP_DISTANCE = REFERENCE_MARGIN + 100.f;

static constexpr size_t NB_SECTIONS = 8;

static const std::string ROOT_PATH = "../../";
static const std::string IMG_PATH = ROOT_PATH + "img/";
static const std::string FONT_PATH = ROOT_PATH + "font/";
static const std::string MUSIC_PATH = ROOT_PATH + "music/";

#endif // !CONSTANTES_H
