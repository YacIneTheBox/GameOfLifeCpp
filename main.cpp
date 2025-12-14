#include "raylib.h"
/*
 * making the system work
 * adding zoom option
 * adding speed control
 * adding pause option
 * adding reset option
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
                    DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, BLACK);
                }

            }
        }
    }
};

int main() {
    const int screenWidth = 1200;
    const int gridareawidth = screenWidth - 400;
    const int screenHeight = 800;
    const int cellSize = 10;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(10);

    Grid grid(gridareawidth / cellSize, gridareawidth / cellSize, cellSize);
    grid.Init();

    bool paused = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // separate line
        DrawLineEx(Vector2{805, 0}, Vector2{805, 800}, 10.0f, GRAY);
        grid.Draw();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) grid.SelectionCheck(GetMousePosition());
        if (IsKeyPressed(KEY_SPACE))paused = !paused;
        if(paused == false)grid.Update();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
