import subprocess

def format_c_code_file(input_file: str, output_file: str):
    # Чтение содержимого исходного файла
    with open(input_file, 'r') as f:
        code = f.read()

    # Запуск clang-format с помощью subprocess
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
    
    # Запись отформатированного кода в выходной файл
    with open(output_file, 'w') as f:
        f.write(formatted_code)

input_file = './output/prog.c'
output_file = './output/formatted_prog.c'
format_c_code_file(input_file, output_file)
