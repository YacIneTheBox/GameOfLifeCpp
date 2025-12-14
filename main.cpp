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
    bool isToggled;  // Variable membre pour garder l'état

    Button(float x, float y, float width, float height, string t){
        this->text = t;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->isToggled = false;  // État initial
    }

    void Draw(){
        if (IsMouseOver()){
            DrawRectangleRoundedLines({x, y, width, height}, 2.0f, 4, BLACK);
        }else{
            DrawRectangleRoundedLines({x, y, width, height}, 2.0f, 4, GOLD);
        }
        DrawText(text.c_str(), x + width/2 - (float)MeasureText(text.c_str(), 20)/2,
                 y + height/2 - 10, 20, BLACK);
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
    const int screenWidth = 1200;
    const int screenHeight = 900;
    const int gridareawidth = screenWidth - (screenWidth-screenHeight);
    const int cellSize = (screenWidth/screenHeight)*15;

    Grid** savedPaterns = new Grid*[10];
    for(int i = 0; i < 10; i++){
        savedPaterns[i] = new Grid(gridareawidth / cellSize, screenHeight / cellSize, cellSize);
    }
    int savedPatternIndex = 0;

    Grid* savedPat = nullptr;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(10);

    Grid grid(gridareawidth / cellSize, screenHeight / cellSize, cellSize);
    grid.Init();

    // buttons
    Button pauseButton(gridareawidth + 50, 30, 200, 50, "Resume");

    bool paused = true;
    Color caseColor = RAYWHITE;

    // créé le slider (vitesse de 1 a 60 fps)
    Slider speedSlider(gridareawidth + 50, 200, 200, 10, 1, 60, 10);

    while (!WindowShouldClose()) {
        SetTargetFPS(speedSlider.GetValue());
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Mettre à jour le bouton
        pauseButton.Update();
        speedSlider.Update();
        speedSlider.Draw();
        // Lire l'état du bouton
        paused = !pauseButton.GetState();  // Si toggled = true, paused = false

        // Mettre à jour le texte
        pauseButton.text = pauseButton.GetState() ? "Pause" : "Start";

        // separate line
        DrawLineEx(Vector2{screenHeight+5, 0}, Vector2{screenHeight+5, screenHeight}, 10.0f, GRAY);
        grid.Draw();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) grid.SelectionCheck(GetMousePosition());
        if (IsKeyPressed(KEY_SPACE))paused = !paused;

        // Pour sauvegarder
        if (IsKeyPressed(KEY_S) && paused == true){
            if(savedPat != nullptr) delete savedPat;  // Libérer l'ancienne sauvegarde
            savedPat = new Grid(grid);  // Utilise le constructeur de copie
        }

        // Pour charger
        if (IsKeyPressed(KEY_L) && paused == true && savedPat != nullptr){
            grid = *savedPat;  // Utilise l'opérateur d'assignation
        }

        if (IsKeyPressed(KEY_R) && paused == true){
            grid.Init();
        }
        if(!paused) grid.Update();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
