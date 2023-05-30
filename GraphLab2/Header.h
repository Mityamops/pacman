#pragma once
void Play();
void renderScene(void);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
int init(int argc, char** argv);