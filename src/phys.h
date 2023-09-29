#include "../lib/raylib.h"
#include "../lib/rcamera.h"
#include "../lib/raymath.h"
#include "../lib/rlgl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    Vector3 position;
    Vector3 netForce;
    Vector3 velocity;
    double mass;
} Body;

Body *createBody()
{
    Body *body = malloc(sizeof(Body));
    body->position = (Vector3){0.0f, 1.0f, 0.0f};
    body->netForce = (Vector3){0.0f, 0.0f, 0.0f};
    body->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    body->mass = 1.0f;
    return body;
}

void applyForce(Body *body, Vector3 force)
{
    body->netForce.x += force.x;
    body->netForce.y += force.y;
    body->netForce.z += force.z;
}

void updateBody(Body *body)
{
    // F = ma
    // a = F/m
    // v = at
    // This is ran every frame, so we can assume t is incrementing linearly by 1 each frame.

    body->velocity.x += body->netForce.x / body->mass;
    body->velocity.y += body->netForce.y / body->mass;
    body->velocity.z += body->netForce.z / body->mass;
    body->position.x += body->velocity.x;
    body->position.y += body->velocity.y;
    body->position.z += body->velocity.z;

    // remove forces every frame
    body->netForce = (Vector3){0.0f, 0.0f, 0.0f};
}