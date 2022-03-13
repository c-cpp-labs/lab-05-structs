# Лабораторная работа 5

## Теоретическая справка

Вы уже имели дело со структурами (с первого занятия аж). Настало время уже серьёзно заняться взаимодействием с этим инструментом языка. 

### Вспоминаем основы:
Структуры - производный тип данных, который может объединять в себе несколько переменных других типов (в том числе и структур).

Объявим структуру координаты
```c++
struct coordinate {
    float x;
    float y;
};
```

У данной структуры имеется два поля: `x` и `y`, с которыми можно взаимодействовать. Объявим объект структуры и введём значения координат
```c++
coordinate zero{0, 0}; // нулевая координата
```
Координаты данного объекта можно вывести на консоль (кстати для удобства можно сделать функцию):
```c++
std::cout << "x: " << zero.x << " y: " << zero.y << '\n';
```

Также значения координаты можно ввести с консоли
```c++
coordinate new_coordinate{}; // обязательно инициализируем переменную, чтобы никто не ругался
std::cin >> new_coordinate.x >> new_coordinate.y;

std::cout << "new_coordinate: x - " << new_coordinate.x << " y - " << new_coordinate.y << '\n';
```





## Задание
Пусть есть структуры `student`
```cpp

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
  student* students;
  size_t size;
};

struct groups {
  group* groups;
  size_t size;
};
```

В поле `ratings` представлены оценки по соответсвующему предмету из поля `subjects`.
Предположим есть список студентов `student* students`.
Ваше задание состоит в реализации ряда функций. Все прототипы функций необходимо разместить
в файле [lab.hpp](sources/lab/lab.hpp).

Реализуйте функции, которые выполняют следующие действия с этим списком:
* отсортирует всех студентов по именам. Прототип:
```cpp
void sort_by_name(group);
```

* отсортирует всех студентов по средней оценке;
```cpp
void sort_by_rating(group);
```

* вернет количество студентов имеющих неудовлетворительную оценку хотя бы по одному предмету;
```cpp
size_t count_bad_students(group);
```

* определит, сколько студентов сдали все экзамены на 5.
```cpp
size_t count_excellent(group);
```

* создаст массив `student*`, в который войдут студенты имеющие отметку отлично, по предмету "Math";
```cpp
group select_math_excellent(group);
```

* вернет массив уникальных названий групп студентов из списка students
```cpp
groups select_distinct_groups(group);
```

* сформирует список групп, т.е. создаст массив структур `group`

Прототип:
```cpp
groups group_by_group(group);
```