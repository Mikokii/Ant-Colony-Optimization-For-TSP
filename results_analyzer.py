import re

print("Type path to file that you want to analyze")
input = input()

f = open(input, 'r')

text = f.readlines()
count = 0
results = {}

for line in text:
    if line == "---------- Best Result ----------\n":
        break
    if count%4 == 0:
        key = re.sub(r' It: \d+ ', ' ', line)
        key = re.sub(r' t: \d+(\.\d+)?\n', '', key)
        if key not in results.keys() and key != "\n":
            results[key] = []
    if count%4 == 1:
        match = re.search(r'\d+(\.\d+)?', line)
        if match:
            number = float(match.group())
            results[key].append(number)
        else:
            print("Number not found")
            f.close()
            exit(1)
    count += 1

for key in results:
    results[key] = round(sum(results[key])/len(results[key]),2)

for key, value in results.items():
    print(key, value)

f.close()