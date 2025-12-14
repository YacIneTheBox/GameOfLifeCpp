#include "raylib.h"
#include <string>
#include <cmath>
using namespace std;

class Slider{
public:
    float x, y, width, height;
    float minValue, maxValue, currentValue;
    bool isDragging;

    Slider(float x, float y, float width, float height, float minVal, float maxVal, float startVal){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->minValue = minVal;
        this->maxValue = maxVal;
        this->currentValue = startVal;
        this->isDragging = false;
    }

    void Update(){
        Vector2 mousePos = GetMousePosition();
        Rectangle sliderRect = {x, y, width, height};
        Rectangle handleRect = GetHandleRect();

        // Vérifier si on clique sur le handle
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(CheckCollisionPointRec(mousePos, handleRect)){
                isDragging = true;
            }
        }

        // Arrêter le drag
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            isDragging = false;
        }

        // Mettre à jour la position si on drag
        if(isDragging){
            float mouseX = mousePos.x;
            float relativeX = mouseX - x;
            relativeX = fmax(0, fmin(relativeX, width)); // Limiter entre 0 et width

            // Convertir la position en valeur
            currentValue = minValue + (relativeX / width) * (maxValue - minValue);
        }
    }

    Rectangle GetHandleRect(){
        float handleWidth = 15;
        float handleHeight = height + 10;
        float percent = (currentValue - minValue) / (maxValue - minValue);
        float handleX = x + (percent * width) - handleWidth/2;
        float handleY = y - 5;

        return {handleX, handleY, handleWidth, handleHeight};
    }

    void Draw(){
        // Dessiner la barre
        DrawRectangleRec({x, y, width, height}, LIGHTGRAY);
        DrawRectangleLinesEx({x, y, width, height}, 2, GRAY);

        // Dessiner le handle
        Rectangle handle = GetHandleRect();
        Color handleColor = isDragging ? DARKGRAY : GOLD;
        DrawRectangleRec(handle, handleColor);
        DrawRectangleLinesEx(handle, 2, BLACK);

        // Afficher la valeur
        string valueText = "Speed: " + to_string((int)currentValue);
        DrawText(valueText.c_str(), x, y - 25, 20, BLACK);
    }

    float GetValue(){
        return currentValue;
    }
};
