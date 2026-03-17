card = 4003600000000014

sum = 0
digit = 0
temp_card = card
position = 1
while (temp_card > 0):
    digit = temp_card % 10 # cái này để chia dư tức là lấy từng số từ bên phải sang 

    if (position % 2 == 0):
        digit = digit * 2
        print("digit: ",digit)
        sum = sum + digit
        print("sum: ", sum)
    position += 1 # biến này và total_digits giống nhau 

    temp_card = round(temp_card / 10) # dùng hàm này để loại bỏ phần thập phân 


print(sum) 
print(position) # nó in ra là 340 total_digits tức là nó đã chạy 340 vòng lặp , mà nếu đúng ra nó chỉ chạy 15 vòng thôi , vì mình muốn vứt bỏ cái "chữ số" đã tính rổi đi 

