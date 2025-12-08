# this is second problem set convert python to c 

def dollars_to_float(dollars: str) -> float:
    # Remove the leading "$" and convert the rest to float
    return float(dollars.replace("$",""))

def percent_to_float(percent: str) -> float:
    # Remove the trailing "%" and convert to float, then divide by 100
    return float(percent.replace("%", "")) / 100

def main():
    dollars = dollars_to_float(input("How much was the meal?"))
    percent = percent_to_float(input("what percentage would you like to tip"))
    tip = dollars * percent
    print(f"Leave ${tip:2f}")

if __name__ == "__name__":
    main()
