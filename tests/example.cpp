#include <gtest/gtest.h>

#include <lab.hpp>

bool operator==(const subjects& lhs, const subjects& rhs) {
  if (lhs.size != rhs.size) {
    return false;
  }

  for (auto i = 0; i < lhs.size; ++i) {
    if (lhs.subjects[i] != rhs.subjects[i]) {
      return false;
    }
  }
  return true;
}

bool operator==(const ratings& lhs, const ratings& rhs) {
  if (lhs.size != rhs.size) {
    return false;
  }

  for (auto i = 0; i < lhs.size; ++i) {
    if (lhs.ratings[i] != rhs.ratings[i]) {
      return false;
    }
  }
  return true;
}

bool operator==(const student& lhs, const student& rhs) {
  return lhs.name == rhs.name && lhs.group_id == rhs.group_id &&
         lhs.subjects == rhs.subjects && lhs.ratings == rhs.ratings;
}

bool operator==(const group& lhs, const group& rhs) {
  return lhs.id == rhs.id && lhs.students == rhs.students;
}

bool operator==(const group& lhs, const std::vector<student>& rhs) {
  if (lhs.size != rhs.size()) {
    return false;
  }

  for (auto i = 0; i < lhs.size; ++i) {
    if (!(lhs.students[i] == rhs[i])) {
      return false;
    }
  }
  return true;
}

ratings convert_to_ratings(const std::vector<unsigned>& v) {
  return {v.data(), v.size()};
}

subjects convert_to_subjects(const std::vector<const char*>& v) {
  return {v.data(), v.size()};
}

class TestLab : public ::testing::Test {
 protected:
  void SetUp() override {
    // TODO add empty ratings
    ratings_1 = {3, 5, 4, 5, 5, 4};
    ratings_2 = {5, 5, 5, 5, 5, 5};
    ratings_3 = {3, 3, 3, 4, 3, 3};
    ratings_4 = {4, 4, 5, 4, 4, 4};
    ratings_5 = {4, 4, 5, 5, 5, 4};
    ratings_6 = {5, 5, 5, 5, 5, 5};
    ratings_7 = {3, 5, 3, 3, 5, 4};
    ratings_8 = {5, 4, 5, 4, 5, 4};
    ratings_9 = {5, 2, 5, 4, 5, 4};
    ratings_10 = {2, 2, 5, 4, 5, 4};
    Subjects1 = {"Math", "Physics", "IT", "English", "Ecology", "Literature"};
    Subjects2 = {"Physics", "Russian", "Politology", "Biology", "History"};
    Subjects3 = {"IT", "English", "Math", "PE", "Electronic", "IT"};
    student1 =  student{"Asya", "iu8-34", convert_to_ratings(ratings_2), convert_to_subjects(Subjects1)};     // 30
    student2 = student{"Romka", "iu8-34", convert_to_ratings(ratings_6), convert_to_subjects(Subjects1)};    // 30
    student3 = student{"Petya", "iu9-54", convert_to_ratings(ratings_1), convert_to_subjects(Subjects3)};    // 26
    student4 = student{"Tasya", "iu9-54", convert_to_ratings(ratings_7), convert_to_subjects(Subjects3)};    // 23
    student5 = student{"Alice", "iu9-54", convert_to_ratings(ratings_8), convert_to_subjects(Subjects3)};    // 27
    student6 = student{"Anton", "ibm3-12", convert_to_ratings(ratings_3), convert_to_subjects(Subjects2)};   // 19
    student7 = student{"Robert", "ibm3-12", convert_to_ratings(ratings_4), convert_to_subjects(Subjects2)};  // 25
    student8 = student{"Tanya", "ibm3-12", convert_to_ratings(ratings_5), convert_to_subjects(Subjects2)};   // 27
    student9 = student{"Ama", "ibm3-12", convert_to_ratings(ratings_9), convert_to_subjects(Subjects2)};     // 25
    student10 = student{"Inga", "ibm3-12", convert_to_ratings(ratings_10), convert_to_subjects(Subjects2)};  // 22
  }

 public:
  std::vector<unsigned> ratings_1;
  std::vector<unsigned> ratings_2;
  std::vector<unsigned> ratings_3;
  std::vector<unsigned> ratings_4;
  std::vector<unsigned> ratings_5;
  std::vector<unsigned> ratings_6;
  std::vector<unsigned> ratings_7;
  std::vector<unsigned> ratings_8;
  std::vector<unsigned> ratings_9;
  std::vector<unsigned> ratings_10;
  std::vector<const char*> Subjects1;
  std::vector<const char*> Subjects2;
  std::vector<const char*> Subjects3;
  student student1{};
  student student2{};
  student student3{};
  student student4{};
  student student5{};
  student student6{};
  student student7{};
  student student8{};
  student student9{};
  student student10{};
};

// Сортировка студентов по именам
TEST_F(TestLab, sort_by_name) {
  // базовый сценарий
  std::vector<student> students = {student1, student2, student3, student4,
                                   student5, student6, student7, student8};
  std::vector<student> result = {
      student5, student6, student1, student3,
      student7, student2, student8, student4,
  };
  sort_by_name(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
  // пустой вектор
  students = {};
  result = {};
  sort_by_name(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
  // вектор, состоящий из имен, начинающихся на одну букву
  students = {student1, student6, student5};
  result = {student5, student6, student1};
  sort_by_name(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
  // вектор из одного элемента
  students = {student4};
  result = {student4};
  sort_by_name(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
}

// Сортировка всех студентов по средней оценке
TEST_F(TestLab, sort_by_rating) {
  // базовый сценарий
  std::vector<student> students = {student1, student2, student3, student4,
                                   student5, student6, student7, student8};
  std::vector<student> result = {student1, student2, student5, student8,
                                 student3, student7, student4, student6};
  sort_by_rating(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
  // вектор, состоящий из ребят с одинаковым рейтингом
  students = {student8, student5};
  result = {student8, student5};
  sort_by_rating(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
  // вектор из одного элемента
  students = {student4};
  result = {student4};
  sort_by_rating(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
  // пустой вектор
  students = {};
  result = {};
  sort_by_rating(group{"1", students.data(), students.size()});
  EXPECT_EQ(students, result);
}

// Возвращаем количество двоечников
TEST_F(TestLab, count_bad_students) {
  // базовый сценарий
  std::vector<student> students = {student1, student2, student3,  student4,
                                   student5, student6, student10, student7,
                                   student8, student9};
  size_t count = 0;
  count = count_bad_students(group{"1", students.data(), students.size()});
  EXPECT_EQ(2, count);
  // без двоечников
  students = {student1, student2, student3, student4,
              student5, student6, student7, student8};
  count = count_bad_students(group{"1", students.data(), students.size()});
  EXPECT_EQ(0, count);
  // вектор с одним элементом
  students = {student9};
  count = count_bad_students(group{"1", students.data(), students.size()});
  EXPECT_EQ(1, count);
  // пустой вектор
  students = {};
  count = count_bad_students(group{"1", students.data(), students.size()});
  EXPECT_EQ(0, count);
}

// Количество отличников
TEST_F(TestLab, count_excellent) {
  // базовый сценарий
  std::vector<student> students = {student1, student2, student3,  student4,
                                   student5, student6, student10, student7,
                                   student8, student9};
  size_t count = 0;
  count = count_excellent(group{"1", students.data(), students.size()});
  EXPECT_EQ(2, count);
  // без отличников
  students = {student9, student10, student3, student4,
              student5, student6,  student7, student8};
  count = count_excellent(group{"1", students.data(), students.size()});
  EXPECT_EQ(0, count);
  // вектор с одним элементом
  students = {student1};
  count = count_excellent(group{"1", students.data(), students.size()});
  EXPECT_EQ(1, count);
  // пустой вектор
  students = {};
  count = count_excellent(group{"1", students.data(), students.size()});
  EXPECT_EQ(0, count);
}

// Создаем массив тех, кто получил по математике 5
TEST_F(TestLab, select_math_excellent) {
  // базовый сценарий
  std::vector<student> students_vector = {student1, student2, student3,  student4,
                                   student5, student6, student10, student7,
                                   student8, student9};

  std::vector<student> result = {student1, student2, student5};
  group students{};
  students = select_math_excellent(group{"1", students_vector.data(), students_vector.size()});
  EXPECT_EQ(students, result);
  // без отличников по математике

  students_vector = {student9, student10, student3, student4,
              student6, student7,  student8};
  result = {};
  students = select_math_excellent(group{"1", students_vector.data(), students_vector.size()});
  EXPECT_EQ(students, result);
  // без ребят с предметом математика
  students_vector = {student6, student7, student8, student9, student10};
  result = {};
  students = select_math_excellent(group{"1", students_vector.data(), students_vector.size()});
  EXPECT_EQ(students, result);
  // вектор с одним элементом
  students_vector = {student1};
  result = {student1};
  students = select_math_excellent(group{"1", students_vector.data(), students_vector.size()});
  EXPECT_EQ(students, result);
  // пустой вектор
  students_vector = {};
  result = {};
  students = select_math_excellent(group{"1", students_vector.data(), students_vector.size()});
  EXPECT_EQ(students, result);
}

// Массив уникальных названий групп
TEST_F(TestLab, select_distinct_groups) {
  // базовый сценарий
  std::vector<student> students = {student1, student2, student3,  student4,
                                   student5, student6, student10, student7,
                                   student8, student9};
  std::vector<const char*> result = {"iu8-34", "iu9-54", "ibm3-12"};
  groups groups = select_distinct_groups(group{"0", students.data(), students.size()});
  EXPECT_EQ(result, groups);
  // все из одной группы
  students = {student3, student4, student5};
  result = {"iu9-54"};
  groups = select_distinct_groups(group{"0", students.data(), students.size()});
  EXPECT_EQ(result, groups);
  // вектор с одним элементом
  students = {student1};
  result = {"iu8-34"};
  groups = select_distinct_groups(group{"0", students.data(), students.size()});
  EXPECT_EQ(result, groups);
  // пустой вектор
  students = {};
  result = {};
  groups = select_distinct_groups(group{"0", students.data(), students.size()});
  EXPECT_EQ(result, groups);
}

// массив структур group
TEST_F(TestLab, groups) {
  // базовый сценарий
  std::vector<student> students = {student1, student2, student3,  student4,
                                   student5, student6, student10, student7,
                                   student8, student9};
  std::vector<student> students1group = {student1, student2};
  std::vector<student> students2group = {student3, student4, student5};
  std::vector<student> students3group = {student6, student7, student8, student9,
                                         student10};
  group group1 = {"iu8-34", students1group.data(), students1group.size()};
  group group2 = {"iu9-54", students2group.data(), students2group.size()};
  group group3 = {"ibm3-12", students3group.data(), students3group.size()};
  std::vector<group> result = {group1, group2, group3};
  groups groups = group_by_group(group{"1", students.data(), students.size()});
  EXPECT_EQ(result, groups);
  // все из одной группы
  students = {student3, student4, student5};
  students2group = {student3, student4, student5};
  group2 = {"iu9-54", students2group.data(), students2group.size()};
  result = {group2};
  groups = group_by_group(group{"1", students.data(), students.size()});
  EXPECT_EQ(result, groups);
  // вектор с одним элементом
  students = {student1};
  students1group = {student1};
  group1 = {"iu8-34", students1group.data(), students1group.size()};
  result = {group1};
  groups = group_by_group(group{"1", students.data(), students.size()});
  EXPECT_EQ(result, groups);
  // пустой вектор
  students = {};
  result = {};
  groups = group_by_group(group{"1", students.data(), students.size()});
  EXPECT_EQ(result, groups);
}