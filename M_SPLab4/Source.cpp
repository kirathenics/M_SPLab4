#include <iostream>
using namespace std;

const int DEFAULT_HEIGHT = 600;
const int DEFAULT_WIDTH = 800;

enum Quality {
    LOW = 0,
    MID,
    HIGH
};

enum Difficulty {
    EASY = 0,
    MEDIUM,
    HARD
};

enum Language {
    ENGLISH = 0,
    RUSSIAN,
    SPANISH
};

class Window
{
public:
    Window();
    Window(int height = DEFAULT_HEIGHT, int width = DEFAULT_WIDTH, bool areAdministatorRightsGranted = false);
    ~Window();

    void showOrHide();
    void doWork();

protected:
    int id, height, width, memoryNeeded;
    bool areAdministatorRightsGranted, isShown;

    static int idCounter;

    virtual int calculateMemory();
};

int Window::idCounter = 0;

Window::Window() :
    id(-1),
    height(0),
    width(0),
    memoryNeeded(0),
    areAdministatorRightsGranted(false),
    isShown(false)
{}

Window::Window(int height, int width, bool areAdministatorRightsGranted) :
    height(height),
    width(width),
    areAdministatorRightsGranted(areAdministatorRightsGranted),
    isShown(true)
{
    ++idCounter;
    id = idCounter;
    doWork();
}

Window::~Window()
{}

void Window::showOrHide()
{
    isShown = !isShown;
}

void Window::doWork()
{
    memoryNeeded = calculateMemory();
}

int Window::calculateMemory()
{
    return height * width;
}



const float DEFAULT_BRIGHTNESS = 0.5;
const float DEFAULT_VOLUME = 0.5;

class Settings
{
public:
    float brightness, volume;
    int quality, difficulty, language;

    Settings(float brightness = DEFAULT_BRIGHTNESS, float volume = DEFAULT_VOLUME, int quality = Quality::MID, int difficulty = Difficulty::MEDIUM, int language = Language::ENGLISH);
    ~Settings();

    virtual int paramsSum();

protected:
    
};

Settings::Settings(float brightness, float volume, int quality, int difficulty, int language) :
    brightness(brightness),
    volume(volume),
    quality(quality),
    difficulty(difficulty),
    language(language)
{}

Settings::~Settings()
{}

int Settings::paramsSum()
{
    return 100 * brightness + 100 * volume + quality + difficulty + language;
}



class GameWindow : public Window
{
public:
    GameWindow(int height = DEFAULT_HEIGHT, int width = DEFAULT_WIDTH, bool areAdministatorRightsGranted = false, Settings* gameSettings = nullptr);
    ~GameWindow();

    virtual void doAction() = 0;

protected:
    Settings* settings;

    int calculateMemory() override;
};

GameWindow::GameWindow(int height, int width, bool areAdministatorRightsGranted, Settings* gameSettings) : Window(height, width, areAdministatorRightsGranted)
{
    settings = gameSettings;
}

GameWindow::~GameWindow()
{
    if (settings)
    {
        delete settings;
    }
}

int GameWindow::calculateMemory()
{
    if (settings->paramsSum() == 0)
    {
        return 0;
    }

    return Window::calculateMemory() + settings->paramsSum();
}



const int DEFAULT_MAX_ROUNDS = 3;

class RockPaperScissorsSettings : public Settings
{
public:
    RockPaperScissorsSettings(int brightness = DEFAULT_BRIGHTNESS, int volume = DEFAULT_VOLUME, int quality = Quality::MID, int difficulty = Difficulty::MEDIUM, int language = Language::ENGLISH, int maxRounds = DEFAULT_MAX_ROUNDS);
    ~RockPaperScissorsSettings();

    int paramsSum() override;

private:
    int maxRounds;
};

RockPaperScissorsSettings::RockPaperScissorsSettings(int brightness, int volume, int quality, int difficulty, int language, int maxRounds) : 
    Settings(brightness, volume, quality, difficulty, language),
    maxRounds(maxRounds)
{}

RockPaperScissorsSettings::~RockPaperScissorsSettings()
{}

int RockPaperScissorsSettings::paramsSum()
{
    return Settings::paramsSum() + maxRounds;
}


class RockPaperScissorsGameWindow : public GameWindow
{
public:
    RockPaperScissorsGameWindow(int height = DEFAULT_HEIGHT, int width = DEFAULT_WIDTH, bool areAdministatorRightsGranted = false, Settings* gameSettings = nullptr);
    void doAction() override;
};

RockPaperScissorsGameWindow::RockPaperScissorsGameWindow(int height, int width, bool areAdministatorRightsGranted, Settings* gameSettings) :
    GameWindow(height, width, areAdministatorRightsGranted, gameSettings)
{}

void RockPaperScissorsGameWindow::doAction()
{
    doWork();
    cout << "RockPaperScissors game window is performing an action with memory needed: " << memoryNeeded << endl;
}



const int DEFAULT_FIELD_SIZE = 3;

class TicTacToeSettings : public Settings
{
public:
    TicTacToeSettings(int brightness = DEFAULT_BRIGHTNESS, int volume = DEFAULT_VOLUME, int quality = Quality::MID, int difficulty = Difficulty::MEDIUM, int language = Language::ENGLISH, int fieldSize = DEFAULT_FIELD_SIZE);
    ~TicTacToeSettings();

    int paramsSum() override;

private:
    int fieldSize;
};

TicTacToeSettings::TicTacToeSettings(int brightness, int volume, int quality, int difficulty, int language, int fieldSize) :
    Settings(brightness, volume, quality, difficulty, language),
    fieldSize(fieldSize)
{}

TicTacToeSettings::~TicTacToeSettings()
{}

int TicTacToeSettings::paramsSum()
{
    return Settings::paramsSum() + fieldSize;
}


class TicTacToeGameWindow : public GameWindow
{
public:
    TicTacToeGameWindow(int height = DEFAULT_HEIGHT, int width = DEFAULT_WIDTH, bool areAdministatorRightsGranted = false, Settings* gameSettings = nullptr);
    void doAction() override;
};

TicTacToeGameWindow::TicTacToeGameWindow(int height, int width, bool areAdministatorRightsGranted, Settings* gameSettings) :
    GameWindow(height, width, areAdministatorRightsGranted, gameSettings)
{}

void TicTacToeGameWindow::doAction()
{
    doWork();
    cout << "TicTacToe game window is performing an action with memory needed: " << memoryNeeded << endl;
}



const int DEFAULT_REMAINING_TIME = 5;

class SudokuSettings : public Settings
{
public:
    SudokuSettings(int brightness = DEFAULT_BRIGHTNESS, int volume = DEFAULT_VOLUME, int quality = Quality::MID, int difficulty = Difficulty::MEDIUM, int language = Language::ENGLISH, int remainingTime = DEFAULT_REMAINING_TIME);
    ~SudokuSettings();

    int paramsSum() override;

private:
    int remainingTime;
};

SudokuSettings::SudokuSettings(int brightness, int volume, int quality, int difficulty, int language, int remainingTime) :
    Settings(brightness, volume, quality, difficulty, language),
    remainingTime(remainingTime)
{}

SudokuSettings::~SudokuSettings()
{}

int SudokuSettings::paramsSum()
{
    --remainingTime;
    if (remainingTime <= 0)
    {
        return 0;
    }

    return Settings::paramsSum() + remainingTime;
}


class SudokuGameWindow : public GameWindow
{
public:
    SudokuGameWindow(int height = DEFAULT_HEIGHT, int width = DEFAULT_WIDTH, bool areAdministatorRightsGranted = false, Settings* gameSettings = nullptr);
    void doAction() override;
};

SudokuGameWindow::SudokuGameWindow(int height, int width, bool areAdministatorRightsGranted, Settings* gameSettings) :
    GameWindow(height, width, areAdministatorRightsGranted, gameSettings)
{}

void SudokuGameWindow::doAction()
{
    doWork();
    if (memoryNeeded == 0)
    {
        cout << "Sudoku game ended!" << endl;
        return;
    }
    cout << "Sudoku game window is performing an action with memory needed: " << memoryNeeded << endl;
}


int main()
{
    RockPaperScissorsGameWindow rrsGW(700, 600, true, new RockPaperScissorsSettings(0.7, 0.3, 1, 0, 1, 2));
    rrsGW.doAction();
    TicTacToeGameWindow tttGW(500, 500, true, new TicTacToeSettings());
    tttGW.doAction();
    SudokuGameWindow sGW(DEFAULT_HEIGHT, 1000, true, new SudokuSettings(0.4, 0.6, 2, 1, 0, 2));
    sGW.doAction();
    sGW.doAction();

    return 0;
}
