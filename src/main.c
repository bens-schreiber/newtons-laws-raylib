#include "phys.h"
#include "tools.h"
#include "consts.h"



int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Camera3D camera = createCamera();
    Body *body = createBody();

    InitWindow(screenWidth, screenHeight, "Newton Laws - Ben Schreiber");

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        updateBody(body);

        // WASD instantenous forces
        checkKeyPress(body);

        // gravity is a constant force, so we can just apply it every frame
        applyForce(body, GRAVITY_FORCE);

        // apply nomral force if body is on the ground
        handleGroundCollision(body);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        drawScene();
        drawBody(body);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}