from collections import Counter
import re
from itertools import islice
import math


#тут просто реалізовані функції
#думаю, що ще й вивід результатів сюди вставляти не варто
#для виводу краще виділити окремий файл



#функції треба дати тільки текст, та його довжину
#див. приклад використання в іншому файлі
def SeparateSymbolFrequency(content, total_length):
    for char, count in content.items():
        frequency_ws = count / total_length
        print(f"'{char}' = {count} ->  {frequency_ws:.4f}")

    print("\nСимволи з найбільшими частотами (топ 5) :")
    print(content.most_common(5))



#для цієх функції параметр step уточнює відстань між символами
#1 - біграми з перетином
#2 - біграми без перетину
def BigramsFrequency(content, step):
    bigrams = [content[i : i + 2] for i in range(0, len(content) - 1, step)]
    counted_bigrams = Counter(bigrams)
    total_bigrams = sum(counted_bigrams.values())
    
    for bigram, count in counted_bigrams.items():
        frequency_bigrams = count / total_bigrams
        print(f"'{bigram}' = {count} -> {frequency_bigrams:.4f}")

    print("\nБіграми з найбільшими частотами (топ 5) :")
    print(counted_bigrams.most_common(5))

    result = [counted_bigrams, total_bigrams]
    return result


#тут зрозуміло
#total_count попередньо треба отримати з функцій,
#що стосуються типів n-грам, які вас цікавлять
def Entropy(content, total_count, n):
    entropy = 0.0
    for count in content.values():
        p = count / total_count
        entropy += -p * math.log2(p)
    return entropy / n  # ділимо на 1 для монограм, на 2 для біграм