def main():
    print("[DEBUG] Program started")

    filename = input("File name: ")
    print(f"[DEBUG] Raw input: {filename!r}")

    filename = filename.strip().lower()
    print(f"[DEBUG] Normalized filename: {filename!r}")

    # how to use isinstance() syntax(parameter)
    assert isinstance(filename, str), "[ASSERT] filename is not a string"

    # Extract extension
    # “What *kind* of "if/elif/else,assert" in this? in keyword, syntax , statement , or else ..
    if "." in filename:
        print("[DEBUG] Dot found in filename")
        # how to use rsplit() syntax(paramter) ?
        extension = filename.rsplit(".", 1)[1]
    else:
        print("[DEBUG] No dot found in filename")
        extension = ""

    print(f"[DEBUG] Extracted extension: {extension!r}")
    assert isinstance(extension, str), "[ASSERT] extension is not a string"

    if extension == "gif":
        print("[DEBUG] Matched GIF")
        result = "image/gif"

    elif extension == "jpg" or extension == "jpeg":
        print("[DEBUG] Matched JPG/JPEG")
        result = "image/jpeg"

    else:
        print("[DEBUG] Extension not recognized, using default")
        result = "application/octet-stream"

    print(f"[DEBUG] Result MIME type: {result}")
    assert "/" in result, "[ASSERT] Invalid MIME format"

    print(result)
    print("[DEBUG] Program finished successfully")


if __name__ == "__main__":
    print("[DEBUG] __name__ == '__main__'")
    main()


