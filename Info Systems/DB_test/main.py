import sqlite3
import pandas as pd

connection = sqlite3.connect("task.db")
cursor = connection.cursor()

cursor.execute('''
    CREATE TABLE IF NOT EXISTS movements (
        "ID операции" INTEGER PRIMARY KEY,
        "Дата" TEXT,
        "ID магазина" TEXT,
        "Артикул" INTEGER,
        "Количество упаковок, шт." REAL,
        "Тип операции" TEXT,
        "Цена руб./шт." REAL
    );
''')

cursor.execute('''
    CREATE TABLE IF NOT EXISTS stores (
        "ID магазина" TEXT PRIMARY KEY,
        "Район" TEXT,
        "Адрес" TEXT
    );
''')

df_movements = pd.read_excel("3.xls", sheet_name="Движение_товаров")
df_stores = pd.read_excel("3.xls", sheet_name="Магазин")

df_movements['Дата'] = pd.to_datetime(df_movements['Дата']).dt.strftime('%Y-%m-%d')

df_movements.to_sql('movements', connection, if_exists='replace', index=False)
df_stores.to_sql('stores', connection, if_exists='replace', index=False)

answer = cursor.execute('''
    SELECT SUM(CASE 
        WHEN "Тип операции" = 'Поступление' THEN "Количество упаковок, шт."
        WHEN "Тип операции" = 'Продажа' THEN -"Количество упаковок, шт."
        ELSE 0 
    END) as result
    FROM movements m
    WHERE m."Артикул" = 15
        AND m."Дата" BETWEEN '2021-06-01' AND '2021-06-10'
        AND m."ID магазина" IN (SELECT "ID магазина" FROM stores WHERE "Район" = 'Заречный')
''').fetchone()[0]

print(answer)

connection.close()