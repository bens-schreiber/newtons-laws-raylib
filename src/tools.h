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
    DrawCube(body->position, BODY_HEIGHT, BODY_HEIGHT, BODY_HEIGHT, RED);
    DrawCubeWires(body->position, 1.0f, 1.0f, 1.0f, BLACK);
}

void drawScene(void)
{
    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);
}

void checkKeyPress(Body *body)
{
    if (IsKeyDown(KEY_F))
    {
        applyForce(body, (Vector3){0.0f, 0.0f, 0.01f});
    }
}

#define COLLISION_HEIGHT 0.5f * BODY_HEIGHT

void handleGroundCollision(Body *body)
{
    if (body->position.y <= COLLISION_HEIGHT || body->position.y - body->velocity.y <= COLLISION_HEIGHT)
    {
        // We need to apply a force of equal magnitude to the bodies velocity, in the direction normal to the ground plane.
        // This will stop the body from falling through the ground.
        // We know the normal of the ground plane is (0, 1, 0), so we can just apply a force of (0, -velocity.y, 0)
        Vector3 normalForce = (Vector3){0, GRAVITY - body->velocity.y, 0};
        applyForce(body, normalForce);
    }
}