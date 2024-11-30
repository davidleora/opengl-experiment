#ifndef SCENE_H
#define SCENE_H

void drawFloorWithGrid(float length, float width, float tileSize);

void drawCustomWall(float startX, float startZ, float endX, float endZ, float thickness, float height);

void drawCustomWallWithStartHeight(float startX, float startZ, float endX, float endZ, float thickness, float startHeight, float height);

void drawCustomFloor(float startX, float startZ, float length, float width, float height);

void drawCustomCeiling(float startX, float startZ, float length, float width, float heightPosition, float thickness);

#endif