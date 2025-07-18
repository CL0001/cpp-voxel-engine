import os
import shutil
import subprocess


def configure_project():
    if not shutil.which("cmake"):
        print("[CONFIG][ERROR] CMake not found.")
        exit(1)

    build_dir_path = os.path.join(os.path.dirname(__file__), "../build")

    if not os.path.exists(build_dir_path):
        print("[CONFIG][INFO] Build directory not found.")
        print("[CONFIG][INFO] Creating 'build' directory...")
        os.makedirs(build_dir_path)
    else:
        print("[CONFIG][INFO] Build directory found.")
        print("[CONFIG][INFO] Configuring project...")

    os.chdir(build_dir_path)

    cmake_configure_command = ["cmake", ".."]

    try:
        subprocess.check_call(cmake_configure_command)
        print("[CONFIG][INFO] Configuration completed successfully.")
    except subprocess.CalledProcessError as error:
        print("[CONFIG][ERROR] Configuration failed.")
        exit(1)


def build_project():
    cmake_build_command = ["cmake", "--build", "."]

    try:
        subprocess.check_call(cmake_build_command)
        print("[BUILD][INFO] Build completed successfully.")
    except subprocess.CalledProcessError:
        print("[BUILD][ERROR] Build failed.")
        exit(1)


if __name__ == "__main__":
    configure_project()
    build_project()