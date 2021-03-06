void EqualQuaternions(quat lhs, quat rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = (float*)&rhs;
    CHECK(CompareFloats(*(lptr + 0), *(rptr + 0)));
    CHECK(CompareFloats(*(lptr + 1), *(rptr + 1)));
    CHECK(CompareFloats(*(lptr + 2), *(rptr + 2)));
    CHECK(CompareFloats(*(lptr + 3), *(rptr + 3)));
}

void EqualQuaternions(quat lhs, glm::quat rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = glm::value_ptr(rhs);
    CHECK(CompareFloats(*(lptr + 0), *(rptr + 3)));
    CHECK(CompareFloats(*(lptr + 1), *(rptr + 0)));
    CHECK(CompareFloats(*(lptr + 2), *(rptr + 1)));
    CHECK(CompareFloats(*(lptr + 3), *(rptr + 2)));
}

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
        quat q = quat(-73.f * GM_DEG2RAD, vec3(0,1,0));
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
        quat q = quat(60.f * GM_DEG2RAD, vec3(1,1,0));
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
        quat q = quat(180.f * GM_DEG2RAD, vec3(1,3,-2));

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
    quat q = quat(60.f * GM_DEG2RAD, vec3(1,1,0));
    CHECK(q.GetInverseUnitQuaternion().w == Approx(0.8660248));
    CHECK(q.GetInverseUnitQuaternion().x == Approx(-0.3535541));
    CHECK(q.GetInverseUnitQuaternion().y == Approx(-0.3535541));
    CHECK(q.GetInverseUnitQuaternion().z == 0.0);
}

TEST_CASE("quaternion Euler to Quat", "[quaternions]")
{
    quat q = EulerToQuat(23.f*GM_DEG2RAD, -50.f*GM_DEG2RAD, 359.f*GM_DEG2RAD);
    quat expect = { -0.8873443, -0.1842958, 0.4156951, -0.0765032 };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));

    q = EulerToQuat(vec3(-90.f, 90.f, -180.f)*GM_DEG2RAD);
    expect = { -0.5, -0.5, 0.5, -0.5 };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));

    q = EulerToQuat(vec3(0.f, 0.f, 0.f)*GM_DEG2RAD);
    expect = { 1.f, 0.f, 0.f, 0.f };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));

    q = EulerToQuat(vec3(0.f, 360.f, 360.f)*GM_DEG2RAD);
    expect = { 1.f, 0.f, 0.f, 0.f };
    CHECK(q.w == Approx(expect.w));
    CHECK(std::fabs(expect.x - q.x) <= std::numeric_limits<float>::epsilon());
    CHECK(std::fabs(expect.y - q.y) <= std::numeric_limits<float>::epsilon());
    CHECK(std::fabs(expect.z - q.z) <= std::numeric_limits<float>::epsilon());

    q = EulerToQuat(vec3(502.f, 32.f, -2.f)*GM_DEG2RAD);
    expect = { -0.317457, -0.9071862, -0.0738627, 0.2660424 };
    CHECK(q.w == Approx(expect.w));
    CHECK(q.x == Approx(expect.x));
    CHECK(q.y == Approx(expect.y));
    CHECK(q.z == Approx(expect.z));
}

TEST_CASE("Rotate Vector with quaternions", "[quaternions]")
{
    quat q1 = EulerToQuat(0.f, 90.f * GM_DEG2RAD, 0.f);
    quat q2 = EulerToQuat(45.f * GM_DEG2RAD, 0.f, 0.f);
    quat q3 = CombineRotations(q1, q2);
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
    quat xrot = EulerToQuat(rot.x * GM_DEG2RAD, 0.f, 0.f);
    quat yrot = EulerToQuat(0.f, rot.y * GM_DEG2RAD, 0.f);
    quat zrot = EulerToQuat(0.f, 0.f, rot.z * GM_DEG2RAD);
    quat combined = yrot * zrot * xrot; // XZY order
    quat expect = { 0.722028, 0.402813, 0.341789, 0.446763 };
    CHECK(combined.w == Approx(expect.w));
    CHECK(combined.x == Approx(expect.x));
    CHECK(combined.y == Approx(expect.y));
    CHECK(combined.z == Approx(expect.z));
}

TEST_CASE("Euler to Quaternion to Euler Conversion", "[quaternions]")
{
    vec3 expected = vec3(220.f, -79.f, -50.f);
    quat q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(-140.f, -79.f, -50.f);
    vec3 actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(actual.z == Approx(expected.z));

    expected = vec3(20.f, -79.f, 220.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(-160.f, 101.f, -40.0f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(actual.z == Approx(expected.z));

    expected = vec3(-300.f, -179.f, 0.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(60.f, -179.f, 0.f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(actual.z == Approx(expected.z));

    expected = vec3(-300.f, -179.f, -91.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(-120.f, 1.0f, -89.f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y).epsilon(0.0001f));
    CHECK(actual.z == Approx(expected.z));

    expected = vec3(-300.f, -179.f, 180.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(-120.f, 1.f, 0.f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(((actual.z - expected.z < 0.0001f) && (actual.z - expected.z > -0.0001f)));

    expected = vec3(-300.f, -179.f, 181.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(-120.f, 1.f, -1.f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(actual.z == Approx(expected.z));

    expected = vec3(-300.f, -179.f, 270.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(0.f, 121.f, -90.f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(actual.z == Approx(expected.z));

    expected = vec3(-300.f, -179.f, 271.f);
    q = EulerToQuat(expected * GM_DEG2RAD);
    expected = vec3(60.f, -179.f, -89.f);
    actual = QuatToEuler(q) * GM_RAD2DEG;
    CHECK(actual.x == Approx(expected.x));
    CHECK(actual.y == Approx(expected.y));
    CHECK(actual.z == Approx(expected.z));
}

TEST_CASE("Combine Rotations", "[quaternions]")
{
    quat q1 = quat(60.f*GM_RAD2DEG, vec3(1,1,-1));
    quat q2 = quat(-30.33f*GM_RAD2DEG, vec3(3,1,-2));
    quat expect = q2 * q1;
    quat actual = CombineRotations(q1, q2);
    EqualQuaternions(actual, expect);
}

TEST_CASE("Rotation Difference", "[quaternions]")
{
    quat a = quat(142.f*GM_RAD2DEG, vec3(1,1,-1));
    quat b = quat(-89.98f*GM_RAD2DEG, vec3(3,1,-2));
    quat expect = Mul(b, a.GetInverseUnitQuaternion());
    quat actual = RotationDifference(a, b);
    EqualQuaternions(actual, expect);
}

TEST_CASE("Rotation From To", "[quaternions]")
{
    SECTION("from to 90")
    {
        vec3 from = vec3(1,0,0);
        vec3 to = vec3(0,0,1);
        quat expect = quat(90.f*GM_DEG2RAD, vec3(0,-1,0));
        quat actual = RotationFromTo(from, to);
        EqualQuaternions(actual, expect);
    }

    SECTION("from to 120")
    {
        vec3 from = vec3(0,-1,0);
        vec3 to = vec3(sqrt(3.f)/2.f, 0.5f, 0.f);
        quat expect = quat(120.f*GM_DEG2RAD, vec3(0,0,1));
        quat actual = RotationFromTo(from, to);
        EqualQuaternions(actual, expect);
    }
}

TEST_CASE("DirectionToOrientation", "[quaternions]")
{
    SECTION("dir to orient 1")
    {
        vec3 dir = vec3(3.4341,16.7249,3.1121);
        quat expect = RotationFromTo(GM_FORWARD_VECTOR, dir);
        quat actual = DirectionToOrientation(dir);
        EqualQuaternions(actual, expect);
    }

    SECTION("dir to orient 2")
    {
        vec3 dir = vec3(8.0431,-1.2318,-13.2272);
        quat expect = RotationFromTo(GM_FORWARD_VECTOR, dir);
        quat actual = DirectionToOrientation(dir);
        EqualQuaternions(actual, expect);
    }

    SECTION("dir to orient 3")
    {
        vec3 dir = vec3(5.019,-10.3291,7.067);
        quat expect = RotationFromTo(GM_FORWARD_VECTOR, dir);
        quat actual = DirectionToOrientation(dir);
        EqualQuaternions(actual, expect);
    }
}

TEST_CASE("OrientationToDirection", "[quaternions]")
{
    SECTION("turn around")
    {
        quat q = quat(0, 0, 1, 0);
        vec3 expect = vec3(-1, 0, 0);
        vec3 actual = OrientationToDirection(q);
        CHECK(actual.x == Approx(expect.x));
        CHECK(actual.y == Approx(expect.y));
        CHECK(actual.z == Approx(expect.z));
    }

    SECTION("roll only")
    {
        quat q = quat(-0.7193398, 0.6946584, 0, 0);
        vec3 expect = vec3(1, 0, 0);
        vec3 actual = OrientationToDirection(q);
        CHECK(actual.x == Approx(expect.x));
        CHECK(actual.y == Approx(expect.y));
        CHECK(actual.z == Approx(expect.z));
    }

    SECTION("rotate 180 around xz axis")
    {
        quat q = quat(0, 0.7071068, 0, 0.7071068);
        vec3 expect = vec3(0, 0, 1);
        expect = Normalize(expect);
        vec3 actual = OrientationToDirection(q);
        CHECK(actual.x == Approx(expect.x));
        CHECK(actual.y == Approx(expect.y));
        CHECK(actual.z == Approx(expect.z));
    }

    SECTION("rotate 90 around xz axis")
    {
        quat q = quat(0.7071068, 0.5, 0, 0.5);
        vec3 expect = vec3(0.500000, 0.707107, 0.500000);
        expect = Normalize(expect);
        vec3 actual = OrientationToDirection(q);
        CHECK(actual.x == Approx(expect.x));
        CHECK(actual.y == Approx(expect.y));
        CHECK(actual.z == Approx(expect.z));
    }
}
