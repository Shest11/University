class User:
    def __check_name(self, name):
        if name == None or name == "" or not isinstance(name, str) or not name.isalpha():
            raise ValueError("Некорректное имя")
        else:
            self.__name = name

    def __check_age(self, age):
        if age <= 0 or age >= 110 or not isinstance(age, int):
            raise ValueError("Некорректный возраст")
        else:
            self._age = age

    def __init__(self, name, age):
        self.__check_name(name)
        self.__check_age(age)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__check_name(new_name)

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, new_age):
        self.__check_age(new_age)

u = User('Даня', 18)
u.name = 'Саня'
u.age = 19
print(u.name, u.age)