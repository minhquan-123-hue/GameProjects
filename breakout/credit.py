number = 4003600000000014

position = 1 
print("đây là vị trí đầu tiên: ", position)
while (number > 0):
    number = number // 10
    position += 1


    if (position == 16):
        print("đây là vị trí của số 16:", position)
        print("number: ", number)

    if (number == 0):
        print("đây là vị trí khi mà chia còn không: ", position)

""" position có tổng là 17 vì để vị trí là một đầu tiên và mỗi """