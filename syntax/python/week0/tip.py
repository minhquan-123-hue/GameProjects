# this is second problem set convert python to c 

# what is the different bewteen these lines of python with c ?
def dollars_to_float(dollars: str) -> float:
    # Remove the leading "$" and convert the rest to float
    # what is replace() ? how to use it ? is that function built-in ? 
    return float(dollars.replace("$",""))

def percent_to_float(percent: str) -> float:
    # Remove the trailing "%" and convert to float, then divide by 100
    return float(percent.replace("%", "")) / 100

def main()->None:
    dollars : str = dollars_to_float(input("How much was the meal? "))
    percent : str= percent_to_float(input("what percentage would you like to tip? "))

    tip: float = dollars * percent
    # what is :.2f ? is that format specification ? how to use it ?
    print(f"Leave ${tip:.2f}")

if __name__ == "__main__":
    main()
