import sqlite3
import tkinter as tk
from tkinter import ttk, messagebox
from datetime import datetime

class StoreApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Магазин")
        self.conn = sqlite3.connect('store.db')
        self.cart = []

        self.create_db()
        self.setup_ui()

    def create_db(self):
        cursor = self.conn.cursor()
        cursor.executescript('''
            CREATE TABLE IF NOT EXISTS products (
                id INTEGER PRIMARY KEY,
                name TEXT, price REAL, stock REAL
            );
            CREATE TABLE IF NOT EXISTS receipts (
                id INTEGER PRIMARY KEY,
                date TEXT, cashier INTEGER
            );
            CREATE TABLE IF NOT EXISTS sale_items (
                id INTEGER PRIMARY KEY,
                receipt_id INTEGER, product_id INTEGER, qty REAL,
                FOREIGN KEY(receipt_id) REFERENCES receipts(id),
                FOREIGN KEY(product_id) REFERENCES products(id)
            );
        ''')
        cursor.execute("SELECT COUNT(*) FROM products")
        if cursor.fetchone()[0] == 0:
            products = [("Хлеб", 50, 10), ("Молоко", 89, 8), ("Сыр", 350, 5), ("Кола", 75, 20)]
            cursor.executemany("INSERT INTO products (name, price, stock) VALUES (?,?,?)", products)
        self.conn.commit()

    def setup_ui(self):
        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(fill='both', expand=True)

        self.sale_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.sale_frame, text="Продажа")

        ttk.Label(self.sale_frame, text="Товар:").grid(row=0, column=0)
        self.product_cb = ttk.Combobox(self.sale_frame, width=30)
        self.product_cb.grid(row=0, column=1)
        self.product_cb.bind('<<ComboboxSelected>>', self.on_select)

        self.info_label = ttk.Label(self.sale_frame, text="")
        self.info_label.grid(row=1, column=0, columnspan=2)

        ttk.Label(self.sale_frame, text="Кол-во:").grid(row=2, column=0)
        self.qty_entry = ttk.Entry(self.sale_frame, width=20)
        self.qty_entry.grid(row=2, column=1)

        ttk.Button(self.sale_frame, text="Добавить", command=self.add).grid(row=3, column=0, columnspan=2, pady=5)

        self.cart_tree = ttk.Treeview(self.sale_frame, columns=('name', 'qty', 'sum'), show='headings', height=8)
        self.cart_tree.heading('name', text='Товар')
        self.cart_tree.heading('qty', text='Кол-во')
        self.cart_tree.heading('sum', text='Сумма')
        self.cart_tree.grid(row=4, column=0, columnspan=2, pady=5)

        ttk.Button(self.sale_frame, text="Оформить", command=self.checkout).grid(row=5, column=0, columnspan=2, pady=5)

        self.report_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.report_frame, text="Отчёт")

        ttk.Label(self.report_frame, text="Дата (ГГГГ-ММ-ДД):").grid(row=0, column=0)
        self.date_entry = ttk.Entry(self.report_frame, width=15)
        self.date_entry.grid(row=0, column=1)
        self.date_entry.insert(0, datetime.now().strftime("%Y-%m-%d"))
        ttk.Button(self.report_frame, text="Показать", command=self.report).grid(row=0, column=2)

        self.report_tree = ttk.Treeview(self.report_frame, columns=('name', 'qty', 'revenue'), show='headings',
                                        height=10)
        self.report_tree.heading('name', text='Товар')
        self.report_tree.heading('qty', text='Продано')
        self.report_tree.heading('revenue', text='Выручка')
        self.report_tree.grid(row=1, column=0, columnspan=3, pady=5)

        self.total_label = ttk.Label(self.report_frame, text="")
        self.total_label.grid(row=2, column=0, columnspan=3)

        self.load_products()

    def load_products(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT id, name, price, stock FROM products")
        self.products = cursor.fetchall()
        self.product_cb['values'] = [f"{p[1]} ({p[3]} шт.)" for p in self.products]

    def on_select(self, event):
        idx = self.product_cb.current()
        if idx >= 0:
            self.current = self.products[idx]
            self.info_label.config(text=f"Цена: {self.current[2]} руб. | Остаток: {self.current[3]}")

    def add(self):
        if not hasattr(self, 'current'):
            messagebox.showerror("Ошибка", "Выберите товар")
            return
        try:
            qty = float(self.qty_entry.get())
            if qty <= 0 or qty > self.current[3]:
                raise ValueError
        except:
            messagebox.showerror("Ошибка", f"Введите кол-во от 1 до {self.current[3]}")
            return

        self.cart.append((self.current[0], self.current[1], self.current[2], qty))
        self.update_cart()
        self.qty_entry.delete(0, tk.END)

    def update_cart(self):
        for row in self.cart_tree.get_children():
            self.cart_tree.delete(row)
        total = 0
        for _, name, price, qty in self.cart:
            summ = price * qty
            total += summ
            self.cart_tree.insert('', 'end', values=(name, qty, f"{summ:.2f}"))
        self.cart_tree.insert('', 'end', values=('ИТОГО', '', f"{total:.2f}"), tags=('total',))
        self.cart_tree.tag_configure('total', background='lightgray')

    def checkout(self):
        if not self.cart:
            messagebox.showwarning("Внимание", "Корзина пуста")
            return
        try:
            cursor = self.conn.cursor()
            cursor.execute("INSERT INTO receipts (date, cashier) VALUES (?, 1)", (datetime.now().isoformat(),))
            receipt_id = cursor.lastrowid

            for prod_id, name, price, qty in self.cart:
                cursor.execute("INSERT INTO sale_items (receipt_id, product_id, qty) VALUES (?,?,?)",
                               (receipt_id, prod_id, qty))
                cursor.execute("UPDATE products SET stock = stock - ? WHERE id = ?", (qty, prod_id))

            self.conn.commit()
            total = sum(p * q for _, _, p, q in self.cart)
            messagebox.showinfo("Успех", f"Чек #{receipt_id}\nСумма: {total:.2f} руб.")
            self.cart.clear()
            self.update_cart()
            self.load_products()
        except Exception as e:
            self.conn.rollback()
            messagebox.showerror("Ошибка", str(e))

    def report(self):
        date = self.date_entry.get()
        cursor = self.conn.cursor()
        cursor.execute('''
            SELECT p.name, SUM(s.qty), SUM(s.qty * p.price)
            FROM sale_items s
            JOIN products p ON s.product_id = p.id
            JOIN receipts r ON s.receipt_id = r.id
            WHERE DATE(r.date) = DATE(?)
            GROUP BY p.id
        ''', (date,))
        rows = cursor.fetchall()

        for row in self.report_tree.get_children():
            self.report_tree.delete(row)

        if not rows:
            self.total_label.config(text=f"За {date} продаж нет")
            return

        total = 0
        for name, qty, revenue in rows:
            self.report_tree.insert('', 'end', values=(name, f"{qty:.1f}", f"{revenue:.2f}"))
            total += revenue
        self.total_label.config(text=f"Общая выручка: {total:.2f} руб.")


root = tk.Tk()
root.geometry("650x500")
StoreApp(root)
root.mainloop()