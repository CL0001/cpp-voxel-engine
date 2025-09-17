import os
import shutil
import subprocess
import argparse
import sys


SCRIPT_DIR = os.path.dirname(__file__)
DEFAULT_BUILD_DIR = os.path.join(SCRIPT_DIR, "../build")
DEFAULT_BINARY = os.path.join(DEFAULT_BUILD_DIR, "source", "app", "Debug", "VoxelEngine.exe")

GENERATOR_MAP = {
    "vs2022": "Visual Studio 17 2022"
}


def configure_project(build_dir, build_type, generator):
    if not shutil.which("cmake"):
        print("[CONFIG][ERROR] CMake not found.")
        sys.exit(1)

    if not os.path.exists(build_dir):
        print(f"[CONFIG][INFO] Creating build directory at {build_dir}...")
        os.makedirs(build_dir)
    else:
        print(f"[CONFIG][INFO] Build directory found at {build_dir}.")

    os.chdir(build_dir)

    cmake_command = ["cmake", "..", f"-DCMAKE_BUILD_TYPE={build_type}"]
    if generator:
        cmake_command.extend(["-G", GENERATOR_MAP[generator]])

    print(f"[CONFIG][INFO] Configuring project with: {' '.join(cmake_command)}")
    try:
        subprocess.check_call(cmake_command)
        print("[CONFIG][INFO] Configuration completed successfully.")
    except subprocess.CalledProcessError:
        print("[CONFIG][ERROR] Configuration failed.")
        sys.exit(1)


def build_project(build_dir):
    os.chdir(build_dir)
    cmake_build_command = ["cmake", "--build", "."]
    print(f"[BUILD][INFO] Building project with: {' '.join(cmake_build_command)}")
    try:
        subprocess.check_call(cmake_build_command)
        print("[BUILD][INFO] Build completed successfully.")
    except subprocess.CalledProcessError:
        print("[BUILD][ERROR] Build failed.")
        sys.exit(1)


def clean_project(build_dir):
    if os.path.exists(build_dir):
        print(f"[CLEAN][INFO] Removing build directory {build_dir}...")
        shutil.rmtree(build_dir)
        print("[CLEAN][INFO] Build directory removed.")
    else:
        print("[CLEAN][INFO] Build directory does not exist; nothing to clean.")


def run_binary(binary_path):
    if not os.path.exists(binary_path):
        print(f"[RUN][ERROR] Binary not found at {binary_path}. Please build first.")
        sys.exit(1)

    print(f"[RUN][INFO] Running {binary_path}...")
    try:
        subprocess.check_call([binary_path])
    except subprocess.CalledProcessError:
        print("[RUN][ERROR] Execution failed.")
        sys.exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Build script for VEng.")
    parser.add_argument("--build", choices=["Debug", "Release"], default="Debug", help="Build type")
    parser.add_argument("--run", action="store_true", help="Run the binary after building")
    parser.add_argument("--clean", action="store_true", help="Remove build directory before building")
    parser.add_argument("--generate", choices=list(GENERATOR_MAP.keys()), help="CMake generator (currently only vs2022)")

    args = parser.parse_args()

    build_dir = DEFAULT_BUILD_DIR
    binary_path = DEFAULT_BINARY

    if args.clean:
        clean_project(build_dir)

    configure_project(build_dir, args.build, args.generate)
    build_project(build_dir)

    if args.run:
        run_binary(binary_path)
