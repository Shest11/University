import sqlite3

connection = sqlite3.connect("my_db.db")
cursor = connection.cursor()

cursor.execute('''
create table if not exists "Должности" (
"Код_должности" integer primary key not null unique,
"Название" text not null
)
''')

cursor.execute('''
create table if not exists "Сотрудники" (
"Код_сотрудника" integer primary key not null unique,
"Фамилия" text not null,
"Имя" text not null,
"Телефон" varchar(20),
"Код_должности" integer not null references "Должности"("Код_должности")
)
''')

cursor.execute('''
create table if not exists "Клиенты" (
"Код_клиента" integer primary key not null unique,
"Организация" text not null,
"Телефон" varchar(20)
)
''')

cursor.execute('''
create table if not exists "Заказы" (
"Код_заказа" integer primary key not null unique,
"Код_клиента" integer not null references "Клиенты"("Код_клиента"),
"Код_сотрудника" integer not null references "Сотрудники"("Код_сотрудника"),
"Сумма" integer not null,
"Дата_выполнения" date not null,
"Отметка_о_выполнении" boolean
)
''')

job_titles_data = [
    (1, 'Менеджер'),
    (2, 'Разработчик'),
    (3, "Аналитик"),
    (4, "Дизайнер")
]

cursor.executemany('insert into "Должности" ("Код_должности", "Название") values (?, ?)', job_titles_data)

employees_data = [
    (1, "Иванов", "Иван", 2),
    (2, "Петров", "Евгений", 1),
    (3, "Шестаков", "Данила", 3),
    (4, "Кротов", "Антон", 2),
    (5, "Ксения", "Сазонова", 4)
]

cursor.executemany('insert into "Сотрудники" ("Код_сотрудника", "Фамилия", "Имя", "Код_должности") values (?, ?, ?, ?)', employees_data)

client_data = [
    (1, "Ромашка", "89836914211"),
    (2, "Ветерок", "83531295471"),
    (3, "Ало, бизнес?", "88005553535")
]

cursor.executemany('insert into "Клиенты" ("Код_клиента", "Организация", "Телефон") values (?, ?, ?)', client_data)

orders_data = [
    (1, 2, 3, 40_000, "2026-04-29", False),
    (2, 1, 4, 50_000, "2026-12-31", True),
    (3, 3, 3, 1_000_000, "2024-01-15", False)
]

cursor.executemany('insert into "Заказы" ("Код_заказа", "Код_клиента", "Код_сотрудника", "Сумма", "Дата_выполнения", "Отметка_о_выполнении") values (?, ?, ?, ?, ?, ?)', orders_data)

connection.commit()

print("Общее кол-во заказов: ")
cursor.execute('select count(*) from "Заказы"')
print(cursor.fetchall()[0][0])
print()
print("Максимальная сумма заказа: ")
cursor.execute('select max("Сумма") from "Заказы"')
print(cursor.fetchall()[0][0])
print()
print("Минимальная сумма заказа: ")
cursor.execute('select min("Сумма") from "Заказы"')
print(cursor.fetchall()[0][0])
print()
print("Общая сумма заказов: ")
cursor.execute('select sum("Сумма") from "Заказы"')
print(cursor.fetchall()[0][0])
print()
print("Средняя сумма заказа: ")
cursor.execute('select avg("Сумма") from "Заказы"')
print(cursor.fetchall()[0][0])
print()
print("Код сотрудника и его кол-во заказов: ")
cursor.execute('SELECT Код_сотрудника, COUNT(*) FROM "Заказы" GROUP BY Код_сотрудника')
print(cursor.fetchall())
print()
print("Код клиента и его сумма: ")
cursor.execute('SELECT Код_клиента, SUM(Сумма) FROM "Заказы" GROUP BY Код_клиента')
print(cursor.fetchall())
print()
print("Статус заказов: ")
cursor.execute('SELECT Отметка_о_выполнении, COUNT(*) FROM "Заказы" GROUP BY Отметка_о_выполнении')
print(cursor.fetchall())
print()
print("Заказы на сумму больше 45 000: ")
cursor.execute('''
    SELECT Заказы.Код_заказа, Клиенты.Организация, Заказы.Сумма
    FROM Заказы, Клиенты
    WHERE Заказы.Код_клиента = Клиенты.Код_клиента
    AND Заказы.Сумма > 45000
''')
print(cursor.fetchall())
print()
print("Только менеджеры: ")
cursor.execute('''
    SELECT Сотрудники.Фамилия, Сотрудники.Имя, Должности.Название
    FROM Сотрудники, Должности
    WHERE Сотрудники.Код_должности = Должности.Код_должности
    AND Должности.Название = 'Менеджер'
''')
print(cursor.fetchall())
print()
print("Выполненные заказы: ")
cursor.execute('''
    SELECT Заказы.Код_заказа, Клиенты.Организация, Заказы.Сумма
    FROM Заказы, Клиенты
    WHERE Заказы.Код_клиента = Клиенты.Код_клиента
    AND Заказы.Отметка_о_выполнении = 1
''')
print(cursor.fetchall())