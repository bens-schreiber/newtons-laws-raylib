#include "../lib/raylib.h"
#include "../lib/rcamera.h"
#include "../lib/raymath.h"
#include "../lib/rlgl.h"
#include "consts.h"

Camera3D createCamera(void)
{
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 4.0f};
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

void drawBody(Body *body)
{
    DrawCube(body->position, BODY_HEIGHT, BODY_HEIGHT, BODY_HEIGHT, body->color);
    DrawCubeWires(body->position, 1.0f, 1.0f, 1.0f, BLACK);
}

void drawScene(void)
{
    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);
}

void checkKeyPress(Body *body1, Body *body2)
{
    if (IsKeyDown(KEY_F))
    {
        applyForce(body1, (Vector3){0.01f, 0.0f, 0.0f});
    }

    if (IsKeyDown(KEY_G))
    {
        applyForce(body2, (Vector3){-0.01f, 0.0f, 0.0f});
    }
}