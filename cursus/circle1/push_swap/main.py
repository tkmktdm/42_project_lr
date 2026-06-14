# イメージ（疑似コード）
a = [1,4,2,3]
mistakes = 0
total_pairs = 0
for i in range(len(a)):
    for j in range(i+1, len(a)):
        total_pairs += 1
        if a[i] > a[j]:
            mistakes += 1
disorder = mistakes / total_pairs
print(disorder)
