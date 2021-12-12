#define SML_min(a, b) ((a) < (b) ? (a) : (b))
#define SML_max(a, b) ((a) > (b) ? (a) : (b))
#define SML_abs(a) ((a) < 0.f ? (-(a)) : (a))
#define SML_clamp(x, lower, upper) SML_max((lower), SML_min((upper), (x)))

TEST_CASE("check constants", "[constants]")
{
    CHECK(SML_PI == Approx(3.1415926535f));
    CHECK(SML_TWOPI == Approx(6.28318530718f));
    CHECK(SML_DEG2RAD == Approx(0.0174532925f));
    CHECK(SML_RAD2DEG == Approx(57.2958f));

    CHECK(SML_FORWARD_VECTOR.x == 1.f);
    CHECK(SML_FORWARD_VECTOR.y == 0.f);
    CHECK(SML_FORWARD_VECTOR.z == 0.f);

    CHECK(SML_BACKWARD_VECTOR.x == -1.f);
    CHECK(SML_BACKWARD_VECTOR.y == 0.f);
    CHECK(SML_BACKWARD_VECTOR.z == 0.f);

    CHECK(SML_UP_VECTOR.x == 0.f);
    CHECK(SML_UP_VECTOR.y == 1.f);
    CHECK(SML_UP_VECTOR.z == 0.f);

    CHECK(SML_DOWN_VECTOR.x == 0.f);
    CHECK(SML_DOWN_VECTOR.y == -1.f);
    CHECK(SML_DOWN_VECTOR.z == 0.f);

    CHECK(SML_RIGHT_VECTOR.x == 0.f);
    CHECK(SML_RIGHT_VECTOR.y == 0.f);
    CHECK(SML_RIGHT_VECTOR.z == 1.f);

    CHECK(SML_LEFT_VECTOR.x == 0.f);
    CHECK(SML_LEFT_VECTOR.y == 0.f);
    CHECK(SML_LEFT_VECTOR.z == -1.f);

    CHECK(SML_min(23.f, 12.f) == 12.f);
    CHECK(SML_max(23.f, 12.f) == 23.f);
    CHECK(SML_min(-23.f, -12.f) == -23.f);
    CHECK(SML_max(-23.f, -12.f) == -12.f);
    CHECK(SML_abs(-1203.f) == 1203.f);
    CHECK(SML_abs(1203.f) == 1203.f);

    CHECK(SML_clamp(1.23f, -1.f, 1.f) == 1.f);
    CHECK(SML_clamp(1.23f, 0.f, 0.f) == 0.f);
    CHECK(SML_clamp(-0.001f, 0.f, 10.f) == 0.f);
    CHECK(SML_clamp(312, 50, 100) == 100);
}