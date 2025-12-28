class Word:
    def __init__(self, word):
        if not isinstance(word, str) or not word.isalpha():
            raise TypeError("Слово должно иметь тип str")
        if not all('a' <= i.lower() <= 'z' for i in word):
            raise ValueError("Слово должно состоять только из латинских букв")
        self.word = word

    def __eq__(self, other):
        if isinstance(other, Word):
            return len(self.word) == len(other.word)
        else:
            return NotImplemented

    def __ne__(self, other):
        if isinstance(other, Word):
            return len(self.word) != len(other.word)
        else:
            return NotImplemented

    def __lt__(self, other):
        if isinstance(other, Word):
            return len(self.word) < len(other.word)
        else:
            return NotImplemented

    def __le__(self, other):
        if isinstance(other, Word):
            return len(self.word) <= len(other.word)
        else:
            return NotImplemented

    def __gt__(self, other):
        if isinstance(other, Word):
            return len(self.word) > len(other.word)
        else:
            return NotImplemented

    def __ge__(self, other):
        if isinstance(other, Word):
            return len(self.word) >= len(other.word)
        else:
            return NotImplemented

    def __str__(self):
        return self.word.capitalize()

    def __repr__(self):
        return f"Word({self.word})"

w1 = Word('danya')
w2 = Word('olga')

print(w1 == w2)
print(w1 != w2)
print(w1 < w2)
print(w1 <= w2)
print(w1 > w2)
print(w1 >= w2)

print(w1)
print(repr(w2))