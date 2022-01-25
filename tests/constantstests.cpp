TEST_CASE("check constants", "[constants]")
{
    CHECK(GM_PI == Approx(3.1415926535f));
    CHECK(GM_TWOPI == Approx(6.28318530718f));
    CHECK(GM_DEG2RAD == Approx(0.0174532925f));
    CHECK(GM_RAD2DEG == Approx(57.2958f));
    CHECK(GM_D2R == Approx(0.0174532925f));
    CHECK(GM_R2D == Approx(57.2958f));

    CHECK(GM_FORWARD_VECTOR.x == 1.f);
    CHECK(GM_FORWARD_VECTOR.y == 0.f);
    CHECK(GM_FORWARD_VECTOR.z == 0.f);

    CHECK(GM_BACKWARD_VECTOR.x == -1.f);
    CHECK(GM_BACKWARD_VECTOR.y == 0.f);
    CHECK(GM_BACKWARD_VECTOR.z == 0.f);

    CHECK(GM_UP_VECTOR.x == 0.f);
    CHECK(GM_UP_VECTOR.y == 1.f);
    CHECK(GM_UP_VECTOR.z == 0.f);

    CHECK(GM_DOWN_VECTOR.x == 0.f);
    CHECK(GM_DOWN_VECTOR.y == -1.f);
    CHECK(GM_DOWN_VECTOR.z == 0.f);

    CHECK(GM_RIGHT_VECTOR.x == 0.f);
    CHECK(GM_RIGHT_VECTOR.y == 0.f);
    CHECK(GM_RIGHT_VECTOR.z == 1.f);

    CHECK(GM_LEFT_VECTOR.x == 0.f);
    CHECK(GM_LEFT_VECTOR.y == 0.f);
    CHECK(GM_LEFT_VECTOR.z == -1.f);

    CHECK(GM_min(23.f, 12.f) == 12.f);
    CHECK(GM_max(23.f, 12.f) == 23.f);
    CHECK(GM_min(-23.f, -12.f) == -23.f);
    CHECK(GM_max(-23.f, -12.f) == -12.f);
    CHECK(GM_abs(-1203.f) == 1203.f);
    CHECK(GM_abs(1203.f) == 1203.f);

    CHECK(GM_clamp(1.23f, -1.f, 1.f) == 1.f);
    CHECK(GM_clamp(1.23f, 0.f, 0.f) == 0.f);
    CHECK(GM_clamp(-0.001f, 0.f, 10.f) == 0.f);
    CHECK(GM_clamp(312, 50, 100) == 100);
}