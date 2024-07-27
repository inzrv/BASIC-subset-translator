import os
import subprocess

def main():
    build_dir = "build"

    # Создаем директорию build, если она не существует
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    # Переходим в директорию build
    os.chdir(build_dir)

    # Вызываем cmake ..
    cmake_command = ["cmake", ".."]
    make_command = ["make"]

    try:
        subprocess.run(cmake_command, check=True)
        subprocess.run(make_command, check=True)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred while running command: {e.cmd}")
        print(f"Return code: {e.returncode}")
        exit(1)

    print("Build completed successfully.")

if __name__ == "__main__":
    main()
