void EqualQuaternions(quat lhs, quat rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = (float*)&rhs;
    CHECK(*(lptr + 0) == *(rptr + 0));
    CHECK(*(lptr + 1) == *(rptr + 1));
    CHECK(*(lptr + 2) == *(rptr + 2));
    CHECK(*(lptr + 3) == *(rptr + 3));
}

void EqualQuaternions(quat lhs, glm::quat rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = glm::value_ptr(rhs);
    CHECK(*(lptr + 0) == *(rptr + 3));
    CHECK(*(lptr + 1) == *(rptr + 0));
    CHECK(*(lptr + 2) == *(rptr + 1));
    CHECK(*(lptr + 3) == *(rptr + 2));
}

#include <glm/gtx/quaternion.hpp>
TEST_CASE("quaternion construction AND normalize", "[quaternions]")
{
    SECTION("default constructor")
    {
        /* quat default construction should be identity quat */
        quat idQ;
        glm::quat glmIdQ = glm::identity<glm::quat>();
        EqualQuaternions(idQ, glmIdQ);
    }

    SECTION("init with values")
    {
        /* This tests normalize too because quat construction always normalizes */
        quat smlQuat = { 0.2777, -1.5318,0.0529,2.861 };
        glm::quat glmQuat = glm::quat(0.2777, -1.5318,0.0529,2.861);
        glmQuat = glm::normalize(glmQuat);
        EqualQuaternions(smlQuat, glmQuat);
    }
}

TEST_CASE("Axis angle to quaternion to euler", "[quaternions]")
{
    SECTION("Axis angle test -73 degs")
    {
        quat q = quat(-73.f * SML_DEG2RAD, vec3(0,1,0));
        CHECK(q.w == Approx(0.8038569));
        CHECK(q.x == Approx(0.0));
        CHECK(q.y == Approx(-0.5948228));
        CHECK(q.z == Approx(0.0));

        CHECK(QuatToEuler(q).x == Approx(0.0));
        CHECK(QuatToEuler(q).y == Approx(-1.2740903));
        CHECK(QuatToEuler(q).z == Approx(0.0));
    }

    SECTION("Axis angle test 60 degs")
    {
        quat q = quat(60.f * SML_DEG2RAD, vec3(1,1,0));
        CHECK(q.w == Approx(0.8660248));
        CHECK(q.x == Approx(0.3535541));
        CHECK(q.y == Approx(0.3535541));
        CHECK(q.z == 0.0);

        CHECK(QuatToEuler(q).x == Approx(0.6847206));
        CHECK(QuatToEuler(q).y == Approx(0.6847206));
        CHECK(QuatToEuler(q).z == Approx(0.2526814));
    }

    SECTION("Axis angle test 180 degs")
    {
        quat q = quat(180.f * SML_DEG2RAD, vec3(1,3,-2));

        CHECK(std::fabs(0.f - q.w) <= std::numeric_limits<float>::epsilon());
        CHECK(q.x == Approx(0.2672612));
        CHECK(q.y == Approx(0.8017837));
        CHECK(q.z == Approx(-0.5345225));

        CHECK(QuatToEuler(q).x == Approx(1.2490458));
        CHECK(QuatToEuler(q).y == Approx(2.8198421));
        CHECK(QuatToEuler(q).z == Approx(0.442911));
    }
}

TEST_CASE("quaternion Dot", "[quaternions]")
{
    quat smlQuat1 = { 0.2777, -1.5318, 0.0529, 2.861 };
    quat smlQuat2 = { -0.2692,2.4476,1.4411,-0.7412 };
    glm::quat glmQuat1 = glm::quat(0.2777, -1.5318,0.0529,2.861);
    glmQuat1 = glm::normalize(glmQuat1);
    glm::quat glmQuat2 = glm::quat(-0.2692,2.4476,1.4411,-0.7412);
    glmQuat2 = glm::normalize(glmQuat2);
    CHECK(Dot(smlQuat1, smlQuat2) == Approx(glm::dot(glmQuat1, glmQuat2)));
}

TEST_CASE("quaternion inverse unit", "[quaternions]")
{
    quat q = quat(60.f * SML_DEG2RAD, vec3(1,1,0));
    CHECK(q.GetInverseUnitQuaternion().w == Approx(0.8660248));
    CHECK(q.GetInverseUnitQuaternion().x == Approx(-0.3535541));
    CHECK(q.GetInverseUnitQuaternion().y == Approx(-0.3535541));
    CHECK(q.GetInverseUnitQuaternion().z == 0.0);
}

TEST_CASE("quaternion Euler to Quat", "[quaternions]")
{
    quat q = EulerToQuat(23.f*SML_DEG2RAD, -50.f*SML_DEG2RAD, 359.f*SML_DEG2RAD);
    quat expect = { -0.8873443, -0.1842958, 0.4156951, -0.0765032 };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));

    q = EulerToQuat(vec3(-90.f, 90.f, -180.f)*SML_DEG2RAD);
    expect = { -0.5, -0.5, 0.5, -0.5 };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));

    q = EulerToQuat(vec3(0.f, 0.f, 0.f)*SML_DEG2RAD);
    expect = { 1.f, 0.f, 0.f, 0.f };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));

    q = EulerToQuat(vec3(0.f, 360.f, 360.f)*SML_DEG2RAD);
    expect = { 1.f, 0.f, 0.f, 0.f };
    CHECK(q.w == Approx(expect.w));
    CHECK(std::fabs(expect.x - q.x) <= std::numeric_limits<float>::epsilon());
    CHECK(std::fabs(expect.y - q.y) <= std::numeric_limits<float>::epsilon());
    CHECK(std::fabs(expect.z - q.z) <= std::numeric_limits<float>::epsilon());

    q = EulerToQuat(vec3(502.f, 32.f, -2.f)*SML_DEG2RAD);
    expect = { -0.317457, -0.9071862, -0.0738627, 0.2660424 };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));
}

TEST_CASE("Rotate Vector with quaternions", "[quaternions]")
{
    quat q1 = EulerToQuat(0.f, 90.f * SML_DEG2RAD, 0.f);
    quat q2 = EulerToQuat(45.f * SML_DEG2RAD, 0.f, 0.f);
    quat q3 = q2 * q1;
    quat expect = { 0.707107, 0.0, 0.707107, 0.0 };
    REQUIRE(q1.w == Approx(expect.w));
    REQUIRE(q1.x == Approx(expect.x));
    REQUIRE(q1.y == Approx(expect.y));
    REQUIRE(q1.z == Approx(expect.z));
    expect = { 0.923880, 0.382683, 0.0, 0.0 };
    REQUIRE(q2.w == Approx(expect.w));
    REQUIRE(q2.x == Approx(expect.x));
    REQUIRE(q2.y == Approx(expect.y));
    REQUIRE(q2.z == Approx(expect.z));
    expect = { 0.653281, 0.270598, 0.653281, 0.270598 };
    REQUIRE(q3.w == Approx(expect.w));
    REQUIRE(q3.x == Approx(expect.x));
    REQUIRE(q3.y == Approx(expect.y));
    REQUIRE(q3.z == Approx(expect.z));

    vec3 vecRotated = RotateVector(vec3(1.f, 0.f, 0.f), q3);
    vec3 vecExpected = { 0.0, 0.707107, -0.707107 };
    CHECK(vecRotated.x == Approx(vecExpected.x));
    CHECK(vecRotated.y == Approx(vecExpected.y));
    CHECK(vecRotated.z == Approx(vecExpected.z));

    vecRotated = RotateVector(vec3(1.f, 0.f, 0.f), q1);
    vecExpected = { 0.0, 0.0, -1.0 };
    REQUIRE(vecRotated.x == Approx(vecExpected.x));
    REQUIRE(vecRotated.y == Approx(vecExpected.y));
    REQUIRE(vecRotated.z == Approx(vecExpected.z));

    vecRotated = RotateVector(vec3(0.f, 0.f, -1.f), q2);
    vecExpected = { 0.0, 0.707107, -0.707107 };
    CHECK(vecRotated.x == Approx(vecExpected.x));
    CHECK(vecRotated.y == Approx(vecExpected.y));
    CHECK(vecRotated.z == Approx(vecExpected.z));
}

TEST_CASE("Compounding rotations with quaternions", "[quaternions]")
{
    // TEST XZY order of rotation
    // For XZY Euler (Y at the top of hierarchy, applied last)

    vec3 rot = vec3(45.f, 20.f, 67.f);
    quat xrot = EulerToQuat(rot.x * SML_DEG2RAD, 0.f, 0.f);
    quat yrot = EulerToQuat(0.f, rot.y * SML_DEG2RAD, 0.f);
    quat zrot = EulerToQuat(0.f, 0.f, rot.z * SML_DEG2RAD);
    quat combined = yrot * zrot * xrot; // XZY order
    quat expect = { 0.722028, 0.402813, 0.341789, 0.446763 };
    CHECK(combined.w == Approx(expect.w));
    CHECK(combined.x == Approx(expect.x));
    CHECK(combined.y == Approx(expect.y));
    CHECK(combined.z == Approx(expect.z));
}

// kc_math tests

    // quaternion q1 = euler_to_quat(0.f, 90.f*KC_DEG2RAD, 0.f);
    // quaternion q2 = euler_to_quat(45.f*KC_DEG2RAD, 0.f, 0.f);
    // quaternion q3 = q2 * q1; // The first rotation should go last.
    // printf("Quaternion 1: (%f, %f, %f, %f)\n", q1.w, q1.x, q1.y, q1.z);
    // printf("Quaternion 2: (%f, %f, %f, %f)\n", q2.w, q2.x, q2.y, q2.z);
    // printf("Quaternion 3, q2 * q1: (%f, %f, %f, %f)\n", q3.w, q3.x, q3.y, q3.z);
    // vec3 vecRotated = rotate_vector(make_vec3(1.f, 0.f, 0.f), q3);
    // printf("Rotating (1, 0, 0) with q3: (%f, %f, %f)\n", vecRotated.x, vecRotated.y, vecRotated.z);
    // std::getline(std::cin, s);
    // vecRotated = rotate_vector(make_vec3(1.f, 0.f, 0.f), q1);
    // printf("Rotating (1, 0, 0) with q1: (%f, %f, %f)\n", vecRotated.x, vecRotated.y, vecRotated.z);
    // std::getline(std::cin, s);
    // vecRotated = rotate_vector(vecRotated, q2);
    // printf("Rotating (0, 0, -1) with q2: (%f, %f, %f)\n", vecRotated.x, vecRotated.y, vecRotated.z);
    // std::getline(std::cin, s);

// 

/************************************
    TEST XZY order of rotation
*************************************/
//     std::string s;
// /*
//     TEST Euler to Quaternion conversion in Euler Order XZY

//     FOR XZY Euler (Y at the top of hierarchy, applied last)
//     euler(x: 45 deg, y: 20 deg, z: 67 deg) converts to quaternion(w: 0.722, x: 0.403, y: 0.342, z: 0.447)
// */
//     vec3 rot = make_vec3(45.f, 20.f, 67.f);
//     quaternion xrot = euler_to_quat(rot.x*KC_DEG2RAD, 0.f, 0.f);
//     quaternion yrot = euler_to_quat(0.f, 0.f, rot.y*KC_DEG2RAD); // euler_to_quat takes roll, pitch, yaw in that order
//     quaternion zrot = euler_to_quat(0.f, rot.z*KC_DEG2RAD, 0.f);
//     // THIS IS XZY ORDER where Y rotation is top of hierarchy (applied last)
//     quaternion expected = yrot * zrot * xrot; // The first rotation should go last here, last rotation should go first
//     quaternion actual = euler_to_quat(rot*KC_DEG2RAD);
//     printf("expected:       (0.722028, 0.402813, 0.341789, 0.446763)\n");
//     printf("individual XZY: (%f, %f, %f, %f)\n", expected.w, expected.x, expected.y, expected.z);
//     printf("allatonce  XZY: (%f, %f, %f, %f)\n", actual.w, actual.x, actual.y, actual.z);
//     printf("---\n");
//     //std::getline(std::cin, s);

// /*
//     TEST Euler to Quaternion then Quaternion to Euler to conversion in Euler Order XZY
// */
//     vec3 expected2 = make_vec3(220, -79, -50);
//     vec3 inrad = expected2 * KC_DEG2RAD;
//     quaternion xzy = euler_to_quat(inrad);
//     vec3 converted_to_quat_and_back = quat_to_euler(xzy);
//     vec3 indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(20.f, -79.f, 220.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, 0.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, 20.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, -90.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, -91.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, 180.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, 181.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");


//     expected2 = make_vec3(-300.f, -179.f, -180.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, -181.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, 270.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     expected2 = make_vec3(-300.f, -179.f, 271.f);
//     inrad = expected2 * KC_DEG2RAD;
//     xzy = euler_to_quat(inrad);
//     converted_to_quat_and_back = quat_to_euler(xzy);
//     indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//     printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//     printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//     printf("---\n");

//     std::getline(std::cin, s);
//     return 0;
// //