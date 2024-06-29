import platform
import os
import shutil

from helper import activate_venv
from helper import deactivate_venv
from helper import parse_args
from helper import run


def configure_project(clean=False, config="Release", generator="Ninja Multi-Config"):
    if clean:
        if os.path.exists("build"):
            print(f"configure.py: Removing folder: {os.path.abspath('CMakeUserPresets.json')}")
            print(f"configure.py: Removing folder: {os.path.abspath('build')}")
            os.remove(os.path.join("CMakeUserPresets.json"))
            shutil.rmtree("build")

    run(f'conan install . -b missing -s build_type={config} -c tools.build:skip_test=False -c tools.cmake.cmaketoolchain:generator="{generator}"')
    activate_venv()

    conan_preset = "conan-default"

    run(f"cmake --preset {conan_preset} --fresh")

    deactivate_venv()

if __name__ == "__main__":
    args = parse_args()

    configure_project(
        clean=args.clean,
        config=args.config,
        generator=args.cmake_generator
    )
