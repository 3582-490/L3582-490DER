import os

def xor_encrypt(data, key=0xAA): # XOR key
    return bytes(b ^ key for b in data)

def convert_to_c_array(encrypted, var_name="encrypted_shellcode"):
    array = ', '.join(f'0x{b:02X}' for b in encrypted)
    return f"unsigned char {var_name}[] = {{ {array} }};"

def get_user_file():
    while True:
        file_path = input("Enter the path to the .bin file: ").strip()
        
        if not file_path:
            print("Error: Please enter a file path.")
            continue
            
        if not os.path.exists(file_path):
            print(f"Error: File '{file_path}' not found.")
            continue
            
        if not file_path.lower().endswith('.bin'):
            confirm = input("File does not have .bin extension. Continue? (y/n): ").lower()
            if confirm != 'y':
                continue
        
        return file_path

def main():
    try:
        input_file = get_user_file()
        
        with open(input_file, "rb") as f:
            data = f.read()
        
        print(f"File size: {len(data)} bytes")
        
        encrypted = xor_encrypt(data)
        c_array = convert_to_c_array(encrypted)
        
        with open("output.txt", "w") as out:
            out.write(c_array)
            out.write(f"\n\n// Original file: {input_file}")
            out.write(f"\n// File size: {len(data)} bytes")
            out.write(f"\n// XOR key: 0xAA")
        
        print("Encrypted array saved in output.txt")
        print(f"Array size: {len(encrypted)} bytes")
        
    except PermissionError:
        print("Error: Permission denied. Cannot read the file.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
