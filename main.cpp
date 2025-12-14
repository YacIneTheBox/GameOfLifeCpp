#include "raylib.h"
#include <string>
#include "Slider.h"
using namespace std;
/*
 * adding speed control
 */
class Cell{
public:
     int x;
     int y;
     bool alive;
 };

class Grid{
public:
    Cell** cells;
    int width;
    int height;
    int cellSize;

    Grid(int width, int height, int cellSize){
        this->width = width;
        this->height = height;
        this->cellSize = cellSize;
        cells = new Cell*[width];
        for(int i = 0; i < width; i++){
            cells[i] = new Cell[height];
        }
    }

    // Constructeur de copie
    Grid(const Grid& other){
        width = other.width;
        height = other.height;
        cellSize = other.cellSize;

        // Allouer un nouveau tableau
        cells = new Cell*[width];
        for(int i = 0; i < width; i++){
            cells[i] = new Cell[height];
            // Copier chaque cellule
            for(int j = 0; j < height; j++){
                cells[i][j] = other.cells[i][j];
            }
        }
    }

    // Opérateur d'assignation
    Grid& operator=(const Grid& other){
        if(this != &other){  // Éviter l'auto-assignation
            // Libérer l'ancienne mémoire
            for(int i = 0; i < width; i++){
                delete[] cells[i];
            }
            delete[] cells;

            // Copier les dimensions
            width = other.width;
            height = other.height;
            cellSize = other.cellSize;

            // Allouer et copier
            cells = new Cell*[width];
            for(int i = 0; i < width; i++){
                cells[i] = new Cell[height];
                for(int j = 0; j < height; j++){
                    cells[i][j] = other.cells[i][j];
                }
            }
        }
        return *this;
    }

    // Destructeur (important pour éviter les fuites mémoire!)
    ~Grid(){
        for(int i = 0; i < width; i++){
            delete[] cells[i];
        }
        delete[] cells;
    }

    void Init(){
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                cells[i][j].x = i * cellSize;
                cells[i][j].y = j * cellSize;
                cells[i][j].alive = false;
            }
        }
    }

    void SelectionCheck(Vector2 mousePos){
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;
        if(x >= 0 && x < width && y >= 0 && y < height){
            cells[x][y].alive = !cells[x][y].alive;
        }
    }

    int NeighborsAliveCount(int i, int j){
        int count = 0;
        if (i == 0 && j == 0){
            if (cells[i+1][j].alive) count++;
            if (cells[i][j+1].alive) count++;
            if (cells[i+1][j+1].alive) count++;
            return count;
        }else if (i == width-1 && j == height-1){
            if (cells[i-1][j].alive) count++;
            if (cells[i][j-1].alive) count++;
            if (cells[i-1][j-1].alive) count++;
            return count;
        }
        else if (i == 0 && j == height-1){  // Coin haut-droit
            if (cells[i+1][j].alive) count++;
            if (cells[i][j-1].alive) count++;
            if (cells[i+1][j-1].alive) count++;
            return count;
        }
        else if (i == width-1 && j == 0){
            if (cells[i-1][j].alive) count++;
            if (cells[i][j+1].alive) count++;
            if (cells[i-1][j+1].alive) count++;
            return count;
        }
        else if (i == 0){
            if (cells[i+1][j].alive) count++;
            if (cells[i][j-1].alive) count++;
            if (cells[i+1][j-1].alive) count++;
            if (cells[i][j+1].alive) count++;
            if (cells[i+1][j+1].alive) count++;
            return count;
        }else if (j == 0){
            if (cells[i-1][j].alive) count++;
            if (cells[i][j+1].alive) count++;
            if (cells[i-1][j+1].alive) count++;
            if (cells[i+1][j].alive) count++;
            if (cells[i+1][j+1].alive) count++;
            return count;
        }else if (i == width-1){
            if (cells[i-1][j].alive) count++;
            if (cells[i][j-1].alive) count++;
            if (cells[i-1][j-1].alive) count++;
            if (cells[i][j+1].alive) count++;
            if (cells[i-1][j+1].alive) count++;
            return count;
        }else if (j == height-1){
            if (cells[i-1][j].alive) count++;
            if (cells[i][j-1].alive) count++;
            if (cells[i-1][j-1].alive) count++;
            if (cells[i+1][j].alive) count++;
            if (cells[i+1][j-1].alive) count++;
            return count;
        }else{
            if (cells[i-1][j].alive) count++;
            if (cells[i][j-1].alive) count++;
            if (cells[i-1][j-1].alive) count++;
            if (cells[i+1][j].alive) count++;
            if (cells[i+1][j-1].alive) count++;
            if (cells[i][j+1].alive) count++;
            if (cells[i-1][j+1].alive) count++;
            if (cells[i+1][j+1].alive) count++;
            return count;
        }
        return count;
    }

    void Update(){
        Cell** nextGen = new Cell*[width];
        for(int i = 0; i < width; i++){
            nextGen[i] = new Cell[height];
        }

        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                int count = NeighborsAliveCount(i, j);
                if (cells[i][j].alive){
                    nextGen[i][j].alive = (count == 2 || count == 3);
                }else{
                    nextGen[i][j].alive = (count == 3);
                }
            }
        }

        // Copier nextGen vers cells
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                cells[i][j].alive = nextGen[i][j].alive;
            }
            delete[] nextGen[i];
        }
        delete[] nextGen;
    }

    void Draw(){
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                if(!cells[i][j].alive){
                    DrawRectangleLines(i * cellSize, j * cellSize, cellSize, cellSize, BLACK);
                }else{
                    DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, GOLD);
                }

            }
        }
    }
};

class Button{
public:
    float x, y, width, height;
    string text;
    bool isToggled;

    Button(float x, float y, float width, float height, string t){
        this->text = t;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->isToggled = false;
    }

    void Draw(){
        // Taille de police adaptative basée sur la hauteur du bouton
        int fontSize = height * 0.4f;  // 40% de la hauteur du bouton

        if (IsMouseOver()){
            DrawRectangleRoundedLines({x, y, width, height}, 0.2f, 4, BLACK);
        }else{
            DrawRectangleRoundedLines({x, y, width, height}, 0.2f, 4, GOLD);
        }

        int textWidth = MeasureText(text.c_str(), fontSize);
        DrawText(text.c_str(),
                 x + (width - textWidth) / 2,
                 y + (height - fontSize) / 2,
                 fontSize, BLACK);
    }

    bool IsMouseOver(){
        return CheckCollisionPointRec(GetMousePosition(), {x, y, width, height});
    }

    void Update(){
        if(IsMouseOver()){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                isToggled = !isToggled;  // Inverse l'état au clic
            }
        }
        Draw();
    }

    bool GetState(){
        return isToggled;
    }
};


int main() {
    // Utiliser des dimensions de base fixes mais raisonnables
    const int BASE_WIDTH = 1200;
    const int BASE_HEIGHT = 900;

    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Game of Life");

    // MAINTENANT on peut récupérer les vraies dimensions de l'écran
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Zone de grille = 75% de la largeur
    const int gridAreaWidth = screenWidth * 0.75f;

    // Zone UI = 25% restante
    const int uiAreaX = gridAreaWidth;
    const int uiAreaWidth = screenWidth - gridAreaWidth;

    // Taille de cellule adaptative basée sur la hauteur
    int cellSize = screenHeight / 60; // Environ 60 cellules en hauteur
    if(cellSize < 8) cellSize = 8;
    if(cellSize > 20) cellSize = 20;

    Grid* savedPat = nullptr;
    SetTargetFPS(10);

    Grid grid(gridAreaWidth / cellSize, screenHeight / cellSize, cellSize);
    grid.Init();

    // Boutons avec positions adaptatives (en pourcentage)
    float buttonWidth = uiAreaWidth * 0.75f;      // 75% de la largeur UI
    float buttonHeight = screenHeight * 0.07f;    // 7% de la hauteur
    float buttonX = uiAreaX + (uiAreaWidth - buttonWidth) / 2;  // Centré
    float marginTop = screenHeight * 0.04f;       // 4% de marge

    Button pauseButton(buttonX, marginTop, buttonWidth, buttonHeight, "Start");

    // Slider adaptatif
    float sliderY = marginTop + buttonHeight + marginTop;
    float sliderHeight = screenHeight * 0.02f;    // 2% de hauteur
    Slider speedSlider(buttonX, sliderY, buttonWidth, sliderHeight, 1, 60, 10);

    // Boutons supplémentaires
    float spacing = screenHeight * 0.025f;
    float buttonY2 = sliderY + sliderHeight + spacing + marginTop;
    float buttonY3 = buttonY2 + buttonHeight + spacing;
    float buttonY4 = buttonY3 + buttonHeight + spacing;

    Button saveButton(buttonX, buttonY2, buttonWidth, buttonHeight, "Save (S)");
    Button loadButton(buttonX, buttonY3, buttonWidth, buttonHeight, "Load (L)");
    Button resetButton(buttonX, buttonY4, buttonWidth, buttonHeight, "Reset (R)");

    bool paused = true;

    while (!WindowShouldClose()) {
        SetTargetFPS(speedSlider.GetValue());
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Mettre à jour les contrôles
        pauseButton.Update();
        speedSlider.Update();
        speedSlider.Draw();

        saveButton.Draw();
        loadButton.Draw();
        resetButton.Draw();

        paused = !pauseButton.GetState();
        pauseButton.text = pauseButton.GetState() ? "Pause" : "Start";

        // Ligne de séparation
        float lineWidth = 5;
        DrawLineEx(Vector2{(float)gridAreaWidth, 0},
                   Vector2{(float)gridAreaWidth, (float)screenHeight},
                   lineWidth, GRAY);

        grid.Draw();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if(mousePos.x < gridAreaWidth) {
                grid.SelectionCheck(mousePos);
            }
            if(saveButton.IsMouseOver() && paused) {
                if(savedPat != nullptr) delete savedPat;
                savedPat = new Grid(grid);
            }
            if(loadButton.IsMouseOver() && paused && savedPat != nullptr) {
                grid = *savedPat;
            }
            if(resetButton.IsMouseOver() && paused) {
                grid.Init();
            }
        }

        if (IsKeyPressed(KEY_SPACE)) paused = !paused;
        if (IsKeyPressed(KEY_S) && paused) {
            if(savedPat != nullptr) delete savedPat;
            savedPat = new Grid(grid);
        }
        if (IsKeyPressed(KEY_L) && paused && savedPat != nullptr) {
            grid = *savedPat;
        }
        if (IsKeyPressed(KEY_R) && paused) {
            grid.Init();
        }

        if(!paused) grid.Update();
        EndDrawing();
    }

    if(savedPat != nullptr) delete savedPat;
    CloseWindow();
    return 0;
}
