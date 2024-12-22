#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>

extern GLuint floorTextureID;

void drawFloorWithGrid(float length, float width, float tileSize);

void drawCustomWall(float startX, float startZ, float endX, float endZ, float thickness, float height);

void drawCustomWallWithStartHeight(float startX, float startZ, float endX, float endZ, float thickness, float startHeight, float height);

void drawCustomFloor(float startX, float startZ, float endX, float endZ, float startHeight, float endHeight);

void drawCustomTriangleFloor(float x1, float z1, float x2, float z2, float x3, float z3, float startHeight, float endHeight);

void drawTexturedFloor(float startX, float startZ, float endX, float endZ, float height);

void drawCustomCeiling(float startX, float startZ, float endX, float endZ, float height, float thickness);

void drawCustomTriangleWallWithStartHeight(float startX, float startZ, float endX, float endZ, float thickness, float startHeight, float height);

void drawCustomWindowA(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawCustomWindowB(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawCustomWindowB(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawCustomWindowC(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawGlassSlidingDoor(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawMainDoorFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawOuterWindowFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawOuterDoorFrame(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawDoorTypeA(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawDoorTypeB(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawDoorTypeC(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawSlidingDoor(float startX, float startZ, float endX, float endZ, float startY, float endY, float thickness);

void drawQuadRoofSegment(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float roofThickness, float colorRed, float colorGreen, float colorBlue);

#endif