class FoodInfo:
    def check_num(self, x):
        if isinstance(x, (float, int)):
            return True
        else:
            return NotImplemented

    def __init__(self, proteins, fats, carbohydrates):
        self.proteins = proteins
        self.fats = fats
        self.carbohydrates = carbohydrates

    def __add__(self, other):
        if isinstance(other, FoodInfo):
            return FoodInfo(self.proteins + other.proteins, self.fats + other.fats, self.carbohydrates + other.carbohydrates)

    def __mul__(self, other):
        if self.check_num(other):
            return FoodInfo(self.proteins * other, self.fats * other, self.carbohydrates * other)

    def __truediv__(self, other):
        if self.check_num(other):
            return FoodInfo(self.proteins / other, self.fats / other, self.carbohydrates / other)

    def __floordiv__(self, other):
        if self.check_num(other):
            return FoodInfo(self.proteins // other, self.fats // other, self.carbohydrates // other)

    def __repr__(self):
        return f"FoodInfo({self.proteins}, {self.fats}, {self.carbohydrates})"

f1 = FoodInfo(30, 50, 40)
f2 = FoodInfo(70, 50, 60)

f_add = f1 + f2
print(f_add)

f_mul = f1 * 2
print(f_mul)

f_truediv = f1 / 1.5
print(f_truediv)

f_floordiv = f1 // 2
print(f_floordiv)