def dollar_to_float(dollar: str) -> float:
    dollar = dollar.replace("$","")
    return (float(dollar))

def percentage_to_float(percentage: str) ->float:
    percentage = percentage.replace("%","")
    return (float(percentage))

def main():
    dollar = input("how much is your meal? ")
    percentage = input("how much do you want to pay? ")
    tip:float = (dollar_to_float(dollar) / 100)* percentage_to_float(percentage) 

    print(f"This is money you want to tip: ${tip:.2f}")

if __name__ == "__main__":
    main()

