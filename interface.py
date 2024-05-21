"""
модуль интерфейса
"""

import sort
import input_output
from tkinter import Tk
from tkinter.filedialog import asksaveasfilename, askopenfilename
from os import getcwd as current_path


class Interface:
    """
    класс с функциями управления интерфейсом
    """
    def __init__(self):
        """
        инициализация объекта класса,
        загрузка последовательности
        """
        self.entered_sequence = self.load_sequence()
        self.result_sequence = []

    def load_sequence(self):
        """
        функция загрузки массива
        """
        while True:
            load_way = input('выберите способ ввода:\n'
                             '\tf -- из файла\n'
                             '\tr -- случайные\n'
                             '\tk -- с клавиатуры\n>>> ').lower()
            if load_way not in ('f', 'r', 'k'):
                print('выберите один из предложенных способов!')
                continue
            else:
                break

        if load_way == 'f':
            loaded_sequence = input_output.load_from_file(askopenfilename(
                title='файл с последовательностью', initialdir=current_path()))
        elif load_way == 'r':
            loaded_sequence = input_output.load_random_digits()
        elif load_way == 'k':
            loaded_sequence = input_output.load_from_input()
            
        return loaded_sequence

    def print(self):
        """
        метод вывода введённой последовательности
        """
        print('изначальная последовательность')
        input_output.pprint(self.entered_sequence, compact=True)

    def sort_sequence(self):
        """
        метод сортировки загруженного массива
        """
        self.result_sequence = sort.sort(self.entered_sequence)

    def save_sorted_sequence(self):
        """
        метод сохранения отсортированного массива
        """
        if not len(self.result_sequence):
            print('последовательность не отсортирована!')

        save = input('сохранить в файл? y/n: ').lower()
        if save in ('да', 'д', 'y', 'yes'):
            input_output.save(self.result_sequence,
                              asksaveasfilename(title='сохранение результата',
                                                initialdir=current_path()))
        else:
            input_output.pprint(self.result_sequence, compact=True)


if __name__ == '__main__':
    root = Tk()

    while True:
        i = Interface()
        i.print()
        i.sort_sequence()
        i.save_sorted_sequence()

    root.destroy()
