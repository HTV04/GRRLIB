/*===========================================
    NoNameNo CubedTileDemo
    A sample code to show how to use Dynamic Texturing
    Have a look a TileDemo sources for diff ;)
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <math.h>
#include <wiiuse/wpad.h>

#include "gfx/tile1.h"
#include "gfx/perso.h"
#include "gfx/bg.h"
#include "gfx/nonameno.h"

#define TileMap1Width (32)
#define TileMap1Height (32)
#define Map1Width (87)
#define Map1Height (51)

signed short Map1Data[53][87] =
{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 6, 7, 3, 8, 9, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 1,10, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,11,12, 3,11,12, 3, 4,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 1,15, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {16,16,17,16,17,16,17,16,17,16, 0, 0, 0, 0, 0, 0, 1, 1,17,16, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,18,19, 3,18,19, 3, 4,20,21, 0,22, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0, 1, 1, 1, 0,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17},
  {23,23,24,23,24,23,24,23,24,23,22,22, 0, 1, 1, 1, 1, 0,24,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,25,26, 0,27,28,28,28,28,28,28,28,28,28,29,30,31,22, 0, 0, 0, 2, 3,32,33, 3,34,35, 3,36,37, 3, 4, 0, 1, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,22,22, 0, 1, 1, 1, 1, 0,24,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,38,39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0,22,13,14, 0, 2, 3,11,12, 3,11,12, 3,11,12, 3, 4, 1, 1, 0, 0,24,23,40,41,40,41,40,41,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,27,28,28,31, 1, 1, 1, 0,24,23,13,14, 0, 0, 0, 0, 0, 0, 0, 0,42,43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0,22,20,21, 0, 2, 3,18,19, 3,18,19, 3,18,19, 3, 4, 1, 0, 0, 0,24,23,44,45,46,44, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,27,28,28,31, 1, 0, 0, 0,24,23,20,21, 0, 0, 0, 0, 0, 0, 0,22,47,48,22, 0, 0, 0, 0, 0, 0, 0, 0, 0,27,28,28,28,28,29,30,28,28,28,28,28,28,28,28,28,28,28,28,28,28,31, 0, 0,24,23,44,11,12,44,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0,27,28,28,31, 0, 0, 0,24,23,13,14, 0, 0, 0,13,14, 0,42,43,42,43,42,43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14,17,16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,23,44,18,19,44,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,27,28,28,31, 0, 0, 0, 0,24,23,20,21, 0, 0, 0,20,21,22,47,48,47,48,47,48,22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20,21,24,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,23,27,28,28,31,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0,27,28,28,31, 0, 0,27,28,28,29,30,28,28,28,29,30,28,28,28,28,28,28,28,31, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 4, 0,13,14,24,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,23,40,41,40,41,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,27,28,28,31, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,49,50, 3, 4,13,14,24,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,23,24,23,24,23,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0,27,28,28,31, 0, 0, 0, 0, 0,13,14, 0, 0, 0,20,21, 0, 0, 0, 0,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,11,12, 3, 4,20,21,24,23, 0, 0, 0, 0,27,28,28,31, 0, 0, 2, 3, 3, 4, 0,40,41,40,41,40,41,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0,27,28,28,31, 0, 0, 0,20,21, 0, 0, 0,13,14, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,18,19, 3, 4,13,14,24,23, 0, 0,17,16, 0,27,28,31, 0, 2, 3,51,52, 3, 4, 0, 0, 0, 0, 0, 0,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 2, 3, 3, 4, 0, 0, 0,13,14, 0, 0, 0,20,21, 0, 0, 0,27,29,30,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,31, 2,53,54, 4, 0,22, 0, 0, 2, 3,11,12, 3, 4, 0, 0, 0, 0, 0, 0,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 2, 3,55,56, 3, 4, 0, 0,20,21, 0, 0, 0,13,14, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,11,12, 3, 4,22, 0, 0, 2, 3,18,19, 3, 4, 0, 0, 0, 0, 0, 0,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 2, 3,11,12, 3, 4, 0, 0,13,14, 0, 0, 0,20,21, 0, 0, 0, 0,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,18,19, 3, 4,22, 0, 0,27,28,28,28,28,28,28,28,28,28,28,31,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 2, 3,18,19, 3, 4, 0, 0,20,21, 0, 0, 0,13,14, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,27,28,28,31, 0,22, 0, 0, 0, 0, 0, 0, 0, 0,17,16,17,16,17,16,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0,27,28,28,28,28,28,28,28,28,28,28,31, 0, 0,20,21, 0, 0, 0,27,29,30,28,28,28,28,28,28,28,28,28,31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22, 0, 0, 0, 0, 0, 0, 0, 0,24,23,24,23,24,23,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,42,43, 0,42,43, 0, 0, 0, 2, 3, 3, 4, 0, 0, 0,24,23,24,23,24,23,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 2, 3, 3, 4, 0, 0, 0, 0, 0, 0,27,28,28,28,28,28,28,28,29,30,31, 0, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,47,48, 0,47,48, 0, 0, 2, 3,58,59, 3, 4, 0, 0,24,23,24,23,24,23,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 2, 3,60,61, 3, 4,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3,11,12, 3, 4, 0, 0,24,23,24,23,24,23,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 2, 3,11,12, 3, 4,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0, 0, 2, 3,18,19, 3, 4, 0, 0,24,23,24,23,24,23,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 2, 3,18,19, 3, 4,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0, 0,27,28,28,28,28,31, 0, 0,24,23,24,23,24,23,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0,27,28,28,28,28,28,29,30,28,28,31, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,23,24,23,24,23,13,14,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 2, 3, 3, 4, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0, 0,42,43, 0, 0, 0, 0, 0, 0,24,23,24,23,24,23,20,21,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 0, 0, 3,62,63, 3, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0, 0,47,48, 0, 0, 0, 0, 0, 0,24,23,40,41,40,41,13,14,40,41,40,41,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 0, 2, 3,11,12, 3, 4, 0,57,57,57,57,57,57, 0, 0,57,57, 0,57,57, 0, 0,25,26, 0, 0,20,21, 0, 0,24,23, 2, 3, 3, 4,20,21, 0, 0, 0, 0,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 0, 2, 3, 3, 4, 0, 0, 0, 0,20,21, 0, 0, 0, 2, 3,18,19, 3, 4, 0, 0,57, 0, 0,57, 0, 0, 0,57,57, 0,57,57, 0, 0,38,39, 0, 0,13,14, 0, 0,24,23, 3,64,65, 3,13,14, 0, 0, 0, 5,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0, 2, 3,66,67, 3, 4, 0, 0, 0,13,14, 0, 0,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,29,30,31, 0,24,23, 3,11,12, 3,20,21, 0,42,43,10,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0, 0, 0, 0, 0, 0,20,21, 0, 0, 2, 3,11,12, 3, 4, 0, 0, 0,20,21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,14, 0, 0,24,23, 3,18,19, 3,13,14, 0,47,48,15,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0,68, 0, 0, 0, 0,13,14, 0, 0, 2, 3,18,19, 3, 4, 0,68, 0,13,14, 0, 0,57,57,57,57, 0, 0, 0,57,57,57, 0, 0, 0, 0,57, 0, 0,57, 0, 0, 0,57,57,57,57, 0, 0,20,21, 0, 0,24,23,27,28,28,28,28,28,28,28,28,31,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0,27,28,28,28,28,28,28,29,30,28,28,28,28,28,28,28,28,28,28,28,28,28,28,31,57,57,57,57,57, 0,57,57,57,57,57, 0, 0,57,57,57,57,57,57, 0, 0,57,57,57,57,57, 0,13,14, 0, 0,24,23,17,16,17,16,17,16,17,16,17,16,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0,17,16,17,16, 0,13,14, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,20,21, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0,24,23,24,23, 0,20,21, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,13,14, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23, 0, 0, 0,24,23,24,23, 0,13,14, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0, 0,57,57,57,57, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57,57,57, 0, 0,20,21, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,22, 0, 0,24,23,24,23, 0,20,21, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,13,14, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,22, 0, 0,24,23,24,23, 0,13,14, 0, 0, 2, 3, 3, 4, 0,44, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,13,14, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,22, 0, 0,17,69,70,16, 0,20,21, 0, 2, 3,71,72, 3, 4,44, 0, 0, 0, 0, 0, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57, 0,13,14, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {23,23,24,23,24,23,24,23,24,23,42,43, 0,44,11,12,44, 0,13,14, 0, 2, 3,11,12, 3, 4,44, 0, 0, 0, 0, 0, 0, 0,57,57,57,57,57, 0,57,57,57,57,57, 0,57,57, 0,57,57, 0,57,57, 0,57,57,57,57,57, 0,20,21, 0, 0,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,24},
  {41,41,40,41,40,41,40,41,40,41,47,48,22,44,18,19,44, 0,13,14, 0, 2, 3,18,19, 3, 4,44, 0, 0,68,68, 0, 0, 0,57,57,57,57, 0, 0, 0,57,57,57, 0, 0,57,57, 0,57,57, 0,57,57, 0,57,57,57,57, 0, 0,13,14, 0, 0,40,41,40,41,40,41,40,41,40,41,40,41,40,41,40,41,40,41,40,41,40},
  {73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73,73},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74},
  {74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}};

signed int Map1Info[53][87] =
{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,63232,63232, 0,63488,63488, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 9, 9, 3, 9, 3, 9, 3, 9, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,43521,43521, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 1, 1, 1, 1, 0, 0, 0, 0, 2, 8,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0,43521,43521, 0, 0, 0,63744,63744, 0,64000,64000, 0,64256,64256, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 1, 1, 1, 1, 0, 0, 0, 0, 2, 8,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,43521,43521, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 8, 0, 0, 0, 0,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 1, 1, 1, 1, 0, 0, 0, 2, 8,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0,64512,64512, 0,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 1, 1, 1, 1, 0, 0, 0, 0, 2, 8,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 1, 1, 1, 1,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1,43521,43521, 1, 1, 1,43521,43521, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,62976,62976, 0, 0,43521,43521, 2, 8, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 1,43521,43521, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65024,65024, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,64768,64768, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0,61440,61440, 0, 0, 0, 0,43521,43521, 0, 0, 0,43521,43521, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,43521,43521, 0, 0, 0, 1,43521,43521, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,43521,43521, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,65280,65280, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0,61696,61696, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 1, 1, 1, 1, 1, 1,43521,43521, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8,43521,43521, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 8,43521,43521, 2, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0,62720,62720, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,43521,43521, 1, 0, 2, 8, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 0,61184,61184, 0,43521,43521, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0,61952,61952, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 1, 1, 1, 1, 1, 1, 1,43521,43521, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 2, 0, 0, 8, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 3, 9, 3, 9, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 2, 8, 2, 8, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 2, 8, 2, 8, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 6,12, 6,12, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 8, 8, 2, 8, 2, 8, 2, 8, 2, 8, 0, 0, 0, 2, 0, 0, 8, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  {12,12, 6,12, 6,12, 6,12, 6,12, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 6,12, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0,62208,62208, 0, 0,43521,43521, 0, 0, 0,62464,62464, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43521,43521, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int main() {
    int startx=0, starty=0;
    int x=0, y=0;
    int dirx=0, diry=0;
    int cptx=0, cpty=0;
    int bgx=-32, bgy=-32;
    float idperso=0;
    int i=0;
    float sinnonameno=0, oldsinnonameno=0;
    float camZ=1400.0f;
    float a=0;

    GRRLIB_Init();
    GRRLIB_Settings.antialias = false;
    WPAD_Init();
    GRRLIB_ClipDrawing(0,0,rmode->fbWidth,rmode->efbHeight);
    GRRLIB_texImg *tex_tile1 = GRRLIB_LoadTexture(tile1);
    GRRLIB_InitTileSet(tex_tile1, TileMap1Width, TileMap1Height, 0);
    GRRLIB_texImg *tex_perso = GRRLIB_LoadTexture(perso);
    GRRLIB_InitTileSet(tex_perso, 64, 64, 0);
    GRRLIB_texImg *tex_bg = GRRLIB_LoadTexture(bg);
    GRRLIB_texImg *tex_nonameno = GRRLIB_LoadTexture(nonameno);
    GRRLIB_InitTileSet(tex_nonameno, 32, 32, 0);

    GRRLIB_texImg *tex_screen = GRRLIB_CreateEmptyTexture(rmode->fbWidth, rmode->efbHeight);

    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    while(1) {
        GRRLIB_2dMode();
        WPAD_ScanPads();
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_PLUS)  camZ+=20.0f;
        if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_MINUS)  camZ-=20.0f;

        if((dirx==0) && (diry==0)) {
            if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_LEFT) { diry=-4; idperso=15;}
            else if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_RIGHT) { diry=4; idperso=15;}
            else if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN) { dirx=-4 ; idperso=1;}
            else if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP) { dirx=4 ; idperso=8;}
        }

        if((dirx==0) && (diry==0)) {
            idperso=0;
        }

        if(((Map1Info[9+starty][10+startx]==1) || (Map1Info[9+starty][11+startx]==1)) || ((Map1Info[9+starty][10+startx]==43521) || (Map1Info[9+starty][11+startx]==43521))) {
        }
        else{
            dirx=0;
            diry=-4;
        }

        if(dirx<0) {
            if((Map1Info[7+starty][12+startx]==8) || (Map1Info[7+starty][12+startx]==2) || (Map1Info[8+starty][12+startx]==8) || (Map1Info[8+starty][12+startx]==2)) {
                dirx=0;
            }
            else {
                idperso++;
                if(idperso>7)
                    idperso=1;
            }
        }

        if(dirx>0) {
            if((Map1Info[7+starty][9+startx]==8) || (Map1Info[7+starty][9+startx]==2) || (Map1Info[8+starty][9+startx]==8) || (Map1Info[8+starty][9+startx]==2)) {
                dirx=0;
            }
            else {
                idperso++;
                if(idperso>14)
                    idperso=8;
           }
        }

        if(diry<0) {
            if((Map1Info[9+starty][10+startx]==1) || (Map1Info[9+starty][11+startx]==1)) {
                diry=0;
            }
        }

        if(diry!=0) {
            idperso++;
            if(idperso>22)
                idperso=16;
        }

        cptx+=dirx;
        if(dirx>0)
            bgx++;
        else if(dirx<0)
            bgx--;
        if((bgx>-1) || (bgx<-63))
            bgx=-32;

        if(cptx==32) {
            cptx=0;
            dirx=0;
            startx--;
        }
        else if(cptx==-32) {
            cptx=0;
            dirx=0;
            startx++;
        }

        cpty+=diry;
        if(diry>0)
            bgy++;
        else if(diry<0)
            bgy--;
        if((bgy>-1) ||(bgy<-63))
            bgy=-32;

        if(cpty==32) {
            cpty=0;
            diry=0;
            starty--;
        }
        else if(cpty==-32) {
            cpty=0;
            if(((Map1Info[9+starty][10+startx]==1) || (Map1Info[9+starty][11+startx]==1)) || ((Map1Info[9+starty][10+startx]==43521) || (Map1Info[9+starty][11+startx]==43521))) {
                diry=0;
            }
            starty++;
        }
        GRRLIB_DrawImg(bgx, bgy, tex_bg, 0, 1, 1, 0xFFFFFFFF);

        for(y=0;y<=(17);y++) {
            for(x=0;x<=(21);x++) {
            if(Map1Data[y+starty][x+startx] != 0) {
                GRRLIB_DrawTile(x*TileMap1Width+cptx-TileMap1Width,y*TileMap1Height+cpty-TileMap1Height,tex_tile1,0,1,1,0xFFFFFFFF,Map1Data[y+starty][x+startx]-1);
            }
            }
        }
        GRRLIB_DrawTile(TileMap1Width*9,TileMap1Height*6,tex_perso,0,1,1,0xFFFFFFFF,(int)idperso);

        oldsinnonameno=sinnonameno;
        for(i=0; i<8; i++) {
            GRRLIB_DrawTile(TileMap1Width*(6+i),(TileMap1Height*10)+sin(sinnonameno)*64,tex_nonameno,0,1,1,0xFFFFFFFF,i);
            sinnonameno+=0.4F;
        }
        sinnonameno=oldsinnonameno+0.08F;

        GRRLIB_Screen2Texture(0, 0, tex_screen, GX_TRUE);


        GRRLIB_Camera3dSettings(0.0f,0.0f,camZ, 0,1,0, 0,0,0);
        GRRLIB_3dMode(0.1,3000,45,1,0);
        GRRLIB_SetTexture(tex_screen,0);
        GRRLIB_ObjectView(0,0,0, a,a*2,a*3,1,1,1);
        GX_Begin(GX_QUADS, GX_VTXFMT0, 16);
            GX_Position3f32(-rmode->fbWidth/2,rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(rmode->fbWidth/2,rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(rmode->fbWidth/2,-rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(-rmode->fbWidth/2,-rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(rmode->fbWidth/2,rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(-rmode->fbWidth/2,rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(-rmode->fbWidth/2,-rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(rmode->fbWidth/2,-rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(rmode->fbWidth/2,rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(rmode->fbWidth/2,rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(rmode->fbWidth/2,-rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(rmode->fbWidth/2,-rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(-rmode->fbWidth/2,rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(-rmode->fbWidth/2,rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(-rmode->fbWidth/2,-rmode->efbHeight/2,rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(-rmode->fbWidth/2,-rmode->efbHeight/2,-rmode->fbWidth/2);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);
        GX_End();

        a+=0.2f;

        GRRLIB_Render();
    }

    GRRLIB_Exit();
    GRRLIB_FreeTexture(tex_tile1);
    GRRLIB_FreeTexture(tex_perso);
    GRRLIB_FreeTexture(tex_bg);
    GRRLIB_FreeTexture(tex_nonameno);
    GRRLIB_FreeTexture(tex_screen);
    exit(0);
}

