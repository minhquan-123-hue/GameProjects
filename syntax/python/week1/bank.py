def main():
    greet = input("Greeting: ").strip().lower()

    if greet.startswith("hello"):
        print("0$")
    elif greet.startswith("h"):
        print("20$")
    else:
        print("100$")
    
if __name__ == "__main__":
    main()