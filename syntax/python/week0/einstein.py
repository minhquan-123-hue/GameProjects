def energy(mass: int) -> int:

    c:int = 300
    mass = mass * c * c

    return mass

def main():
    mass = int(input("mass: "))
    print(energy(mass))

if __name__ == "__main__":
    main()
