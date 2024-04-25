"""
модуль сортировки
"""

def sort(sorting_sequence, place_number=0):
    """
    Shell sort
    """
    sorted_sequence = sorting_sequence[:]
    
    interval = len(sorted_sequence) // 2
    while interval > 0:
        for i in range(interval, len(sorted_sequence)):
            temp = int(sorted_sequence[i])
            j = i
            while j >= interval and int(sorted_sequence[j - interval]) > int(temp):
                sorted_sequence[j] = sorted_sequence[j - interval]
                j -= interval

            sorted_sequence[j] = temp
        interval //= 2
    sorted_sequence = list(map(str, sorted_sequence))
    return sorted_sequence
