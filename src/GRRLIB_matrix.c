/*------------------------------------------------------------------------------
Copyright (c) 2009-2022 The GRRLIB Team and HTV04

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
------------------------------------------------------------------------------*/

#include <grrlib-mod.h>

/**
 * Get the current matrix as a new matrix object.
 * @return A handle to the matrix object.
 * @see GRRLIB_matrix
 */
GRRLIB_matrix GRRLIB_GetMatrix (void) {
    GRRLIB_matrix matrixObject;

    guMtxCopy(GRRLIB_View2D, matrixObject.matrix);

    return matrixObject;
}

/**
 * Set the current matrix using a matrix object.
 * @param matrixObject The matrix object to set the matrix with.
 */
void GRRLIB_SetMatrix (GRRLIB_matrix *matrixObject) {
    guMtxCopy(matrixObject->matrix, GRRLIB_View2D);
    GX_LoadPosMtxImm(matrixObject->matrix, GX_PNMTX0);
}

/**
 * Scale the current matrix.
 * @param scaleX The scaling in the direction of the x-axis.
 * @param scaleY The scaling in the direction of the y-axis.
 */
void GRRLIB_Scale (f32 scaleX, f32 scaleY) {
    Mtx m;

    guMtxIdentity(m);
    guMtxScaleApply(m, m, scaleX, scaleY, 1.0);

    guMtxConcat(GRRLIB_View2D, m, GRRLIB_View2D);
    GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);
}

/**
 * Rotate the current matrix.
 * @param degrees The amount to rotate the current matrix in degrees.
 */
void GRRLIB_Rotate (f32 degrees) {
    Mtx m;

    guMtxRotAxisDeg(m, &GRRLIB_Axis2D, degrees);

    guMtxConcat(GRRLIB_View2D, m, GRRLIB_View2D);
    GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);
}

/**
 * Translate the current matrix.
 * @param posX The translation relative to the x-axis.
 * @param posY The translation relative to the y-axis.
 */
void GRRLIB_Translate (f32 posX, f32 posY) {
    Mtx m;

    guMtxIdentity(m);
    guMtxTransApply(m, m, posX, posY, 0.0);

    guMtxConcat(GRRLIB_View2D, m, GRRLIB_View2D);
    GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);
}

/**
 * Transform the current matrix (scale, rotate, then translate).
 * @param scaleX The scaling in the direction of the x-axis.
 * @param scaleY The scaling in the direction of the y-axis.
 * @param degrees The amount to rotate the current matrix in degrees.
 * @param posX The translation relative to the x-axis.
 * @param posY The translation relative to the y-axis.
 */
void GRRLIB_Transform (f32 scaleX, f32 scaleY, f32 degrees, f32 posX, f32 posY) {
    Mtx m1, m2, m;

    guMtxIdentity(m1);
    guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
    guMtxRotAxisDeg(m2, &GRRLIB_Axis2D, degrees);
    guMtxConcat(m1, m2, m);
    guMtxTransApply(m, m, posX, posY, 0.0);

    guMtxConcat(GRRLIB_View2D, m, GRRLIB_View2D);
    GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);
}

/**
 * Transform the current matrix (scale, translate, then rotate).
 * @param scaleX The scaling in the direction of the x-axis.
 * @param scaleY The scaling in the direction of the y-axis.
 * @param posX The translation relative to the x-axis.
 * @param posY The translation relative to the y-axis.
 * @param degrees The amount to rotate the current matrix in degrees.
 */
void GRRLIB_TransformInv (f32 scaleX, f32 scaleY, f32 posX, f32 posY, f32 degrees) {
    Mtx m1, m2, m;

    guMtxIdentity(m1);
    guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
    guMtxTransApply(m2, m2, posX, posY, 0.0);
    guMtxConcat(m1, m2, m);
    guMtxRotAxisDeg(m, &GRRLIB_Axis2D, degrees);

    guMtxConcat(GRRLIB_View2D, m, GRRLIB_View2D);
    GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);
}

/**
 * Reset the current matrix.
 */
void GRRLIB_Origin (void) {
    guMtxIdentity(GRRLIB_View2D);
    guMtxTransApply(GRRLIB_View2D, GRRLIB_View2D, 0.0, 0.0, -100.0);
    GX_LoadPosMtxImm(GRRLIB_View2D, GX_PNMTX0);
}
