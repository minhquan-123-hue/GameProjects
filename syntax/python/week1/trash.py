user= input("")
print(user,"\n")
new = user.rsplit("/",1) # maxsplit == quantity want change if you want 1 / it will change 1 / from the right be a list (an array of the strings )
c_new = new[1]
print(new)
print(c_new,"\n")

new_1 = user.split("/",1)
c_new_1 = new_1[1]
print(new_1)
print(c_new_1)