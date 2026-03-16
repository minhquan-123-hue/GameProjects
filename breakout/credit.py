number = 4003600000000014

position = 1
while (number > 0):
    digit = number % 10 # dấu % là cái gì ?
    print(digit)
    position += 1
    if (number == 0):
        break