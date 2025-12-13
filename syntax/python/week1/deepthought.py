def main():
    anwser = input("what is the answer for life? ")

    normalize = anwser.strip().lower()

    if normalize == "42" or normalize == "forty-two" or normalize == "forty two" or normalize == "FORTY-TWO" or normalize == "Forty Two":
        print("That's right answer")
    else:
        print("Not a deep thought")

if __name__ == "__main__":
    main()