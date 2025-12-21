import tkinter as tk
from tkinter import messagebox

mainWindow = tk.Tk()
mainWindow.title("Анкета о путешествиях")
mainWindow.geometry("1000x680")
mainWindow.configure(bg="#F0F0F0")

questions = [
    {
        "question": "1. Какой тип отдыха вы предпочитаете?",
        "answers": [
            "Пляжный отдых", "Горнолыжный курорт", "Экскурсионный тур",
            "Активный отдых (походы)", "Городской туризм"
        ]
    },
    {
        "question": "2. Как вы обычно выбираете жилье?",
        "answers": [
            "Отель 4-5 звезд", "Апартаменты/квартира", "Гостевой дом/B&B",
            "Хостел", "Кемпинг"
        ]
    },
    {
        "question": "3. Какой бюджет на поездку для вас комфортен?",
        "answers": [
            "До 50 000 руб.", "50 000 - 100 000 руб.", "100 000 - 200 000 руб.",
            "200 000 - 500 000 руб.", "Не считаю деньги"
        ]
    },
    {
        "question": "4. Как вы планируете путешествие?",
        "answers": [
            "Самостоятельно", "Через турфирму", "Покупаю готовый тур",
            "По рекомендациям", "Спонтанные поездки"
        ]
    },
    {
        "question": "5. Что для вас важнее всего в путешествии?",
        "answers": [
            "Комфорт и сервис", "Новые впечатления", "Фото для соцсетей",
            "Местная кухня", "Общение с людьми"
        ]
    }
]

answers = [""] * len(questions)
selected_buttons = []


def select_answer(question_index, answer_index, button):
    answers[question_index] = questions[question_index]["answers"][answer_index]

    button.config(bg="#FFFFFF", fg="white")

def save_results():
    for i, ans in enumerate(answers):
        if ans == "":
            tk.messagebox.showwarning(
                "Не все ответы",
                f"Пожалуйста, ответьте на вопрос {i + 1}"
            )
            return

    try:
        filename = "answers.txt"

        with open(filename, "a", encoding="utf-8") as f:
            f.write(f"АНКЕТА О ПУТЕШЕСТВИЯХ\n")
            for i in range(len(questions)):
                f.write('\n')
                f.write(f"{questions[i]['question']}\n")
                f.write(f"{answers[i]}\n")

        tk.messagebox.showinfo(
            "Успешно!",
            f"Результаты сохранены в файл: {filename}"
        )

    except Exception as e:
        tk.messagebox.showerror("Ошибка", f"Не удалось сохранить: {str(e)}")

row = 0

titleLabel = tk.Label(mainWindow, text="Анкета о путешествиях", fg="#3372FF", bg="#F0F0F0", font=("Arial", 30, "bold"))
titleLabel.grid(row=row, column=0, columnspan=5, pady=20)
row += 1

subtitleLabel = tk.Label(mainWindow, text="Выберите по одному варианту ответа на каждый вопрос", fg="#666666", bg="#F0F0F0", font=("Arial", 14))
subtitleLabel.grid(row=row, column=0, columnspan=5, pady=(0, 20))
row += 1

for i, q_data in enumerate(questions):
    questionLabel = tk.Label(mainWindow, text=q_data["question"], fg="#333333", bg="#F0F0F0", font=("Arial", 16, "bold"), justify="left", anchor="w")
    questionLabel.grid(row=row, column=0, columnspan=5, sticky="w", padx=20, pady=(20, 10))
    row += 1

    question_buttons = []
    for j, answer_text in enumerate(q_data["answers"]):
        buttonVariant = tk.Button(mainWindow, text=answer_text, bg="#808080", fg="white", borderwidth=3, font=("Arial", 12), wraplength=180, height=3, width=15, command=lambda q_idx=i, a_idx=j, btn=None: select_answer(q_idx, a_idx, btn))

        buttonVariant.command = lambda q_idx=i, a_idx=j, b=buttonVariant: select_answer(q_idx, a_idx, b)
        buttonVariant.config(command=buttonVariant.command)

        buttonVariant.grid(row=row, column=j, padx=10, pady=10, sticky="nsew")
        question_buttons.append(buttonVariant)

    selected_buttons.append(question_buttons)
    row += 1

row += 1

button_frame = tk.Frame(mainWindow, bg="#F0F0F0")
button_frame.grid(row=row, column=0, columnspan=5, pady=30)

saveButton = tk.Button(button_frame, text="СОХРАНИТЬ ОТВЕТЫ", bg="#22AA44", fg="white", font=("Arial", 14, "bold"), borderwidth=3, width=20, height=2, command=save_results)
saveButton.pack(side="left", padx=20)

exitButton = tk.Button(button_frame, text="ВЫХОД", bg="#CC3333", fg="white", font=("Arial", 14, "bold"), borderwidth=3, width=15, height=2, command=mainWindow.quit)
exitButton.pack(side="left", padx=20)

for c in range(5):
    mainWindow.grid_columnconfigure(c, weight=1)

row += 1
infoLabel = tk.Label(mainWindow, text="Результаты сохраняются в файл travel_survey_results.txt", fg="#666666", bg="#F0F0F0", font=("Arial", 10))
infoLabel.grid(row=row, column=0, columnspan=5, pady=10)

mainWindow.mainloop()