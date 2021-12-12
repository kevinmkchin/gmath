/**


     ad88888ba                                            88b           d88                       88
    d8"     "8b                                           888b         d888                ,d     88
    Y8,                                                   88`8b       d8'88                88     88
    `Y8aaaaa,     ,adPPYba,  8b,     ,d8  8b       d8     88 `8b     d8' 88  ,adPPYYba,  MM88MMM  88,dPPYba,
      `"""""8b,  a8P_____88   `Y8, ,8P'   `8b     d8'     88  `8b   d8'  88  ""     `Y8    88     88P'    "8a
            `8b  8PP"""""""     )888(      `8b   d8'      88   `8b d8'   88  ,adPPPPP88    88     88       88
    Y8a     a8P  "8b,   ,aa   ,d8" "8b,     `8b,d8'       88    `888'    88  88,    ,88    88,    88       88
     "Y88888P"    `"Ybbd8"'  8P'     `Y8      Y88'        88     `8'     88  `"8bbdP"Y8    "Y888  88       88
                                              d8'
                                             d8'

    88           88  88
    88           ""  88
    88               88
    88           88  88,dPPYba,   8b,dPPYba,  ,adPPYYba,  8b,dPPYba,  8b       d8
    88           88  88P'    "8a  88P'   "Y8  ""     `Y8  88P'   "Y8  `8b     d8'
    88           88  88       d8  88          ,adPPPPP88  88           `8b   d8'
    88           88  88b,   ,a8"  88          88,    ,88  88            `8b,d8'
    88888888888  88  8Y"Ybbd8"'   88          `"8bbdP"Y8  88              Y88'
                                                                          d8'
                                                                         d8'


    A 3D math and linear algebra library written by Kevin Chin (https://kevch.in/)

    Do this:
        #define SEXY_MATH_IMPLEMENTATION
    before you include this file in *one* C or C++ file to create the implementation.
        // i.e. it should look like this:
        #include ...
        #include ...
        #define SEXY_MATH_IMPLEMENTATION
        #include "sexymathlibrary.h"

Features:
        - Vectors & vector operations
        - Matrices & matrix operations
        - Quaternions & quaternion operations
        - Methods to create transformation matrices
        - Methods to create projection matrices
        - Method to create view matrix
        - Spherical linear interpolation & vector linear interpolation

STANDARDS:
    This library imposes some standards and rules for 3D math:
        - Positive X axis is forward vector. Positive Y axis is up vector. Positive Z
          axis is right vector.
        - Therefore, Roll is rotation around X axis, Pitch is rotation around Z axis,
          and Yaw is rotation around Y axis.
        - Quaternions: Sexy Math Library uses Quaternions to represent all rotations.
          They are compact, don't suffer from gimbal lock and can easily be interpolated.

*/
#ifndef _INCLUDE_SEXY_MATH_LIBRARY_H_
#define _INCLUDE_SEXY_MATH_LIBRARY_H_

#include <cstdlib>

#define SML_FORWARD_VECTOR vec3(1.f,0.f,0.f)
#define SML_BACKWARD_VECTOR (-SML_FORWARD_VECTOR)
#define SML_UP_VECTOR vec3(0.f,1.f,0.f)
#define SML_DOWN_VECTOR (-SML_UP_VECTOR)
#define SML_RIGHT_VECTOR vec3(0.f,0.f,1.f)
#define SML_LEFT_VECTOR (-SML_RIGHT_VECTOR)
#define SML_PI 3.1415926535f
#define SML_TWOPI 6.28318530718f
#define SML_DEG2RAD 0.0174532925f  // degrees * SML_DEG2RAD = radians
#define SML_RAD2DEG 57.2958f       // radians * SML_RAD2DEG = degrees

#define SML_min(a, b) ((a) < (b) ? (a) : (b))
#define SML_max(a, b) ((a) > (b) ? (a) : (b))
#define SML_abs(a) ((a) < 0.f ? (-(a)) : (a))
#define SML_clamp(x, lower, upper) SML_max((lower), SML_min((upper), (x)))


struct vec4;
union vec3;
struct vec2;
union mat3;
union mat4;
struct quat;

union vec3
{
    struct
    {
        float x, y, z;
    };
    struct
    {
        float roll, yaw, pitch;
    };

    vec3()
        : x(0.f)
        , y(0.f)
        , z(0.f)
    {}

    vec3(float xVal, float yVal, float zVal)
        : x(xVal)
        , y(yVal)
        , z(zVal)
    {}

    float& operator[] (int row)
    {
        float* address = (float*)this;
        return address[row];
    }
    const float& operator[] (int row) const
    {
        float* address = (float*)this;
        return address[row];
    }
};

struct vec4
{
    union
    {
        struct
        {
            float x, y, z;
        };
        vec3 xyz;
    };
    float w;

    vec4()
        : x(0.f)
        , y(0.f)
        , z(0.f)
        , w(0.f)
    {}

    vec4(float xVal, float yVal, float zVal, float wVal)
        : x(xVal)
        , y(yVal)
        , z(zVal)
        , w(wVal)
    {}

    vec4(vec3 v3, float wVal)
        : xyz(v3)
        , w(wVal)
    {}

    float& operator[] (int row)
    {
        float* address = (float*)this;
        return address[row];
    }
    const float& operator[] (int row) const
    {
        float* address = (float*)this;
        return address[row];
    }
};

struct vec2
{
    float x;
    float y;

    vec2()
        : x(0.f)
        , y(0.f)
    {}

    vec2(float xVal, float yVal)
        : x(xVal)
        , y(yVal)
    {}

    float& operator[] (int row)
    {
        float* address = (float*)this;
        return address[row];
    }
    const float& operator[] (int row) const
    {
        float* address = (float*)this;
        return address[row];
    }
};

struct ivec3
{
    int x;
    int y;
    int z;

    ivec3()
        : x(0)
        , y(0)
        , z(0)
    {}

    ivec3(int xVal, int yVal, int zVal)
        : x(xVal)
        , y(yVal)
        , z(zVal)
    {}
};

struct ivec2
{
    int x;
    int y;

    ivec2()
        : x(0)
        , y(0)
    {}

    ivec2(int xVal, int yVal)
        : x(xVal)
        , y(yVal)
    {}
};

/** - Matrices -
    Column-major order
    Access like so: mat4[col][row]
    Laid in memory like so:
    0x????0000  col 0 row 0 : float
    0x????0004  col 0 row 1 : float
    0x????0008  col 0 row 2 : float
    0x????000c  col 0 row 3 : float
    0x????0010  col 1 row 0 : float
    0x????0014  col 1 row 1 : float
    0x????0018  col 1 row 2 : float
    0x????001c  col 1 row 3 : float
    0x????0020  col 2 row 0 : float
    0x????0024  col 2 row 1 : float
    0x????0028  col 2 row 2 : float
    0x????002c  col 2 row 3 : float
    0x????0030  col 3 row 0 : float
    0x????0034  col 3 row 1 : float
    0x????0038  col 3 row 2 : float
    0x????003c  col 3 row 3 : float
    Get float array address through ptr()
    Can use initializer list like mat4 m = { 00, 01, ... , 33 };

    [00][04][08][12]
    [01][05][09][13]
    [02][06][10][14]
    [03][07][11][15]
*/

union mat4
{
    float e[16];
    vec4 columns[4];

    /** Constructs a 4x4 identity matrix */
    mat4()
    {
        columns[0] = vec4(1.f, 0.f, 0.f, 0.f);
        columns[1] = vec4(0.f, 1.f, 0.f, 0.f);
        columns[2] = vec4(0.f, 0.f, 1.f, 0.f);
        columns[3] = vec4(0.f, 0.f, 0.f, 1.f);
    }

    mat4(float e00, float e01, float e02, float e03,
         float e10, float e11, float e12, float e13,
         float e20, float e21, float e22, float e23,
         float e30, float e31, float e32, float e33);

    mat4(const mat3& from);

    /** Construct a 4x4 rotation matrix from the given quaternion */
    mat4(quat q);

    inline mat4 GetTranspose();

    /** Returns a float pointer to the memory layout of the matrix. Useful
        for uploading data to graphics API. OpenGL uses column-major order.*/
    float* ptr() const { return((float*)this); }

    vec4& operator[] (int col) { return columns[col]; }
    const vec4& operator[] (int col) const { return columns[col]; }
};

union mat3
{
    float e[9];
    vec3 columns[3];

    /** Constructs a 3x3 identity matrix */
    mat3()
    {
        columns[0] = vec3(1.f, 0.f, 0.f);
        columns[1] = vec3(0.f, 1.f, 0.f);
        columns[2] = vec3(0.f, 0.f, 1.f);
    }

    mat3(float e00, float e01, float e02,
         float e10, float e11, float e12,
         float e20, float e21, float e22);

    mat3(const mat4& from);

    /** Construct 3x3 rotation matrix from given quaternion */
    mat3(quat q);

    mat3 GetTranspose();

    /** Returns a float pointer to the memory layout of the matrix. Useful
        for uploading data to graphics API. OpenGL uses column-major order.*/
    float* ptr() { return((float*)this); }

    vec3& operator[] (int col) { return columns[col]; }
    const vec3& operator[] (int col) const { return columns[col]; }
};

/** - Quaternions -
    You shouldn't modify quaternions values directly--use functions
*/
struct quat
{
    float w = 0.f;
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    /* Constructs an identity quaternion */
    quat()
        : w(1.f)
        , x(0.f)
        , y(0.f)
        , z(0.f)
    {}

    quat(float W, float X, float Y, float Z);
    quat(float angleInRadians, vec3 axisOfRotation);

    /** Gets the conjugate of given quaternion. Doesn't check that Magnitude is 1. */
    inline quat GetConjugate() const;

    /** Identical to conjugate */
    inline quat GetInverse() const;

    /** Gets the conjugate of the given quaternion with Magnitude 1 */
    inline quat GetInverseUnitQuaternion();
};

/**
 *
 * Basic Vector Operations
 *
 */
inline vec2 Add(vec2 a, vec2 b);
inline vec3 Add(vec3 a, vec3 b);
inline vec4 Add(vec4 a, vec4 b);
inline vec2 Sub(vec2 a, vec2 b);
inline vec3 Sub(vec3 a, vec3 b);
inline vec4 Sub(vec4 a, vec4 b);
inline vec2 Mul(vec2 a, float b);
inline vec3 Mul(vec3 a, float b);
inline vec4 Mul(vec4 a, float b);
inline vec2 Div(vec2 a, float b);
inline vec3 Div(vec3 a, float b);
inline vec4 Div(vec4 a, float b);
inline float Dot(vec2 a, vec2 b);
inline float Dot(vec3 a, vec3 b);
inline float Dot(vec4 a, vec4 b);
inline vec3 Cross(vec3 a, vec3 b);
inline float Magnitude(vec2 a);
inline float Magnitude(vec3 a);
inline float Magnitude(vec4 a);
inline vec2 Normalize(vec2 a);
inline vec3 Normalize(vec3 a);
inline vec4 Normalize(vec4 a);
inline vec3 Lerp(vec3 from, vec3 to, float ratio);
inline vec4 Lerp(vec4 from, vec4 to, float ratio);
inline vec3 operator-(vec3 a);
inline vec3 operator+(vec3 a, vec3 b);
inline vec3 operator-(vec3 a, vec3 b);
inline vec3 operator*(vec3 a, float b);
inline vec3 operator*(float b, vec3 a);
inline vec3 operator/(vec3 a, float b);
inline vec3 &operator+=(vec3& a, vec3 b);
inline vec3 &operator-=(vec3& a, vec3 b);
inline vec3 &operator*=(vec3& a, float b);
inline vec3 &operator/=(vec3& a, float b);
inline vec4 operator-(vec4 a);
inline vec4 operator+(vec4 a, vec4 b);
inline vec4 operator-(vec4 a, vec4 b);
inline vec4 operator*(vec4 a, float b);
inline vec4 operator*(float b, vec4 a);
inline vec4 operator/(vec4 a, float b);
inline vec4 &operator+=(vec4& a, vec4 b);
inline vec4 &operator-=(vec4& a, vec4 b);
inline vec4 &operator*=(vec4& a, float b);
inline vec4 &operator/=(vec4& a, float b);

/**
 *
 * Basic Matrix Operations
 *
 */
inline mat3 Mul(const mat3& a, const mat3& b);
inline vec3 Mul(const mat3& A, vec3 v);
inline mat4 Mul(const mat4& a, const mat4& b);
inline vec4 Mul(const mat4& A, vec4 v);
inline vec3 operator*(mat3 A, vec3 v);
inline mat3 operator*(mat3 a, mat3 b);
inline mat3& operator*=(mat3& a, mat3 b);
inline vec4 operator*(mat4 A, vec4 v);
inline mat4 operator*(mat4 a, mat4 b);
inline mat4& operator*=(mat4& a, mat4 b);

/**
 *
 *  Basic Quaternion Operations
 *
 */
inline quat Add(quat a, quat b);
inline quat Sub(quat a, quat b);
inline float Dot(quat a, quat b);
inline quat Mul(quat a, quat b);
inline quat Mul(quat a, float scale);
inline quat Div(quat a, float scale);
inline float Magnitude(quat a);
inline quat Normalize(quat a);

/**
 *
 * Advanced Operations
 *
 */
/** Generates translation matrix for given delta x delta y delta z
    https://en.wikipedia.org/wiki/Translation_(geometry)#Matrix_resentation */
inline mat4 TranslationMatrix(float x, float y, float z);
inline mat4 TranslationMatrix(vec3 translation);

/** Generates rotation matrix for given quaternion represented rotation
    https://en.wikipedia.org/wiki/Rotation_matrix#In_three_dimensions */
inline mat4 RotationMatrix(quat q);

/** Generates scaling matrix for given x y z scales
    https://en.wikipedia.org/wiki/Scaling_(geometry)#Using_homogeneous_coordinates */
inline mat4 ScaleMatrix(float x_scale, float y_scale, float z_scale);
inline mat4 ScaleMatrix(vec3 scale);

/** Creates a matrix for a symetric perspective-view frustum based on the default handedness and default near and far clip planes definition.
    fovy: Specifies the field of view angle in the y direction. Expressed in radians.
    aspect: Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
    nearclip: Specifies the distance from the viewer to the near clipping plane (always positive).
    farclip: Specifies the distance from the viewer to the far clipping plane (always positive).
    https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml */
inline mat4 ProjectionMatrixPerspective(float fovy, float aspect, float nearclip, float farclip);

/** Creates a matrix for projecting two-dimensional coordinates onto the screen.
    https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluOrtho2D.xml
    left, right: Specify the coordinates for the left and right vertical clipping planes.
    bottom, top: Specify the coordinates for the bottom and top horizontal clipping planes.
    e.g. ProjectionMatrixOrthographic(0.f, 1920.f, 1080.f, 0.f); */
inline mat4 ProjectionMatrixOrthographic2D(float left, float right, float bottom, float top);

/** Creates a matrix for an orthographic parallel viewing volume, using right-handed coordinates.
    https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml
    The near and far clip planes correspond to z normalized device coordinates of -1 and +1
    respectively (OpenGL clip volume definition). */
inline mat4 ProjectionMatrixOrthographic(float left, float right, float bottom, float top, float z_near, float z_far);

/** Creates a ViewMatrix at eye looking at target. */
inline mat4 ViewMatrixLookAt(vec3 const& eye, vec3 const& target, vec3 const& eyeUpVector);

/** Checks if Dot product of a and b is within 1 +/- tolerance */
inline bool Similar(quat a, quat b, float tolerance = 0.001f);

/** Combines rotations represented by quaternions. Equivalent to second * first. */
inline quat CombineRotations(quat firstRotation, quat secondRotation);

/** Convert Quaternion to Euler angles IN RADIANS. When you read the .eulerAngles property,
    Unity converts the Quaternion's internal representation of the rotation to Euler angles.
    Because, there is more than one way to represent any given rotation using Euler angles,
    the values you read back out may be quite different from the values you assigned. This
    can cause confusion if you are trying to gradually increment the values to produce animation.
    To avoid these kinds of problems, the recommended way to work with rotations is to avoid
    relying on consistent results when reading .eulerAngles particularly when attempting to
    gradually increment a rotation to produce animation.
    This will not work when the Z euler angle is within [90, 270] degrees. This is a
    limitation with euler angles: euler angles (of any type) have a singularity. Unity's
    Quaternion.eulerAngle also experiences the same limitation, so I don't think there is
    anything I can do about it. Just whenever possible, avoid using euler angles.
*/
inline vec3 QuatToEuler(quat q);

/** Convert Euler angles IN RADIANS to a rotation Quaternion representing a rotation
    x/roll degrees around the x-axis, z/pitch degrees around the z-axis, and y/yaw degrees
    around the y-axis; APPLIED IN THAT ORDER.
    See https://ntrs.nasa.gov/api/citations/19770024290/downloads/19770024290.pdf
    The following wikipedia page uses a different order of rotation, but still helpful:
    https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Euler_angles_to_quaternion_conversion
*/
inline quat EulerToQuat(float roll, float yaw, float pitch);
inline quat EulerToQuat(vec3 eulerAnglesInRadians);

/** Returns an orientation that faces the given direction. The return value represents
    the rotation from the world's forward direction (forward vector) in order to face
    the same direction as the given direction. */
inline quat DirectionToOrientation(vec3 direction);

/** Returns the direction of this orientation. The world's forward direction (forward vector)
    rotated by the orientation is the direction. */
inline vec3 OrientationToDirection(quat orientation);

/** Creates a rotation which rotates from fromDirection to toDirection
    Similar to https://docs.unity3d.com/ScriptReference/Quaternion.FromToRotation.html
    Usually you use this to rotate a transform so that one of its axes eg. the y-axis -
    follows a target direction toDirection in world space.
*/
inline quat RotationFromTo(vec3 fromDirection, vec3 toDirection);

/** Finds the difference such that b = difference * a */
inline quat RotationDifference(quat a, quat b);

/** Rotates given vector by given quaternion represented rotation.
    The center of rotation is the origin. If you want to rotate around another point,
    translate the vector before calling RotateVector, then inverse translate (translate back). */
inline vec3 RotateVector(vec3 vector, quat rotation);

/** Converts quaternion to a 3x3 matrix representing the rotation */
inline mat3 QuatToMat3(quat q);

/** Converts quaternion to a 4x4 matrix representing the rotation */
inline mat4 QuatToMat4(quat q);

/** Spherically interpolates between quaternions from and to by ratio. The parameter ratio is clamped to the range [0, 1].
    Use this to create a rotation which smoothly interpolates between the first quaternion a to the second quaternion b,
    based on the value of the interpolation ratrio.
    from : Start value, returned when t = 0.
    to : End value, returned when t = 1.
    ratio : Interpolation ratio.
    https://www.youtube.com/watch?v=x1aCcyD0hqE&ab_channel=JorgeRodriguez
*/
inline quat SLerp(const quat from, const quat to, const float ratio);

/** Linearly interpolate between two floats */
inline float Lerp(float from, float to, float ratio);

#endif // _INCLUDE_SEXY_MATH_LIBRARY_H_
// INTERFACE ENDS HERE

// IMPLEMENTATION STARTS HERE
#ifdef SEXY_MATH_IMPLEMENTATION

// ==================================================================================================================
//                                               IMPLEMENTATION
// ==================================================================================================================

mat4::mat4(float e00, float e01, float e02, float e03,
           float e10, float e11, float e12, float e13,
           float e20, float e21, float e22, float e23,
           float e30, float e31, float e32, float e33)
{
    e[0] = e00;
    e[1] = e01;
    e[2] = e02;
    e[3] = e03;
    e[4] = e10;
    e[5] = e11;
    e[6] = e12;
    e[7] = e13;
    e[8] = e20;
    e[9] = e21;
    e[10] = e22;
    e[11] = e23;
    e[12] = e30;
    e[13] = e31;
    e[14] = e32;
    e[15] = e33;
}

mat4::mat4(const mat3& from)
{
    columns[0][0] = from[0][0];
    columns[0][1] = from[0][1];
    columns[0][2] = from[0][2];
    columns[0][3] = 0.f;
    columns[1][0] = from[1][0];
    columns[1][1] = from[1][1];
    columns[1][2] = from[1][2];
    columns[1][3] = 0.f;
    columns[2][0] = from[2][0];
    columns[2][1] = from[2][1];
    columns[2][2] = from[2][2];
    columns[2][3] = 0.f;
    columns[3][0] = 0.f;
    columns[3][1] = 0.f;
    columns[3][2] = 0.f;
    columns[3][3] = 1.f;
}

mat3::mat3(float e00, float e01, float e02,
           float e10, float e11, float e12,
           float e20, float e21, float e22)
{
    e[0] = e00;
    e[1] = e01;
    e[2] = e02;
    e[3] = e10;
    e[4] = e11;
    e[5] = e12;
    e[6] = e20;
    e[7] = e21;
    e[8] = e22;
}


mat3::mat3(const mat4& from)
{
    columns[0][0] = from[0][0];
    columns[0][1] = from[0][1];
    columns[0][2] = from[0][2];
    columns[1][0] = from[1][0];
    columns[1][1] = from[1][1];
    columns[1][2] = from[1][2];
    columns[2][0] = from[2][0];
    columns[2][1] = from[2][1];
    columns[2][2] = from[2][2];
}

quat::quat(float W, float X, float Y, float Z)
        : w(W)
        , x(X)
        , y(Y)
        , z(Z)
{
    *this = Normalize(*this);
}

quat::quat(float angleInRadians, vec3 axisOfRotation)
{
    axisOfRotation = Normalize(axisOfRotation);
    float half_angle = angleInRadians * 0.5f;
    float s = sinf(half_angle);
    w = cosf(half_angle);
    x = axisOfRotation.x * s;
    y = axisOfRotation.y * s;
    z = axisOfRotation.z * s;
}

mat4::mat4(quat q)
{
    *this = QuatToMat4(q);
}

mat3::mat3(quat q)
{
    *this = QuatToMat3(q);
}



inline vec2 Add(vec2 a, vec2 b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline vec3 Add(vec3 a, vec3 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline vec4 Add(vec4 a, vec4 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

inline vec2 Sub(vec2 a, vec2 b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

inline vec3 Sub(vec3 a, vec3 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

inline vec4 Sub(vec4 a, vec4 b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

inline vec2 Mul(vec2 a, float b)
{
    a.x *= b;
    a.y *= b;
    return a;
}

inline vec3 Mul(vec3 a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}

inline vec4 Mul(vec4 a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.w *= b;
    return a;
}

inline vec2 Div(vec2 a, float b)
{
    b = 1.f/b;
    a.x *= b;
    a.y *= b;
    return a;
}

inline vec3 Div(vec3 a, float b)
{
    b = 1.f/b;
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}

inline vec4 Div(vec4 a, float b)
{
    b = 1.f/b;
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.w *= b;
    return a;
}

inline float Dot(vec2 a, vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

inline float Dot(vec3 a, vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Dot(vec4 a, vec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline vec3 Cross(vec3 a, vec3 b)
{
    vec3 R;
    R.x = a.y * b.z - b.y * a.z;
    R.y = a.z * b.x - b.z * a.x;
    R.z = a.x * b.y - b.x * a.y;
    return R;
}

inline float Magnitude(vec2 a) { return sqrtf(Dot(a, a)); }

inline float Magnitude(vec3 a) { return sqrtf(Dot(a, a)); }

inline float Magnitude(vec4 a) { return sqrtf(Dot(a, a)); }

inline vec2 Normalize(vec2 a)
{
    if(a.x == 0.f && a.y == 0.f)
    {
        return {0.f,0.f};
    }
    return Div(a, Magnitude(a));
}

inline vec3 Normalize(vec3 a)
{
    if(a.x == 0.f && a.y == 0.f && a.z == 0.f)
    {
        return {0.f,0.f,0.f};
    }
    return Div(a, Magnitude(a));
}

inline vec4 Normalize(vec4 a)
{
    if(a.x == 0.f && a.y == 0.f && a.z == 0.f && a.w == 0.f)
    {
        return {0.f,0.f,0.f,0.f};
    }
    return Div(a, Magnitude(a));
}

inline vec3 operator-(vec3 a) { vec3 r = { -a.x, -a.y, -a.z }; return(r); }
inline vec3 operator+(vec3 a, vec3 b) { return Add(a, b); }
inline vec3 operator-(vec3 a, vec3 b) { return Sub(a, b); }
inline vec3 operator*(vec3 a, float b) { return Mul(a, b); }
inline vec3 operator*(float b, vec3 a) { return Mul(a, b); }
inline vec3 operator/(vec3 a, float b) { return Div(a, b); }
inline vec3 &operator+=(vec3& a, vec3 b) { return(a = a + b); }
inline vec3 &operator-=(vec3& a, vec3 b) { return(a = a - b); }
inline vec3 &operator*=(vec3& a, float b) { return(a = a * b); }
inline vec3 &operator/=(vec3& a, float b) { return(a = a / b); }

inline vec4 operator-(vec4 a) { vec4 r = { -a.x, -a.y, -a.z, -a.w }; return(r); }
inline vec4 operator+(vec4 a, vec4 b) { return Add(a, b); }
inline vec4 operator-(vec4 a, vec4 b) { return Sub(a, b); }
inline vec4 operator*(vec4 a, float b) { return Mul(a, b); }
inline vec4 operator*(float b, vec4 a) { return Mul(a, b); }
inline vec4 operator/(vec4 a, float b) { return Div(a, b); }
inline vec4 &operator+=(vec4& a, vec4 b) { return(a = a + b); }
inline vec4 &operator-=(vec4& a, vec4 b) { return(a = a - b); }
inline vec4 &operator*=(vec4& a, float b) { return(a = a * b); }
inline vec4 &operator/=(vec4& a, float b) { return(a = a / b); }

inline vec3 Lerp(vec3 from, vec3 to, float ratio) { return((1.0f - ratio) * from + to * ratio); }
inline vec4 Lerp(vec4 from, vec4 to, float ratio) { return((1.0f - ratio) * from + to * ratio); }


inline mat3 Mul(const mat3& a, const mat3& b)
{
    mat3 res;

    res.columns[0][0] = Dot(vec3(a[0][0], a[1][0], a[2][0]), b[0]);
    res.columns[0][1] = Dot(vec3(a[0][1], a[1][1], a[2][1]), b[0]);
    res.columns[0][2] = Dot(vec3(a[0][2], a[1][2], a[2][2]), b[0]);

    res.columns[1][0] = Dot(vec3(a[0][0], a[1][0], a[2][0]), b[1]);
    res.columns[1][1] = Dot(vec3(a[0][1], a[1][1], a[2][1]), b[1]);
    res.columns[1][2] = Dot(vec3(a[0][2], a[1][2], a[2][2]), b[1]);

    res.columns[2][0] = Dot(vec3(a[0][0], a[1][0], a[2][0]), b[2]);
    res.columns[2][1] = Dot(vec3(a[0][1], a[1][1], a[2][1]), b[2]);
    res.columns[2][2] = Dot(vec3(a[0][2], a[1][2], a[2][2]), b[2]);

    return res;
}

inline vec3 Mul(const mat3& A, vec3 v)
{
    return A[0] * v.x + A[1] * v.y + A[2] * v.z;
}

inline mat4 Mul(const mat4& a, const mat4& b)
{
    mat4 res;

    res.columns[0][0] = Dot(vec4(a[0][0], a[1][0], a[2][0], a[3][0]), b[0]);
    res.columns[0][1] = Dot(vec4(a[0][1], a[1][1], a[2][1], a[3][1]), b[0]);
    res.columns[0][2] = Dot(vec4(a[0][2], a[1][2], a[2][2], a[3][2]), b[0]);
    res.columns[0][3] = Dot(vec4(a[0][3], a[1][3], a[2][3], a[3][3]), b[0]);

    res.columns[1][0] = Dot(vec4(a[0][0], a[1][0], a[2][0], a[3][0]), b[1]);
    res.columns[1][1] = Dot(vec4(a[0][1], a[1][1], a[2][1], a[3][1]), b[1]);
    res.columns[1][2] = Dot(vec4(a[0][2], a[1][2], a[2][2], a[3][2]), b[1]);
    res.columns[1][3] = Dot(vec4(a[0][3], a[1][3], a[2][3], a[3][3]), b[1]);

    res.columns[2][0] = Dot(vec4(a[0][0], a[1][0], a[2][0], a[3][0]), b[2]);
    res.columns[2][1] = Dot(vec4(a[0][1], a[1][1], a[2][1], a[3][1]), b[2]);
    res.columns[2][2] = Dot(vec4(a[0][2], a[1][2], a[2][2], a[3][2]), b[2]);
    res.columns[2][3] = Dot(vec4(a[0][3], a[1][3], a[2][3], a[3][3]), b[2]);

    res.columns[3][0] = Dot(vec4(a[0][0], a[1][0], a[2][0], a[3][0]), b[3]);
    res.columns[3][1] = Dot(vec4(a[0][1], a[1][1], a[2][1], a[3][1]), b[3]);
    res.columns[3][2] = Dot(vec4(a[0][2], a[1][2], a[2][2], a[3][2]), b[3]);
    res.columns[3][3] = Dot(vec4(a[0][3], a[1][3], a[2][3], a[3][3]), b[3]);

    return res;
}

inline vec4 Mul(const mat4& A, vec4 v)
{
    return A[0] * v.x + A[1] * v.y + A[2] * v.z + A[3] * v.w;
}

inline vec3 operator*(mat3 A, vec3 v) { return(Mul(A, v)); }
inline mat3 operator*(mat3 a, mat3 b) { return(Mul(a, b)); }
inline mat3& operator*=(mat3& a, mat3 b) { a = Mul(a, b); return a; }
inline vec4 operator*(mat4 A, vec4 v) { return(Mul(A, v)); }
inline mat4 operator*(mat4 a, mat4 b) { return(Mul(a, b)); }
inline mat4& operator*=(mat4& a, mat4 b) { a = Mul(a, b); return a; }

inline mat4 TranslationMatrix(float x, float y, float z)
{
    mat4 ret = mat4();
    ret[3][0] = x;
    ret[3][1] = y;
    ret[3][2] = z;
    return ret;
}

inline mat4 TranslationMatrix(vec3 translation)
{
    return TranslationMatrix(translation.x, translation.y, translation.z);
}

inline mat4 RotationMatrix(quat q)
{
    return mat4(q);
}

inline mat4 ScaleMatrix(float x_scale, float y_scale, float z_scale)
{
    mat4 ret;
    ret[0][0] = x_scale;
    ret[1][1] = y_scale;
    ret[2][2] = z_scale;
    ret[3][3] = 1.f;
    return ret;
}

inline mat4 ScaleMatrix(vec3 scale)
{
    return ScaleMatrix(scale.x, scale.y, scale.z);
}

inline mat4 ProjectionMatrixPerspective(float fovy, float aspect, float nearclip, float farclip)
{
    float const tanHalfFovy = tan(fovy / 2.f);

    mat4 Result;
    Result[0][0] = 1.f / (aspect * tanHalfFovy);
    Result[1][1] = 1.f / (tanHalfFovy);
    Result[2][2] = -(farclip + nearclip) / (farclip - nearclip);
    Result[2][3] = -1.f;
    Result[3][2] = -(2.f * farclip * nearclip) / (farclip - nearclip);
    return Result;
}

inline mat4 ProjectionMatrixOrthographic2D(float left, float right, float bottom, float top)
{
    mat4 ret = mat4();
    ret[0][0] = 2.f / (right - left);
    ret[1][1] = 2.f / (top - bottom);
    ret[2][2] = -1.f;
    ret[3][0] = -(right + left) / (right - left);
    ret[3][1] = -(top + bottom) / (top - bottom);
    return ret;
}

inline mat4 ProjectionMatrixOrthographic(float left, float right, float bottom, float top, float z_near, float z_far)
{
    mat4 ret = mat4();
    ret[0][0] = 2.f / (right - left);
    ret[1][1] = 2.f / (top - bottom);
    ret[2][2] = - 2.f / (z_far - z_near);
    ret[3][0] = - (right + left) / (right - left);
    ret[3][1] = - (top + bottom) / (top - bottom);
    ret[3][2] = - (z_far + z_near) / (z_far - z_near);
    return ret;
}

inline mat4 ViewMatrixLookAt(vec3 const& eye, vec3 const& target, vec3 const& eyeUpVector)
{
    vec3 const direction = Normalize(target - eye);
    vec3 const right = Normalize(Cross(direction, eyeUpVector));
    vec3 const up = Cross(right, direction);

    mat4 ret = mat4();

    ret[0][0] = right.x;
    ret[1][0] = right.y;
    ret[2][0] = right.z;

    ret[0][1] = up.x;
    ret[1][1] = up.y;
    ret[2][1] = up.z;

    ret[0][2] = -direction.x;
    ret[1][2] = -direction.y;
    ret[2][2] = -direction.z;

    ret[3][0] = -Dot(right, eye);
    ret[3][1] = -Dot(up, eye);
    ret[3][2] = Dot(direction, eye);

    return ret;
}

inline mat3 mat3::GetTranspose()
{
    mat3 ret = {};
    for(int col = 0; col < 3; ++col)
    {
        for(int row = 0; row < 3; ++row)
        {
            ret[col][row] = columns[row][col];
        }
    }
    return ret;
}

inline mat4 mat4::GetTranspose()
{
    mat4 ret = {};
    for(int col = 0; col < 4; ++col)
    {
        for(int row = 0; row < 4; ++row)
        {
            ret[col][row] = columns[row][col];
        }
    }
    return ret;
}

inline quat Add(quat a, quat b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

inline quat Sub(quat a, quat b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

inline float Dot(quat a, quat b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline quat Mul(quat a, quat b)
{
    quat R;
    R.w = a.w * b.w - Dot(vec3(a.x, a.y, a.z), vec3(b.x, b.y, b.z));
    vec3 va = vec3(a.x, a.y, a.z);
    vec3 vb = vec3(b.x, b.y, b.z);
    vec3 first = b.w * va;
    vec3 second = a.w * vb;
    vec3 third = Cross(va, vb);
    R.x = first.x + second.x + third.x;
    R.y = first.y + second.y + third.y;
    R.z = first.z + second.z + third.z;
    return R;
}

inline quat Mul(quat a, float scale)
{
    a.w *= scale;
    a.x *= scale;
    a.y *= scale;
    a.z *= scale;
    return a;
}

inline quat Div(quat a, float scale)
{
    float one_over_s = 1.0f / scale;
    a.w *= one_over_s;
    a.x *= one_over_s;
    a.y *= one_over_s;
    a.z *= one_over_s;
    return a;
}

inline quat operator*(quat a, quat b) { return(Mul(a, b)); }

inline float Magnitude(quat a)
{
    return(sqrtf(Dot(a, a)));
}

inline quat Normalize(quat a)
{
    return Div(a, Magnitude(a));
}

inline bool Similar(quat a, quat b, float tolerance)
{
    return(SML_abs(Dot(a, b) - 1.f) <= tolerance);
}

inline quat CombineRotations(quat firstRotation, quat secondRotation)
{
    return secondRotation * firstRotation; // order matters!
}

inline quat quat::GetConjugate() const
{
    quat ret;
    ret.w = w;
    ret.x = -x;
    ret.y = -y;
    ret.z = -z;
    return ret;
}

inline quat quat::GetInverse() const
{
    return GetConjugate();
}

inline quat quat::GetInverseUnitQuaternion()
{
    quat ret = Div(GetConjugate(), Dot(*this, *this));
    return ret;
}

inline vec3 QuatToEuler(quat q)
{
    vec3 euler_angles;

    float x2 = q.x * q.x;
    float y2 = q.y * q.y;
    float z2 = q.z * q.z;
    float xy = q.x * q.y;
    float zw = q.z * q.w;
    float xz = q.x * q.z;
    float yw = q.y * q.w;
    float yz = q.y * q.z;
    float xw = q.x * q.w;

    float r10 = 2.0f * (xy + zw);
    float r20 = 2.0f * (xz - yw);
    float r00 = 1.0f - 2.0f * (y2 + z2);
    float r12 = 2.0f * (yz - xw);
    float r11 = 1.0f - 2.0f * (x2 + z2);
    float r21 = 2.0f * (yz + xw) ;
    float r22 = 1.0f - 2.0f * (x2 + y2);

    if(r10 < 1.f)
    {
        if(r10 > -1.f)
        {
            euler_angles.z = asinf(r10);
            euler_angles.y = atan2f(-r20, r00);
            euler_angles.x = atan2f(-r12, r11);
        }
        else // r10 = -1
        {
            euler_angles.z = -SML_PI / 2.f;
            euler_angles.y = -atan2f(r21, r22);
            euler_angles.x = 0;
        }
    }
    else
    {
        euler_angles.z = SML_PI / 2.f;
        euler_angles.y = atan2f(r21, r22);
        euler_angles.x = 0;
    }

    return euler_angles;
}

inline quat EulerToQuat(float roll, float yaw, float pitch)
{
    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);

    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);

    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);

    quat ret;

    ret.w = cr * cp * cy - sr * sp * sy;
    ret.x = sr * cp * cy + cr * sp * sy;
    ret.y = cr * cp * sy + sr * sp * cy;
    ret.z = cr * cy * sp - sr * sy * cp;

    return ret;
}

inline quat EulerToQuat(vec3 eulerAnglesInRadians)
{
    return EulerToQuat(eulerAnglesInRadians.x, eulerAnglesInRadians.y, eulerAnglesInRadians.z);
}

inline quat DirectionToOrientation(vec3 direction)
{
    return RotationFromTo(SML_FORWARD_VECTOR, direction);
}

inline vec3 OrientationToDirection(quat orientation)
{
    return RotateVector(SML_FORWARD_VECTOR, orientation);
}

inline quat RotationFromTo(vec3 fromDirection, vec3 toDirection)
{
    vec3 start = Normalize(fromDirection);
    vec3 dest = Normalize(toDirection);

    float cos_theta = Dot(start, dest);
    vec3 rotation_axis;
    quat rotation_quat;

    rotation_axis = Cross(start, dest);
    if (cos_theta >= -1 + 0.0001f)
    {
        float s = sqrt((1 + cos_theta) * 2);
        float sin_of_half_angle = 1 / s;

        rotation_quat = quat(
            s * 0.5f, // recall cos(theta/2) trig identity
            rotation_axis.x * sin_of_half_angle,
            rotation_axis.y * sin_of_half_angle,
            rotation_axis.z * sin_of_half_angle
        );
    }
    else
    {
        // When vectors in opposite directions, there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotation_axis = Cross(vec3(0.0f, 0.0f, 1.0f), start);
        if (Dot(rotation_axis, rotation_axis) < 0.01f) // bad luck, they were parallel, try again!
            rotation_axis = Cross(vec3(1.0f, 0.0f, 0.0f), start);
        rotation_quat = quat(SML_PI, rotation_axis);
    }

    return rotation_quat;
}

inline quat RotationDifference(quat a, quat b)
{
    quat ret = Mul(b, a.GetInverseUnitQuaternion());
    return ret;
}

inline vec3 RotateVector(vec3 vector, quat rotation)
{
    quat vector_quat = {0.f, vector.x, vector.y, vector.z };
    quat rotated_vector = rotation * vector_quat * rotation.GetInverse();
    return vec3(rotated_vector.x, rotated_vector.y, rotated_vector.z);
}

inline mat3 QuatToMat3(quat q)
{
    q = q.GetInverseUnitQuaternion();

    mat3 ret;

    float x2 = q.x * q.x;
    float y2 = q.y * q.y;
    float z2 = q.z * q.z;

    float xy = q.x * q.y;
    float zw = q.z * q.w;
    float xz = q.x * q.z;
    float yw = q.y * q.w;
    float yz = q.y * q.z;
    float xw = q.x * q.w;

    ret.columns[0][0] = 1.0f - 2.0f * (y2 + z2);
    ret.columns[1][0] = 2.0f * (xy + zw);
    ret.columns[2][0] = 2.0f * (xz - yw);

    ret.columns[0][1] = 2.0f * (xy - zw);
    ret.columns[1][1] = 1.0f - 2.0f * (x2 + z2);
    ret.columns[2][1] = 2.0f * (yz + xw);

    ret.columns[0][2] = 2.0f * (xz + yw);
    ret.columns[1][2] = 2.0f * (yz - xw);
    ret.columns[2][2] = 1.0f - 2.0f * (x2 + y2);

    return ret;
}

inline mat4 QuatToMat4(quat q)
{
    return mat4(QuatToMat3(q));
}

inline quat SLerp(const quat from, const quat to, const float ratio)
{
    float t = SML_clamp(ratio, 0.f, 1.f);
    quat start = Normalize(from);
    quat end = Normalize(to);
    quat d = end * from.GetInverse();
    float cos_theta = Dot(start, end);
    float theta = acosf(cos_theta);
    theta *= t;
    quat d_raised_t = quat(theta, vec3(d.x, d.y, d.z));
    return d_raised_t * start;
}

inline float Lerp(float from, float to, float ratio)
{
    return from + ratio * (to - from);
}

#undef SEXY_MATH_IMPLEMENTATION
#endif // SEXY_MATH_IMPLEMENTATION

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2021 Kevin Chin
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/