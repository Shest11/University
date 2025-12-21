import tkinter as tk
from tkinter import messagebox


class SimpleTestSystem:
    def __init__(self, root):
        self.root = root
        self.root.title("Тестовая система")
        self.root.geometry("1000x680")
        self.root.configure(bg="#F0F0F0")

        self.questions = self.load_questions("test_questions.txt")

        self.display_questions = self.questions[:5]

        self.score = 0
        self.user_answers = [None] * 5

        self.create_widgets()
        self.display_all_questions()
        self.hide_results()

    def load_questions(self, filename):
        questions = []
        try:
            with open(filename, 'r', encoding='utf-8') as f:
                lines = f.readlines()

            current_question = None
            current_answers = []

            for line in lines:
                line = line.strip()
                if line.startswith("q:"):
                    if current_question is not None:
                        questions.append({'question': current_question, 'answers': current_answers.copy()})

                    current_question = line[2:].strip()
                    current_answers = []
                elif line and line[0].isdigit() and line[1] == '.':
                    answer_text = line[2:].strip()
                    is_correct = False
                    if answer_text.endswith("+"):
                        answer_text = answer_text[:-1].strip()
                        is_correct = True

                    current_answers.append({'text': answer_text, 'correct': is_correct})

            if current_question is not None:
                questions.append({'question': current_question, 'answers': current_answers.copy()})

            return questions

        except FileNotFoundError:
            messagebox.showerror("Ошибка", f"Файл {filename} не найден!")
            return []

    def create_widgets(self):
        titleLabel = tk.Label(
            self.root,
            text="Тестовая система",
            fg="#3372FF",
            bg="#F0F0F0",
            font=("Arial", 30, "bold")
        )
        titleLabel.grid(row=0, column=0, columnspan=5, pady=20)

        subtitleLabel = tk.Label(
            self.root,
            text="Ответьте на 5 вопросов (выберите по одному варианту):",
            fg="#666666",
            bg="#F0F0F0",
            font=("Arial", 14)
        )
        subtitleLabel.grid(row=1, column=0, columnspan=5, pady=(0, 10))

        self.questions_frame = tk.Frame(self.root, bg="#F0F0F0")
        self.questions_frame.grid(row=2, column=0, columnspan=5, sticky="nsew", padx=20, pady=10)

        self.results_frame = tk.Frame(self.root, bg="#F0F0F0")
        self.results_frame.grid(row=3, column=0, columnspan=5, sticky="ew", padx=20, pady=10)

        self.results_label = tk.Label(
            self.results_frame,
            text="",
            fg="#333333",
            bg="#F0F0F0",
            font=("Arial", 14, "bold")
        )
        self.results_label.pack()

        button_frame = tk.Frame(self.root, bg="#F0F0F0")
        button_frame.grid(row=4, column=0, columnspan=5, pady=20)

        self.checkButton = tk.Button(
            button_frame,
            text="ПРОВЕРИТЬ ТЕСТ",
            bg="#22AA44",
            fg="white",
            font=("Arial", 14, "bold"),
            borderwidth=3,
            width=20,
            height=2,
            command=self.check_test
        )
        self.checkButton.pack(side="left", padx=20)

        self.resetButton = tk.Button(
            button_frame,
            text="СБРОСИТЬ",
            bg="#FF6600",
            fg="white",
            font=("Arial", 14, "bold"),
            borderwidth=3,
            width=15,
            height=2,
            command=self.reset_test
        )
        self.resetButton.pack(side="left", padx=20)

        exitButton = tk.Button(
            button_frame,
            text="ВЫХОД",
            bg="#CC3333",
            fg="white",
            font=("Arial", 14, "bold"),
            borderwidth=3,
            width=15,
            height=2,
            command=self.root.quit
        )
        exitButton.pack(side="left", padx=20)

        for c in range(5):
            self.root.grid_columnconfigure(c, weight=1)

        self.root.grid_rowconfigure(2, weight=1)

    def display_all_questions(self):
        for widget in self.questions_frame.winfo_children():
            widget.destroy()

        self.answer_buttons = []
        self.selected_buttons = []

        row_counter = 0

        for q_index, q_data in enumerate(self.display_questions):
            questionLabel = tk.Label(
                self.questions_frame,
                text=f"{q_index + 1}. {q_data['question']}",
                fg="#333333",
                bg="#F0F0F0",
                font=("Arial", 14, "bold"),
                justify="left",
                anchor="w",
                wraplength=950
            )
            questionLabel.grid(row=row_counter, column=0, columnspan=5, sticky="w", pady=(20, 10))
            row_counter += 1

            question_buttons = []
            for a_index, answer in enumerate(q_data['answers']):
                buttonVariant = tk.Button(
                    self.questions_frame,
                    text=answer['text'],
                    bg="#808080",
                    fg="white",
                    borderwidth=2,
                    font=("Arial", 11),
                    wraplength=180,
                    height=2,
                    width=15
                )

                def make_command(q_idx=q_index, a_idx=a_index, btn=buttonVariant):
                    return lambda: self.select_answer(q_idx, a_idx, btn)

                buttonVariant.config(command=make_command())
                buttonVariant.grid(row=row_counter, column=a_index, padx=5, pady=5, sticky="ew")
                question_buttons.append(buttonVariant)
            self.answer_buttons.append(question_buttons)
            self.selected_buttons.append(None)
            row_counter += 1
        for c in range(5):
            self.questions_frame.grid_columnconfigure(c, weight=1)

    def select_answer(self, question_index, answer_index, button):
        prev_selected = self.selected_buttons[question_index]
        if prev_selected is not None:
            prev_selected.config(bg="#808080", fg="white")
        self.user_answers[question_index] = answer_index
        button.config(bg="#3372FF", fg="white")
        self.selected_buttons[question_index] = button
        self.hide_results()

    def check_test(self):
        unanswered = []
        for i, answer in enumerate(self.user_answers):
            if answer is None:
                unanswered.append(str(i + 1))

        if unanswered:
            messagebox.showwarning(
                "Не все ответы",
                f"Пожалуйста, ответьте на вопросы: {', '.join(unanswered)}"
            )
            return

        self.score = 0
        for i, user_answer in enumerate(self.user_answers):
            q_data = self.display_questions[i]
            correct_answers = [j for j, ans in enumerate(q_data['answers']) if ans['correct']]
            if user_answer in correct_answers:
                self.score += 1
        self.show_results()

    def show_results(self):
        total_questions = len(self.display_questions)
        percentage = (self.score / total_questions) * 100
        results_text = f"Результат: {self.score}/{total_questions} правильных ответов ({percentage:.1f}%)"
        self.results_label.config(text=results_text)
        self.results_frame.grid()

    def hide_results(self):
        self.results_label.config(text="")
        self.results_frame.grid_remove()

    def reset_test(self):
        self.user_answers = [None] * 5
        self.selected_buttons = [None] * 5
        self.score = 0

        for i, question_buttons in enumerate(self.answer_buttons):
            for button in question_buttons:
                button.config(bg="#808080", fg="white")

        self.hide_results()

if __name__ == "__main__":
    root = tk.Tk()
    app = SimpleTestSystem(root)
    root.mainloop()