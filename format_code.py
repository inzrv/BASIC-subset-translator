import sys
import subprocess

def format_c_code_file(input_file: str, output_file: str):
    with open(input_file, 'r') as f:
        code = f.read()

    process = subprocess.Popen(
        ['clang-format'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    stdout, stderr = process.communicate(input=code.encode('utf-8'))
    
    if process.returncode != 0:
        raise RuntimeError(f"clang-format failed with error: {stderr.decode('utf-8')}")
    
    formatted_code = stdout.decode('utf-8')
    
    with open(output_file, 'w') as f:
        f.write(formatted_code)

def main():
    if len(sys.argv) < 2:
        print("Usage: python format_code.py <file1> [file2]")
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else input_file

    format_c_code_file(input_file, output_file)


if __name__ == "__main__":
    main()