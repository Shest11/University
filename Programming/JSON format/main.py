import json

def create_json():
    data = {}
    while True:
        a = input('1 Добавить нового пользователя\n'
                  '0 Выйти/Получить результат\n'
                  'Введите номер команды: ')
        print()
        if a == '1':
            name = input('Введите логин: ').lower()
            age = input('Введите возраст (только число): ')
            time = input('Введите время входа: ')
            print(f'Пользователь \033[1m\033[3m{name}\033[0m добавлен!')
            print()
            data[name] = {'age': age, 'time': time}
        if a == '0':
            json.dump(data, open('data.json', 'w'))
            break
create_json()

def get_json():
    data = json.load(open('data.json'))
    print(f'Кол-во пользователей: {len(data)}')
    cnt = len(data)
    while True:
        if cnt != 0:
            name = input('Введите логин пользователя и получите инфу: ').lower()
            print(f'Возраст \033[1m\033[3m{name}\033[0m: {data[name]['age']} лет\n'
                  f'Время входа: {data[name]["time"]}')
            ans = input('Хотите ещё получить инфу по пользователям? yes/no: ')
            print()
            if ans == 'yes':
                continue
            elif ans == 'no':
                break
        else:
            break
get_json()