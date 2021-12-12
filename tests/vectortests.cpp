
TEST_CASE("Vector construction", "[vectors]")
{
    SECTION("vec2 default")
    {
        vec2 v2 = vec2();
        REQUIRE(v2.x == 0.f);
        REQUIRE(v2.y == 0.f);
    }
    SECTION("vec3 default")
    {
        vec3 v3 = vec3();
        REQUIRE(v3.x == 0.f);
        REQUIRE(v3.y == 0.f);
        REQUIRE(v3.z == 0.f);
    }
    SECTION("vec4 default")
    {
        vec4 v4 = vec4();
        REQUIRE(v4.x == 0.f);
        REQUIRE(v4.y == 0.f);
        REQUIRE(v4.z == 0.f);
        REQUIRE(v4.w == 0.f);    
    }
    SECTION("ivec2 default")
    {
        ivec2 v2 = ivec2();
        REQUIRE(v2.x == 0);
        REQUIRE(v2.y == 0);
    }
    SECTION("ivec3 default")
    {
        ivec3 v3 = ivec3();
        REQUIRE(v3.x == 0);
        REQUIRE(v3.y == 0);
        REQUIRE(v3.z == 0);
    }

    SECTION("vec2 construct with values")
    {
        const float x = 1209312.f;
        const float y = -0.0004131f;
        vec2 v2 = vec2(x, y);
        REQUIRE(v2.x == x);
        REQUIRE(v2.y == y);
    }
    SECTION("vec3 construct with values")
    {
        const float x = -3.1415926535f;
        const float y = 0.789912f;
        const float z = 0.0f;
        vec3 v3 = vec3(x,y,z);
        REQUIRE(v3.x == x);
        REQUIRE(v3.y == y);
        REQUIRE(v3.z == z);
        REQUIRE(v3.roll == x);
        REQUIRE(v3.yaw == y);
        REQUIRE(v3.pitch == z);
    }
    SECTION("vec4 construct with values")
    {
        const float x = 28.555968f;
        const float y = 103.31391f;
        const float z = -86.237464f;
        const float w = 31.8898f;
        vec4 v4 = vec4(x,y,z,w);
        REQUIRE(v4.x == x);
        REQUIRE(v4.y == y);
        REQUIRE(v4.z == z);
        REQUIRE(v4.w == w);
        REQUIRE(v4.xyz.x == vec3(x,y,z).x);
        REQUIRE(v4.xyz.y == vec3(x,y,z).y);
        REQUIRE(v4.xyz.z == vec3(x,y,z).z);
    }
    SECTION("ivec2 construct with values")
    {
        const int x = -2398;
        const int y = 99999;
        ivec2 v2 = ivec2(x,y);
        REQUIRE(v2.x == x);
        REQUIRE(v2.y == y);
    }
    SECTION("ivec3 construct with values")
    {
        const int x = -2398;
        const int y = 1;
        const int z = -99999;
        ivec3 v3 = ivec3(x,y,z);
        REQUIRE(v3.x == x);
        REQUIRE(v3.y == y);
        REQUIRE(v3.z == z);
    }
}

TEST_CASE("Vector []operators", "[vectors]")
{
    SECTION("vec3 []operator")
    {
        const float x = 80.87f;
        const float y = -0.87f;
        const float z = -29.8095f;
        vec3 v3 = vec3(x, y, z);
        REQUIRE(v3[0] == x);
        REQUIRE(v3[1] == y);
        REQUIRE(v3[2] == z);
    }
    SECTION("vec4 []operator")
    {
        const float x = 80.87f;
        const float y = -30.87f;
        const float z = -19.8095f;
        const float w = 29.8095f;
        vec4 v4 = vec4(x, y, z, w);
        REQUIRE(v4[0] == x);
        REQUIRE(v4[1] == y);
        REQUIRE(v4[2] == z);
        REQUIRE(v4[3] == w);
    }
    SECTION("vec2 []operator")
    {
        const float x = 80.87f;
        const float y = 19.8095f;
        vec2 v2 = vec2(x, y);
        REQUIRE(v2[0] == x);
        REQUIRE(v2[1] == y);
    }
}

TEST_CASE("vec3 +-operators", "[vectors]")
{
    float x1 = randf();
    float y1 = randf();
    float z1 = randf();
    vec3 v1 = vec3(x1,y1,z1);

    float x2 = randf();
    float y2 = randf();
    float z2 = randf();
    vec3 v2 = vec3(x2,y2,z2);

    vec3 vecSum = v1 + v2;
    REQUIRE(vecSum.x == x1 + x2);
    REQUIRE(vecSum.y == y1 + y2);
    REQUIRE(vecSum.z == z1 + z2);

    vecSum = v1;
    vecSum += v2;
    REQUIRE(vecSum.x == x1 + x2);
    REQUIRE(vecSum.y == y1 + y2);
    REQUIRE(vecSum.z == z1 + z2);

    vecSum = v2;
    vecSum += v1;
    REQUIRE(vecSum.x == x1 + x2);
    REQUIRE(vecSum.y == y1 + y2);
    REQUIRE(vecSum.z == z1 + z2);

    vec3 vecDiff = v1 - v2;
    REQUIRE(vecDiff.x == x1 - x2);
    REQUIRE(vecDiff.y == y1 - y2);
    REQUIRE(vecDiff.z == z1 - z2);

    vecDiff = v1;
    vecDiff -= v2;
    REQUIRE(vecDiff.x == x1 - x2);
    REQUIRE(vecDiff.y == y1 - y2);
    REQUIRE(vecDiff.z == z1 - z2);

    vecDiff = v2;
    vecDiff -= v1;
    REQUIRE(vecDiff.x == x2 - x1);
    REQUIRE(vecDiff.y == y2 - y1);
    REQUIRE(vecDiff.z == z2 - z1);
}

TEST_CASE("vec4 +-operators", "[vectors]")
{
    float x1 = randf();
    float y1 = randf();
    float z1 = randf();
    float w1 = randf();
    vec4 v1 = vec4(x1,y1,z1,w1);

    float x2 = randf();
    float y2 = randf();
    float z2 = randf();
    float w2 = randf();
    vec4 v2 = vec4(x2,y2,z2,w2);

    vec4 vecSum = v1 + v2;
    REQUIRE(vecSum.x == x1 + x2);
    REQUIRE(vecSum.y == y1 + y2);
    REQUIRE(vecSum.z == z1 + z2);
    REQUIRE(vecSum.w == w1 + w2);

    vecSum = v1;
    vecSum += v2;
    REQUIRE(vecSum.x == x1 + x2);
    REQUIRE(vecSum.y == y1 + y2);
    REQUIRE(vecSum.z == z1 + z2);
    REQUIRE(vecSum.w == w1 + w2);

    vecSum = v2;
    vecSum += v1;
    REQUIRE(vecSum.x == x1 + x2);
    REQUIRE(vecSum.y == y1 + y2);
    REQUIRE(vecSum.z == z1 + z2);
    REQUIRE(vecSum.w == w1 + w2);

    vec4 vecDiff = v1 - v2;
    REQUIRE(vecDiff.x == x1 - x2);
    REQUIRE(vecDiff.y == y1 - y2);
    REQUIRE(vecDiff.z == z1 - z2);
    REQUIRE(vecDiff.w == w1 - w2);

    vecDiff = v1;
    vecDiff -= v2;
    REQUIRE(vecDiff.x == x1 - x2);
    REQUIRE(vecDiff.y == y1 - y2);
    REQUIRE(vecDiff.z == z1 - z2);
    REQUIRE(vecDiff.w == w1 - w2);

    vecDiff = v2;
    vecDiff -= v1;
    REQUIRE(vecDiff.x == x2 - x1);
    REQUIRE(vecDiff.y == y2 - y1);
    REQUIRE(vecDiff.z == z2 - z1);
    REQUIRE(vecDiff.w == w2 - w1);
}

TEST_CASE("vec3 */operators", "[vectors]")
{
    float x1 = randf();
    float y1 = randf();
    float z1 = randf();
    float w1 = randf();
    vec3 v1 = vec3(x1,y1,z1);
    float f = randf();

    vec3 vecProduct = v1 * f;
    REQUIRE(vecProduct.x == x1 * f);
    REQUIRE(vecProduct.y == y1 * f);
    REQUIRE(vecProduct.z == z1 * f);

    vecProduct = f * v1;
    REQUIRE(vecProduct.x == x1 * f);
    REQUIRE(vecProduct.y == y1 * f);
    REQUIRE(vecProduct.z == z1 * f);

    vecProduct = v1;
    vecProduct *= f;
    REQUIRE(vecProduct.x == x1 * f);
    REQUIRE(vecProduct.y == y1 * f);
    REQUIRE(vecProduct.z == z1 * f);

    if(f == 0.f)
    {
        f = 0.1234f;
    }

    vecProduct = v1 / f;
    REQUIRE(vecProduct.x == Approx(x1 / f));
    REQUIRE(vecProduct.y == Approx(y1 / f));
    REQUIRE(vecProduct.z == Approx(z1 / f));

    vecProduct = v1;
    vecProduct /= f;
    REQUIRE(vecProduct.x == Approx(x1 / f));
    REQUIRE(vecProduct.y == Approx(y1 / f));
    REQUIRE(vecProduct.z == Approx(z1 / f));
}

TEST_CASE("vec4 */operators", "[vectors]")
{
    float x1 = randf();
    float y1 = randf();
    float z1 = randf();
    float w1 = randf();
    vec4 v1 = vec4(x1,y1,z1,w1);
    float f = randf();

    vec4 vecProduct = v1 * f;
    REQUIRE(vecProduct.x == x1 * f);
    REQUIRE(vecProduct.y == y1 * f);
    REQUIRE(vecProduct.z == z1 * f);
    REQUIRE(vecProduct.w == w1 * f);

    vecProduct = f * v1;
    REQUIRE(vecProduct.x == x1 * f);
    REQUIRE(vecProduct.y == y1 * f);
    REQUIRE(vecProduct.z == z1 * f);
    REQUIRE(vecProduct.w == w1 * f);

    vecProduct = v1;
    vecProduct *= f;
    REQUIRE(vecProduct.x == x1 * f);
    REQUIRE(vecProduct.y == y1 * f);
    REQUIRE(vecProduct.z == z1 * f);
    REQUIRE(vecProduct.w == w1 * f);

    if(f == 0.f)
    {
        f = 0.1234f;
    }

    vecProduct = v1 / f;
    REQUIRE(vecProduct.x == Approx(x1 / f));
    REQUIRE(vecProduct.y == Approx(y1 / f));
    REQUIRE(vecProduct.z == Approx(z1 / f));
    REQUIRE(vecProduct.w == Approx(w1 / f));

    vecProduct = v1;
    vecProduct /= f;
    REQUIRE(vecProduct.x == Approx(x1 / f));
    REQUIRE(vecProduct.y == Approx(y1 / f));
    REQUIRE(vecProduct.z == Approx(z1 / f));
    REQUIRE(vecProduct.w == Approx(w1 / f));
}

TEST_CASE("vec3 Magnitude", "[vectors]")
{
    vec3 a = { -7.2171,50.8564,-79.2506 };
    REQUIRE(Magnitude(a) == Approx( 94.4411 ));

    a = { 0,0,0 };
    REQUIRE(Magnitude(a) == 0);

    a = { 0,-1000,0 };
    REQUIRE(Magnitude(a) == 1000);
}

TEST_CASE("vec4 Magnitude", "[vectors]")
{
    vec4 a = { -26.5442,-98.014,21.6079,-8.7283 };
    REQUIRE(Magnitude(a) == Approx( 104.185 ));

    a = { 0,0,0 , 0 };
    REQUIRE(Magnitude(a) == 0);

    a = { 0,-1000,0 , 0 };
    REQUIRE(Magnitude(a) == 1000);
}

TEST_CASE("vec2 Magnitude", "[vectors]")
{
    vec2 a = { -26.5442,-98.014 };
    REQUIRE(Magnitude(a) == Approx( 101.545 ));

    a = { 0,0 };
    REQUIRE(Magnitude(a) == 0);

    a = { -1000,0 };
    REQUIRE(Magnitude(a) == 1000);
}

TEST_CASE("vec3 Dot", "[vectors]")
{
    vec3 a = vec3(-56.6139,26.0876,60.963);
    vec3 b = vec3(-29.9211,30.9289,-43.0554);
    REQUIRE(Dot(a, b) == Approx(-123.975f));

    a = vec3( -52.394,-54.4943,-7.7292 );
    b = vec3( 31.1434,-4.9766,-57.8896 );
    REQUIRE(Dot(a, b) == Approx( -913.091 ));

    a = vec3( 0, 0, 0 );
    b = vec3( 31.1434,-4.9766,-57.8896 );
    REQUIRE(Dot(a, b) == 0.f);

    a = vec3( 0, 1, 0 );
    b = vec3( 31.1434,-4.9766,-57.8896 );
    REQUIRE(Dot(a, b) == Approx(-4.9766));

    a = vec3( 10000, -10000, 0 );
    b = vec3( 31.1434,-4.9766,-57.8896 );
    REQUIRE(Dot(a, b) == Approx(361200));
}
TEST_CASE("vec4 Dot", "[vectors]")
{
    vec4 a = {-61.3919, 6.3233, -55.6448, 51.4228};
    vec4 b = {16.2629, -29.4638, 29.0174, -8.9311};
    REQUIRE(Dot(a, b) == Approx(-3258.65f));

    a = {86.7134, -0.5726, -1.0076, -92.8532};
    b = {-26.5442, -98.014, 21.6079, -8.7283};
    REQUIRE(Dot(a, b) == Approx( -1456.94 ));

    a = vec4( 0, 0, 0, 0 );
    b = {-26.5442, -98.014, 21.6079, -8.7283};
    REQUIRE(Dot(a, b) == 0.f);

    a = vec4( 0, 1, 0, 1 );
    b = {-26.5442, -98.014, 21.6079, -8.7283};
    REQUIRE(Dot(a, b) == Approx(-106.7423));
}
TEST_CASE("vec2 Dot", "[vectors]")
{
    vec2 a = vec2(-86.5802,-12.6629);
    vec2 b = vec2(-18.6965,75.2702);
    REQUIRE(Dot(a, b) == Approx(665.608f));

    a = vec2( 0, 0);
    b = vec2( 31.1434,-4.9766 );
    REQUIRE(Dot(a, b) == 0.f);

    a = vec2( 1, 0);
    b = vec2( 31.1434,-4.9766 );
    REQUIRE(Dot(a, b) == Approx(31.1434));

    a = vec2( 10000, 0);
    b = vec2( 31.1434, -57.8896 );
    REQUIRE(Dot(a, b) == Approx(311434));
}



TEST_CASE("vec3 normalize", "[vectors]")
{
    vec3 a = vec3(23.f, 13.f, -0.313f);
    REQUIRE(Normalize(a).x == Approx(0.870502f));
    REQUIRE(Normalize(a).y == Approx(0.492023f));
    REQUIRE(Normalize(a).z == Approx(-0.0118464f));

    a = vec3(50.2f, -23.1f, 123.74f);
    REQUIRE(Normalize(a).x == Approx(0.370429f));
    REQUIRE(Normalize(a).y == Approx(-0.170456f));
    REQUIRE(Normalize(a).z == Approx(0.91308f));

    a = vec3(0.000001f, 0.f, -0.f);
    REQUIRE(Normalize(a).x == Approx(1.f));
    REQUIRE(Normalize(a).y == Approx(0.f));
    REQUIRE(Normalize(a).z == Approx(0.f));

    a = vec3(0.f, 0.f, 0.f);
    REQUIRE(Normalize(a).x == 0.f);
    REQUIRE(Normalize(a).y == 0.f);
    REQUIRE(Normalize(a).z == 0.f);
}

TEST_CASE("vec4 normalize", "[vectors]")
{
    vec4 a = vec4(-31.f, 12.f, 99.f, -5.f);
    REQUIRE(Normalize(a).x == Approx(-0.296505f));
    REQUIRE(Normalize(a).y == Approx(0.114776f));
    REQUIRE(Normalize(a).z == Approx(0.946902f));
    REQUIRE(Normalize(a).w == Approx(-0.0478234f));

    a = vec4(9.f, -5.f, 0.f, 8.f);
    REQUIRE(Normalize(a).x == Approx(0.690268f));
    REQUIRE(Normalize(a).y == Approx(-0.383482f));
    REQUIRE(Normalize(a).z == Approx(0.f));
    REQUIRE(Normalize(a).w == Approx(0.613572f));

    a = vec4(0.f, 0.000001f, 0.f, 0.f);
    REQUIRE(Normalize(a).x == Approx(0.f));
    REQUIRE(Normalize(a).y == Approx(1.f));
    REQUIRE(Normalize(a).z == Approx(0.f));
    REQUIRE(Normalize(a).w == Approx(0.f));

    a = vec4(0.f, 0.f, 0.f, 0.f);
    REQUIRE(Normalize(a).x == 0.f);
    REQUIRE(Normalize(a).y == 0.f);
    REQUIRE(Normalize(a).z == 0.f);
    REQUIRE(Normalize(a).w == 0.f);
}

TEST_CASE("vec3 lerp", "[vectors]")
{
    glm::vec3 glmA = { 23.f, 11.54f, -5.f };
    glm::vec3 glmB = { -7.4649,-19.9294,-13.0428 };
    vec3 smlA = { 23.f, 11.54f, -5.f };
    vec3 smlB = { -7.4649,-19.9294,-13.0428 };

    REQUIRE(glm::mix(glmA, glmB, 0.5f).x == Lerp(smlA, smlB, 0.5f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).y == Lerp(smlA, smlB, 0.5f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).z == Lerp(smlA, smlB, 0.5f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.f).x == Lerp(smlA, smlB, 0.f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.f).y == Lerp(smlA, smlB, 0.f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.f).z == Lerp(smlA, smlB, 0.f).z);

    REQUIRE(glm::mix(glmA, glmB, 1.0f).x == Lerp(smlA, smlB, 1.0f).x);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).y == Lerp(smlA, smlB, 1.0f).y);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).z == Lerp(smlA, smlB, 1.0f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.333f).x == Lerp(smlA, smlB, 0.333f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).y == Lerp(smlA, smlB, 0.333f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).z == Lerp(smlA, smlB, 0.333f).z);

    float f = randf();
    REQUIRE(glm::mix(glmA, glmB, f).x == Lerp(smlA, smlB, f).x);
    REQUIRE(glm::mix(glmA, glmB, f).y == Lerp(smlA, smlB, f).y);
    REQUIRE(glm::mix(glmA, glmB, f).z == Lerp(smlA, smlB, f).z);


    glmA = { 25.4655,18.0719,-3.435 };
    glmB = { 12.9089,-39.8666,-33.9054 };
    smlA = { 25.4655,18.0719,-3.435 };
    smlB = { 12.9089,-39.8666,-33.9054 };

    REQUIRE(glm::mix(glmA, glmB, 0.5f).x == Lerp(smlA, smlB, 0.5f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).y == Lerp(smlA, smlB, 0.5f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).z == Lerp(smlA, smlB, 0.5f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.f).x == Lerp(smlA, smlB, 0.f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.f).y == Lerp(smlA, smlB, 0.f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.f).z == Lerp(smlA, smlB, 0.f).z);

    REQUIRE(glm::mix(glmA, glmB, 1.0f).x == Lerp(smlA, smlB, 1.0f).x);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).y == Lerp(smlA, smlB, 1.0f).y);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).z == Lerp(smlA, smlB, 1.0f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.333f).x == Lerp(smlA, smlB, 0.333f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).y == Lerp(smlA, smlB, 0.333f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).z == Lerp(smlA, smlB, 0.333f).z);

    f = randf();
    REQUIRE(glm::mix(glmA, glmB, f).x == Lerp(smlA, smlB, f).x);
    REQUIRE(glm::mix(glmA, glmB, f).y == Lerp(smlA, smlB, f).y);
    REQUIRE(glm::mix(glmA, glmB, f).z == Lerp(smlA, smlB, f).z);
}

TEST_CASE("vec4 lerp", "[vectors]")
{
    glm::vec4 glmA = { -18.7552,21.9275,-2.6982,-38.184 };
    glm::vec4 glmB = { -3.1036,1.8474,27.2853,3.4404 };
    vec4 smlA = { -18.7552,21.9275,-2.6982,-38.184 };
    vec4 smlB = { -3.1036,1.8474,27.2853,3.4404 };

    REQUIRE(glm::mix(glmA, glmB, 0.5f).x == Lerp(smlA, smlB, 0.5f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).y == Lerp(smlA, smlB, 0.5f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).z == Lerp(smlA, smlB, 0.5f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.f).x == Lerp(smlA, smlB, 0.f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.f).y == Lerp(smlA, smlB, 0.f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.f).z == Lerp(smlA, smlB, 0.f).z);

    REQUIRE(glm::mix(glmA, glmB, 1.0f).x == Lerp(smlA, smlB, 1.0f).x);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).y == Lerp(smlA, smlB, 1.0f).y);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).z == Lerp(smlA, smlB, 1.0f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.333f).x == Lerp(smlA, smlB, 0.333f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).y == Lerp(smlA, smlB, 0.333f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).z == Lerp(smlA, smlB, 0.333f).z);

    float f = randf();
    REQUIRE(glm::mix(glmA, glmB, f).x == Lerp(smlA, smlB, f).x);
    REQUIRE(glm::mix(glmA, glmB, f).y == Lerp(smlA, smlB, f).y);
    REQUIRE(glm::mix(glmA, glmB, f).z == Lerp(smlA, smlB, f).z);

    glmA = { -36.212,33.1605,10.2079,1.0178 };
    glmB = { 10.3152,8.1638,-10.3037,-12.5339 };
    smlA = { -36.212,33.1605,10.2079,1.0178 };
    smlB = { 10.3152,8.1638,-10.3037,-12.5339 };

    REQUIRE(glm::mix(glmA, glmB, 0.5f).x == Lerp(smlA, smlB, 0.5f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).y == Lerp(smlA, smlB, 0.5f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.5f).z == Lerp(smlA, smlB, 0.5f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.f).x == Lerp(smlA, smlB, 0.f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.f).y == Lerp(smlA, smlB, 0.f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.f).z == Lerp(smlA, smlB, 0.f).z);

    REQUIRE(glm::mix(glmA, glmB, 1.0f).x == Lerp(smlA, smlB, 1.0f).x);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).y == Lerp(smlA, smlB, 1.0f).y);
    REQUIRE(glm::mix(glmA, glmB, 1.0f).z == Lerp(smlA, smlB, 1.0f).z);

    REQUIRE(glm::mix(glmA, glmB, 0.333f).x == Lerp(smlA, smlB, 0.333f).x);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).y == Lerp(smlA, smlB, 0.333f).y);
    REQUIRE(glm::mix(glmA, glmB, 0.333f).z == Lerp(smlA, smlB, 0.333f).z);

    f = randf();
    REQUIRE(glm::mix(glmA, glmB, f).x == Lerp(smlA, smlB, f).x);
    REQUIRE(glm::mix(glmA, glmB, f).y == Lerp(smlA, smlB, f).y);
    REQUIRE(glm::mix(glmA, glmB, f).z == Lerp(smlA, smlB, f).z);
}

TEST_CASE("vec3 cross product", "[vectors]")
{
    vec3 a = {-7.2171,50.8564,-79.2506};
    vec3 b = {72.247,16.2563,41.809};
    REQUIRE(Cross(a, b).x == Approx(3414.57675));
    REQUIRE(Cross(a, b).y == Approx(-5423.87836));
    REQUIRE(Cross(a, b).z == Approx(-3791.54567));
}
