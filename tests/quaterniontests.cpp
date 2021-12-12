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

    SECTION("construct with angle and vector")
    {
        quat q1 = quat();
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



//
//// kc_math tests
//
//// quaternion q1 = euler_to_quat(0.f, 90.f*KC_DEG2RAD, 0.f);
//// quaternion q2 = euler_to_quat(45.f*KC_DEG2RAD, 0.f, 0.f);
//// quaternion q3 = q2 * q1; // The first rotation should go last.
//// printf("Quaternion 1: (%f, %f, %f, %f)\n", q1.w, q1.x, q1.y, q1.z);
//// printf("Quaternion 2: (%f, %f, %f, %f)\n", q2.w, q2.x, q2.y, q2.z);
//// printf("Quaternion 3, q2 * q1: (%f, %f, %f, %f)\n", q3.w, q3.x, q3.y, q3.z);
//// vec3 vecRotated = rotate_vector(make_vec3(1.f, 0.f, 0.f), q3);
//// printf("Rotating (1, 0, 0) with q3: (%f, %f, %f)\n", vecRotated.x, vecRotated.y, vecRotated.z);
//// std::getline(std::cin, s);
//// vecRotated = rotate_vector(make_vec3(1.f, 0.f, 0.f), q1);
//// printf("Rotating (1, 0, 0) with q1: (%f, %f, %f)\n", vecRotated.x, vecRotated.y, vecRotated.z);
//// std::getline(std::cin, s);
//// vecRotated = rotate_vector(vecRotated, q2);
//// printf("Rotating (0, 0, -1) with q2: (%f, %f, %f)\n", vecRotated.x, vecRotated.y, vecRotated.z);
//// std::getline(std::cin, s);
//
////
//
///************************************
//    TEST XZY order of rotation
//*************************************/
//std::string s;
///*
//    TEST Euler to Quaternion conversion in Euler Order XZY
//
//    FOR XZY Euler (Y at the top of hierarchy, applied last)
//    euler(x: 45 deg, y: 20 deg, z: 67 deg) converts to quaternion(w: 0.722, x: 0.403, y: 0.342, z: 0.447)
//*/
//vec3 rot = make_vec3(45.f, 20.f, 67.f);
//quaternion xrot = euler_to_quat(rot.x*KC_DEG2RAD, 0.f, 0.f);
//quaternion yrot = euler_to_quat(0.f, 0.f, rot.y*KC_DEG2RAD); // euler_to_quat takes roll, pitch, yaw in that order
//quaternion zrot = euler_to_quat(0.f, rot.z*KC_DEG2RAD, 0.f);
//// THIS IS XZY ORDER where Y rotation is top of hierarchy (applied last)
//quaternion expected = yrot * zrot * xrot; // The first rotation should go last here, last rotation should go first
//quaternion actual = euler_to_quat(rot*KC_DEG2RAD);
//printf("expected:       (0.722028, 0.402813, 0.341789, 0.446763)\n");
//printf("individual XZY: (%f, %f, %f, %f)\n", expected.w, expected.x, expected.y, expected.z);
//printf("allatonce  XZY: (%f, %f, %f, %f)\n", actual.w, actual.x, actual.y, actual.z);
//printf("---\n");
////std::getline(std::cin, s);
//
///*
//    TEST Euler to Quaternion then Quaternion to Euler to conversion in Euler Order XZY
//*/
//vec3 expected2 = make_vec3(220, -79, -50);
//vec3 inrad = expected2 * KC_DEG2RAD;
//quaternion xzy = euler_to_quat(inrad);
//vec3 converted_to_quat_and_back = quat_to_euler(xzy);
//vec3 indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(20.f, -79.f, 220.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, 0.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, 20.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, -90.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, -91.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, 180.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, 181.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//
//expected2 = make_vec3(-300.f, -179.f, -180.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, -181.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, 270.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//expected2 = make_vec3(-300.f, -179.f, 271.f);
//inrad = expected2 * KC_DEG2RAD;
//xzy = euler_to_quat(inrad);
//converted_to_quat_and_back = quat_to_euler(xzy);
//indegrees = converted_to_quat_and_back * KC_RAD2DEG;
//printf("expected: (%f, %f, %f)\n", expected2.x, expected2.y, expected2.z);
//printf("actual  : (%f, %f, %f)\n", indegrees.x, indegrees.y, indegrees.z);
//printf("---\n");
//
//std::getline(std::cin, s);
//return 0;
////