#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

struct ratings {
  const unsigned* ratings;
  size_t size;
};

struct subjects {
  const char* const* subjects;
  size_t size;
};

struct student
{
  const char* name;
  const char* group_id;
  ratings ratings; // 1 - 5
  subjects subjects;
};

struct group {
  const char* id;
  const student* students;
  size_t size;
};

struct groups {
  const group* groups;
  size_t size;
};

void sort_by_name(group);
void sort_by_rating(group);
size_t count_bad_students(group);
size_t count_excellent(group);
group select_math_excellent(group);
groups select_distinct_groups(group);

groups group_by_group(group);
#endif // INCLUDE_EXAMPLE_HPP_
