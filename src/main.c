#include "phys.h"
#include "tools.h"
#include "consts.h"

/* 


1) An object at rest remains at rest, and an object in motion remains in motion at constant speed 
and in a straight line unless acted on by an unbalanced force.

2) The acceleration of an object depends on the mass of the object and the amount of force applied.

3) Whenever one object exerts a force on another object, the second object exerts an equal and opposite on the first.

*/



int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Camera3D camera = createCamera();
    Body *body1 = createBody((Vector3){0.0f, 10.0f, 0.0f}, RED, 1.0f);
    Body *body2 = createBody((Vector3){2.0f, 10.0f, 0.0f}, BLUE, 1.0f);


    InitWindow(screenWidth, screenHeight, "Newton Laws - Ben Schreiber");

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Instantly apply force to body if key is pressed
        checkKeyPress(body1, body2);

        // gravity is a constant force, so we can just apply it every frame
        applyForce(body1, GRAVITY_FORCE);
        applyForce(body2, GRAVITY_FORCE);

        handleBodyCollision(body1, body2);

        // apply nomral force if body is on the ground
        handleGroundCollision(body1);
        handleGroundCollision(body2);

        updateBody(body1);
        updateBody(body2);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        drawScene();
        drawBody(body1);
        drawBody(body2);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}