def convert(text:str) -> str:
    text = text.replace(":)","happy")
    text = text.replace(":(","sad")
    return text

def main():
    user_input:str = input("Input: ").strip()
    print(convert(user_input))

if __name__ == "__main__":
    main()
