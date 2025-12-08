# this is day is comeback to write all the project in python to connect with other new programing language that i learn 

# what is def ? what is return ? what is print ? what is __name__ & "__main__" ? are those function built-in ?
def energy(mass: int) -> int:
    """
    Return the energy equivalent (in Joules) of a given mass using E = m * c^2
    """
    c: int = 300_000_000
    return mass * c * c 

def main() -> None:
    mass: int = int(input("m: "))
    print(energy(mass))

if __name__ == "__main__":
    main()