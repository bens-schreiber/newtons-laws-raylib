#include "../lib/raylib.h"
#include "../lib/rcamera.h"
#include "../lib/raymath.h"
#include "../lib/rlgl.h"
#include "consts.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    Vector3 position;
    Vector3 velocity;
    double mass;
    Color color;
} Body;

Body *createBody(Vector3 position, Color color, double mass)
{
    Body *body = malloc(sizeof(Body));
    body->position = position;
    body->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    body->mass = mass;
    body->color = color;
    return body;
}

void applyForce(Body *body, Vector3 force)
{
    // F = ma
    // a = F/m
    // v = at
    body->velocity.x += force.x / body->mass;
    body->velocity.y += force.y / body->mass;
    body->velocity.z += force.z / body->mass;
}

void updateBody(Body *body)
{
    // This is ran every frame, so we can assume t is incrementing linearly by 1 each frame.
    body->position.x += body->velocity.x;
    body->position.y += body->velocity.y;
    body->position.z += body->velocity.z;
}


#define COLLISION_HEIGHT 0.5f * BODY_HEIGHT

void handleGroundCollision(Body *body)
{

    // To handle ground collision, we need to accurately deduce the frame in which the body will collide with the ground.
    // We do not know the exact motion or position function of the body, but we do know the velocity.
    // Since we know the line tangent to the position at any given moment (as we know velocity and position), we can use this to estimate the position in the next frame.

    // We can use the velocities y component added to the position to get an estimate of the position in the next frame.
    double positionEstimate = body->position.y + body->velocity.y;

    if (positionEstimate <= COLLISION_HEIGHT)
    {
        // We need to apply a force of equal magnitude to the bodies velocity, in the direction normal to the ground plane.
        // This will stop the body from falling through the ground.
        // We know the normal of the ground plane is (0, 1, 0), so we can just apply a force of (0, -velocity.y, 0)
        Vector3 normalForce = (Vector3){0, -body->velocity.y, 0};
        applyForce(body, normalForce);
    }
}

void handleBodyCollision(Body *body1, Body *body2) {
    // We need to estimate the frame in which the vectors intersect.
    // Given a body we can represent the position as <v_x * t + x0, v_y * t + y0, v_z * t + z0>
    // Both bodies use the same t (the frame), so we can just solve for t.

    // Parallel vectors will never intersect, so we can just check if the vectors are parallel.
    if (Vector3Equals(Vector3Add(body1->velocity, body1->position), Vector3Add(body2->velocity, body2->position))) return;

    // Solving the system for t:
    // v1_x * t + x1 = v2_x * t + x2
    // t(v1_x - v2_x) = x2 - x1
    // t = (x2 - x1) / (v1_x - v2_x)
    const double POS_ADJUST = BODY_HEIGHT - 0.1f;
    double t = ((body2->position.x) - (body1->position.x) - POS_ADJUST) / (body1->velocity.x - body2->velocity.x);

    // Round t to the nearest integer, as we can only have collisions on integer frames.
    t = round(t);
    if (t != 0) return;

    // We need to apply a force equal magnitude to each body's forces in the direction opposite to the other body.

    Vector3 body1Force = (Vector3){body1->velocity.x, body1->velocity.y, body1->velocity.z};
    Vector3 body2Force = (Vector3){body2->velocity.x, body2->velocity.y, body2->velocity.z};

    // Body1 applies this force
    applyForce(body2, body1Force);

    // Body2 applies this force
    applyForce(body1, Vector3Scale(body1Force, -1));

    // Body2 applies this force
    applyForce(body1, body2Force);

    // Body1 applies this force
    applyForce(body2, Vector3Scale(body2Force, -1));



}