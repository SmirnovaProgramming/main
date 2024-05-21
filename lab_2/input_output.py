"""
модуль ввода / вывода
"""

from random import randint
from os.path import exists
from pprint import pprint, pformat


def load_from_file(path_to_file):
    """
    функция загрузки из файла

    path_to_file: str -- путь до файла
    """
    if not exists(path_to_file):
        print(f'файл "{path_to_file}" не существует')
        return None
    with open(path_to_file) as outer_file:
        # вычленение всех подстрок разделённых пробелами
        result_sequence = outer_file.read().strip().split()
    return result_sequence


def load_random_digits():
    """
    функция создания последовательности из числовых подстрок
    """
    while True:
        try:
            elements_number = int(input('введите количество элементов: '))
            if elements_number <= 0:
                raise ValueError
            break
        except ValueError:
            print('введите корректное значение!')
    while True:
        try:
            elements_lenght = int(input('введите максимальную длину элементов: '))
            if elements_lenght <= 0:
                raise ValueError
            break
        except ValueError:
            print('введите корректное значение!')
    
    result_sequence = list([str(randint(0, 10**randint(0, elements_lenght))) for i in range(elements_number)])
    return result_sequence


def load_from_input():
    """
    функция загрузки данных вводимых с клавиатуры
    """
    # получение элементов из ввода пользователем
    result_sequence = input('введите элементы через пробел:\n').strip().split()
    return result_sequence


def save(sorted_sequence, path_to_file):
    """
    метод сохранения отсортированных данных
    """
    with open(path_to_file, 'w') as out_file:
        out_file.write(' '.join(sorted_sequence))
