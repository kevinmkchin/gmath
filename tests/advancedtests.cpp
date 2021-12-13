
TEST_CASE("Translation Matrix", "[matrices]")
{
    vec3 sv = { 10.f, 32.f, -100.f };
    mat4 smlTrans = TranslationMatrix(sv);
    glm::vec3 gv = { 10.f, 32.f, -100.f };
    glm::mat4 glmTrans = glm::translate(glm::mat4(1.0f), gv);
    EqualMatrices(smlTrans, glmTrans);

    sv = { 0.f, 0.f, 0.f };
    smlTrans = TranslationMatrix(sv);
    gv = { 0.f, 0.f, 0.f };
    glmTrans = glm::translate(glm::mat4(1.0f), gv);
    EqualMatrices(smlTrans, glmTrans);

    sv = { 1.f, 0.f, 1.f };
    smlTrans = TranslationMatrix(sv);
    gv = { 1.f, 0.f, 1.f };
    glmTrans = glm::translate(glm::mat4(1.0f), gv);
    EqualMatrices(smlTrans, glmTrans);

    sv = { 0.92f, -9999.f, 99.99f };
    smlTrans = TranslationMatrix(sv);
    gv = { 0.92f, -9999.f, 99.99f };
    glmTrans = glm::translate(glm::mat4(1.0f), gv);
    EqualMatrices(smlTrans, glmTrans);

    smlTrans = TranslationMatrix(0.92f, -9999.f, 99.99f);
    gv = { 0.92f, -9999.f, 99.99f };
    glmTrans = glm::translate(glm::mat4(1.0f), gv);
    EqualMatrices(smlTrans, glmTrans);

    smlTrans = TranslationMatrix(12345678912345.f, 9999999999.f, -12345678912345.f);
    gv = { 12345678912345.f, 9999999999.f, -12345678912345.f };
    glmTrans = glm::translate(glm::mat4(1.0f), gv);
    EqualMatrices(smlTrans, glmTrans);
}

TEST_CASE("Rotation Matrix", "[matrices]")
{
    SECTION("23 -23 50")
    {
        vec3 sv = { 23.f, -23.f, 50.f };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        glm::vec3 gv = { 23.f, -23.f, 50.f };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order
        EqualMatrices(smlRotate, glmRotate);
    }

    SECTION("0 0 0")
    {
        vec3 sv = { 0.f, 0.f, 0.f };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        glm::vec3 gv = { 0.f, 0.f, 0.f };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order
        EqualMatrices(smlRotate, glmRotate);
    }

    SECTION("1 -1 1")
    {
        vec3 sv = {1.f, -1.f, 1.f};
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv * SML_DEG2RAD));
        glm::vec3 gv = {1.f, -1.f, 1.f};
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order
        EqualMatrices(smlRotate, glmRotate);
    }

    SECTION("-1 -89 91")
    {
        vec3 sv = {-1.f, -89.f, 91.f};
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv * SML_DEG2RAD));
        glm::vec3 gv = {-1.f, -89.f, 91.f};
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order
        EqualMatrices(smlRotate, glmRotate);
    }

    SECTION("269 -271 179")
    {
        vec3 sv = {269.f, -271.f, 179.f};
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv * SML_DEG2RAD));
        glm::vec3 gv = {269.f, -271.f, 179.f};
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order
        EqualMatrices(smlRotate, glmRotate);
    }

    SECTION("181 180 0")
    {
        vec3 sv = {181.f, 180.f, 0.f};
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv * SML_DEG2RAD));
        glm::vec3 gv = {181.f, 180.f, 0.f};
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order
        EqualMatrices(smlRotate, glmRotate);
    }
}

TEST_CASE("Scale Matrix", "[matrices]")
{
    vec3 sv = { 0.f, 0.f, 0.f };
    mat4 smlScale = ScaleMatrix(sv);
    glm::vec3 gv = { 0.f, 0.f, 0.f };
    glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), gv);
    EqualMatrices(smlScale, glmScale);

    sv = { 1.f, -1.f, 1000.f };
    smlScale = ScaleMatrix(sv);
    gv = { 1.f, -1.f, 1000.f };
    glmScale = glm::scale(glm::mat4(1.0f), gv);
    EqualMatrices(smlScale, glmScale);

    smlScale = ScaleMatrix(12.345f, -99.99f, 1000.f);
    gv = { 12.345f, -99.99f, 1000.f };
    glmScale = glm::scale(glm::mat4(1.0f), gv);
    EqualMatrices(smlScale, glmScale);
}

TEST_CASE("Transformation Matrix", "[matrices]")
{
    SECTION("Transformation SRT 1")
    {
        vec3 sv = { 10.f, 32.f, -100.f };
        mat4 smlTrans = TranslationMatrix(sv);
        glm::vec3 gv = { 10.f, 32.f, -100.f };
        glm::mat4 glmTrans = glm::translate(glm::mat4(1.0f), gv);

        sv = { 23.f, -23.f, 50.f };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        gv = { 23.f, -23.f, 50.f };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order

        sv = { 1.f, 1.f, 1.f };
        mat4 smlScale = ScaleMatrix(sv);
        gv = { 1.f, 1.f, 1.f };
        glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), gv);

        mat4 smlTransform = smlScale * smlRotate * smlTrans;
        glm::mat4 glmTransform = glmScale * glmRotate * glmTrans;

        EqualMatrices(smlTransform, glmTransform, 0.001f);
    }

    SECTION("Transformation SRT 2")
    {
        vec3 sv = { 11.7362,24.2728,7.8319 };
        mat4 smlTrans = TranslationMatrix(sv);
        glm::vec3 gv = { 11.7362,24.2728,7.8319 };
        glm::mat4 glmTrans = glm::translate(glm::mat4(1.0f), gv);

        sv = { -47.514,120.393,23.124 };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        gv = { -47.514,120.393,23.124 };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order

        sv = { -158.053,92.727,14.78 };
        mat4 smlScale = ScaleMatrix(sv);
        gv = { -158.053,92.727,14.78 };
        glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), gv);

        mat4 smlTransform = smlScale * smlRotate * smlTrans;
        glm::mat4 glmTransform = glmScale * glmRotate * glmTrans;

        EqualMatrices(smlTransform, glmTransform, 0.001f);
    }

    SECTION("Transformation SRT 3")
    {
        vec3 sv = { 3.146,-57.039,102.719 };
        mat4 smlTrans = TranslationMatrix(sv);
        glm::vec3 gv = { 3.146,-57.039,102.719 };
        glm::mat4 glmTrans = glm::translate(glm::mat4(1.0f), gv);

        sv = { -72.573,-13.62,-66.19 };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        gv = { -72.573,-13.62,-66.19 };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order

        sv = { 4.499,2.578,2.79 };
        mat4 smlScale = ScaleMatrix(sv);
        gv = { 4.499,2.578,2.79 };
        glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), gv);

        mat4 smlTransform = smlScale * smlRotate * smlTrans;
        glm::mat4 glmTransform = glmScale * glmRotate * glmTrans;

        EqualMatrices(smlTransform, glmTransform, 0.001f);
    }

    SECTION("Transform Vector 1")
    {
        // test transforming vector by scale * rotation * translation * vector

        vec3 sv = { 3.146,-57.039,102.719 };
        mat4 smlTrans = TranslationMatrix(sv);
        glm::vec3 gv = { 3.146,-57.039,102.719 };
        glm::mat4 glmTrans = glm::translate(glm::mat4(1.0f), gv);

        sv = { -72.573,-13.62,-66.19 };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        gv = { -72.573,-13.62,-66.19 };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order

        sv = { 4.499,2.578,2.79 };
        mat4 smlScale = ScaleMatrix(sv);
        gv = { 4.499,2.578,2.79 };
        glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), gv);

        mat4 smlTransform = smlScale * smlRotate * smlTrans;
        glm::mat4 glmTransform = glmScale * glmRotate * glmTrans;

        vec4 smlResult = vec4(-1.123, 3.4, 50.5, 1.f);
        glm::vec4 glmResult = glm::vec4(-1.123, 3.4, 50.5, 1.f);
        smlResult = smlTransform * smlResult;
        glmResult = glmTransform * glmResult;
        CHECK(smlResult.x == Approx(glmResult.x));
        CHECK(smlResult.y == Approx(glmResult.y));
        CHECK(smlResult.z == Approx(glmResult.z));
        CHECK(smlResult.w == Approx(glmResult.w));
    }

    SECTION("Transform Vector 2 ")
    {
        vec3 sv = { -31.769,26.13,-26.213 };
        mat4 smlTrans = TranslationMatrix(sv);
        glm::vec3 gv = { -31.769,26.13,-26.213 };
        glm::mat4 glmTrans = glm::translate(glm::mat4(1.0f), gv);

        sv = { 8.715,14.429,33.86 };
        mat4 smlRotate = RotationMatrix(EulerToQuat(sv*SML_DEG2RAD));
        gv = { 8.715,14.429,33.86 };
        glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), gv.x * SML_DEG2RAD, glm::vec3(1,0,0));
        glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), gv.y * SML_DEG2RAD, glm::vec3(0,1,0));
        glm::mat4 zRotMat = glm::rotate(glm::mat4(1.0f), gv.z * SML_DEG2RAD, glm::vec3(0,0,1));
        glm::mat4 glmRotate = yRotMat * zRotMat * xRotMat; // XZY order

        sv = { 5.47,5.065,2.066 };
        mat4 smlScale = ScaleMatrix(sv);
        gv = { 5.47,5.065,2.066 };
        glm::mat4 glmScale = glm::scale(glm::mat4(1.0f), gv);

        mat4 smlTransform = smlScale * smlRotate * smlTrans;
        glm::mat4 glmTransform = glmScale * glmRotate * glmTrans;

        vec4 smlResult = vec4(20.719,-25.057,1.686, 1.f);
        glm::vec4 glmResult = glm::vec4(20.719,-25.057,1.686, 1.f);
        smlResult = smlTransform * smlResult;
        glmResult = glmTransform * glmResult;
        CHECK(smlResult.x == Approx(glmResult.x));
        CHECK(smlResult.y == Approx(glmResult.y));
        CHECK(smlResult.z == Approx(glmResult.z));
        CHECK(smlResult.w == Approx(glmResult.w));
    }
}

TEST_CASE("Projection Matrix Perspective", "[matrices]")
{
    SECTION("perspective 45.f")
    {
        mat4 smlProj = ProjectionMatrixPerspective(45.f, 16.f/9.f, 0.1f, 1000.f);
        glm::mat4 glmProj = glm::perspective(45.f, 16.f/9.f, 0.1f, 1000.f);
        EqualMatrices(smlProj, glmProj);
    }

    SECTION("perspective 30.f")
    {
        mat4 smlProj = ProjectionMatrixPerspective(30.f, 4.f/3.f, -100.f, 100.f);
        glm::mat4 glmProj = glm::perspective(30.f, 4.f/3.f, -100.f, 100.f);
        EqualMatrices(smlProj, glmProj);
    }
}

TEST_CASE("Projection Matrix Orthographic 2D", "[matrices]")
{
    SECTION("ortho2d 0.f 1000.f")
    {
        mat4 smlOrtho = ProjectionMatrixOrthographic2D(0.f, 1000.f, 0.f, 1000.f);
        glm::mat4 glmOrtho = glm::ortho(0.f, 1000.f, 0.f, 1000.f);
        EqualMatrices(smlOrtho, glmOrtho);
    }

    SECTION("ortho2d -300.f 300f")
    {
        mat4 smlOrtho = ProjectionMatrixOrthographic2D(-300.f, 300.f, -300.f, 300.f);
        glm::mat4 glmOrtho = glm::ortho(-300.f, 300.f, -300.f, 300.f);
        EqualMatrices(smlOrtho, glmOrtho);
    }
}

TEST_CASE("Projection Matrix Orthographic", "[matrices]")
{
    SECTION("ortho 0 1000")
    {
        mat4 smlOrtho = ProjectionMatrixOrthographic(0.f, 1000.f, 0.f, 1000.f, 0.1f, 1000.f);
        glm::mat4 glmOrtho = glm::ortho(0.f, 1000.f, 0.f, 1000.f, 0.1f, 1000.f);
        EqualMatrices(smlOrtho, glmOrtho);
    }

    SECTION("ortho -300 300")
    {
        mat4 smlOrtho = ProjectionMatrixOrthographic(-300.f, 300.f, -300.f, 300.f, 0.f, 100.f);
        glm::mat4 glmOrtho = glm::ortho(-300.f, 300.f, -300.f, 300.f, 0.f, 100.f);
        EqualMatrices(smlOrtho, glmOrtho);
    }
}

TEST_CASE("View Matrix LookAt", "[matrices]")
{
    SECTION("view 0 0 1")
    {
        mat4 smlView = ViewMatrixLookAt(vec3(0,0,0), vec3(0,0,1), vec3(0,1,0));
        glm::mat4 glmView = glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,1),glm::vec3(0,1,0));
        EqualMatrices(smlView, glmView);
    }

    SECTION("view 0 1 0")
    {
        mat4 smlView = ViewMatrixLookAt(vec3(0,0,0), vec3(0,1,0), vec3(-1,0,0));
        glm::mat4 glmView = glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,1,0),glm::vec3(-1,0,0));
        EqualMatrices(smlView, glmView);
    }

    SECTION("view 40.3 -20.123 4")
    {
        vec3 e = vec3(-3.62f,1000.1f,43.178f);
        vec3 t = vec3(40.3f,-20.123f,4.f);
        vec3 te = t - e;
        vec3 r = Cross(te, SML_UP_VECTOR);
        vec3 u = Cross(r, te);
        mat4 smlView = ViewMatrixLookAt(e,t,u);
        glm::mat4 glmView = glm::lookAt(glm::vec3(e.x,e.y,e.z),glm::vec3(t.x,t.y,t.z),glm::vec3(u.x,u.y,u.z));
        EqualMatrices(smlView, glmView);
    }

    SECTION("view random floats")
    {
        vec3 e = vec3(randf(),randf(),randf());
        vec3 t = vec3(randf(),randf(),randf());
        vec3 te = t - e;
        vec3 r = Cross(te, SML_UP_VECTOR);
        vec3 u = Cross(r, te);
        mat4 smlView = ViewMatrixLookAt(e,t,u);
        glm::mat4 glmView = glm::lookAt(glm::vec3(e.x,e.y,e.z),glm::vec3(t.x,t.y,t.z),glm::vec3(u.x,u.y,u.z));
        EqualMatrices(smlView, glmView);
    }
}


quat ExpectedSlerp(quat from, quat to, float ratio)
{
    float t = ratio;
    quat start = Normalize(from);
    quat end = Normalize(to);
    quat d = end * from.GetInverse();
    float cos_theta = Dot(start, end);
    float theta = acosf(cos_theta);
    theta *= t;
    quat d_raised_t = quat(theta, vec3(d.x, d.y, d.z));
    return d_raised_t * start;
}

TEST_CASE("SLerp", "[advanced]")
{


    SECTION("Slerp 0")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 0.f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp 0.12")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 0.12f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp -0.2")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = -0.2f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp 0.433333")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 0.433333f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp 0.5")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 0.5f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp 0.72222")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 0.72222f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp 1")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 1.f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }

    SECTION("Slerp 1.4444")
    {
        float ax = randf();
        float ay = randf();
        float az = randf();
        float aw = randf();
        quat sqa = quat(aw, ax, ay, az);
        float bx = randf();
        float by = randf();
        float bz = randf();
        float bw = randf();
        quat sqb = quat(bw, bx, by, bz);

        float ratio = 1.4444f;
        EqualQuaternions(Slerp(sqa, sqb, ratio), ExpectedSlerp(sqa, sqb, ratio));
    }
}

TEST_CASE("Lerp", "[advanced]")
{
    SECTION("lerp 0")
    {
        float from = randf();
        float to = randf();
        float ratio = 0.f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp 0.1")
    {
        float from = randf();
        float to = randf();
        float ratio = 0.1f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp 0.22222")
    {
        float from = randf();
        float to = randf();
        float ratio = 0.22222f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp 0.5")
    {
        float from = randf();
        float to = randf();
        float ratio = 0.5f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp 0.732")
    {
        float from = randf();
        float to = randf();
        float ratio = 0.732f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp 1")
    {
        float from = randf();
        float to = randf();
        float ratio = 1.f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp -0.79")
    {
        float from = randf();
        float to = randf();
        float ratio = -0.79f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }

    SECTION("lerp 1.67")
    {
        float from = randf();
        float to = randf();
        float ratio = 1.67f;
        float expect = from + ratio * (to - from);
        float actual = Lerp(from, to, ratio);
        CHECK(CompareFloats(actual, expect));
    }
}
