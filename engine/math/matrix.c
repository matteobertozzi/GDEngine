#include "matrix.h"
#include "maths.h"

void gdMatrixCopy (GDMatrix *dst, const GDMatrix *src) {
    dst->m11 = src->m11;
    dst->m12 = src->m12;
    dst->m13 = src->m13;
    dst->m14 = src->m14;

    dst->m21 = src->m21;
    dst->m22 = src->m22;
    dst->m23 = src->m23;
    dst->m24 = src->m24;

    dst->m31 = src->m31;
    dst->m32 = src->m32;
    dst->m33 = src->m33;
    dst->m34 = src->m34;

    dst->m41 = src->m41;
    dst->m42 = src->m42;
    dst->m43 = src->m43;
    dst->m44 = src->m44;
}

void gdMatrixInitIdentity (GDMatrix *matrix) {
    matrix->m11 = 1.0f;
    matrix->m12 = 0.0f;
    matrix->m13 = 0.0f;
    matrix->m14 = 0.0f;

    matrix->m21 = 0.0f;
    matrix->m22 = 1.0f;
    matrix->m23 = 0.0f;
    matrix->m24 = 0.0f;

    matrix->m31 = 0.0f;
    matrix->m32 = 0.0f;
    matrix->m33 = 1.0f;
    matrix->m34 = 0.0f;

    matrix->m41 = 0.0f;
    matrix->m42 = 0.0f;
    matrix->m43 = 0.0f;
    matrix->m44 = 1.0f;
}

/**
 * Initialize Matrix with rotations of randians on X Axis.
 */
void gdMatrixInitRotationX (GDMatrix *matrix, GDFloat radians) {
    GDFloat fcos = gdMathCos(-radians);
    GDFloat fsin = gdMathSin(-radians);

    matrix->m11 = 1.0f;
    matrix->m12 = 0.0f;
    matrix->m13 = 0.0f;
    matrix->m14 = 0.0f;

    matrix->m21 = 0.0f;
    matrix->m22 = fcos;
    matrix->m23 = fsin;
    matrix->m24 = 0.0f;

    matrix->m31 = 0.0f;
    matrix->m32 = -fsin;
    matrix->m33 = fcos;
    matrix->m34 = 0.0f;

    matrix->m41 = 0.0f;
    matrix->m42 = 0.0f;
    matrix->m43 = 0.0f;
    matrix->m44 = 1.0f;
}

/**
 * Initialize Matrix with rotations of randians on Y Axis.
 */
void gdMatrixInitRotationY (GDMatrix *matrix, GDFloat radians) {
    GDFloat fcos = gdMathCos(-radians);
    GDFloat fsin = gdMathSin(-radians);

    matrix->m11 = fcos;
    matrix->m12 = 0.0f;
    matrix->m13 = -fsin;
    matrix->m14 = 0.0f;

    matrix->m21 = 0.0f;
    matrix->m22 = 1.0f;
    matrix->m23 = 0.0f;
    matrix->m24 = 0.0f;

    matrix->m31 = fsin;
    matrix->m32 = 0.0f;
    matrix->m33 = fcos;
    matrix->m34 = 0.0f;

    matrix->m41 = 0.0f;
    matrix->m42 = 0.0f;
    matrix->m43 = 0.0f;
    matrix->m44 = 1.0f;
}

/**
 * Initialize Matrix with rotations of randians on Z Axis.
 */
void gdMatrixInitRotationZ (GDMatrix *matrix, GDFloat radians) {
    GDFloat fcos = gdMathCos(-radians);
    GDFloat fsin = gdMathSin(-radians);

    matrix->m11 = fcos;
    matrix->m12 = fsin;
    matrix->m13 = 0.0f;
    matrix->m14 = 0.0f;

    matrix->m21 = -fsin;
    matrix->m22 = fcos;
    matrix->m23 = 0.0f;
    matrix->m24 = 0.0f;

    matrix->m31 = 0.0f;
    matrix->m32 = 0.0f;
    matrix->m33 = 1.0f;
    matrix->m34 = 0.0f;

    matrix->m41 = 0.0f;
    matrix->m42 = 0.0f;
    matrix->m43 = 0.0f;
    matrix->m44 = 1.0f;
}

/**
 * Initialize Matrix with translation of x, y, z.
 */
void gdMatrixInitTranslation (GDMatrix *matrix, GDFloat x, GDFloat y, GDFloat z)
{
    matrix->m11 = 1.0f;
    matrix->m12 = 0.0f;
    matrix->m13 = 0.0f;
    matrix->m14 = x;

    matrix->m21 = 0.0f;
    matrix->m22 = 1.0f;
    matrix->m23 = 0.0f;
    matrix->m24 = y;

    matrix->m31 = 0.0f;
    matrix->m32 = 0.0f;
    matrix->m33 = 1.0f;
    matrix->m34 = z;

    matrix->m41 = 0.0f;
    matrix->m42 = 0.0f;
    matrix->m43 = 0.0f;
    matrix->m44 = 1.0f;
}

GDFloat gdMatrixTrace (const GDMatrix *matrix) {
    return(matrix->m11 + matrix->m22 + matrix->m33 + matrix->m44);
}

/**
 * Multiply Matrix m1 by Matrix m2 and store result in Matrix result.
 */
void gdMatrixMultiply (GDMatrix *result, const GDMatrix *m1, const GDMatrix *m2)
{
    GDMatrix r;

	r.m11 = m1->m11 * m2->m11 + m1->m21 * m2->m12 + m1->m31 * m2->m13 + m1->m41 * m2->m14;
	r.m21 = m1->m11 * m2->m21 + m1->m21 * m2->m22 + m1->m31 * m2->m23 + m1->m41 * m2->m24;
	r.m31 = m1->m11 * m2->m31 + m1->m21 * m2->m32 + m1->m31 * m2->m33 + m1->m41 * m2->m34;
	r.m41 = m1->m11 * m2->m41 + m1->m21 * m2->m42 + m1->m31 * m2->m43 + m1->m41 * m2->m44;

	r.m12 = m1->m12 * m2->m11 + m1->m22 * m2->m12 + m1->m32 * m2->m13 + m1->m42 * m2->m14;
	r.m22 = m1->m12 * m2->m21 + m1->m22 * m2->m22 + m1->m32 * m2->m23 + m1->m42 * m2->m24;
	r.m32 = m1->m12 * m2->m31 + m1->m22 * m2->m32 + m1->m32 * m2->m33 + m1->m42 * m2->m34;
	r.m42 = m1->m12 * m2->m41 + m1->m22 * m2->m42 + m1->m32 * m2->m43 + m1->m42 * m2->m44;

	r.m13 = m1->m13 * m2->m11 + m1->m23 * m2->m12 + m1->m33 * m2->m13 + m1->m43 * m2->m14;
	r.m23 = m1->m13 * m2->m21 + m1->m23 * m2->m22 + m1->m33 * m2->m23 + m1->m43 * m2->m24;
	r.m33 = m1->m13 * m2->m31 + m1->m23 * m2->m32 + m1->m33 * m2->m33 + m1->m43 * m2->m34;
	r.m43 = m1->m13 * m2->m41 + m1->m23 * m2->m42 + m1->m33 * m2->m43 + m1->m43 * m2->m44;

	r.m14 = m1->m14 * m2->m11 + m1->m24 * m2->m12 + m1->m34 * m2->m13 + m1->m44 * m2->m14;
	r.m24 = m1->m14 * m2->m21 + m1->m24 * m2->m22 + m1->m34 * m2->m23 + m1->m44 * m2->m24;
	r.m34 = m1->m14 * m2->m31 + m1->m24 * m2->m32 + m1->m34 * m2->m33 + m1->m44 * m2->m34;
	r.m44 = m1->m14 * m2->m41 + m1->m24 * m2->m42 + m1->m34 * m2->m43 + m1->m44 * m2->m44;

    gdMatrixCopy(result, &r);
}

void gdMatrixInverse (GDMatrix *result, GDMatrix *matrix) {
	GDMatrix dm;
	double det_1;
	double pos, neg, temp;

    /* Calculate the determinant of submatrix A and determine if the
       the matrix is singular as limited by the double precision
       floating-point data representation. */
    pos = neg = 0.0;
    temp =  matrix->m11 * matrix->m22 * matrix->m33;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  matrix->m12 * matrix->m23 * matrix->m31;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  matrix->m13 * matrix->m21 * matrix->m32;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -matrix->m13 * matrix->m22 * matrix->m31;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -matrix->m12 * matrix->m21 * matrix->m33;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -matrix->m11 * matrix->m23 * matrix->m32;
    if (temp >= 0.0) pos += temp; else neg += temp;
    det_1 = pos + neg;

    /* Is the submatrix A singular? */
    if ((det_1 == 0.0) || (gdMathAbs(det_1 / (pos - neg)) < 1.0e-15))
	{
        /* Matrix M has no inverse */
        printf("Matrix has no inverse : singular matrix\n");
        return;
    }
    else
	{
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0 / det_1;
        dm.m11 =   ( matrix->m22 * matrix->m33 - matrix->m23 * matrix->m32 ) * (float)det_1;
        dm.m21 = - ( matrix->m21 * matrix->m33 - matrix->m23 * matrix->m31 ) * (float)det_1;
        dm.m31 =   ( matrix->m21 * matrix->m32 - matrix->m22 * matrix->m31 ) * (float)det_1;
        dm.m12 = - ( matrix->m12 * matrix->m33 - matrix->m13 * matrix->m32 ) * (float)det_1;
        dm.m22 =   ( matrix->m11 * matrix->m33 - matrix->m13 * matrix->m31 ) * (float)det_1;
        dm.m32 = - ( matrix->m11 * matrix->m32 - matrix->m12 * matrix->m31 ) * (float)det_1;
        dm.m13 =   ( matrix->m12 * matrix->m23 - matrix->m13 * matrix->m22 ) * (float)det_1;
        dm.m23 = - ( matrix->m11 * matrix->m23 - matrix->m13 * matrix->m21 ) * (float)det_1;
        dm.m33 =   ( matrix->m11 * matrix->m22 - matrix->m12 * matrix->m21 ) * (float)det_1;

        /* Calculate -C * inverse(A) */
        dm.m14 = - ( matrix->m14 * dm.m11 + matrix->m24 * dm.m12 + matrix->m34 * dm.m13 );
        dm.m24 = - ( matrix->m14 * dm.m21 + matrix->m24 * dm.m22 + matrix->m34 * dm.m23 );
        dm.m34 = - ( matrix->m14 * dm.m31 + matrix->m24 * dm.m32 + matrix->m34 * dm.m33 );

        /* Fill in last row */
        dm.m41 = 0.0f;
		dm.m42 = 0.0f;
		dm.m43 = 0.0f;
        dm.m44 = 1.0f;
	}

    gdMatrixCopy(result, &dm);
}

void gdMatrixTransposed (GDMatrix *result, GDMatrix *matrix) {
    GDMatrix r;

    r.m11 = matrix->m11;
    r.m12 = matrix->m21;
    r.m13 = matrix->m31;
    r.m14 = matrix->m41;

    r.m21 = matrix->m12;
    r.m22 = matrix->m22;
    r.m23 = matrix->m32;
    r.m24 = matrix->m42;

    r.m31 = matrix->m13;
    r.m32 = matrix->m23;
    r.m33 = matrix->m33;
    r.m34 = matrix->m43;

    r.m41 = matrix->m14;
    r.m42 = matrix->m24;
    r.m43 = matrix->m34;
    r.m44 = matrix->m44;

    gdMatrixCopy(result, &r);
}

void gdMatrixAdd (GDMatrix *result, const GDMatrix *m1, const GDMatrix *m2) {
    result->m11 = m1->m11 + m2->m11;
    result->m12 = m1->m12 + m2->m12;
    result->m13 = m1->m13 + m2->m13;
    result->m14 = m1->m14 + m2->m14;

    result->m21 = m1->m21 + m2->m21;
    result->m22 = m1->m22 + m2->m22;
    result->m23 = m1->m23 + m2->m23;
    result->m24 = m1->m24 + m2->m24;

    result->m31 = m1->m31 + m2->m31;
    result->m32 = m1->m32 + m2->m32;
    result->m33 = m1->m33 + m2->m33;
    result->m34 = m1->m34 + m2->m34;

    result->m41 = m1->m41 + m2->m41;
    result->m42 = m1->m42 + m2->m42;
    result->m43 = m1->m43 + m2->m43;
    result->m44 = m1->m44 + m2->m44;
}

void gdMatrixSubtract (GDMatrix *result, const GDMatrix *m1, const GDMatrix *m2)
{
    result->m11 = m1->m11 - m2->m11;
    result->m12 = m1->m12 - m2->m12;
    result->m13 = m1->m13 - m2->m13;
    result->m14 = m1->m14 - m2->m14;

    result->m21 = m1->m21 - m2->m21;
    result->m22 = m1->m22 - m2->m22;
    result->m23 = m1->m23 - m2->m23;
    result->m24 = m1->m24 - m2->m24;

    result->m31 = m1->m31 - m2->m31;
    result->m32 = m1->m32 - m2->m32;
    result->m33 = m1->m33 - m2->m33;
    result->m34 = m1->m34 - m2->m34;

    result->m41 = m1->m41 - m2->m41;
    result->m42 = m1->m42 - m2->m42;
    result->m43 = m1->m43 - m2->m43;
    result->m44 = m1->m44 - m2->m44;
}

/**
 * Rotate Matrix by radians on X Axis.
 */
void gdMatrixRotateX (GDMatrix *matrix, GDFloat radians) {
    GDMatrix m;
    gdMatrixInitRotationX(&m, radians);
    gdMatrixMultiply(matrix, &m, matrix);
}

/**
 * Rotate Matrix by radians on Y Axis.
 */
void gdMatrixRotateY (GDMatrix *matrix, GDFloat radians) {
    GDMatrix m;
    gdMatrixInitRotationY(&m, radians);
    gdMatrixMultiply(matrix, &m, matrix);
}

/**
 * Rotate Matrix by radians on Z Axis.
 */
void gdMatrixRotateZ (GDMatrix *matrix, GDFloat radians) {
    GDMatrix m;
    gdMatrixInitRotationZ(&m, radians);
    gdMatrixMultiply(matrix, &m, matrix);
}

/**
 * Translate Matrix by x, y, z.
 */
void gdMatrixTranslate (GDMatrix *matrix, GDFloat x, GDFloat y, GDFloat z) {
    GDMatrix m;
    gdMatrixInitTranslation(&m, x, y, z);
    gdMatrixMultiply(matrix, &m, matrix);
}

void gdMatrixVector3dMultiply (GDVector3d *result, 
                               const GDVector3d *vector,
                               const GDMatrix *matrix)
{
    GDVector3d r;
	
	r.x = matrix->m11 * vector->x + matrix->m12 * vector->y + matrix->m13 * vector->z + matrix->m14;
	r.y = matrix->m21 * vector->x + matrix->m22 * vector->y + matrix->m23 * vector->z + matrix->m24;
	r.z = matrix->m31 * vector->x + matrix->m32 * vector->y + matrix->m33 * vector->z + matrix->m34;

    gdVector3dCopy(result, &r);
}

void gdQuaternionInitFromMatrix (GDQuaternion *quaternion,
                                 const GDMatrix *matrix)
{
    GDFloat trace = gdMatrixTrace(matrix);
    GDFloat s;

    if (trace > GD_MATH_EPSILON) {
        s = gdMathSqrt(1.0f + trace);
        quaternion->w = s * 0.5f;

        s = 0.5f / s;
        quaternion->x = (matrix->m23 - matrix->m32) * s;
        quaternion->y = (matrix->m31 - matrix->m13) * s;
        quaternion->z = (matrix->m12 - matrix->m21) * s;
    } else {
        if (matrix->m11 > matrix->m22 && matrix->m11 > matrix->m33) {
            s = gdMathSqrt(1.0f + matrix->m11 - matrix->m22 - matrix->m33);
            quaternion->x = s * 0.5f;

            s = 0.5f / s;
            quaternion->y = (matrix->m12 + matrix->m21) * s;
            quaternion->z = (matrix->m13 + matrix->m31) * s;
            quaternion->w = (matrix->m23 + matrix->m32) * s;
        } else if (matrix->m22 > matrix->m33) {
            s = gdMathSqrt(1.0f + matrix->m22 - matrix->m11 - matrix->m33);
            quaternion->y = s * 0.5f;

            s = 0.5f / s;
            quaternion->x = (matrix->m21 + matrix->m12) * s;
            quaternion->z = (matrix->m32 + matrix->m23) * s;
            quaternion->w = (matrix->m31 + matrix->m13) * s;
        } else {
            s = gdMathSqrt(1.0f + matrix->m33 - matrix->m11 - matrix->m22);
            quaternion->z = s * 0.5f;

            s = 0.5f / s;
            quaternion->x = (matrix->m31 + matrix->m13) * s;
            quaternion->y = (matrix->m32 + matrix->m23) * s;
            quaternion->w = (matrix->m12 + matrix->m21) * s;
        }
    }
}

void gdMatrixPrint (GDMatrix *m) {
    printf("%.3f %.3f %.3f %.3f\n", m->m11, m->m12, m->m13, m->m14);
    printf("%.3f %.3f %.3f %.3f\n", m->m21, m->m22, m->m23, m->m24);
    printf("%.3f %.3f %.3f %.3f\n", m->m31, m->m32, m->m33, m->m34);
    printf("%.3f %.3f %.3f %.3f\n", m->m41, m->m42, m->m43, m->m44);
    printf("\n");
}

