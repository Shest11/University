class BankAccount:
    __balance = 0
    def __init__(self, b):
        self.__balance = b

    def get_balance(self):
        return self.__balance

    def deposit(self, amount):
        self.__balance += amount

    def withdraw(self, amount):
        if self.__balance < amount:
            raise ValueError("На счете недостаточно средств")
        else:
            self.__balance -= amount

    def transfer(self, account, amount):
        if self.__balance < amount:
            raise ValueError("На счете недостаточно средств")
        else:
            self.__balance -= amount
            account += amount

bank = BankAccount(100)