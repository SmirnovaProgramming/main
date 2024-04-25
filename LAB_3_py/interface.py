"""
модуль интерфейса
"""

import sort
import base
from tkinter import Tk, END, VERTICAL, IntVar, Scale, HORIZONTAL, Menu, Toplevel
from tkinter.scrolledtext import ScrolledText
from tkinter.ttk import Button, Label, Treeview, Scrollbar, Progressbar
from tkinter.messagebox import showwarning, showinfo, showerror
from tkinter.filedialog import asksaveasfilename, askopenfilename
from os import getcwd as current_path
from os.path import exists
from random import randint
from threading import Thread


class TextEntry(ScrolledText):
    """
    объект пролистываемого текстового поля с удобным интерфейсом управления для данной задачи
    """
    def fill(self, text):
        self.delete('1.0', END)
        self.insert('1.0', text)


class SequenceChoice(Toplevel):
    def __init__(self, outer_base, parent, type_='raw'):
        """
        инициализация объекта графического интерфейса
        """
        super().__init__(parent)
        seq_type = 'начальные' if type_ == 'raw' else 'отсортированные' if type_ == 'sorted' else ''
        self.title(seq_type + ' последовательности для загрузки')
        self.resizable(True, False)

        self.table = Treeview(self, show='headings', columns=('num', 'seq'))
        self.table.column('#1', width=10)
        self.table.heading('#1', text='№')
        self.table.column('#2', width=800)
        self.table.heading('#2', text='последовательность')
        self.table.grid(row=0, column=0, sticky='new')

        ysb = Scrollbar(self, orient=VERTICAL, command=self.table.yview)
        self.table.configure(yscrollcommand=ysb.set)
        ysb.grid(row=0, column=1, sticky='ns')

        Button(self, text='загрузить', command=self.choice_sequence).grid(row=1, column=0, sticky='new')

        self.table.bind('<Double-1>', self.choice_sequence)

        # загрузка записей из базы
        sequences = outer_base.show(type_)
        if len(sequences):
            for ind, sequence in enumerate(sequences, start=1):
                self.table.insert("", END, values=(ind, *sequence))

        self.type = type_

        self.columnconfigure(0, weight=1)

        self.grab_set()
        self.focus_set()

    def choice_sequence(self, event=None):
        """
        выбор последовательности из списка, параметр event передаётся при двойном нажатии
        """
        selection = self.table.selection()
        if len(selection) == 0:
            showwarning(master=self, title='неправильный параметр', detail='выберите хотя бы одну строку')
        elif len(selection) > 1:
            showwarning(master=self, title='неправильный параметр', detail='выберите только одну строку')
        else:
            if self.type == 'raw':
                self.master.entry.fill(self.table.item(selection[0])['values'][1])
            elif self.type == 'sorted':
                self.master.answer.fill(self.table.item(selection[0])['values'][1])
            self.destroy()


class RandomChoice(Toplevel):
    quantity_range = 1, 1000
    length_range = 1, 150

    def __init__(self, parent):
        """
        инициализация объекта графического интерфейса
        """
        super().__init__(parent)
        self.resizable(False, False)
        self.title('создание последовательности из случайных чисел')

        Label(self, text='количество элементов').grid(row=0, column=0, sticky='new')
        self.quantity = IntVar(self, value=1)
        Scale(self, variable=self.quantity, from_=self.quantity_range[0], orient=HORIZONTAL, length=800,
              to=self.quantity_range[1]).grid(row=0, column=1, sticky='new', columnspan=2)

        Label(self, text='максимальная длина элементов').grid(row=1, column=0, sticky='new')
        self.length = IntVar(self, value=1)
        Scale(self, variable=self.length, from_=self.quantity_range[0], orient=HORIZONTAL, length=800,
              to=self.length_range[1]).grid(row=1, column=1, sticky='new', columnspan=2)

        Label(self, text='последовательность').grid(row=2, column=0, sticky='new')

        self.entry = TextEntry(self, height=10, width=110)
        self.entry.grid(row=3, column=0, columnspan=2, rowspan=2, sticky='new')

        Button(self, text='создать', command=self.create_sequence).grid(row=3, column=2)
        Button(self, text='загрузить', command=self.send_to_parent).grid(row=4, column=2)

        self.grab_set()
        self.focus_set()

    def create_sequence(self):
        result_sequence = tuple([str(randint(0, 10 ** randint(0, self.length.get())))
                                 for i in range(self.quantity.get())])
        self.entry.fill(' '.join(result_sequence))

    def send_to_parent(self):
        self.master.entry.fill(self.entry.get('1.0', END))
        self.destroy()


class Interface(Tk):
    """
    класс с функциями управления интерфейсом
    """

    def __init__(self):
        """
        инициализация объекта графического интерфейса
        """
        super().__init__()
        self.resizable(False, False)
        self.title('Shell sort / Сортировка Шелла')

        Label(self, text='Начальная последовательность').grid(row=0, column=0, sticky='new')
        self.entry = TextEntry(self, height=10, width=110)
        self.entry.grid(row=1, column=0, columnspan=3, sticky='new')

        Label(self, text='Отсортированная последовательность').grid(row=2, column=0, sticky='new')
        self.answer = TextEntry(self, height=10, width=110)
        self.answer.grid(row=3, column=0, columnspan=3, sticky='new')

        main_menu = Menu(self, tearoff=False)

        load_menu = Menu(main_menu, tearoff=False)

        load_raw_menu = Menu(load_menu, tearoff=False)
        load_raw_menu.add_command(label='Из базы', command=self.load_sequence_from_base)
        load_raw_menu.add_command(label='Из файла', command=self.load_sequence_from_file)
        load_raw_menu.add_command(label='Случайные', command=self.load_sequence_random)
        load_menu.add_cascade(label='Начальную', menu=load_raw_menu)

        load_sorted_menu = Menu(load_menu, tearoff=False)
        load_sorted_menu.add_command(label='Из базы', command=self.load_sorted_sequence_from_base)
        load_menu.add_cascade(label='Отсортированную', menu=load_sorted_menu)

        main_menu.add_cascade(label='Загрузить', menu=load_menu)

        save_menu = Menu(main_menu, tearoff=False)

        raw_seq_menu = Menu(save_menu, tearoff=False)
        raw_seq_menu.add_command(label='В базу', command=self.save_raw_sequence_to_base)
        raw_seq_menu.add_command(label='В файл', command=self.save_raw_sequence_to_file)
        save_menu.add_cascade(label='Начальную', menu=raw_seq_menu)

        sort_seq_menu = Menu(save_menu, tearoff=False)
        sort_seq_menu.add_command(label='В базу', command=self.save_sorted_sequence_to_base)
        sort_seq_menu.add_command(label='В файл', command=self.save_sorted_sequence_to_file)
        save_menu.add_cascade(label='Отсортированную', menu=sort_seq_menu)

        main_menu.add_cascade(label='Сохранить', menu=save_menu)

        main_menu.add_command(label='Очистить', command=self.clear_text_entries)

        self.config(menu=main_menu)

        self.start_sort_button = Button(self, text='Отсортировать', command=self.start_new_sort_thread)
        self.start_sort_button.grid(row=4, column=0, columnspan=3, sticky='new')

        self.base = base.Base()

        self.progress = Progressbar(self, mode='indeterminate')

    def start_new_sort_thread(self):
        """
        создание потока, в котором выполняется сортировка, для поддержки работы основного окна
        """
        Thread(target=self.sort_sequence).start()

    def sort_sequence(self):
        self.start_sort_button.config(state='disable')
        self.progress.grid(row=5, column=0, columnspan=3, sticky='new')
        self.progress.start()

        entered_sequence = self.entry.get('1.0', END).split()
        if not len(entered_sequence):
            showerror(title='Ошибка!', message='Пустая начальная последовательность!')
            return
        
        string = ''.join(entered_sequence)
        if string.isdigit() == False:
            showerror(title='Ошибка!', message='Введена некорректная последовательность! Допускаются только целочисленные числа.')
            return
        
        result_sequence = sort.sort(entered_sequence)
        self.answer.fill(' '.join(result_sequence))

        self.progress.stop()
        self.progress.grid_forget()
        self.start_sort_button.config(state='enable')

    def load_sequence_from_base(self):
        self.wait_window(SequenceChoice(self.base, self))

    def load_sequence_from_file(self):
        path_to_file = askopenfilename(initialdir=current_path(), title='выберите файл',
                                       filetypes=(('Текстовый', '.txt'),),
                                       defaultextension=(('Текстовый', '.txt'),))
        if path_to_file:
            if not exists(path_to_file):
                print(f'Файл "{path_to_file}" не существует')
                return None
            with open(path_to_file, encoding='utf-8') as outer_file:
                # вычленение всех подстрок разделённых пробелами
                entered_sequence = outer_file.read().strip().split()
                self.entry.fill(entered_sequence)

    def load_sequence_random(self):
        self.wait_window(RandomChoice(self))

    def save_raw_sequence_to_base(self):
        sequence = self.entry.get('1.0', END)
        self.base.add(sequence, 'raw')
        showinfo(title='успех', message='сохранено в базу')

    def save_raw_sequence_to_file(self):
        sequence = self.entry.get('1.0', END)
        path_to_file = asksaveasfilename(initialdir=current_path(), title='выберите название',
                                         filetypes=(('Текстовый', '.txt'),),
                                         defaultextension=(('Текстовый', '.txt'),))
        if path_to_file:
            with open(path_to_file, 'w', encoding='utf-8') as outer_file:
                outer_file.write(sequence)
        showinfo(title='успех', message='сохранено в файл')

    def save_sorted_sequence_to_base(self):
        sequence = self.answer.get('1.0', END)
        self.base.add(sequence, 'sorted')
        showinfo(title='успех', message='сохранено в базу')

    def save_sorted_sequence_to_file(self):
        sequence = self.answer.get('1.0', END)
        path_to_file = asksaveasfilename(initialdir=current_path(), title='выберите название',
                                         filetypes=(('Текстовый', '.txt'),),
                                         defaultextension=(('Текстовый', '.txt'),))
        if path_to_file:
            with open(path_to_file, 'w') as outer_file:
                outer_file.write(sequence)
        showinfo(title='успех', message='сохранено в файл')

    def load_sorted_sequence_from_base(self):
        self.wait_window(SequenceChoice(self.base, self, 'sorted'))

    def clear_text_entries(self):
        self.entry.fill('')
        self.answer.fill('')


if __name__ == '__main__':
    root = Interface()

    root.mainloop()
