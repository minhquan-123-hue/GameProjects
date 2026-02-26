
radius = 3
diameter_distance = [-3,-2,-1,0,1,2,3]

for radius_y in diameter_distance:
    for radius_x in diameter_distance:
        if (radius_y * radius_y + radius_x * radius_x) <= radius * radius: 
            print("*" , end="")
        else:
            print(" ", end="")
    print()    
            
