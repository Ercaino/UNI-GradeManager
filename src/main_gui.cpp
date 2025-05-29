#include <raylib.h>
#include "../include/raygui.h"

// Include per printf
#include <cstdio>

// Stato dell'applicazione
enum AppState {
    APP_STATE_LOGIN,
    APP_STATE_MAIN
};

int main()
{
    // Impostazione delle dimensioni della finestra
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Manage System");

    SetTargetFPS(60);

    // Variabili per gestire lo stato dell'applicazione
    bool quit = false;
    AppState currentState = APP_STATE_LOGIN;

    while (!quit && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (currentState == APP_STATE_LOGIN)
        {
            // Schermata di login
            DrawCircle(screenWidth / 2, screenHeight / 4, 100, BLACK);
            DrawText("Manage System", screenWidth / 2 - MeasureText("Manage System", 20) / 2, screenHeight / 4 + 120, 20, BLACK);

            // Logo all'interno del cerchio
            DrawRectangle(screenWidth / 2 - 50, screenHeight / 4 - 50, 100, 100, LIGHTGRAY); // Blocco di note
            DrawRectangleLines(screenWidth / 2 - 50, screenHeight / 4 - 50, 100, 100, PURPLE); // Contorno del blocco di note
            for (int i = 0; i < 7; i++) {
                DrawLine(screenWidth / 2 - 40, screenHeight / 4 - 30 + i * 10, screenWidth / 2 + 40, screenHeight / 4 - 30 + i * 10, PURPLE);
            }
            DrawLine(screenWidth / 2 - 20, screenHeight / 4 - 20, screenWidth / 2 + 20, screenHeight / 4 + 20, BLACK); // Asta matita
            DrawLine(screenWidth / 2 - 20, screenHeight / 4 - 20, screenWidth / 2 - 20, screenHeight / 4 + 20, BLACK); // Bordo sinistro
            DrawLine(screenWidth / 2 + 20, screenHeight / 4 - 20, screenWidth / 2 + 20, screenHeight / 4 + 20, BLACK); // Bordo destro

            // Pulsanti Login e Quit
            if (GuiButton((Rectangle){ (float)(screenWidth / 2 - 75), (float)(screenHeight / 2), 150, 50 }, "Login"))
            {
                printf("Login button pressed!\n");
                currentState = APP_STATE_MAIN; // Passa alla schermata principale
            }

            if (GuiButton((Rectangle){ (float)(screenWidth / 2 - 75), (float)(screenHeight / 2 + 70), 150, 50 }, "Quit"))
            {
                quit = true;
            }
        }
        else if (currentState == APP_STATE_MAIN)
        {
            // Schermata principale

            // Barra laterale sinistra
            DrawRectangle(0, 0, 400, screenHeight, GRAY);

            // Logo nella barra laterale
            DrawCircle(200, 100, 50, BLACK);
            DrawText("Manage System", 100, 150, 20, BLACK);

            // Logo all'interno del cerchio
            DrawRectangle(150, 50, 100, 100, LIGHTGRAY); // Blocco di note
            DrawRectangleLines(150, 50, 100, 100, PURPLE); // Contorno del blocco di note
            for (int i = 0; i < 7; i++) {
                DrawLine(170, 70 + i * 10, 230, 70 + i * 10, PURPLE);
            }
            DrawLine(180, 90, 220, 110, BLACK); // Asta matita
            DrawLine(180, 90, 180, 110, BLACK); // Bordo sinistro
            DrawLine(220, 90, 220, 110, BLACK); // Bordo destro

            // Pulsanti nella barra laterale
            if (GuiButton((Rectangle){ 50, 200, 300, 50 }, "Courses"))
            {
                printf("Courses button pressed!\n");
            }

            if (GuiButton((Rectangle){ 50, 260, 300, 50 }, "Classes"))
            {
                printf("Classes button pressed!\n");
            }

            if (GuiButton((Rectangle){ 50, 320, 300, 50 }, "Students"))
            {
                printf("Students button pressed!\n");
            }

            if (GuiButton((Rectangle){ 50, 650, 300, 50 }, "Quit"))
            {
                quit = true;
            }

            // Area principale destra
            DrawRectangle(400, 0, 400, screenHeight, LIGHTGRAY);

            // Tabella dei corsi
            DrawRectangle(450, 50, 300, 30, GREEN);
            DrawText("Courses", 470, 55, 20, WHITE);

            // Righe della tabella
            for (int i = 0; i < 4; i++)
            {
                DrawRectangle(450, 90 + i * 60, 300, 50, DARKGRAY);
                DrawText("Course Name", 470, 100 + i * 60, 20, WHITE);
                DrawText("ID", 650, 100 + i * 60, 20, WHITE);

                // Icone di modifica e eliminazione
                DrawText("✎", 700, 100 + i * 60, 20, WHITE);
                DrawText("🗑️", 750, 100 + i * 60, 20, WHITE);
            }

            // Pulsante "+"
            DrawCircle(screenWidth - 50, screenHeight - 50, 30, BLUE);
            DrawText("+", screenWidth - 45, screenHeight - 50, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}