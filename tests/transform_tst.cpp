#include "Transform.h"

#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

// Test fixture for Transform class
class TransformTest : public ::testing::Test
{
  protected:
  void SetUp() override
  {
    // Helper epsilon for floating point comparisons
    epsilon = 0.0001f;
  }

  void TearDown() override {}

  // Helper to compare vec3
  bool Vec3Near(const glm::vec3& a, const glm::vec3& b, float eps = 0.0001f)
  {
    return glm::length(a - b) < eps;
  }

  // Helper to compare quaternions
  bool QuatNear(const glm::quat& a, const glm::quat& b, float eps = 0.0001f)
  {
    return glm::length(a - b) < eps || glm::length(a + b) < eps;  // Account for double cover
  }

  // Helper to compare matrices
  bool Mat4Near(const glm::mat4& a, const glm::mat4& b, float eps = 0.0001f)
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (std::abs(a[i][j] - b[i][j]) > eps)
          return false;
      }
    }
    return true;
  }

  float epsilon;
};

// =============================================================================
// CONSTRUCTOR TESTS
// =============================================================================

TEST_F(TransformTest, DefaultConstructor)
{
  // Transform should initialize to:
  // - positposition: (0, 0, 0)
  // - rotation: identity quaternion (0, 0, 0, 1)
  // - scale: (1, 1, 1)
  Transform t;
  EXPECT_TRUE(Vec3Near(t.position(), glm::vec3(0.0f)));
  EXPECT_TRUE(QuatNear(t.rotation(), glm::quat(1.0f, 0.0f, 0.0f, 0.0f)));
  EXPECT_TRUE(Vec3Near(t.scale(), glm::vec3(1.0f)));
}

TEST_F(TransformTest, ParameterizedConstructor)
{
  glm::vec3 pos(1.0f, 2.0f, 3.0f);
  glm::quat rot = glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0));
  glm::vec3 scale(2.0f, 2.0f, 2.0f);
  Transform t(pos, rot, scale);
  EXPECT_TRUE(Vec3Near(t.position(), pos));
  EXPECT_TRUE(QuatNear(t.rotation(), rot));
  EXPECT_TRUE(Vec3Near(t.scale(), scale));
}

TEST_F(TransformTest, CopyConstructor)
{
  Transform t1;
  t1.setPosition(glm::vec3(5.0f, 6.0f, 7.0f));
  Transform t2(t1);
  EXPECT_TRUE(Vec3Near(t2.position(), glm::vec3(5.0f, 6.0f, 7.0f)));
}

// =============================================================================
// POSITION/TRANSLATION TESTS
// =============================================================================

TEST_F(TransformTest, SetAndposition)
{
  Transform t;
  glm::vec3 newPos(10.0f, 20.0f, 30.0f);
  t.setPosition(newPos);
  EXPECT_TRUE(Vec3Near(t.position(), newPos));
}

TEST_F(TransformTest, Translate)
{
  Transform t;
  t.setPosition(glm::vec3(1.0f, 2.0f, 3.0f));
  t.translate(glm::vec3(5.0f, 5.0f, 5.0f));
  EXPECT_TRUE(Vec3Near(t.position(), glm::vec3(6.0f, 7.0f, 8.0f)));
}

TEST_F(TransformTest, TranslateLocal)
{
  // Should translate in local space (relative to rotation)

  // TODO: Implement TranslateLocal(vec3)
  // Transform t;
  // // Rotate 90 degrees around Y axis
  // t.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
  // // Translate forward (local Z) should move in world -X direction
  // t.TranslateLocal(glm::vec3(0, 0, 1));
  // EXPECT_TRUE(Vec3Near(t.position(), glm::vec3(-1.0f, 0.0f, 0.0f), 0.01f));
}

// =============================================================================
// ROTATION TESTS
// =============================================================================

TEST_F(TransformTest, SetAndrotation)
{
  // Should be able to set and retrieve rotation as quaternion

  // TODO: Implement SetRotation(quat) and rotation()
  // Transform t;
  // glm::quat rot = glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0));
  // t.SetRotation(rot);
  // EXPECT_TRUE(QuatNear(t.rotation(), rot));
}

TEST_F(TransformTest, SetRotationFromEuler)
{
  // Should be able to set rotation from euler angles (pitch, yaw, roll)

  // TODO: Implement SetRotationEuler(vec3) or SetRotationEuler(float, float, float)
  // Transform t;
  // t.SetRotationEuler(glm::vec3(0, glm::radians(90.0f), 0)); // 90 degrees around Y
  // glm::quat expected = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0));
  // EXPECT_TRUE(QuatNear(t.rotation(), expected));
}

TEST_F(TransformTest, rotationAsEuler)
{
  // Should be able to get rotation as euler angles

  // TODO: Implement rotationEuler()
  // Transform t;
  // t.SetRotation(glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0)));
  // glm::vec3 euler = t.rotationEuler();
  // EXPECT_NEAR(euler.y, glm::radians(45.0f), epsilon);
}

TEST_F(TransformTest, Rotate)
{
  // Should apply a rotation delta (quaternion multiplication)

  // TODO: Implement Rotate(quat)
  // Transform t;
  // glm::quat rot1 = glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0));
  // glm::quat rot2 = glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0));
  // t.SetRotation(rot1);
  // t.Rotate(rot2);
  // glm::quat expected = rot2 * rot1; // Note: quaternion multiplication order
  // EXPECT_TRUE(QuatNear(t.rotation(), expected));
}

TEST_F(TransformTest, RotateAroundAxis)
{
  // Should rotate around a specific axis by an angle

  // TODO: Implement RotateAxis(vec3 axis, float angle)
  // Transform t;
  // t.RotateAxis(glm::vec3(0, 1, 0), glm::radians(90.0f));
  // glm::quat expected = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0));
  // EXPECT_TRUE(QuatNear(t.rotation(), expected));
}

TEST_F(TransformTest, RotateEuler)
{
  // Should rotate by euler angle deltas

  // TODO: Implement RotateEuler(vec3) or RotateEuler(float, float, float)
  // Transform t;
  // t.RotateEuler(glm::vec3(0, glm::radians(45.0f), 0));
  // t.RotateEuler(glm::vec3(0, glm::radians(45.0f), 0));
  // // Should now be rotated 90 degrees around Y
  // glm::vec3 euler = t.rotationEuler();
  // EXPECT_NEAR(euler.y, glm::radians(90.0f), 0.01f);
}

TEST_F(TransformTest, LookAt)
{
  // Should orient the transform to look at a target point

  // TODO: Implement LookAt(vec3 target) or LookAt(vec3 target, vec3 up)
  // Transform t;
  // t.SetPosition(glm::vec3(0, 0, 0));
  // t.LookAt(glm::vec3(1, 0, 0)); // Look at point on +X axis
  // // Forward direction should point towards target
  // glm::vec3 forward = t.GetForward();
  // EXPECT_TRUE(Vec3Near(forward, glm::vec3(1, 0, 0)));
}

// =============================================================================
// SCALE TESTS
// =============================================================================

TEST_F(TransformTest, SetAndscale)
{
  // Should be able to set and retrieve scale

  // TODO: Implement SetScale(vec3) and scale()
  // Transform t;
  // glm::vec3 newScale(2.0f, 3.0f, 4.0f);
  // t.SetScale(newScale);
  // EXPECT_TRUE(Vec3Near(t.scale(), newScale));
}

TEST_F(TransformTest, SetUniformScale)
{
  // Should be able to set uniform scale with single value

  // TODO: Implement SetScale(float)
  // Transform t;
  // t.SetScale(5.0f);
  // EXPECT_TRUE(Vec3Near(t.scale(), glm::vec3(5.0f)));
}

TEST_F(TransformTest, Scale)
{
  // Should multiply current scale by a factor

  // TODO: Implement Scale(vec3) or Scale(float)
  // Transform t;
  // t.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
  // t.Scale(glm::vec3(2.0f, 3.0f, 1.0f));
  // EXPECT_TRUE(Vec3Near(t.scale(), glm::vec3(4.0f, 6.0f, 2.0f)));
}

// =============================================================================
// DIRECTION VECTOR TESTS
// =============================================================================

TEST_F(TransformTest, GetForward)
{
  // Should return the forward direction vector (local -Z in world space)

  // TODO: Implement GetForward()
  // Transform t;
  // // Default forward should be (0, 0, -1) in OpenGL or (0, 0, 1) depending on convention
  // glm::vec3 forward = t.GetForward();
  // EXPECT_TRUE(Vec3Near(forward, glm::vec3(0, 0, -1)) ||
  //             Vec3Near(forward, glm::vec3(0, 0, 1)));
}

TEST_F(TransformTest, GetRight)
{
  // Should return the right direction vector (local +X in world space)

  // TODO: Implement GetRight()
  // Transform t;
  // glm::vec3 right = t.GetRight();
  // EXPECT_TRUE(Vec3Near(right, glm::vec3(1, 0, 0)));
}

TEST_F(TransformTest, GetUp)
{
  // Should return the up direction vector (local +Y in world space)

  // TODO: Implement GetUp()
  // Transform t;
  // glm::vec3 up = t.GetUp();
  // EXPECT_TRUE(Vec3Near(up, glm::vec3(0, 1, 0)));
}

TEST_F(TransformTest, DirectionsAfterRotation)
{
  // Direction vectors should update correctly after rotation

  // TODO: Test that GetForward(), GetRight(), GetUp() work after rotation
  // Transform t;
  // // Rotate 90 degrees around Y axis
  // t.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
  // glm::vec3 forward = t.GetForward();
  // glm::vec3 right = t.GetRight();
  // // Forward should now point in +X or -X direction
  // // Right should now point in +Z or -Z direction
  // EXPECT_NEAR(std::abs(forward.x), 1.0f, epsilon);
  // EXPECT_NEAR(std::abs(right.z), 1.0f, epsilon);
}

// =============================================================================
// MATRIX CONVERSION TESTS
// =============================================================================

TEST_F(TransformTest, GetModelMatrix)
{
  // Should return a 4x4 transformation matrix (TRS: Translation * Rotation * Scale)

  // TODO: Implement GetModelMatrix()
  // Transform t;
  // t.SetPosition(glm::vec3(1, 2, 3));
  // t.SetRotation(glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0)));
  // t.SetScale(glm::vec3(2, 2, 2));
  //
  // glm::mat4 model = t.GetModelMatrix();
  //
  // // Verify by constructing expected matrix manually
  // glm::mat4 expected = glm::translate(glm::mat4(1.0f), glm::vec3(1, 2, 3));
  // expected = expected * glm::mat4_cast(glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0)));
  // expected = glm::scale(expected, glm::vec3(2, 2, 2));
  //
  // EXPECT_TRUE(Mat4Near(model, expected));
}

TEST_F(TransformTest, GetInverseModelMatrix)
{
  // Should return the inverse transformation matrix

  // TODO: Implement GetInverseModelMatrix()
  // Transform t;
  // t.SetPosition(glm::vec3(5, 10, 15));
  // t.SetRotation(glm::angleAxis(glm::radians(30.0f), glm::vec3(1, 0, 0)));
  // t.SetScale(glm::vec3(2, 3, 4));
  //
  // glm::mat4 model = t.GetModelMatrix();
  // glm::mat4 inverse = t.GetInverseModelMatrix();
  // glm::mat4 identity = model * inverse;
  //
  // EXPECT_TRUE(Mat4Near(identity, glm::mat4(1.0f)));
}

TEST_F(TransformTest, SetFromMatrix)
{
  // Should be able to decompose a matrix into TRS components

  // TODO: Implement SetFromMatrix(mat4)
  // glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(10, 20, 30));
  // matrix = matrix * glm::mat4_cast(glm::angleAxis(glm::radians(60.0f), glm::vec3(0, 1, 0)));
  // matrix = glm::scale(matrix, glm::vec3(3, 3, 3));
  //
  // Transform t;
  // t.SetFromMatrix(matrix);
  //
  // EXPECT_TRUE(Vec3Near(t.position(), glm::vec3(10, 20, 30)));
  // EXPECT_TRUE(Vec3Near(t.scale(), glm::vec3(3, 3, 3), 0.01f));
}

// =============================================================================
// TRANSFORM POINT/VECTOR TESTS
// =============================================================================

TEST_F(TransformTest, TransformPoint)
{
  // Should transform a point from local to world space

  // TODO: Implement TransformPoint(vec3)
  // Transform t;
  // t.SetPosition(glm::vec3(10, 0, 0));
  // t.SetScale(glm::vec3(2, 2, 2));
  //
  // glm::vec3 localPoint(1, 0, 0);
  // glm::vec3 worldPoint = t.TransformPoint(localPoint);
  // // Should be scaled by 2 then translated by 10 in X
  // EXPECT_TRUE(Vec3Near(worldPoint, glm::vec3(12, 0, 0)));
}

TEST_F(TransformTest, TransformDirection)
{
  // Should transform a direction vector (ignores translation, affected by rotation)

  // TODO: Implement TransformDirection(vec3)
  // Transform t;
  // t.SetPosition(glm::vec3(100, 100, 100)); // Should not affect direction
  // t.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
  //
  // glm::vec3 localDir(0, 0, -1);
  // glm::vec3 worldDir = t.TransformDirection(localDir);
  // // After 90 degree Y rotation, -Z should become +X
  // EXPECT_TRUE(Vec3Near(worldDir, glm::vec3(1, 0, 0), 0.01f));
}

TEST_F(TransformTest, InverseTransformPoint)
{
  // Should transform a point from world to local space

  // TODO: Implement InverseTransformPoint(vec3)
  // Transform t;
  // t.SetPosition(glm::vec3(5, 10, 15));
  // t.SetRotation(glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0)));
  //
  // glm::vec3 worldPoint(10, 15, 20);
  // glm::vec3 localPoint = t.InverseTransformPoint(worldPoint);
  // glm::vec3 backToWorld = t.TransformPoint(localPoint);
  //
  // EXPECT_TRUE(Vec3Near(backToWorld, worldPoint));
}

// =============================================================================
// HIERARCHY/PARENT-CHILD TESTS (if you implement hierarchy)
// =============================================================================

TEST_F(TransformTest, SetParent)
{
  // Should be able to parent one transform to another

  // TODO: Implement SetParent(Transform*)
  // Transform parent;
  // parent.SetPosition(glm::vec3(10, 0, 0));
  //
  // Transform child;
  // child.SetPosition(glm::vec3(5, 0, 0));
  // child.SetParent(&parent);
  //
  // // Child's world position should be parent position + local position
  // glm::vec3 worldPos = child.GetWorldPosition();
  // EXPECT_TRUE(Vec3Near(worldPos, glm::vec3(15, 0, 0)));
}

TEST_F(TransformTest, GetLocalPosition)
{
  // Should return position relative to parent

  // TODO: Implement GetLocalPosition() and GetWorldPosition()
  // Transform parent;
  // parent.SetPosition(glm::vec3(10, 0, 0));
  //
  // Transform child;
  // child.SetParent(&parent);
  // child.SetPosition(glm::vec3(5, 0, 0)); // Local position
  //
  // EXPECT_TRUE(Vec3Near(child.GetLocalPosition(), glm::vec3(5, 0, 0)));
  // EXPECT_TRUE(Vec3Near(child.GetWorldPosition(), glm::vec3(15, 0, 0)));
}

TEST_F(TransformTest, ParentRotationAffectsChild)
{
  // Child should rotate with parent

  // TODO: Test parent rotation affecting child world position
  // Transform parent;
  // parent.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
  //
  // Transform child;
  // child.SetParent(&parent);
  // child.SetPosition(glm::vec3(0, 0, 5)); // 5 units in local +Z
  //
  // glm::vec3 worldPos = child.GetWorldPosition();
  // // After parent's 90 degree Y rotation, child's +Z becomes parent's -X
  // EXPECT_TRUE(Vec3Near(worldPos, glm::vec3(-5, 0, 0), 0.01f));
}

// =============================================================================
// INTERPOLATION TESTS
// =============================================================================

TEST_F(TransformTest, LerpPosition)
{
  // Should linearly interpolate between two transforms

  // TODO: Implement Lerp(Transform a, Transform b, float t) or similar
  // Transform start;
  // start.SetPosition(glm::vec3(0, 0, 0));
  //
  // Transform end;
  // end.SetPosition(glm::vec3(10, 0, 0));
  //
  // Transform result = Transform::Lerp(start, end, 0.5f);
  // EXPECT_TRUE(Vec3Near(result.position(), glm::vec3(5, 0, 0)));
}

TEST_F(TransformTest, SlerpRotation)
{
  // Should spherically interpolate rotation (slerp)

  // TODO: Implement rotation interpolation
  // Transform start;
  // start.SetRotation(glm::quat(1, 0, 0, 0)); // Identity
  //
  // Transform end;
  // end.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
  //
  // Transform result = Transform::Lerp(start, end, 0.5f);
  // glm::vec3 euler = result.rotationEuler();
  // EXPECT_NEAR(euler.y, glm::radians(45.0f), 0.01f);
}

// =============================================================================
// EQUALITY/COMPARISON TESTS
// =============================================================================

TEST_F(TransformTest, EqualityOperator)
{
  // Should compare two transforms for equality

  // TODO: Implement operator==
  // Transform t1;
  // t1.SetPosition(glm::vec3(1, 2, 3));
  //
  // Transform t2;
  // t2.SetPosition(glm::vec3(1, 2, 3));
  //
  // EXPECT_TRUE(t1 == t2);
}

TEST_F(TransformTest, InequalityOperator)
{
  // Should compare two transforms for inequality

  // TODO: Implement operator!=
  // Transform t1;
  // t1.SetPosition(glm::vec3(1, 2, 3));
  //
  // Transform t2;
  // t2.SetPosition(glm::vec3(4, 5, 6));
  //
  // EXPECT_TRUE(t1 != t2);
}

// =============================================================================
// EDGE CASES AND SPECIAL CONDITIONS
// =============================================================================

TEST_F(TransformTest, ZeroScale)
{
  // Should handle zero scale gracefully

  // TODO: Test behavior with zero scale
  // Transform t;
  // t.SetScale(glm::vec3(0, 0, 0));
  // // Should not crash, matrix might be singular
  // glm::mat4 model = t.GetModelMatrix();
  // // Verify it doesn't crash and produces expected result
}

TEST_F(TransformTest, NegativeScale)
{
  // Should handle negative scale (mirroring)

  // TODO: Test negative scale values
  // Transform t;
  // t.SetScale(glm::vec3(-1, 1, 1));
  // glm::vec3 point(1, 0, 0);
  // glm::vec3 transformed = t.TransformPoint(point);
  // EXPECT_TRUE(Vec3Near(transformed, glm::vec3(-1, 0, 0)));
}

TEST_F(TransformTest, GimbalLock)
{
  // Should handle gimbal lock situation with euler angles

  // TODO: Test gimbal lock scenario (pitch = 90 degrees)
  // Transform t;
  // t.SetRotationEuler(glm::vec3(glm::radians(90.0f), 0, 0));
  // glm::vec3 euler = t.rotationEuler();
  // // Should handle this gracefully
}

TEST_F(TransformTest, IdentityTransform)
{
  // Identity transform should produce identity matrix

  // TODO: Test that default transform produces identity matrix
  // Transform t;
  // glm::mat4 model = t.GetModelMatrix();
  // EXPECT_TRUE(Mat4Near(model, glm::mat4(1.0f)));
}

TEST_F(TransformTest, CombinedTransformationOrder)
{
  // Verify the order of transformations is correct (TRS)

  // TODO: Test that transformations are applied in correct order
  // Transform t;
  // t.SetPosition(glm::vec3(10, 0, 0));
  // t.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
  // t.SetScale(glm::vec3(2, 2, 2));
  //
  // glm::vec3 point(1, 0, 0);
  // glm::vec3 result = t.TransformPoint(point);
  //
  // // Should be: Scale (2,0,0) -> Rotate (0,0,-2) -> Translate (10,0,-2)
  // EXPECT_TRUE(Vec3Near(result, glm::vec3(10, 0, -2), 0.01f));
}

TEST_F(TransformTest, Reset)
{
  // Should reset transform to identity

  // TODO: Implement Reset()
  // Transform t;
  // t.SetPosition(glm::vec3(10, 20, 30));
  // t.SetRotation(glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 1, 0)));
  // t.SetScale(glm::vec3(5, 5, 5));
  //
  // t.Reset();
  //
  // EXPECT_TRUE(Vec3Near(t.position(), glm::vec3(0, 0, 0)));
  // EXPECT_TRUE(QuatNear(t.rotation(), glm::quat(1, 0, 0, 0)));
  // EXPECT_TRUE(Vec3Near(t.scale(), glm::vec3(1, 1, 1)));
}
