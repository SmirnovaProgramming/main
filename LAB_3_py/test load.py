import os

import base
import sort
from random import randint
import time
import traceback
from os import remove


def add_to_(base_object, sequence_number, max_elements_length=2, max_elements_number=5):
    for sequence_iter in range(sequence_number):
        elements_length, elements_number = randint(1, max_elements_length), randint(1, max_elements_number)
        sequence = tuple([str(randint(0, 10 ** randint(0, elements_length))) for i in range(elements_number)])
        base_object.add(sequence, 'raw')


def sort_sequences_of_(base_object):
    for sequence in base_object.show('raw'):
        sort.sort(sequence)


def clear_(base_object):
    base_object.clear()


b = base.Base('test.db')
b.clear()

for number in (100, 1000, 10000):
    print('-' * 100)
    print('test load {}'.format(number))
    try:
        print('load:\n')
        start = time.time()
        add_to_(b, number)
        load_time = time.time() - start
        print('\tsuccess\n')
        print('\ttotal:\t\t{}\n\tper iter:\t{}'.format(load_time, load_time / number))
    except Exception:
        print('\tfail\n')
        traceback.print_exc()

    try:
        print('sort:\n')
        sort_time = [0, 0, 0]
        start = time.time()
        for i in range(3):
            start = time.time()
            sort_sequences_of_(b)
            sort_time[0] += (time.time() - start)
        avg_sort_time = sort_time[0] / 3 
        print('\tsuccess\n')
        print('\ttotal:\t\t{}\n\tper iter:\t{}'.format(avg_sort_time, avg_sort_time / number))
    except Exception:
        print('\tfail\n')
        traceback.print_exc()

    try:
        print('clear:\n')
        start = time.time()
        clear_(b)
        clear_time = time.time() - start
        print('\tsuccess\n')
        print('\ttotal:\t\t{}'.format(clear_time))
    except Exception:
        print('\tfail\n')
        traceback.print_exc()
os.system("PAUSE")
del b
remove('test.db')
