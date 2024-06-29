import os

from configure import configure_project
from helper import activate_venv
from helper import deactivate_venv
from helper import parse_args
from helper import run
from helper import list_build_presets


def build_project(clean=False, config="Release", generator="Ninja Multi-Config"):
    build_presets = list_build_presets()
    conan_preset = f"conan-{config.lower()}"
    if (not os.path.exists("build")) or clean or (conan_preset not in build_presets):
        configure_project(clean=clean, config=config, generator=generator)

    activate_venv()

    run(f"cmake --build --preset conan-{config.lower()}")

    deactivate_venv()

if __name__ == "__main__":
    args = parse_args()

    build_project(
        clean=args.clean,
        config=args.config,
        generator=args.cmake_generator
    )
