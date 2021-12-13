void EqualMatrices(mat3 lhs, mat3 rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = (float*)&rhs;
    for(int i = 0; i < 9; ++i)
    {
        float l = *(lptr + i);
        float r = *(rptr + i);
        CHECK(CompareFloats(l, r));
    }
}

void EqualMatrices(mat3 lhs, glm::mat3 rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = glm::value_ptr(rhs);
    for(int i = 0; i < 9; ++i)
    {
        float l = *(lptr + i);
        float r = *(rptr + i);
        CHECK(CompareFloats(l, r));
    }
}

void EqualMatrices(mat4 lhs, mat4 rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = (float*)&rhs;
    for(int i = 0; i < 16; ++i)
    {
        float l = *(lptr + i);
        float r = *(rptr + i);
        CHECK(CompareFloats(l, r));
    }
}

void EqualMatrices(mat4 lhs, glm::mat4 rhs)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = glm::value_ptr(rhs);
    for(int i = 0; i < 16; ++i)
    {
        float l = *(lptr + i);
        float r = *(rptr + i);
        CHECK(CompareFloats(l, r));
    }
}

void EqualMatrices(mat4 lhs, glm::mat4 rhs, float ep)
{
    /* Compares actual memory */
    float* lptr = (float*)&lhs;
    float* rptr = glm::value_ptr(rhs);
    for(int i = 0; i < 16; ++i)
    {
        float l = *(lptr + i);
        float r = *(rptr + i);
        CHECK(CompareFloats(l, r, ep));
    }
}

TEST_CASE("matrix construction", "[matrices]")
{
    SECTION("default mat3")
    {
        mat3 smlId3;
        glm::mat3 glmId3 = glm::mat3(1.0f);
        EqualMatrices(smlId3, glmId3);
    }

    SECTION("mat3 with values")
    {
        float values3[9] = { -28.4425,-18.9364,-11.3309,8.3001,17.8063,-3.1234,6.2378,-0.9961,1.7009 };
        mat3 X;
        memcpy(&X, values3, sizeof(values3));
        glm::mat3 Y = glm::make_mat3(values3);
        EqualMatrices(X, Y);
    }

    SECTION("default mat4")
    {
        mat4 smlId;
        glm::mat4 glmId = glm::mat4(1.0f);
        EqualMatrices(smlId, glmId);
    }

    SECTION("mat4 with values")
    {
        float values4[16] = { -49.7159,29.482,-22.0336,-20.6768,46.2668,-4.8843,14.7134,-29.0603,-3.5923,-12.8735,-6.7302,-5.8481,-15.7787,-2.2624,-12.0854,6.4252 };
        mat4 A;
        memcpy(&A, values4, sizeof(values4));
        glm::mat4 B = glm::make_mat4(values4);
        EqualMatrices(A, B);
    }

    SECTION("mat3 from mat4")
    {
        float values[16] = { -20.5667,1.1961,4.9842,8.568,-42.8199,-30.0301,-45.2805,-2.3747,44.2903,7.7129,16.9976,-7.4345,-47.6795,1.7379,14.7239,38.5073};
        mat4 A;
        memcpy(&A, values, sizeof(values));
        mat3 B = mat3(A);
        CHECK(A[0][0] == B[0][0]);
        CHECK(A[0][1] == B[0][1]);
        CHECK(A[0][2] == B[0][2]);
        CHECK(A[1][0] == B[1][0]);
        CHECK(A[1][1] == B[1][1]);
        CHECK(A[1][2] == B[1][2]);
        CHECK(A[2][0] == B[2][0]);
        CHECK(A[2][1] == B[2][1]);
        CHECK(A[2][2] == B[2][2]);
        CHECK(A[2][2] == B[2][2]);
    }

    SECTION("mat4 from mat3 back to mat4")
    {
        float values[9] = { -40.8881,-1.2438,-20.0107,-1.0601,-21.6366,-10.1375,25.5236,-1.1968,-2.1366 };
        mat3 A;
        memcpy(&A, values, sizeof(values));
        mat4 B = mat4(A);
        CHECK(A[0][0] == B[0][0]);
        CHECK(A[0][1] == B[0][1]);
        CHECK(A[0][2] == B[0][2]);
        CHECK(A[1][0] == B[1][0]);
        CHECK(A[1][1] == B[1][1]);
        CHECK(A[1][2] == B[1][2]);
        CHECK(A[2][0] == B[2][0]);
        CHECK(A[2][1] == B[2][1]);
        CHECK(A[2][2] == B[2][2]);
        CHECK(A[2][2] == B[2][2]);
        CHECK(0.f == B[0][3]);
        CHECK(0.f == B[1][3]);
        CHECK(0.f == B[2][3]);
        CHECK(0.f == B[3][0]);
        CHECK(0.f == B[3][1]);
        CHECK(0.f == B[3][2]);
        CHECK(1.f == B[3][3]);

        mat3 backToA = mat3(B);
        EqualMatrices(A, backToA);
    }
}

TEST_CASE("matrix []operator", "[matrices]")
{
    SECTION("mat3 []operator")
    {
        float values[9] = { -40.8881,-1.2438,-20.0107,-1.0601,-21.6366,-10.1375,25.5236,-1.1968,-2.1366 };
        mat3 A;
        memcpy(&A, values, sizeof(values));
        CHECK(A[0][0] == values[0]);
        CHECK(A[0][1] == values[1]);
        CHECK(A[0][2] == values[2]);
        CHECK(A[1][0] == values[3]);
        CHECK(A[1][1] == values[4]);
        CHECK(A[1][2] == values[5]);
        CHECK(A[2][0] == values[6]);
        CHECK(A[2][1] == values[7]);
        CHECK(A[2][2] == values[8]);
    }

    SECTION("mat4 []operator")
    {
        float values[16] = { -13.5259,46.896,-39.7194,-37.9357,-6.3035,39.0683,-37.5612,-15.4636,-21.3852,-17.1204,-42.0679,-22.6063,49.3979,14.7548,-24.8728,39.3605 };
        mat4 A;
        memcpy(&A, values, sizeof(values));
        CHECK(A[0][0] == values[0]);
        CHECK(A[0][1] == values[1]);
        CHECK(A[0][2] == values[2]);
        CHECK(A[0][3] == values[3]);
        CHECK(A[1][0] == values[4]);
        CHECK(A[1][1] == values[5]);
        CHECK(A[1][2] == values[6]);
        CHECK(A[1][3] == values[7]);
        CHECK(A[2][0] == values[8]);
        CHECK(A[2][1] == values[9]);
        CHECK(A[2][2] == values[10]);
        CHECK(A[2][3] == values[11]);
        CHECK(A[3][0] == values[12]);
        CHECK(A[3][1] == values[13]);
        CHECK(A[3][2] == values[14]);
        CHECK(A[3][3] == values[15]);
    }
}

TEST_CASE("matrix transpose", "[matrices]")
{
    SECTION("mat3 transpose")
    {
        float values3[9] = { 43.3388,-24.2657,-24.578,-40.3444,-9.2415,36.0978,-44.4972,-40.4869,14.7503 };
        mat3 X;
        memcpy(&X, values3, sizeof(values3));
        glm::mat3 Y = glm::make_mat3(values3);
        EqualMatrices(X.GetTranspose(), glm::transpose(Y));
    }

    SECTION("mat4 transpose")
    {
        float values4[16] = { 0.6568,6.9482,13.0404,4.7824,8.7806,-38.0424,-16.1504,-33.9266,46.1679,4.0745,-31.8799,-44.0691,48.6592,37.7199,-16.8735,27.4653 };
        mat4 A;
        memcpy(&A, values4, sizeof(values4));
        glm::mat4 B = glm::make_mat4(values4);
        EqualMatrices(A.GetTranspose(), glm::transpose(B));
    }
}

TEST_CASE("mat3 multiplication")
{
        SECTION("mat3 *operator")
    {
        float valueA[9] = { -11.448,17.0307,-2.3019,-9.4354,7.0369,1.0214,21.6274,3.9856,-8.3734 };
        float valueB[9] = { -7.1151,-55.3905,29.3006,10.2583,-47.0294,19.9018,-43.7839,9.319,4.7907 };

        mat3 A;
        mat3 B;
        memcpy(&A, valueA, sizeof(valueA));
        memcpy(&B, valueB, sizeof(valueB));
        glm::mat3 glmA = glm::make_mat3(valueA);
        glm::mat3 glmB = glm::make_mat3(valueB);

        mat3 smlProduct = A * B;
        glm::mat3 glmProduct = glmA * glmB;

        EqualMatrices(smlProduct, glmProduct);
    }

    SECTION("mat3 *=operator")
    {
        float valueA[9] = { -11.448,17.0307,-2.3019,-9.4354,7.0369,1.0214,21.6274,3.9856,-8.3734 };
        float valueB[9] = { -7.1151,-55.3905,29.3006,10.2583,-47.0294,19.9018,-43.7839,9.319,4.7907 };

        mat3 A;
        mat3 B;
        memcpy(&A, valueA, sizeof(valueA));
        memcpy(&B, valueB, sizeof(valueB));
        glm::mat3 glmA = glm::make_mat3(valueA);
        glm::mat3 glmB = glm::make_mat3(valueB);

        A *= B;
        glmA *= glmB;

        EqualMatrices(A, glmA);
    }

    SECTION("mat3 * vec4")
    {
        float valueA[9] = { -11.448,17.0307,-2.3019,-9.4354,7.0369,1.0214,21.6274,3.9856,-8.3734 };
        mat3 A;
        memcpy(&A, valueA, sizeof(valueA));
        vec3 v = vec3(-91.4206,26.7128,32.1783);
        glm::mat3 glmA = glm::make_mat3(valueA);
        glm::vec3 glmv = glm::vec3(-91.4206,26.7128,32.1783);
        vec3 smlProduct = A * v;
        glm::vec3 glmProduct = glmA * glmv;
        CHECK(smlProduct.x == glmProduct.x);
        CHECK(smlProduct.y == glmProduct.y);
        CHECK(smlProduct.z == glmProduct.z);
    }
}

TEST_CASE("mat4 multiplication")
{
    SECTION("mat4 *operator")
    {
        float valueA[16] = { -11.448,17.0307,-2.3019,-9.4354,7.0369,1.0214,21.6274,3.9856,-8.3734,11.6748,6.4804,-6.3727,-2.049,5.4984,19.3069,5.0344 };
        float valueB[16] = { -7.1151,-55.3905,29.3006,10.2583,-47.0294,19.9018,-43.7839,9.319,4.7907,-30.121,6.0986,69.147,1.7965,-7.8994,-13.7642,-6.416 };

        mat4 A;
        mat4 B;
        memcpy(&A, valueA, sizeof(valueA));
        memcpy(&B, valueB, sizeof(valueB));
        glm::mat4 glmA = glm::make_mat4(valueA);
        glm::mat4 glmB = glm::make_mat4(valueB);

        mat4 smlProduct = A * B;
        glm::mat4 glmProduct = glmA * glmB;

        EqualMatrices(smlProduct, glmProduct);
    }

    SECTION("mat4 *=operator")
    {
        float valueA[16] = { -11.448,17.0307,-2.3019,-9.4354,7.0369,1.0214,21.6274,3.9856,-8.3734,11.6748,6.4804,-6.3727,-2.049,5.4984,19.3069,5.0344 };
        float valueB[16] = { -7.1151,-55.3905,29.3006,10.2583,-47.0294,19.9018,-43.7839,9.319,4.7907,-30.121,6.0986,69.147,1.7965,-7.8994,-13.7642,-6.416 };

        mat4 A;
        mat4 B;
        memcpy(&A, valueA, sizeof(valueA));
        memcpy(&B, valueB, sizeof(valueB));
        glm::mat4 glmA = glm::make_mat4(valueA);
        glm::mat4 glmB = glm::make_mat4(valueB);

        A *= B;
        glmA *= glmB;

        EqualMatrices(A, glmA);
    }

    SECTION("mat4 * vec4")
    {
        float valueA[16] = { -11.448,17.0307,-2.3019,-9.4354,7.0369,1.0214,21.6274,3.9856,-8.3734,11.6748,6.4804,-6.3727,-2.049,5.4984,19.3069,5.0344 };
        mat4 A;
        memcpy(&A, valueA, sizeof(valueA));
        vec4 v = vec4(-91.4206,26.7128,32.1783,13.7332);
        glm::mat4 glmA = glm::make_mat4(valueA);
        glm::vec4 glmv = glm::vec4(-91.4206,26.7128,32.1783,13.7332);
        vec4 smlProduct = A * v;
        glm::vec4 glmProduct = glmA * glmv;
        CHECK(smlProduct.x == glmProduct.x);
        CHECK(smlProduct.y == glmProduct.y);
        CHECK(smlProduct.z == glmProduct.z);
        CHECK(smlProduct.w == glmProduct.w);
    }
}
