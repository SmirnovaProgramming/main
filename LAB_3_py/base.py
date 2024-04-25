import sqlite3
import datetime


class Base:
    """
    класс управления базой данных
    """
    def __init__(self, db_path='base.db'):
        self.connection = sqlite3.connect(db_path)
        self.cursor = self.connection.cursor()

        self.cursor.execute('CREATE TABLE IF NOT EXISTS sequences '
                            '(sequence TEXT,'
                            ' type TEXT)')
        self.connection.commit()

    def add(self, sequence, type_):
        """
        процедура добавления поледовательности в базу данных
        """
        date = datetime.datetime.now().strftime('%d.%m.%Y %H:%M:%S')
        assert type_ in ('raw', 'sorted'), 'incorrect type'

        if type(sequence) == str:
            sequence = sequence.split()
        if not all([type(element) == str for element in sequence]):
            sequence = list(map(str, sequence))
        self.cursor.execute('INSERT INTO sequences (sequence, type) VALUES ("{}", "{}")'
                            ''.format(' '.join(sequence), type_, date))
        self.connection.commit()
    
    def show(self, type_):
        """
        процедура получения последовательностей из базы данных
        """
        self.cursor.execute(f'SELECT sequence FROM sequences WHERE type="{type_}"')
        return self.cursor.fetchall()

    def clear(self):
        """
        процедура удаления всех последовательностей из базы данных
        """
        self.cursor.execute('DELETE FROM sequences')
        self.connection.commit()

    def __del__(self):
        """
        деструктор объекта базы
        """
        self.connection.close()
        
